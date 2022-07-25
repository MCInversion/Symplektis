/*! \file  MeshGeometryConverter_Tests.cpp
 *  \brief Unit tests for converters between geometry reps
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   3.10.2021
 *
 */

#include "gtest/gtest.h"

#include "Symplekt_GeometryKernel/VertexUtils.h"
#include "Symplekt_GeometryKernel/FaceUtils.h"

#include "Symplekt_GeometryKernel/BufferMeshGeometry.h"
#include "Symplekt_GeometryKernel/ReferencedMeshGeometry.h"
#include "Symplekt_GeometryKernel/ReferencedToBufferMeshGeometryConverter.h"
#include "Symplekt_GeometryKernel/BufferToReferencedMeshGeometryConverter.h"
#include "Symplekt_GeometryKernel/MeshGeometryDataTypes.h"

#include "MeshGeometryDataForTesting.h"

namespace Symplektis::UnitTests
{
	using namespace GeometryKernel;
	
	class MeshGeometryConverters_TestFixture : public ::testing::Test
	{
	protected:

		void SetUp() override
		{
			// initialize base data
			const BasePolygonalGeometryData icosahedronBaseData = { L"icosahedron", icosahedronDataVertices, icosahedronDataVertexIndices};
			
			m_TestIcosahedronRefGeom = ReferencedMeshGeometry(icosahedronBaseData);
			m_TestIcosahedronBuffGeom = BufferMeshGeometry(icosahedronBaseData);

			// build geometries
			m_TestIcosahedronRefGeom.BuildGeometry();
			m_TestIcosahedronBuffGeom.BuildGeometry();
		}

		ReferencedMeshGeometry m_TestIcosahedronRefGeom;
		BufferMeshGeometry     m_TestIcosahedronBuffGeom;
	};

	TEST_F(MeshGeometryConverters_TestFixture, ReferencedGeometry_ConvertReferencedGeometryToBufferGeometry_CorrectBufferGeometryData)
	{
		// Arrange, Act
        auto refToBuffConverter = ReferencedToBufferMeshGeometryConverter(m_TestIcosahedronRefGeom);
		refToBuffConverter.ConvertGeometry();
		const auto& resultGeometry = refToBuffConverter.GetResultGeometry();
		
		auto& testBuffGeomResultData = resultGeometry.GetMeshData();
		constexpr size_t expectedIcoBuffGeomSize = 608;
		const size_t icosahedronDataSize = testBuffGeomResultData.Size();
		const auto [v0, v1, v2] = ObtainTriangleVerticesFromTriangulationIndices(0, testBuffGeomResultData);
		const double face0Area = ComputeTriangleArea(v0, v1, v2);

		// Assert
		EXPECT_EQ(icosahedronDataSize, expectedIcoBuffGeomSize);
		EXPECT_EQ(testBuffGeomResultData.TriangulationIndices.size(), 20);
		EXPECT_EQ(testBuffGeomResultData.TriangulationIndices[0].size(), 1);
		EXPECT_EQ(testBuffGeomResultData.TriangulationIndices[1].size(), 1);
		EXPECT_EQ(testBuffGeomResultData.VertexIndices.size(), 60);
		EXPECT_EQ(testBuffGeomResultData.VertexCoords.size(), 36);
		EXPECT_EQ(testBuffGeomResultData.VertexNormalCoords.size(), 0);
		EXPECT_DOUBLE_EQ(face0Area, ico_triangle_area);
	}

	TEST_F(MeshGeometryConverters_TestFixture, BufferGeometry_ConvertBufferGeometryToReferencedGeometry_CorrectRefGeometryData)
	{
		// Arrange, Act
		auto buffToRefConverter = BufferToReferencedMeshGeometryConverter(m_TestIcosahedronBuffGeom);
		buffToRefConverter.ConvertGeometry();
		const auto& resultGeometry = buffToRefConverter.GetResultGeometry();
		
		const auto& testRefGeomResultData = resultGeometry.GetMeshData();
#if _DEBUG
		constexpr size_t expectedIcoRefGeomSize = 10880;
#else
		constexpr size_t expectedIcoRefGeomSize = 4736;
#endif
		const size_t icosahedronDataSize = testRefGeomResultData.Size();
		const unsigned int vertex0Valence = GetValence(testRefGeomResultData.Vertices[0], testRefGeomResultData);
		const double face0Area = ComputeArea(testRefGeomResultData.Faces[0], testRefGeomResultData);

		// Assert
		EXPECT_EQ(icosahedronDataSize, expectedIcoRefGeomSize);
		EXPECT_EQ(testRefGeomResultData.Vertices.size(), 12);
		EXPECT_EQ(testRefGeomResultData.Faces.size(), 20);
		EXPECT_EQ(testRefGeomResultData.HalfEdges.size(), 60);
		EXPECT_EQ(testRefGeomResultData.Edges.size(), 30);
		EXPECT_EQ(testRefGeomResultData.BoundaryCycles.size(), 0);
		EXPECT_EQ(testRefGeomResultData.VertexNormals.size(), 0);
		EXPECT_EQ(vertex0Valence, 5);
		EXPECT_DOUBLE_EQ(face0Area, ico_triangle_area);
	}
	
} // namespace Symplektis::UnitTests