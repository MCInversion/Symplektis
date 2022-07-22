/*! \file  BufferMeshGeometry_DataValidity_Tests.cpp
 *  \brief Data validity unit tests for icosahedron BufferMeshGeometry
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   30.9.2021
 *
 */

#include "gtest/gtest.h"

#include "Symplekt_GeometryKernel/FaceUtils.h"
#include "Symplekt_GeometryKernel/Vector3.h"

#include "Symplekt_GeometryKernel/MeshGeometryDataTypes.h"
#include "Symplekt_GeometryKernel/BufferMeshGeometry.h"

#include "MeshGeometryDataForTesting.h"

#include <corecrt_math_defines.h>

namespace Symplektis::UnitTests
{
    using namespace GeometryKernel;

    //
	// ===========================================================
	//

    class BufferMeshGeometry_DataValidity_TestFixture : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
        	// initialize base data
            const BasePolygonalGeometryData icosahedronBaseData = { L"icosahedron", icosahedronDataVertices, icosahedronDataVertexIndices};
            const BasePolygonalGeometryData icosahedronWithQuadBaseData = { L"icosahedronWithQuad", icosahedronDataVertices, icosahedronFirstQuadDataVertexIndices};
            const BasePolygonalGeometryData icosahedronWithHoleBaseData = { L"icosahedronWithHole", icosahedronDataVertices, icosahedronMissingTwoTrianglesDataVertexIndices};
        	
            m_Icosahedron = std::make_unique<BufferMeshGeometry>(BufferMeshGeometry(icosahedronBaseData));
            m_IcosahedronWithQuad = std::make_unique<BufferMeshGeometry>(BufferMeshGeometry(icosahedronWithQuadBaseData));
            m_IcosahedronWithHole = std::make_unique<BufferMeshGeometry>(BufferMeshGeometry(icosahedronWithHoleBaseData));

