/*! \file  ReferencedGeometryBuilder.cpp
 *  \brief Implementation of an object for constructing ReferencedMeshGeometryData from vertex data and vertex index data.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   9.9.2021
 *
 */

#include "ReferencedGeometryBuilder.h"

#include "Symplekt_UtilityGeneral/Assert.h"
#include "Symplekt_GeometryKernel/Edge.h"
#include "Symplekt_GeometryKernel/Face.h"
#include "Symplekt_GeometryKernel/FaceUtils.h"
#include "Symplekt_GeometryKernel/HalfEdge.h"
#include "Symplekt_GeometryKernel/Vertex.h"
#include "Symplekt_GeometryKernel/VertexUtils.h"

#include <string>
#include <set>

namespace Symplektis::GeometryKernel
{
	ReferencedMeshGeometryBuilder::ReferencedMeshGeometryBuilder(BasePolygonalGeometryData& inputData)
	{
		m_BaseData = std::make_unique<BasePolygonalGeometryData>(inputData);
		m_ResultData = std::make_unique<ReferencedMeshGeometryData>(inputData.Name);
	}

	//-----------------------------------------------------------------------------
	/*! \brief Check for isolated vertices given a half-edge container
	*   \param[in] vert      vertex to be checked
	*   \return true if this vertex's half-edge index is NULL_HALF_EDGE
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

	void ReferencedMeshGeometryBuilder::FillVertexBufferAndIndexMap(std::map<unsigned int, VertexIterator>& vertIndexToVertexIter) const
	{
		const auto& dataVertices = m_BaseData->Vertices;
		const auto& dataVertexNormals = m_BaseData->VertexNormals;

		for (const auto & vertex : dataVertices)
		{
			auto newVertexIter = m_ResultData->Vertices.insert(m_ResultData->Vertices.end(), Vertex(vertex));
			//ASSERT(newVertexIter != m_ResultData->Vertices.end(), "ReferencedMeshGeometryBuilder::FillVertexBufferAndIndexMap: Vertex insertion failed! newVertexIter == m_ResultData->Vertices.end()");
			newVertexIter->SetHalfEdge(NULL_HALF_EDGE);
			const auto vertId = VertexIndex(static_cast<unsigned int>(newVertexIter - m_ResultData->Vertices.cbegin()));
			newVertexIter->SetIndex(vertId.get());
			vertIndexToVertexIter[vertId.get()] = newVertexIter;

			if (m_HasNormals) // fill in vertex normals
			{
				const auto& vertNormalVec = dataVertexNormals[vertId.get()];
				auto newVertexNormalIter = m_ResultData->VertexNormals.insert(m_ResultData->VertexNormals.end(), VertexNormal(vertNormalVec, vertId));
				//ASSERT(newVertexNormalIter != m_ResultData->VertexNormals.end(), "ReferencedMeshGeometryBuilder::FillVertexBufferAndIndexMap: VertexNormal insertion failed! newVertexNormalIter == m_ResultData->VertexNormals.end()");
				const auto vertNormalId = VertexNormalIndex(static_cast<unsigned int>(newVertexNormalIter - m_ResultData->VertexNormals.cbegin()));
				newVertexIter->SetNormal(vertNormalId);
			}
		}
	}

	bool ReferencedMeshGeometryBuilder::FillHalfEdgesAndFaces(
		std::map<unsigned int, VertexIterator>& vertIndexToVertexIter,
		std::map<HalfEdgeIterator, bool>& halfEdgeHasOpposite) const
	{
		const auto& dataVertexIndices = m_BaseData->PolyVertexIndices;

		bool degenerateFacesEncountered = false;
		std::map<std::pair<unsigned int, unsigned int>, HalfEdgeIterator> edgeVertIdsToExistingHalfEdges;
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

			std::vector<VertexIndex> polyVertIds;
			polyVertIds.reserve(nIndicesInTuple);
			for (const auto& vId : indexTuple) polyVertIds.emplace_back(VertexIndex(vId));

			const Face newFace{ polyVertIds, m_ResultData->Vertices };
			auto newFaceIter = m_ResultData->Faces.insert(m_ResultData->Faces.end(), newFace);
			newFaceIter->SetIndex(faceIndex);

			std::vector<HalfEdgeIterator> halfEdges(nIndicesInTuple);
			for (auto& he : halfEdges) he = m_ResultData->HalfEdges.insert(m_ResultData->HalfEdges.end(), HalfEdge());

			// initialize new half-edges
			for (unsigned int i = 0; i < nIndicesInTuple; i++)
			{
				const unsigned int nextPolyIndex = (i + static_cast<size_t>(1)) % nIndicesInTuple;

				// half-edge endpoint indices in index tuple
				unsigned int firstEdgeVertId = indexTuple[i];
				unsigned int secondEdgeVertId = indexTuple[nextPolyIndex];

				HalfEdgeReferenceData heData;
				heData.NextHalfEdge = HalfEdgeIndex(static_cast<unsigned int>(halfEdges[nextPolyIndex] - m_ResultData->HalfEdges.begin()));
				heData.TailVertex = VertexIndex(static_cast<unsigned int>(vertIndexToVertexIter[firstEdgeVertId] - m_ResultData->Vertices.begin()));

				constexpr bool isBoundary = false;
				*halfEdges[i] = HalfEdge(heData, isBoundary);

				// keep track of which half-edges have flip edges defined (for detecting boundaries)
				halfEdgeHasOpposite[halfEdges[i]] = false;

				// point vertex a at the current half-edge
				vertIndexToVertexIter[firstEdgeVertId]->HalfEdge() = HalfEdgeIndex(static_cast<unsigned int>(halfEdges[i] - m_ResultData->HalfEdges.begin()));

				// point the new face and this half edge to each-other
				halfEdges[i]->SetAdjacentFace(HalfEdgeIndex(static_cast<unsigned int>(newFaceIter - m_ResultData->Faces.begin())));
				newFaceIter->SetHalfEdge(HalfEdgeIndex(static_cast<unsigned int>(halfEdges[i] - m_ResultData->HalfEdges.begin())));

				if (firstEdgeVertId > secondEdgeVertId) std::swap(firstEdgeVertId, secondEdgeVertId);

				// if we've created an edge between firstEdgeVert and secondEdgeVert in the past, it is the
				// opposite edge of the current half-edge
				if (edgeVertIdsToExistingHalfEdges.contains({ firstEdgeVertId, secondEdgeVertId }))
				{
					halfEdges[i]->OppositeHalfEdge() = HalfEdgeIndex(static_cast<unsigned int>(edgeVertIdsToExistingHalfEdges[{ firstEdgeVertId, secondEdgeVertId }] - m_ResultData->HalfEdges.begin()));
					m_ResultData->HalfEdges[halfEdges[i]->OppositeHalfEdge().get()].OppositeHalfEdge() = HalfEdgeIndex(static_cast<unsigned int>(halfEdges[i] - m_ResultData->HalfEdges.begin()));
					halfEdges[i]->Edge() = m_ResultData->HalfEdges[halfEdges[i]->OppositeHalfEdge().get()].Edge();
					halfEdgeHasOpposite[halfEdges[i]] = true;
					halfEdgeHasOpposite[m_ResultData->HalfEdges.begin() + halfEdges[i]->OppositeHalfEdge().get()] = true;
				}
				// otherwise, construct an edge connected to the current half-edge
				else
				{
					auto newEdgeIter = m_ResultData->Edges.insert(m_ResultData->Edges.end(), Edge());
					halfEdges[i]->Edge() = EdgeIndex(static_cast<unsigned int>(newEdgeIter - m_ResultData->Edges.begin()));
					m_ResultData->Edges[halfEdges[i]->Edge().get()].SetIndex(edgeIndex);
					m_ResultData->Edges[halfEdges[i]->Edge().get()].HalfEdge() = HalfEdgeIndex(static_cast<unsigned int>(halfEdges[i] - m_ResultData->HalfEdges.begin()));
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

	void ReferencedMeshGeometryBuilder::FillBoundaryCycles(std::map<HalfEdgeIterator, bool>& halfEdgeHasOpposite) const
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
				std::vector<HalfEdgeIterator> boundaryCycleHalfEdges;
				auto heIt = halfEdgeIt;
				do
				{
					// create a new half-edge on the boundary face
					auto newHEIt = m_ResultData->HalfEdges.insert(m_ResultData->HalfEdges.end(), HalfEdge());

					// mark only the half-edge on the boundary face as being on the boundary
					newHEIt->SetIsBoundary(true);

					// link the current half-edge in the cycle to its new flip edge
					heIt->OppositeHalfEdge() = HalfEdgeIndex(static_cast<unsigned int>(newHEIt - m_ResultData->HalfEdges.begin()));

					// grab the next half-edge along the boundary by finding
					// the next half-edge around the current vertex that doesn't
					// have a flip edge defined
					auto nextHEId = heIt->NextHalfEdge();
					while (halfEdgeHasOpposite[m_ResultData->HalfEdges.begin() + nextHEId.get()])
					{
						nextHEId = m_ResultData->HalfEdges[m_ResultData->HalfEdges[nextHEId.get()].OppositeHalfEdge().get()].NextHalfEdge();
					}

					// set attributes for the flip edge (we'll set ->next below)
					newHEIt->OppositeHalfEdge() = HalfEdgeIndex(static_cast<unsigned int>(heIt - m_ResultData->HalfEdges.begin()));
					newHEIt->TailVertex() = m_ResultData->HalfEdges[nextHEId.get()].TailVertex();
					m_ResultData->HalfEdges[newHEIt->TailVertex().get()].SetIsBoundary(true);
					newHEIt->Edge() = heIt->Edge();
					newHEIt->AdjacentFace() = FaceIndex(static_cast<unsigned int>(newBoundaryCycle - m_ResultData->BoundaryCycles.begin()));

					// point the new face to this half-edge
					newBoundaryCycle->HalfEdge() = HalfEdgeIndex(static_cast<unsigned int>(newHEIt - m_ResultData->HalfEdges.begin()));

					// keep track of all the new half-edges in the boundary cycle
					boundaryCycleHalfEdges.push_back(newHEIt);

					// continue to walk along the cycle
					heIt = m_ResultData->HalfEdges.begin() + nextHEId.get();
				} while (heIt != halfEdgeIt);

				// link together the cycle of boundary half-edges
				const auto nBDCycleHECount = boundaryCycleHalfEdges.size();
				for (unsigned int i = 0; i < nBDCycleHECount; i++)
				{
					boundaryCycleHalfEdges[i]->NextHalfEdge() = HalfEdgeIndex(static_cast<unsigned int>(boundaryCycleHalfEdges[(i + nBDCycleHECount - 1) % nBDCycleHECount] - m_ResultData->HalfEdges.begin()));
					halfEdgeHasOpposite[boundaryCycleHalfEdges[i]] = true;
					halfEdgeHasOpposite[m_ResultData->HalfEdges.begin() + boundaryCycleHalfEdges[i]->OppositeHalfEdge().get()] = true;
				}
			}
		}
	}

	void ReferencedMeshGeometryBuilder::PerformIsolatedVertexCheck() const
	{

		for (unsigned int vertexId = 0; const auto & vert : m_ResultData->Vertices)
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
		std::map<VertexConstIterator, unsigned int> valencePerVisitedVertex;

		// count along the list of faces
		for (auto& face : m_ResultData->Faces)
		{
			auto heId = face.HalfEdge();
			do
			{   // iterate along face half-edge tail vertices
				valencePerVisitedVertex[m_ResultData->Vertices.begin() + m_ResultData->HalfEdges[heId.get()].TailVertex().get()]++;
				heId = m_ResultData->HalfEdges[heId.get()].NextHalfEdge();
			} while (heId != face.HalfEdge());
		}

		// count along the list of boundary cycles
		for (auto& bdCycle : m_ResultData->BoundaryCycles)
		{
			auto heId = bdCycle.HalfEdge();
			do
			{   // iterate along boundary cycle half-edge tail vertices
				valencePerVisitedVertex[m_ResultData->Vertices.begin() + m_ResultData->HalfEdges[heId.get()].TailVertex().get()]++;
				heId = m_ResultData->HalfEdges[heId.get()].NextHalfEdge();
			} while (heId != bdCycle.HalfEdge());
		}

		// throw warnings when encountering a valence discrepancy in a vertex
		unsigned int vertexId = 0;
		for (auto vIter = m_ResultData->Vertices.begin(); vIter != m_ResultData->Vertices.end(); ++vIter)
		{
			if (const unsigned int computedValence = GetValence(*vIter, *m_ResultData); valencePerVisitedVertex[vIter] != computedValence)
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

		std::map<unsigned int, VertexIterator> vertIndexToVertexIter;
		FillVertexBufferAndIndexMap(vertIndexToVertexIter);

		// fill the half-edges and faces buffers using the above helper containers
		// =======================================================================
		//

		// helper containers for half-edge construction
		std::map<HalfEdgeIterator, bool> halfEdgeHasOpposite;
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

} // Symplektis::GeometryKernel