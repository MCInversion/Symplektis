/*! \file  BufferToReferencedMeshGeometryConverter.cpp
 *  \brief An implementation of a converter object for transforming BufferMeshGeometryData to ReferencedMeshGeometryData
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   2.10.2021
 *
 */

#include "BufferToReferencedMeshGeometryConverter.h"

#include "../Symplekt_GeometryBase/FaceUtils.h"

namespace Symplektis::GeometryReps
{
	using namespace GeometryBase;
	
	BufferToReferencedMeshGeometryConverter::BufferToReferencedMeshGeometryConverter(const BufferMeshGeometry& geomIn)
	{
		m_GeomIn = std::make_unique<BufferMeshGeometry>(geomIn);
	}
	
	void BufferToReferencedMeshGeometryConverter::ConvertGeometry()
	{
		const auto baseGeomData = PrepareBaseGeometryData();
		m_GeomOut = std::make_unique<ReferencedMeshGeometry>(ReferencedMeshGeometry(baseGeomData));
		m_GeomOut->BuildGeometry();
	}

	BasePolygonalGeometryData BufferToReferencedMeshGeometryConverter::PrepareBaseGeometryData() const
	{
		BasePolygonalGeometryData geoData{};

		const auto& meshData = m_GeomIn->GetMeshData();
		geoData.Name = meshData.Name;
		
		const bool hasNormals = !meshData.VertexNormalCoords.empty();
		geoData.Vertices.reserve(meshData.VertexCoords.size() / 3);
		geoData.VertexNormals.reserve(meshData.VertexNormalCoords.size() / 3);

		for (unsigned int i = 0; i < meshData.VertexCoords.size(); i += 3)
		{
			geoData.Vertices.emplace_back(Vector3(
				meshData.VertexCoords[i],
				meshData.VertexCoords[static_cast<size_t>(i) + 1],
				meshData.VertexCoords[static_cast<size_t>(i) + 2]
			));

			if (hasNormals)
			{
				const auto normalVec = Vector3(
					meshData.VertexNormalCoords[i],
					meshData.VertexNormalCoords[static_cast<size_t>(i) + 1],
					meshData.VertexNormalCoords[static_cast<size_t>(i) + 2]
				).Normalize();
				geoData.VertexNormals.emplace_back(normalVec);
			}
		}

		geoData.PolyVertexIndices.reserve(meshData.TriangulationIndices.size());
		for (const auto& triIds : meshData.TriangulationIndices)
			geoData.PolyVertexIndices.emplace_back(GetPolygonIndicesFromTriangulation(triIds, meshData.VertexIndices));
		
		return geoData;
	}

} // Symplektis::GeometryReps