        	// build geometries
            m_Icosahedron->BuildGeometry();
            m_IcosahedronWithQuad->BuildGeometry();
            m_IcosahedronWithHole->BuildGeometry();
        }

        std::unique_ptr<BufferMeshGeometry> m_Icosahedron;
        std::unique_ptr<BufferMeshGeometry> m_IcosahedronWithQuad;
        std::unique_ptr<BufferMeshGeometry> m_IcosahedronWithHole;
    };

    //
    // ===========================================================
    //

	TEST_F(BufferMeshGeometry_DataValidity_TestFixture, BufferMeshGeometry_ObtainTriangleVerticesFromTriangulationIndices_CorrectVertexCoords)
	{
		// Arrange
        const unsigned int triId = 0;

		// Act
        const auto [v0, v1, v2] = ObtainTriangleVerticesFromTriangulationIndices(triId, m_Icosahedron->GetMeshData());

		// Assert
		EXPECT_DOUBLE_EQ(v0.X(), -1.0);
        EXPECT_DOUBLE_EQ(v0.Y(), phi);
        EXPECT_DOUBLE_EQ(v0.Z(), 0.0);

        EXPECT_DOUBLE_EQ(v1.X(), -phi);
        EXPECT_DOUBLE_EQ(v1.Y(), 0.0);
        EXPECT_DOUBLE_EQ(v1.Z(), 1.0);

        EXPECT_DOUBLE_EQ(v2.X(), 0.0);
        EXPECT_DOUBLE_EQ(v2.Y(), 1.0);
        EXPECT_DOUBLE_EQ(v2.Z(), phi);
	}

    TEST_F(BufferMeshGeometry_DataValidity_TestFixture, BufferMeshGeometry_IcosahedronTestGeometries_CorrectGeometrySizes)
    {
        // Arrange, Act
        const size_t icosahedronDataSize = m_Icosahedron->GetMeshData().Size();
        const size_t icosahedronWithQuadDataSize = m_IcosahedronWithQuad->GetMeshData().Size();
        const size_t icosahedronWithHoleDataSize = m_IcosahedronWithHole->GetMeshData().Size();

        // Assert
        EXPECT_EQ(icosahedronDataSize, 608);
        EXPECT_EQ(icosahedronWithQuadDataSize, 604);
        EXPECT_EQ(icosahedronWithHoleDataSize, 576);
    }

    TEST_F(BufferMeshGeometry_DataValidity_TestFixture, BufferMeshGeometry_IcosahedronBufferGeometries_CorrectBufferSizes)
    {
        // Arrange, Act, Assert
        const auto& icoMeshData = m_Icosahedron->GetMeshData();
        EXPECT_EQ(icoMeshData.TriangulationIndices.size(), 20);
        EXPECT_EQ(icoMeshData.TriangulationIndices[0].size(), 1);
        EXPECT_EQ(icoMeshData.TriangulationIndices[1].size(), 1);
        EXPECT_EQ(icoMeshData.VertexIndices.size(), 60);
        EXPECT_EQ(icoMeshData.VertexCoords.size(), 36);
        EXPECT_EQ(icoMeshData.VertexNormalCoords.size(), 0);

        const auto& icoWithQuadMeshData = m_IcosahedronWithQuad->GetMeshData();
        EXPECT_EQ(icoWithQuadMeshData.TriangulationIndices.size(), 19);
        EXPECT_EQ(icoWithQuadMeshData.TriangulationIndices[0].size(), 2);
        EXPECT_EQ(icoWithQuadMeshData.TriangulationIndices[1].size(), 1);
        EXPECT_EQ(icoWithQuadMeshData.VertexIndices.size(), 60);
        EXPECT_EQ(icoWithQuadMeshData.VertexCoords.size(), 36);
        EXPECT_EQ(icoWithQuadMeshData.VertexNormalCoords.size(), 0);

        const auto& icoWithHoleMeshData = m_IcosahedronWithHole->GetMeshData();
        EXPECT_EQ(icoWithHoleMeshData.TriangulationIndices.size(), 18);
        EXPECT_EQ(icoWithHoleMeshData.TriangulationIndices[0].size(), 1);
        EXPECT_EQ(icoWithHoleMeshData.TriangulationIndices[1].size(), 1);
        EXPECT_EQ(icoWithHoleMeshData.VertexIndices.size(), 54);
        EXPECT_EQ(icoWithHoleMeshData.VertexCoords.size(), 36);
        EXPECT_EQ(icoWithHoleMeshData.VertexNormalCoords.size(), 0);
    }
	TEST_F(BufferMeshGeometry_DataValidity_TestFixture, BufferMeshGeometry_ComputeTrianglesArea_TriangleAreasCorrect)
	{
        // Arrange, Act, Assert
        const auto& meshData = m_Icosahedron->GetMeshData();
        const size_t vertexIdsSize = meshData.VertexIndices.size();
        EXPECT_EQ(vertexIdsSize, 60);
        for (unsigned int triVertId = 0; triVertId < vertexIdsSize; triVertId += 3)
        {
            const auto [v0, v1, v2] = ObtainTriangleVerticesFromTriangulationIndices(triVertId, meshData);
        	
            const double area = ComputeTriangleArea(v0, v1, v2);
            EXPECT_DOUBLE_EQ(area, ico_triangle_area);
        }
	}

    TEST_F(BufferMeshGeometry_DataValidity_TestFixture, BufferMeshGeometry_ComputeTriangulatedFaceAreas_FaceAreasCorrect)
    {
        // Arrange, Act, Assert
        const auto& icoWithQuadMeshData = m_IcosahedronWithQuad->GetMeshData();
        const size_t triangulationIdsSize = icoWithQuadMeshData.TriangulationIndices.size();
        EXPECT_EQ(triangulationIdsSize, 19);
        for (unsigned int triangulationFaceId = 0; triangulationFaceId < triangulationIdsSize; triangulationFaceId++)
        {
            const unsigned int firstTriVertId = 3 * triangulationFaceId;
            const auto [v0, v1, v2] = ObtainTriangleVerticesFromTriangulationIndices(firstTriVertId, icoWithQuadMeshData);

            const double area = ComputeTriangleArea(v0, v1, v2);
            EXPECT_DOUBLE_EQ(area, ico_triangle_area);
        }
    }

	
} // Symplektis::UnitTests