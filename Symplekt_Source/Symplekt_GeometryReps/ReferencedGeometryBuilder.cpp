/*! \file  ReferencedGeometryBuilder.cpp
 *  \brief Implementation of an object for constructing ReferencedMeshGeometryData from vertex data and vertex index data.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   9.9.2021
 *
 */

#include "ReferencedGeometryBuilder.h"

#include "Symplekt_UtilityGeneral/Assert.h"
#include "Symplekt_GeometryBase/Edge.h"
#include "Symplekt_GeometryBase/Face.h"
#include "Symplekt_GeometryBase/FaceUtils.h"
#include "Symplekt_GeometryBase/HalfEdge.h"
#include "Symplekt_GeometryBase/Vertex.h"
#include "Symplekt_GeometryBase/VertexUtils.h"

#include <string>
#include <set>

namespace Symplektis::GeometryReps
{
	ReferencedMeshGeometryBuilder::ReferencedMeshGeometryBuilder(BasePolygonalGeometryData& inputData)
	{
        m_BaseData = std::make_unique<BasePolygonalGeometryData>(inputData);
        m_ResultData = std::make_unique<ReferencedMeshGeometryData>(inputData.Name);
	}
	
	using namespace GeometryBase;
	
	//-----------------------------------------------------------------------------
	/*! \brief Check for isolated vertices given a half-edge container
	*   \param[in] vert      vertex to be checked
	*   \return true if this vertex's half-edge is null.
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   16.9.2021
	*/
	//-----------------------------------------------------------------------------
	[[nodiscard]] static bool IsIsolated(const Vertex& vert)
	{
		return vert.HalfEdge() == NULL_HALF_EDGE;
	}

	void ReferencedMeshGeometryBuilder::PreallocateMeshGeometryContainers()
	{
		if (m_BaseData->Vertices.empty() || m_BaseData->PolyVertexIndices.empty())
			return; // null geometry (just indices or just a point cloud)
		
		auto& dataVertices = m_BaseData->Vertices;
		auto& dataVertexIndices = m_BaseData->PolyVertexIndices;
		auto& dataVertexNormals = m_BaseData->VertexNormals;

		m_HasNormals = !dataVertexNormals.empty();

		MSG_CHECK(!m_HasNormals || dataVertexNormals.size() == dataVertices.size(),
			"ReferencedMeshGeometryBuilder::PreallocateMeshGeometryContainers: dataVertexNormals.size() != dataVertices.size() for non-empty dataVertexNormals buffer!\n");
		
		// count edges
		std::set<std::pair<unsigned int, unsigned int>> edgeIdsSet;
		for (const auto& indexTuple : dataVertexIndices)
		{
			for (unsigned int i = 0; i < indexTuple.size(); i++)
			{
				unsigned int vertId0 = indexTuple[i];
				unsigned int vertId1 = indexTuple[(static_cast<size_t>(i) + 1) % indexTuple.size()];

				if (vertId0 > vertId1) std::swap(vertId0, vertId1);

				edgeIdsSet.insert({ vertId0, vertId1 });
			}
		}

		const size_t nVertices = dataVertices.size();
		const size_t nVertexNormals = dataVertexNormals.size();
		const size_t nEdges = edgeIdsSet.size();
		const size_t nFaces = dataVertexIndices.size();
		const size_t nHalfEdges = 2 * nEdges;
		const int EulerCharacteristic = static_cast<int>(nVertices - nEdges + nFaces);
		const size_t nBoundaryCycles = std::max<int>(0, 2 - EulerCharacteristic);

		m_ResultData->HalfEdges.clear();
		m_ResultData->Vertices.clear();
		m_ResultData->Edges.clear();
		m_ResultData->Faces.clear();
		m_ResultData->BoundaryCycles.clear();
		m_ResultData->VertexNormals.clear();

		m_ResultData->HalfEdges.reserve(nHalfEdges);
		m_ResultData->Vertices.reserve(nVertices);
		m_ResultData->Edges.reserve(nEdges);
		m_ResultData->Faces.reserve(nFaces);
		m_ResultData->BoundaryCycles.reserve(nBoundaryCycles);
		m_ResultData->VertexNormals.reserve(nVertexNormals);
	}

