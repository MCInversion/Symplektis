/*! \file  ReferencedToBufferMeshGeometryConverter.cpp
 *  \brief An implementation of a converter object for transforming ReferencedMeshGeometryData to BufferMeshGeometryData
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   2.10.2021
 *
 */

#include "ReferencedToBufferMeshGeometryConverter.h"

#include "Symplekt_GeometryBase/Face.h"
#include "Symplekt_GeometryBase/GeometryHelperTypes.h"
#include "Symplekt_GeometryBase/HalfEdge.h"

#include "BufferMeshGeometry.h"

namespace Symplektis::GeometryReps
{
	using namespace GeometryBase;
	
	ReferencedToBufferMeshGeometryConverter::ReferencedToBufferMeshGeometryConverter(const ReferencedMeshGeometry& geomIn)
	{
		m_GeomIn = std::make_unique<ReferencedMeshGeometry>(geomIn);
	}

    void ReferencedToBufferMeshGeometryConverter::ConvertGeometry()
    {
		const auto baseGeomData = PrepareBaseGeometryData();
		m_GeomOut = std::make_unique<BufferMeshGeometry>(BufferMeshGeometry(baseGeomData));
		m_GeomOut->BuildGeometry();
    }

    BasePolygonalGeometryData ReferencedToBufferMeshGeometryConverter::PrepareBaseGeometryData() const
    {
		BasePolygonalGeometryData geoData{};
		
		const auto& meshData = m_GeomIn->GetMeshData();
		geoData.Name = meshData.Name;
		
		geoData.Vertices.reserve(meshData.Vertices.size());
		geoData.VertexNormals.reserve(meshData.VertexNormals.size());
		
		std::vector<VertexHandle> vertexHandles;
		vertexHandles.reserve(meshData.Vertices.size());
		std::ranges::transform(meshData.Vertices, std::back_inserter(vertexHandles), 
			[&meshData](const Vertex& vert){
				return VertexHandle(static_cast<Util::ContainerIndex>(vert.Index()), &meshData.Vertices);
			});
		if (!meshData.VertexNormals.empty()) // has normals
		{
			std::ranges::transform(meshData.VertexNormals, std::back_inserter(geoData.VertexNormals),
			[](const VertexNormal& normal) {
					return normal.Get();
			});
		}

		geoData.PolyVertexIndices = std::vector<std::vector<unsigned int>>{ meshData.Faces.size() };
		for (unsigned int faceIndex = 0; const auto& face : meshData.Faces)
		{
			const auto& baseHeHandle = face.HalfEdge();
			auto heHandle = baseHeHandle;
			geoData.PolyVertexIndices[faceIndex].reserve(face.GetTriangulation().size() + 2);
			do
			{
				const Util::Symplekt_IndexType vertexIndex = heHandle.GetElement().TailVertex().GetIndex().get();
				geoData.PolyVertexIndices[faceIndex].emplace_back(vertexHandles[vertexIndex].GetElement().Position());
				heHandle = heHandle.GetElement().NextHalfEdge();
			}
			while (heHandle != baseHeHandle);
			faceIndex++;
		}

		return geoData;
    }

} // Symplektis::GeometryReps