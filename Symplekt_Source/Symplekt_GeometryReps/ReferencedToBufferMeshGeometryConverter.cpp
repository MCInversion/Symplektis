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

#include <map>

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

		const bool hasNormals = !meshData.VertexNormals.empty();
		geoData.VertexNormals.reserve(meshData.VertexNormals.size());
		std::map<VertexConstIterator, unsigned int> vertexToVertexIndex{};

		unsigned int currentVertId = 0;
		for (auto vert = meshData.Vertices.begin(); vert != meshData.Vertices.end(); ++vert)
		{
			vertexToVertexIndex[vert] = currentVertId;
			geoData.Vertices.emplace_back(vert->Position());

			if (hasNormals)
			{
				geoData.VertexNormals.emplace_back(vert->Normal()->Get());
			}
			currentVertId++;
		}

		geoData.PolyVertexIndices = std::vector<std::vector<unsigned int>>{ meshData.Faces.size() };
		for (unsigned int faceIndex = 0; const auto& face : meshData.Faces)
		{
			const auto& baseHeIt = face.HalfEdge();
			auto heIt = baseHeIt;
			geoData.PolyVertexIndices[faceIndex].reserve(face.GetTriangulation().size() + 2);
			do
			{
				geoData.PolyVertexIndices[faceIndex].emplace_back(vertexToVertexIndex[heIt->TailVertex()]);
				heIt = heIt->NextHalfEdge();
			}
			while (heIt != baseHeIt);
			faceIndex++;
		}

		return geoData;
    }

} // Symplektis::GeometryReps