	void ReferencedMeshGeometryBuilder::FillVertexBufferAndIndexMap(std::map<unsigned int, VertexHandle>& vertIndexToVertexHandle) const
	{
		auto& dataVertices = m_BaseData->Vertices;
		auto& dataVertexNormals = m_BaseData->VertexNormals;
		
		for (unsigned int vertId = 0; const auto & vertex : dataVertices)
		{
			auto newVertexIter = m_ResultData->Vertices.insert(m_ResultData->Vertices.end(), Vertex(vertex));
			newVertexIter->SetHalfEdge(NULL_HALF_EDGE);
			newVertexIter->SetIndex(vertId);
			vertIndexToVertexHandle[vertId] = newVertexIter;

			if (m_HasNormals) // fill in vertex normals
			{
				const auto& vertNormalVec = dataVertexNormals[vertId];
				auto newVertexNormalIter = m_ResultData->VertexNormals.insert(m_ResultData->VertexNormals.end(), VertexNormal(vertNormalVec, newVertexIter));
				newVertexIter->SetNormal(newVertexNormalIter);				
			}
			vertId++;
		}
	}

	bool ReferencedMeshGeometryBuilder::FillHalfEdgesAndFaces(
		std::map<unsigned int, VertexHandle>&     vertIndexToVertexIter,
		std::map<HalfEdgeHandle, bool>&           halfEdgeHasOpposite) const
	{
		auto& dataVertexIndices = m_BaseData->PolyVertexIndices;
		
		bool degenerateFacesEncountered = false;
		std::map<std::pair<unsigned int, unsigned int>, HalfEdgeHandle> edgeVertIdsToExistingHalfEdges;
		std::map<std::pair<unsigned int, unsigned int>, unsigned int> edgeVertIdsToEdgeCount;

		for (unsigned int faceIndex = 0, edgeIndex = 0; const auto & indexTuple : dataVertexIndices)
		{
			if (indexTuple.size() < 3)
			{
				std::string message = "Face " + std::to_string(faceIndex) + " is degenerate (with less than three vertices). Skipping!\n";
				degenerateFacesEncountered = true;
				MSG_CHECK(false, message);
				continue;
			}

			const size_t nIndicesInTuple = indexTuple.size();

			std::vector<VertexHandle> polyVertIters;
			polyVertIters.reserve(nIndicesInTuple);
			for (const auto& vId : indexTuple) polyVertIters.emplace_back(vertIndexToVertexIter[vId]);

			const Face newFace{ polyVertIters };
			auto newFaceIter = m_ResultData->Faces.insert(m_ResultData->Faces.end(), newFace);
			newFaceIter->SetIndex(faceIndex);

			std::vector<HalfEdgeHandle> halfEdges(nIndicesInTuple);
			for (auto& he : halfEdges) he = m_ResultData->HalfEdges.insert(m_ResultData->HalfEdges.end(), HalfEdge());

			// initialize new half-edges
			for (unsigned int i = 0; i < nIndicesInTuple; i++)
			{
				const unsigned int nextPolyIndex = (i + static_cast<size_t>(1)) % nIndicesInTuple;

				// half-edge endpoint indices in index tuple
				unsigned int firstEdgeVertId = indexTuple[i];
				unsigned int secondEdgeVertId = indexTuple[nextPolyIndex];

				HalfEdgeReferenceData heData;
				heData.NextHalfEdge = halfEdges[nextPolyIndex];
				heData.TailVertex = vertIndexToVertexIter[firstEdgeVertId];

				const bool isBoundary = false;
				*halfEdges[i] = HalfEdge(heData, isBoundary);

				// keep track of which half-edges have flip edges defined (for detecting boundaries)
				halfEdgeHasOpposite[halfEdges[i]] = false;

				// point vertex a at the current half-edge
				vertIndexToVertexIter[firstEdgeVertId]->HalfEdge() = halfEdges[i];

				// point the new face and this half edge to each-other
				halfEdges[i]->SetAdjacentFace(newFaceIter);
				newFaceIter->SetHalfEdge(halfEdges[i]);

				if (firstEdgeVertId > secondEdgeVertId) std::swap(firstEdgeVertId, secondEdgeVertId);

				// if we've created an edge between firstEdgeVert and secondEdgeVert in the past, it is the
				// opposite edge of the current half-edge
				if (edgeVertIdsToExistingHalfEdges.find({ firstEdgeVertId, secondEdgeVertId }) != edgeVertIdsToExistingHalfEdges.cend())
				{
					halfEdges[i]->OppositeHalfEdge() = edgeVertIdsToExistingHalfEdges[{ firstEdgeVertId, secondEdgeVertId }];
					halfEdges[i]->OppositeHalfEdge()->OppositeHalfEdge() = halfEdges[i];
					halfEdges[i]->Edge() = halfEdges[i]->OppositeHalfEdge()->Edge();
					halfEdgeHasOpposite[halfEdges[i]] = true;
					halfEdgeHasOpposite[halfEdges[i]->OppositeHalfEdge()] = true;
				}
				// otherwise, construct an edge connected to the current half-edge
				else
				{
					halfEdges[i]->Edge() = m_ResultData->Edges.insert(m_ResultData->Edges.end(), Edge());
					halfEdges[i]->Edge()->SetIndex(edgeIndex);
					halfEdges[i]->Edge()->HalfEdge() = halfEdges[i];
					edgeVertIdsToEdgeCount[{firstEdgeVertId, secondEdgeVertId}] = 0;
					edgeIndex++;
				}

				// store the information about half-edge having been created from vertex[firstEdgeVertId] to vertex[secondEdgeVertId]
				edgeVertIdsToExistingHalfEdges[{firstEdgeVertId, secondEdgeVertId}] = halfEdges[i];

				// non-manifold edges check
				edgeVertIdsToEdgeCount[{firstEdgeVertId, secondEdgeVertId}]++;
				if (edgeVertIdsToEdgeCount[{firstEdgeVertId, secondEdgeVertId}] > 2)
				{
					const std::string message = "Encountered non-manifold edges at Face " + std::to_string(faceIndex) + ". i.e.: more than two faces sharing and edge. Aborting!\n";
					MSG_CHECK(false, message);
					return true;
				}
			}

			faceIndex++;
		}

		return degenerateFacesEncountered;
	}

