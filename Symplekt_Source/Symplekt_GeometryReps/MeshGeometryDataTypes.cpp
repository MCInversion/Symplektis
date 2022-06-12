/*! \file  MeshGeometryDataTypes.cpp
 *  \brief Implementations of data container types (mostly structs) for mesh geometry data.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   7.10.2021
 *
 */

#include "MeshGeometryDataTypes.h"

#include "Symplekt_UtilityGeneral/Assert.h"

#include <algorithm>

namespace Symplektis::GeometryReps
{
	using namespace GeometryBase;
	
	void ReferencedMeshGeometryData::TrivialCopySet(const ReferencedMeshGeometryData& otherData) noexcept
	{
		try
		{
			Name = otherData.Name;
			HalfEdges = otherData.HalfEdges;
			Vertices = otherData.Vertices;
			Edges = otherData.Edges;
			Faces = otherData.Faces;
			BoundaryCycles = otherData.BoundaryCycles;
			VertexNormals = otherData.VertexNormals;
		}
		catch(...)
		{
			// this shouldn't throw exceptions
		}
	}

	void ReferencedMeshGeometryData::SetHalfEdgesBuffer(const ReferencedMeshGeometryData& otherData)
	{
		unsigned int halfEdgeIndex = 0;
		for (auto heIt = otherData.HalfEdges.begin(); heIt != otherData.HalfEdges.end(); ++heIt)
		{
			HalfEdgeReferenceData newRefData;

			const size_t nextHeBufferPosition = heIt->NextHalfEdge() - otherData.HalfEdges.begin();
			const size_t oppositeHeBufferPosition = heIt->OppositeHalfEdge() - otherData.HalfEdges.begin();
			const size_t tailVertexBufferPosition = heIt->TailVertex() - otherData.Vertices.begin();
			const size_t edgeBufferPosition = heIt->Edge() - otherData.Edges.begin();

			if (std::ranges::find(otherData.Faces, *heIt->AdjacentFace()) != otherData.Faces.cend())
			{
				// Adjacent face is in the Faces buffer
				const size_t faceBufferPosition = heIt->AdjacentFace() - otherData.Faces.begin();
				newRefData.AdjacentFace = Faces.begin() + faceBufferPosition;
			}
			else if (std::ranges::find(otherData.BoundaryCycles, *heIt->AdjacentFace()) != otherData.BoundaryCycles.cend())
			{
				// Adjacent face is in the BoundaryCycles buffer
				const size_t bdCyclesBufferPosition = heIt->AdjacentFace() - otherData.BoundaryCycles.begin();
				newRefData.AdjacentFace = BoundaryCycles.begin() + bdCyclesBufferPosition;
			}
			else
			{
				// This shouldn't happen
				throw std::runtime_error("ReferencedMeshGeometryData::SetHalfEdgesBuffer: adjacent face not found in any buffer!\n");
			}

			newRefData.NextHalfEdge = HalfEdges.begin() + nextHeBufferPosition;
			newRefData.OppositeHalfEdge = HalfEdges.begin() + oppositeHeBufferPosition;
			newRefData.TailVertex = Vertices.begin() + tailVertexBufferPosition;
			newRefData.Edge = Edges.begin() + edgeBufferPosition;  

			HalfEdges[halfEdgeIndex] = HalfEdge(newRefData, heIt->IsBoundary());
			halfEdgeIndex++;
		}
	}

	void ReferencedMeshGeometryData::SetVerticesBuffer(const ReferencedMeshGeometryData& otherData)
	{
		unsigned int vertIndex = 0;
		for (auto vIt = otherData.Vertices.cbegin(); vIt != otherData.Vertices.cend(); ++vIt)
		{			
			const size_t halfEdgeBufferPosition = vIt->HalfEdge() - otherData.HalfEdges.begin();
			const auto newHeIter = HalfEdges.begin() + halfEdgeBufferPosition;

			Vertices[vertIndex] = Vertex(newHeIter, vIt->Position(), vIt->Index());
			Vertices[vertIndex].SetIsBoundary(vIt->IsBoundary());
			vertIndex++;
		}
	}

	void ReferencedMeshGeometryData::SetEdgesBuffer(const ReferencedMeshGeometryData& otherData)
	{
		unsigned int edgeIndex = 0;
		for (auto edgeIt = otherData.Edges.cbegin(); edgeIt != otherData.Edges.cend(); ++edgeIt)
		{
			const size_t halfEdgeBufferPosition = edgeIt->HalfEdge() - otherData.HalfEdges.begin();
			const auto newHeIter = HalfEdges.begin() + halfEdgeBufferPosition;

			Edges[edgeIndex] = Edge(newHeIter, edgeIt->Index());
			edgeIndex++;
		}
	}

