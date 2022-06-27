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
		
		const auto& dataVertices = m_BaseData->Vertices;
		const auto& dataVertexIndices = m_BaseData->PolyVertexIndices;
		const auto& dataVertexNormals = m_BaseData->VertexNormals;

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
		const int eulerCharacteristic = static_cast<int>(nVertices - nEdges + nFaces);
		const size_t nBoundaryCycles = std::max<int>(0, 2 - eulerCharacteristic);

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
		const auto& dataVertices = m_BaseData->Vertices;
		const auto& dataVertexNormals = m_BaseData->VertexNormals;
		
		for (const auto & vertex : dataVertices)
		{
			const auto newVertexIter = m_ResultData->Vertices.insert(m_ResultData->Vertices.end(), Vertex(vertex));
			const auto newIndex = Util::ContainerIndex(m_ResultData->Vertices.size() - 1);
			newVertexIter->SetHalfEdge(NULL_HALF_EDGE);
			newVertexIter->SetIndex(newIndex.get());

			const auto newVertexHandle = VertexHandle(newIndex, &m_ResultData->Vertices);
			ASSERT(newVertexHandle.IsValid(), "ReferencedMeshGeometryBuilder::FillVertexBufferAndIndexMap: Pre-exception handle check: Invalid VertexHandle!\n");
			vertIndexToVertexHandle[newIndex.get()] = newVertexHandle;

			if (m_HasNormals) // fill in vertex normals
			{
				const auto& vertNormalVec = dataVertexNormals[newIndex.get()];
				const auto newVertexNormalIter = m_ResultData->VertexNormals.insert(m_ResultData->VertexNormals.end(), VertexNormal(vertNormalVec, newVertexHandle));
				const auto newVertexNormalHandle = VertexNormalHandle(newIndex, &m_ResultData->VertexNormals);
				ASSERT(newVertexNormalHandle.IsValid(), "ReferencedMeshGeometryBuilder::FillVertexBufferAndIndexMap: Pre-exception handle check: Invalid VertexNormalHandle!\n");
				newVertexIter->SetNormal(newVertexNormalHandle);
			}
		}
	}

	bool ReferencedMeshGeometryBuilder::FillHalfEdgesAndFaces(
		std::map<unsigned int, VertexHandle>&     vertIndexToVertexHandle,
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

			std::vector<VertexHandle> polyVertHandles;
			polyVertHandles.reserve(nIndicesInTuple);
			for (const auto& vId : indexTuple)
			{
				ASSERT(vertIndexToVertexHandle[vId].IsValid(), "ReferencedMeshGeometryBuilder::FillHalfEdgesAndFaces: Pre-exception handle check: Invalid VertexHandle!\n");
				polyVertHandles.emplace_back(vertIndexToVertexHandle[vId]);
			}

			const Face newFace{ polyVertHandles };
			const auto newFaceIter = m_ResultData->Faces.insert(m_ResultData->Faces.end(), newFace);
			newFaceIter->SetIndex(faceIndex);
			const auto newFaceIndex = Util::ContainerIndex(faceIndex);
			const auto newFaceHandle = FaceHandle(newFaceIndex, &m_ResultData->Faces);
			ASSERT(newFaceHandle.IsValid(), "ReferencedMeshGeometryBuilder::FillHalfEdgesAndFaces: Pre-exception handle check: Invalid FaceHandle!\n");

			std::vector<HalfEdgeHandle> halfEdges(nIndicesInTuple);
			for (auto& he : halfEdges)
			{
				m_ResultData->HalfEdges.emplace_back(HalfEdge());
				const auto newHEIndex = Util::ContainerIndex(m_ResultData->HalfEdges.size() - 1);
				he = HalfEdgeHandle(newHEIndex, &m_ResultData->HalfEdges);
				ASSERT(he.IsValid(), "ReferencedMeshGeometryBuilder::FillHalfEdgesAndFaces: Pre-exception handle check: Invalid HalfEdgeHandle!\n");
			}

			// initialize new half-edges
			for (unsigned int i = 0; i < nIndicesInTuple; i++)
			{
				const unsigned int nextPolyIndex = (i + static_cast<size_t>(1)) % nIndicesInTuple;

				// half-edge endpoint indices in index tuple
				unsigned int firstEdgeVertId = indexTuple[i];
				unsigned int secondEdgeVertId = indexTuple[nextPolyIndex];

				HalfEdgeReferenceData heData;
				heData.NextHalfEdge = halfEdges[nextPolyIndex]; // verified above
				heData.TailVertex = vertIndexToVertexHandle[firstEdgeVertId]; // verified above

				constexpr bool isBoundary = false;
				halfEdges[i].GetElement().Set(heData, isBoundary);

				// keep track of which half-edges have flip edges defined (for detecting boundaries)
				halfEdgeHasOpposite[halfEdges[i]] = false;

				// point vertex a at the current half-edge
				vertIndexToVertexHandle[firstEdgeVertId].GetElement().HalfEdge() = halfEdges[i];

				// point the new face and this half edge to each-other
				halfEdges[i].GetElement().SetAdjacentFace(newFaceHandle);
				newFaceIter->SetHalfEdge(halfEdges[i]);

				if (firstEdgeVertId > secondEdgeVertId) std::swap(firstEdgeVertId, secondEdgeVertId);

				// if we've created an edge between firstEdgeVert and secondEdgeVert in the past, it is the
				// opposite edge of the current half-edge
				if (edgeVertIdsToExistingHalfEdges.find({ firstEdgeVertId, secondEdgeVertId }) != edgeVertIdsToExistingHalfEdges.cend())
				{
					halfEdges[i].GetElement().OppositeHalfEdge() = edgeVertIdsToExistingHalfEdges[{ firstEdgeVertId, secondEdgeVertId }];
					halfEdges[i].GetElement().OppositeHalfEdge().GetElement().OppositeHalfEdge() = halfEdges[i];
					halfEdges[i].GetElement().Edge() = halfEdges[i].GetElement().OppositeHalfEdge().GetElement().Edge();
					halfEdgeHasOpposite[halfEdges[i]] = true;
					halfEdgeHasOpposite[halfEdges[i].GetElement().OppositeHalfEdge()] = true;
				}
				// otherwise, construct an edge connected to the current half-edge
				else
				{
					m_ResultData->Edges.emplace_back(Edge());
					const auto newEdgeIndex = Util::ContainerIndex(m_ResultData->Edges.size() - 1);
					const auto newEdgeHandle = EdgeHandle(newEdgeIndex, &m_ResultData->Edges);
					ASSERT(newEdgeHandle.IsValid(), "ReferencedMeshGeometryBuilder::FillHalfEdgesAndFaces: Pre-exception handle check: Invalid EdgeHandle!\n");
					halfEdges[i].GetElement().Edge() = newEdgeHandle;
					halfEdges[i].GetElement().Edge().GetElement().SetIndex(edgeIndex);
					halfEdges[i].GetElement().Edge().GetElement().HalfEdge() = halfEdges[i];
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
		auto halfEdgeHandle = HalfEdgeHandle(static_cast<Util::ContainerIndex>(0), &m_ResultData->HalfEdges);
		do
		{
			// If a half-edge without an opposite half-edge is found, a new face is to be created
			// corresponding to a boundary cycle.

			if (!halfEdgeHasOpposite[halfEdgeHandle])
			{
				// create a new face
				auto newBoundaryCycleIt = m_ResultData->BoundaryCycles.insert(m_ResultData->BoundaryCycles.end(), Face());
				const auto newBoundaryCycleId = Util::ContainerIndex(m_ResultData->BoundaryCycles.size() - 1);
				const auto newBoundaryCycleHandle = FaceHandle(newBoundaryCycleId, &m_ResultData->BoundaryCycles);
				ASSERT(newBoundaryCycleHandle.IsValid(), "ReferencedMeshGeometryBuilder::FillBoundaryCycles: Pre-exception handle check: Invalid FaceHandle!\n");

				// iterate along this boundary cycle
				std::vector<HalfEdgeHandle> boundaryCycleHalfEdges;
				auto heHandle = halfEdgeHandle;
				do
				{
					// create a new exterior half-edge on the boundary face
					const auto newExteriorHeIt = m_ResultData->HalfEdges.insert(m_ResultData->HalfEdges.end(), HalfEdge());
					const auto newExteriorHeId = Util::ContainerIndex(m_ResultData->HalfEdges.size() - 1);
					const auto newExteriorHeHandle = HalfEdgeHandle(newExteriorHeId, &m_ResultData->HalfEdges);
					ASSERT(newExteriorHeHandle.IsValid(), "ReferencedMeshGeometryBuilder::FillBoundaryCycles: Pre-exception handle check: Invalid HalfEdgeHandle!\n");

					// mark only the half-edge on the boundary face as being on the boundary
					newExteriorHeIt->SetIsBoundary(true);

					// link the current half-edge in the cycle to its new flip edge
					heHandle.GetElement().OppositeHalfEdge() = newExteriorHeHandle;

					// grab the next half-edge along the boundary by finding
					// the next half-edge around the current vertex that doesn't
					// have a flip edge defined
					auto nextHeHandle = heHandle.GetElement().NextHalfEdge();
					while (halfEdgeHasOpposite[nextHeHandle])
					{
						nextHeHandle = nextHeHandle.GetElement().OppositeHalfEdge().GetElement().NextHalfEdge();
					}

					// set attributes for the flip edge (we'll set ->next below)
					newExteriorHeIt->OppositeHalfEdge() = heHandle;
					newExteriorHeIt->TailVertex() = nextHeHandle.GetElement().TailVertex();
					newExteriorHeIt->TailVertex().GetElement().SetIsBoundary(true);
					newExteriorHeIt->Edge() = heHandle.GetElement().Edge();
					newExteriorHeIt->AdjacentFace() = newBoundaryCycleHandle;

					// point the new face to this half-edge
					newBoundaryCycleIt->HalfEdge() = newExteriorHeHandle;

					// keep track of all the new half-edges in the boundary cycle
					boundaryCycleHalfEdges.push_back(newExteriorHeHandle);

					// continue to walk along the cycle
					heHandle = nextHeHandle;
				} while (heHandle != halfEdgeHandle);

				// link together the cycle of boundary half-edges
				const auto nBDCycleHECount = boundaryCycleHalfEdges.size();
				for (unsigned int i = 0; i < nBDCycleHECount; i++)
				{
					boundaryCycleHalfEdges[i].GetElement().NextHalfEdge() = boundaryCycleHalfEdges[(i + nBDCycleHECount - 1) % nBDCycleHECount];
					halfEdgeHasOpposite[boundaryCycleHalfEdges[i]] = true;
					halfEdgeHasOpposite[boundaryCycleHalfEdges[i].GetElement().OppositeHalfEdge()] = true;
				}
			}
			++halfEdgeHandle.GetIndex();
		} while (halfEdgeHandle.IsValid());
	}

	void ReferencedMeshGeometryBuilder::PerformIsolatedVertexCheck() const
	{
		
		for (unsigned int vertexId = 0; const auto& vert : m_ResultData->Vertices)
		{
			if (IsIsolated(vert))
			{
				auto warningMsg = std::string("Warning: Vertex ") + std::to_string(vertexId) + " is isolated (not contained in any face).\n";
				MSG_CHECK(false, warningMsg);
			}
			vertexId++;
		}
	}


    void ReferencedMeshGeometryBuilder::PerformNonManifoldVertexCheck() const
    {
		std::map<VertexHandle, unsigned int> valencePerVisitedVertex;

		// count along the list of faces
		for (auto& face : m_ResultData->Faces)
		{
			HalfEdgeHandle heHandle = face.HalfEdge();
			do
			{   // iterate along face half-edge tail vertices
				ASSERT(heHandle.IsValid(), "ReferencedMeshGeometryBuilder::PerformNonManifoldVertexCheck: Pre-exception handle check: Invalid HalfEdgeHandle!\n");
				valencePerVisitedVertex[heHandle.GetElement().TailVertex()]++;
				heHandle = heHandle.GetElement().NextHalfEdge();
			}
			while (heHandle != face.HalfEdge());
		}

		// count along the list of boundary cycles
        for (auto& bdCycle : m_ResultData->BoundaryCycles)
        {
            HalfEdgeHandle heHandle = bdCycle.HalfEdge();
            do
            {   // iterate along boundary cycle half-edge tail vertices
				ASSERT(heHandle.IsValid(), "ReferencedMeshGeometryBuilder::PerformNonManifoldVertexCheck: Pre-exception handle check: Invalid HalfEdgeHandle!\n");
                valencePerVisitedVertex[heHandle.GetElement().TailVertex()]++;
				heHandle = heHandle.GetElement().NextHalfEdge();
            }
			while (heHandle != bdCycle.HalfEdge());
        }

		// throw warnings when encountering a valence discrepancy in a vertex
        unsigned int vertexId = 0;
        for (auto vIter = m_ResultData->Vertices.begin(); vIter != m_ResultData->Vertices.end(); ++vIter)
        {
			const auto vHandle = VertexHandle(static_cast<Util::ContainerIndex>(vertexId), &m_ResultData->Vertices);
			ASSERT(vHandle.IsValid(), "ReferencedMeshGeometryBuilder::PerformNonManifoldVertexCheck: Pre-exception handle check: Invalid VertexHandle!\n");
            if (const unsigned int computedValence = GetValence(*vIter); valencePerVisitedVertex[vHandle] != computedValence)
            {
                auto warningMsg = std::string("Warning: Vertex ") + std::to_string(vertexId) + " is non-manifold\n" +
					              " with valencePerVisitedVertex : " + std::to_string(valencePerVisitedVertex[vHandle]) +
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