	void ReferencedMeshGeometryBuilder::FillBoundaryCycles(std::map<HalfEdgeHandle, bool>& halfEdgeHasOpposite) const
	{
		// extra Faces need to be added for each boundary cycle
		for (auto halfEdgeIt = m_ResultData->HalfEdges.begin(); halfEdgeIt != m_ResultData->HalfEdges.end(); ++halfEdgeIt)
		{
			// If a half-edge without an opposite half-edge is found, a new face is to be created
			// corresponding to a boundary cycle.

			if (!halfEdgeHasOpposite[halfEdgeIt])
			{
				// create a new face
				auto newBoundaryCycle = m_ResultData->BoundaryCycles.insert(m_ResultData->BoundaryCycles.end(), Face());

				// iterate along this boundary cycle
				std::vector<HalfEdgeHandle> boundaryCycleHalfEdges;
				auto heIt = halfEdgeIt;
				do
				{
					// create a new half-edge on the boundary face
					auto newHEIt = m_ResultData->HalfEdges.insert(m_ResultData->HalfEdges.end(), HalfEdge());

					// mark only the half-edge on the boundary face as being on the boundary
					newHEIt->SetIsBoundary(true);

					// link the current half-edge in the cycle to its new flip edge
					heIt->OppositeHalfEdge() = newHEIt;

					// grab the next half-edge along the boundary by finding
					// the next half-edge around the current vertex that doesn't
					// have a flip edge defined
					auto nextHEIt = heIt->NextHalfEdge();
					while (halfEdgeHasOpposite[nextHEIt])
					{
						nextHEIt = nextHEIt->OppositeHalfEdge()->NextHalfEdge();
					}

					// set attributes for the flip edge (we'll set ->next below)
					newHEIt->OppositeHalfEdge() = heIt;
					newHEIt->TailVertex() = nextHEIt->TailVertex();
					newHEIt->TailVertex()->SetIsBoundary(true);
					newHEIt->Edge() = heIt->Edge();
					newHEIt->AdjacentFace() = newBoundaryCycle;

					// point the new face to this half-edge
					newBoundaryCycle->HalfEdge() = newHEIt;

					// keep track of all the new half-edges in the boundary cycle
					boundaryCycleHalfEdges.push_back(newHEIt);

					// continue to walk along the cycle
					heIt = nextHEIt;
				} while (heIt != halfEdgeIt);

				// link together the cycle of boundary half-edges
				const auto nBDCycleHECount = boundaryCycleHalfEdges.size();
				for (unsigned int i = 0; i < nBDCycleHECount; i++)
				{
					boundaryCycleHalfEdges[i]->NextHalfEdge() = boundaryCycleHalfEdges[(i + nBDCycleHECount - 1) % nBDCycleHECount];
					halfEdgeHasOpposite[boundaryCycleHalfEdges[i]] = true;
					halfEdgeHasOpposite[boundaryCycleHalfEdges[i]->OppositeHalfEdge()] = true;
				}
			}
		}
	}