	void ReferencedMeshGeometryData::SetFacesBuffer(const ReferencedMeshGeometryData& otherData)
	{
		unsigned int faceIndex = 0;
		for (auto faceIt = otherData.Faces.cbegin(); faceIt != otherData.Faces.cend(); ++faceIt)
		{
			const size_t halfEdgeBufferPosition = faceIt->HalfEdge() - otherData.HalfEdges.begin();
			const auto newHeIter = HalfEdges.begin() + halfEdgeBufferPosition;			

			// recompute face triangulation iterators
			Triangulation newTri;
			newTri.reserve(faceIt->GetTriangulation().size());
			for (auto triangulation = faceIt->GetTriangulation(); auto & tri : triangulation)
			{
				const size_t vertexBufferPosition0 = std::get<0>(tri) - otherData.Vertices.begin();
				const size_t vertexBufferPosition1 = std::get<1>(tri) - otherData.Vertices.begin();
				const size_t vertexBufferPosition2 = std::get<2>(tri) - otherData.Vertices.begin();

				auto newVertIter0 = Vertices.begin() + vertexBufferPosition0;
				auto newVertIter1 = Vertices.begin() + vertexBufferPosition1;
				auto newVertIter2 = Vertices.begin() + vertexBufferPosition2;

				newTri.emplace_back(std::tuple{ newVertIter0 , newVertIter1, newVertIter2 });
			}

			Faces[faceIndex] = Face(newTri, newHeIter, faceIt->Index());
			faceIndex++;
		}
	}

	void ReferencedMeshGeometryData::SetBoundaryCyclesBuffer(const ReferencedMeshGeometryData& otherData)
	{
		unsigned int bdCycleIndex = 0;
		for (auto faceIt = otherData.BoundaryCycles.cbegin(); faceIt != otherData.BoundaryCycles.cend(); ++faceIt)
		{
			const size_t halfEdgeBufferPosition = faceIt->HalfEdge() - otherData.HalfEdges.begin();
			const auto newHeIter = HalfEdges.begin() + halfEdgeBufferPosition;

			BoundaryCycles[bdCycleIndex] = Face(newHeIter, faceIt->Index());
			bdCycleIndex++;
		}
	}

	void ReferencedMeshGeometryData::SetVertexNormalsBuffer(const ReferencedMeshGeometryData& otherData)
	{
		unsigned int normalIndex = 0;
		for (auto normIt = otherData.VertexNormals.cbegin(); normIt != otherData.VertexNormals.cend(); ++normIt)
		{
			const size_t vertexBufferPosition = normIt->Vertex() - otherData.Vertices.begin();
			const auto newVertexIter = Vertices.begin() + vertexBufferPosition;

			VertexNormals[normalIndex] = VertexNormal(normIt->Get(), newVertexIter);
			normalIndex++;
		}
	}
	
	void ReferencedMeshGeometryData::SetDataSafely(const ReferencedMeshGeometryData& other)
	{
		TrivialCopySet(other);
		
		SetHalfEdgesBuffer(other);
		SetVerticesBuffer(other);
		SetEdgesBuffer(other);
		SetFacesBuffer(other);
		SetBoundaryCyclesBuffer(other);
		SetVertexNormalsBuffer(other);
	}
	
	size_t ReferencedMeshGeometryData::Size() const
	{
		return
			                  HalfEdges.size() * sizeof(GeometryBase::HalfEdge) +
			                     Vertices.size() * sizeof(GeometryBase::Vertex) + 
			                          Edges.size() * sizeof(GeometryBase::Edge) + 
			(Faces.size() + BoundaryCycles.size()) * sizeof(GeometryBase::Face) +
			VertexNormals.size() * sizeof(GeometryBase::VertexNormal);
	}

	ReferencedMeshGeometryData::ReferencedMeshGeometryData(const ReferencedMeshGeometryData& other)
	{
		try
		{
			SetDataSafely(other);
		}
		catch (...)
		{
			MSG_CHECK(false, "ReferencedMeshGeometryData::ReferencedMeshGeometryData copy constructor has thrown an exception!\n");
		}
	}
	
	ReferencedMeshGeometryData& ReferencedMeshGeometryData::operator=(const ReferencedMeshGeometryData& other)
	{
		if (this == &other)
			return *this;

		SetDataSafely(other);
		return *this;
	}

	size_t BasePolygonalGeometryData::Size() const
	{
		size_t polySize = 0;
		for (const auto& poly : PolyVertexIndices)
			polySize += poly.size();
		return Vertices.size() * sizeof(GeometryBase::Vector3) +
			          polySize * sizeof(unsigned int)          +
		  VertexNormals.size() * sizeof(GeometryBase::Vector3);
	}

	size_t BufferMeshGeometryData::Size() const
	{
		return            VertexCoords.size() * sizeof(double) + 
			        VertexNormalCoords.size() * sizeof(double) + 
			       VertexIndices.size() * sizeof(unsigned int) +
			TriangulationIndices.size() * sizeof(unsigned int);
	}

} // Symplektis::GeometryReps