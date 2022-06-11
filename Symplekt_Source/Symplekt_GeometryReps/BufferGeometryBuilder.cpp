/*! \file  BufferMeshGeometry.cpp
 *  \brief Implementation of an object for constructing the most condensed form of mesh data: BufferGeometryData from vertex data and vertex index data.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   30.9.2021
 *
 */

#include "BufferGeometryBuilder.h"

#include "../Symplekt_GeometryBase/FaceUtils.h"

#include <vector>

namespace Symplektis::GeometryReps
{
	using namespace GeometryBase;

	BufferMeshGeometryBuilder::BufferMeshGeometryBuilder(BasePolygonalGeometryData& inputData)
	{
		m_BaseData = std::make_unique<BasePolygonalGeometryData>(inputData);
		m_ResultData = std::make_unique<BufferMeshGeometryData>(inputData.Name);
	}

	void BufferMeshGeometryBuilder::PreallocateMeshGeometryContainers()
	{
		if (m_BaseData->Vertices.empty() || m_BaseData->PolyVertexIndices.empty())
			return; // null geometry (just indices or just a point cloud)
		
        auto& dataVertices = m_BaseData->Vertices;
        auto& dataVertexIndices = m_BaseData->PolyVertexIndices;
		auto& dataVertexNormals = m_BaseData->VertexNormals;

		m_HasNormals = !dataVertexNormals.empty();

		m_ResultData->VertexCoords.clear();
		m_ResultData->VertexNormalCoords.clear();
		m_ResultData->VertexIndices.clear();
		m_ResultData->TriangulationIndices.clear();
		
		const size_t nVertexCoords = 3 * dataVertices.size();
		const size_t nTriangulations = dataVertexIndices.size();
		
		m_ResultData->TriangulationIndices = std::vector<std::vector<unsigned int>>(nTriangulations);
		
		size_t nTriangles = 0;

		for (unsigned int polygonId = 0; const auto& indexTuple : dataVertexIndices)
		{
			const size_t idTupleSize = indexTuple.size();
			const size_t assumedTriangleCount = (idTupleSize > 2 ? (idTupleSize - 2) : 0);

			m_ResultData->TriangulationIndices[polygonId].reserve(assumedTriangleCount);
			nTriangles += assumedTriangleCount;
			polygonId++;
		}
		
		const size_t nVertexIndices = 3 * nTriangles;

		m_ResultData->VertexCoords.reserve(nVertexCoords);
		m_ResultData->VertexIndices.reserve(nVertexIndices);
		if (m_HasNormals) m_ResultData->VertexNormalCoords.reserve(nVertexCoords);
	}	

    void BufferMeshGeometryBuilder::FillVertexCoordinateBuffer() const
    {
        for (unsigned int vertId = 0; const auto& vertex : m_BaseData->Vertices)
        {
            m_ResultData->VertexCoords.emplace_back(vertex.X());
            m_ResultData->VertexCoords.emplace_back(vertex.Y());
            m_ResultData->VertexCoords.emplace_back(vertex.Z());

        	if (m_HasNormals)
        	{
				m_ResultData->VertexNormalCoords.emplace_back(m_BaseData->VertexNormals[vertId].X());
				m_ResultData->VertexNormalCoords.emplace_back(m_BaseData->VertexNormals[vertId].Y());
				m_ResultData->VertexNormalCoords.emplace_back(m_BaseData->VertexNormals[vertId].Z());
        	}
			vertId++;
        }
    }

    void BufferMeshGeometryBuilder::FillVertexAndTriangulationIndexBuffers() const
    {
        auto& dataVertices = m_BaseData->Vertices;
        auto& dataVertexIndices = m_BaseData->PolyVertexIndices;

		for (unsigned int faceIndex = 0, triangleIndex = 0; const auto& indexTuple : dataVertexIndices)
		{
			auto [triangFaceIds, triangVertexIds] = ConstructFaceTriangulationFromVertices(indexTuple, triangleIndex, dataVertices);

			const size_t nTrianglesInPolygon = triangFaceIds.size();
			for (unsigned int i = 0; i < nTrianglesInPolygon; i++)
			{
				m_ResultData->TriangulationIndices[faceIndex].emplace_back(triangFaceIds[i]);
				
				m_ResultData->VertexIndices.emplace_back(triangVertexIds[static_cast<size_t>(3) * i                         ]);
				m_ResultData->VertexIndices.emplace_back(triangVertexIds[static_cast<size_t>(3) * i + static_cast<size_t>(1)]);
				m_ResultData->VertexIndices.emplace_back(triangVertexIds[static_cast<size_t>(3) * i + static_cast<size_t>(2)]);
			}
			faceIndex++;
		}
    }

    void BufferMeshGeometryBuilder::BuildGeometry()
    {
		// preallocate buffers:
		// =======================================================================
		//

		PreallocateMeshGeometryContainers();

		// fill the vertex buffer
		// =======================================================================
		//

		FillVertexCoordinateBuffer();

		// fill the vertex indices and triangulation indices buffers
		// =======================================================================
		//

		FillVertexAndTriangulationIndexBuffers();
    }

	std::tuple<Vector3, Vector3, Vector3> ObtainTriangleVerticesFromTriangulationIndices(const unsigned int& triangleId, const BufferMeshGeometryData& data)
	{
		const unsigned int vId_0x = 3 * data.VertexIndices[triangleId];
		const unsigned int vId_0y = 3 * data.VertexIndices[triangleId] + static_cast<size_t>(1);
		const unsigned int vId_0z = 3 * data.VertexIndices[triangleId] + static_cast<size_t>(2);

		const unsigned int vId_1x = 3 * data.VertexIndices[triangleId + static_cast<size_t>(1)];
		const unsigned int vId_1y = 3 * data.VertexIndices[triangleId + static_cast<size_t>(1)] + static_cast<size_t>(1);
		const unsigned int vId_1z = 3 * data.VertexIndices[triangleId + static_cast<size_t>(1)] + static_cast<size_t>(2);

		const unsigned int vId_2x = 3 * data.VertexIndices[triangleId + static_cast<size_t>(2)];
		const unsigned int vId_2y = 3 * data.VertexIndices[triangleId + static_cast<size_t>(2)] + static_cast<size_t>(1);
		const unsigned int vId_2z = 3 * data.VertexIndices[triangleId + static_cast<size_t>(2)] + static_cast<size_t>(2);

		const auto v0 = Vector3(data.VertexCoords[vId_0x], data.VertexCoords[vId_0y], data.VertexCoords[vId_0z]);
		const auto v1 = Vector3(data.VertexCoords[vId_1x], data.VertexCoords[vId_1y], data.VertexCoords[vId_1z]);
		const auto v2 = Vector3(data.VertexCoords[vId_2x], data.VertexCoords[vId_2y], data.VertexCoords[vId_2z]);

		return { v0, v1, v2 };
	}

} // Symplektis::GeometryReps