	void ReferencedMeshGeometryBuilder::PerformIsolatedVertexCheck() const
	{
		
		for (unsigned int vertexId = 0; const auto& vert : m_ResultData->Vertices)
		{
			if (IsIsolated(vert, m_ResultData->HalfEdges))
			{
				auto warningMsg = std::string("Warning: Vertex ") + std::to_string(vertexId) + " is isolated (not contained in any face).\n";
				MSG_CHECK(false, warningMsg);
			}
			vertexId++;
		}
	}


    void ReferencedMeshGeometryBuilder::PerformNonManifoldVertexCheck() const
    {
		std::map<VertexConstIterator, unsigned int> valencePerVisitedVertex;

		// count along the list of faces
		for (auto& face : m_ResultData->Faces)
		{
			HalfEdgeConstIterator heConstIt = face.HalfEdge();
			do
			{   // iterate along face half-edge tail vertices
				valencePerVisitedVertex[heConstIt->TailVertex()]++;
				heConstIt = heConstIt->NextHalfEdge();
			}
			while (heConstIt != face.HalfEdge());
		}

		// count along the list of boundary cycles
        for (auto& bdCycle : m_ResultData->BoundaryCycles)
        {
            HalfEdgeConstIterator heConstIt = bdCycle.HalfEdge();
            do
            {   // iterate along boundary cycle half-edge tail vertices
                valencePerVisitedVertex[heConstIt->TailVertex()]++;
                heConstIt = heConstIt->NextHalfEdge();
            }
			while (heConstIt != bdCycle.HalfEdge());
        }

		// throw warnings when encountering a valence discrepancy in a vertex
        unsigned int vertexId = 0;
        for (auto vIter = m_ResultData->Vertices.begin(); vIter != m_ResultData->Vertices.end(); ++vIter)
        {			
            if (const unsigned int computedValence = GetValence(*vIter); valencePerVisitedVertex[vIter] != computedValence)
            {
                auto warningMsg = std::string("Warning: Vertex ") + std::to_string(vertexId) + " is non-manifold\n" +
					              " with valencePerVisitedVertex : " + std::to_string(valencePerVisitedVertex[vIter]) +
					              ", and computed valence: " + std::to_string(computedValence);
                MSG_CHECK(false, warningMsg);
            }
            vertexId++;
        }
    }


	void ReferencedMeshGeometryBuilder::BuildGeometry()
	{
		// preallocate buffers:
		// =======================================================================
		//
		
		PreallocateMeshGeometryContainers();

		// fill the vertex buffer, and a vertexId -> Vertex map per each Vertex
		// =======================================================================
		//

		std::map<unsigned int, VertexHandle> vertIndexToVertexIter;
		FillVertexBufferAndIndexMap(vertIndexToVertexIter);

		// fill the half-edges and faces buffers using the above helper containers
		// =======================================================================
		//
		
		// helper containers for half-edge construction
		std::map<HalfEdgeHandle, bool> halfEdgeHasOpposite;
		const bool degenerateFacesEncountered = FillHalfEdgesAndFaces(vertIndexToVertexIter, halfEdgeHasOpposite);

		// it's unsafe to continue to boundary cycle construction if degenerate faces were encountered
		if (degenerateFacesEncountered)
			return;

		// fill the boundary cycles container
		// =======================================================================
		//

		FillBoundaryCycles(halfEdgeHasOpposite);

		// perform additional tests & trigger asserts if necessary
		// =======================================================================
		//
		
		PerformIsolatedVertexCheck();
		PerformNonManifoldVertexCheck();

		// done
	}

} // Symplektis::GeometryReps