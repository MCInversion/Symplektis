/*! \file  ReferencedMeshGeometry_DataValidity_Tests.cpp
 *  \brief Data validity unit tests for icosahedron ReferencedMeshGeometry
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   9.9.2021
 *
 */

#include "gtest/gtest.h"

#include "../../Symplekt_GeometryBase/VertexUtils.h"
#include "../../Symplekt_GeometryBase/FaceUtils.h"
#include "../../Symplekt_GeometryBase/Vertex.h"

#include "../ReferencedMeshGeometry.h"
#include "MeshGeometryDataForTesting.h"

#include <corecrt_math_defines.h>

namespace Symplektis::UnitTests
{
    using namespace GeometryBase;
    using namespace GeometryReps;

    //
    // ===========================================================
    //

	class ReferencedMeshGeometry_DataValidity_TestFixture : public ::testing::Test
	{
	protected:
		void SetUp() override
		{
            // initialize base data
            const BasePolygonalGeometryData icosahedronBaseData = { L"icosahedron", icosahedronDataVertices, icosahedronDataVertexIndices};
            const BasePolygonalGeometryData icosahedronWithQuadBaseData = { L"icosahedronWithQuad", icosahedronDataVertices, icosahedronFirstQuadDataVertexIndices};
            const BasePolygonalGeometryData icosahedronWithHoleBaseData = { L"icosahedronWithHole", icosahedronDataVertices, icosahedronMissingTwoTrianglesDataVertexIndices};
			
            m_Icosahedron         = std::make_unique<ReferencedMeshGeometry>(ReferencedMeshGeometry(icosahedronBaseData));
            m_IcosahedronWithQuad = std::make_unique<ReferencedMeshGeometry>(ReferencedMeshGeometry(icosahedronWithQuadBaseData));
            m_IcosahedronWithHole = std::make_unique<ReferencedMeshGeometry>(ReferencedMeshGeometry(icosahedronWithHoleBaseData));

            // build geometries
            m_Icosahedron->BuildGeometry();
            m_IcosahedronWithQuad->BuildGeometry();
            m_IcosahedronWithHole->BuildGeometry();
		}

		//!< using rvalue instantiation so that reference data does not lose some of its deeper references (otherwise utils like ComputeArea crash)
        std::unique_ptr<ReferencedMeshGeometry> m_Icosahedron;
        std::unique_ptr<ReferencedMeshGeometry> m_IcosahedronWithQuad;
        std::unique_ptr<ReferencedMeshGeometry> m_IcosahedronWithHole;
	};

    //
    // ===========================================================
    //

	TEST_F(ReferencedMeshGeometry_DataValidity_TestFixture, MeshGeometry_IcosahedronTestGeometries_CorrectGeometrySizes)
	{
		// Arrange, Act
        const size_t icosahedronDataSize = m_Icosahedron->GetMeshData().Size();
        const size_t icosahedronWithQuadDataSize = m_IcosahedronWithQuad->GetMeshData().Size();
        const size_t icosahedronWithHolesDataSize = m_IcosahedronWithHole->GetMeshData().Size();

		// Assert
#if _DEBUG
        EXPECT_EQ(icosahedronDataSize, 10880);
        EXPECT_EQ(icosahedronWithHolesDataSize, 10528);
        EXPECT_EQ(icosahedronWithQuadDataSize, 10528);
#else
        EXPECT_EQ(icosahedronDataSize, 4736);
        EXPECT_EQ(icosahedronWithHolesDataSize, 4584);
        EXPECT_EQ(icosahedronWithQuadDataSize, 4584);
#endif
	}
	
    TEST_F(ReferencedMeshGeometry_DataValidity_TestFixture, Triangle_IcosahedronTrianglesEdgeLengths_EqualEdgeLengths)
    {
    	// Arrange, Act, Assert
        const auto& icoMeshData = m_Icosahedron->GetMeshData();
        EXPECT_EQ(icoMeshData.Edges.size(), 30);        
    	for (unsigned int edgeCounter = 0; auto& edge : icoMeshData.Edges)
    	{
            const Vector3 v0 = edge.HalfEdge()->TailVertex()->Position();
            const Vector3 v1 = edge.HalfEdge()->OppositeHalfEdge()->TailVertex()->Position();
            const double length = (v1 - v0).GetLength();
            EXPECT_DOUBLE_EQ(length, ico_edge_length);
            EXPECT_EQ(edge.Index(), edgeCounter);
            edgeCounter++;
    	}
    }

	TEST_F(ReferencedMeshGeometry_DataValidity_TestFixture, MeshGeometry_IcosahedronReferencedGeometries_FaceAndBoundaryBufferSizesCorrect)
	{
        // Arrange, Act, Assert
        const auto& icoMeshData = m_Icosahedron->GetMeshData();
        EXPECT_EQ(icoMeshData.Faces.size(), 20);
        EXPECT_EQ(icoMeshData.BoundaryCycles.size(), 0);

        const auto& icoWithQuadMeshData = m_IcosahedronWithQuad->GetMeshData();
        EXPECT_EQ(icoWithQuadMeshData.Faces.size(), 19);
        EXPECT_EQ(icoWithQuadMeshData.BoundaryCycles.size(), 0);

        const auto& icoWithHoleMeshData = m_IcosahedronWithHole->GetMeshData();
        EXPECT_EQ(icoWithHoleMeshData.Faces.size(), 18);
        EXPECT_EQ(icoWithHoleMeshData.BoundaryCycles.size(), 1);
	}

	TEST_F(ReferencedMeshGeometry_DataValidity_TestFixture, MeshGeometry_IcosahedronTrianglesAreas_EqualAreasFromFormula)
    {
        // Arrange, Act, Assert
        const auto& icoMeshData = m_Icosahedron->GetMeshData();
    	for (auto& face : icoMeshData.Faces)
    	{
            const double area = ComputeArea(face);
            EXPECT_DOUBLE_EQ(area, ico_triangle_area);
    	}
    }

    TEST_F(ReferencedMeshGeometry_DataValidity_TestFixture, MeshGeometry_IcosahedronWithHoleFaceAreas_CorrectAreasFromFormula)
    {
        // Arrange, Act, Assert
        const auto& icoWithHoleMeshData = m_IcosahedronWithHole->GetMeshData();
        unsigned int faceCounter = 0;
        for (auto& face : icoWithHoleMeshData.Faces)
        {
            const double area = ComputeArea(face);
            EXPECT_DOUBLE_EQ(area, ico_triangle_area);
            EXPECT_EQ(face.Index(), faceCounter);
            faceCounter++;
        }

        EXPECT_EQ(icoWithHoleMeshData.BoundaryCycles.size(), 1);
        const auto& hole = icoWithHoleMeshData.BoundaryCycles[0];
        EXPECT_EQ(hole.GetTriangulation().size(), 0);
        const double holeArea = ComputeArea(hole);
        EXPECT_DOUBLE_EQ(holeArea, 0.0);
    }

    TEST_F(ReferencedMeshGeometry_DataValidity_TestFixture, MeshGeometry_IcosahedronWithQuadFaceAreas_CorrectAreasFromFormula)
    {
        // Arrange, Act, Assert
        const auto& icoWithQuadMeshData = m_IcosahedronWithQuad->GetMeshData();
        const auto& icoFaces = icoWithQuadMeshData.Faces;
		
        const size_t faceCount = icoFaces.size();
        EXPECT_EQ(faceCount, 19);
        for (unsigned int i = 0; i < faceCount; i++)
        {
	        const double area = ComputeArea(icoFaces[i]);
            EXPECT_EQ(icoFaces[i].Index(), i);
        	if (icoFaces[i].GetTriangulation().size() == 1) // triangles
        	{
	            EXPECT_DOUBLE_EQ(area, ico_triangle_area);
        	}
            else if (icoFaces[i].GetTriangulation().size() == 2) // quad
            {
                EXPECT_DOUBLE_EQ(area, 2 * ico_triangle_area);
                EXPECT_EQ(i, 0); // first face should be a quad
            }
            else
            {
                const std::string msg = "Error at face " + std::to_string(i) + ", invalid triangulations count!\n";
                FAIL() << msg;
            }
        }
    }

    TEST_F(ReferencedMeshGeometry_DataValidity_TestFixture, Vertex_GetValenceOfBoundaryVertices_ValenceIs4And5)
    {
        // Arrange
        const auto& icoWithHoleMeshData = m_IcosahedronWithHole->GetMeshData();
        const Vertex testVertex0 = icoWithHoleMeshData.Vertices[0]; // non-boundary vertex
        const Vertex testVertex2 = icoWithHoleMeshData.Vertices[2]; // boundary vertex
        const Vertex testVertex3 = icoWithHoleMeshData.Vertices[3]; // boundary vertex
        const Vertex testVertex4 = icoWithHoleMeshData.Vertices[4]; // boundary vertex

        // Act
        const unsigned int vertex0Valence = GetValence(testVertex0); 
        const unsigned int vertex2Valence = GetValence(testVertex2);
        const unsigned int vertex3Valence = GetValence(testVertex3);
        const unsigned int vertex4Valence = GetValence(testVertex4);

        // Assert
        EXPECT_EQ(vertex0Valence, 5);
        EXPECT_EQ(vertex2Valence, 4);
        EXPECT_EQ(vertex3Valence, 4);
        EXPECT_EQ(vertex4Valence, 5);
    }

	TEST_F(ReferencedMeshGeometry_DataValidity_TestFixture, HoleMeshData_IsBoundary_MeshDataAreBoundary)
	{
		// Arrange
        const auto& icoWithHoleMeshData = m_IcosahedronWithHole->GetMeshData();
        const auto& hole = icoWithHoleMeshData.BoundaryCycles[0];
        const auto& nonBoundaryVertex0 = icoWithHoleMeshData.Vertices[0];
        const auto& boundaryVertex3 = icoWithHoleMeshData.Vertices[3];
        const auto& boundaryVertex4 = icoWithHoleMeshData.Vertices[4];

		// Act & Assert
        EXPECT_TRUE(hole.IsBoundary());
        EXPECT_TRUE(boundaryVertex3.IsBoundary());
        EXPECT_TRUE(boundaryVertex4.IsBoundary());
        EXPECT_FALSE(nonBoundaryVertex0.IsBoundary());
	}

    //
    // ============ Data Copy/Move Validity Tests ================================
    //

    TEST_F(ReferencedMeshGeometry_DataValidity_TestFixture, HoleMeshData_DataCopyConstructor_DataCopyConstructed)
    {
        // Arrange
        const auto& icoWithHoleMeshData = m_IcosahedronWithHole->GetMeshData();

		// Act
        const ReferencedMeshGeometryData copiedData(icoWithHoleMeshData);

		// Assert
        EXPECT_EQ(copiedData.Faces.size(), 18);
        EXPECT_EQ(copiedData.BoundaryCycles.size(), 1);
        EXPECT_DOUBLE_EQ(ComputeArea(copiedData.Faces[0]), ico_triangle_area);
        // original data should keep its values
        EXPECT_EQ(icoWithHoleMeshData.Faces.size(), 18);
        EXPECT_EQ(icoWithHoleMeshData.BoundaryCycles.size(), 1);
        EXPECT_DOUBLE_EQ(ComputeArea(icoWithHoleMeshData.Faces[0]), ico_triangle_area);
    }

    TEST_F(ReferencedMeshGeometry_DataValidity_TestFixture, HoleMeshData_DataCopyAssignment_DataCopyAssigned)
    {
        // Arrange
        const auto& icoWithHoleMeshData = m_IcosahedronWithHole->GetMeshData();

        // Act
        const auto copiedData = icoWithHoleMeshData;

        // Assert
        EXPECT_EQ(copiedData.Faces.size(), 18);
        EXPECT_EQ(copiedData.BoundaryCycles.size(), 1);
        EXPECT_DOUBLE_EQ(ComputeArea(copiedData.Faces[0]), ico_triangle_area);
        // original data should keep its values
        EXPECT_EQ(icoWithHoleMeshData.Faces.size(), 18);
        EXPECT_EQ(icoWithHoleMeshData.BoundaryCycles.size(), 1);
        EXPECT_DOUBLE_EQ(ComputeArea(icoWithHoleMeshData.Faces[0]), ico_triangle_area);
    }

    TEST_F(ReferencedMeshGeometry_DataValidity_TestFixture, HoleMeshData_DataMoveConstructor_DataMoveConstructed)
    {
        // Arrange
        auto icoWithHoleMeshData = m_IcosahedronWithHole->GetMeshData();

        // Act
        const ReferencedMeshGeometryData copiedData(std::move(icoWithHoleMeshData));

        // Assert
        EXPECT_EQ(copiedData.Faces.size(), 18);
        EXPECT_EQ(copiedData.BoundaryCycles.size(), 1);
        EXPECT_DOUBLE_EQ(ComputeArea(copiedData.Faces[0]), ico_triangle_area);
        // original data should lose its values
        EXPECT_EQ(icoWithHoleMeshData.Faces.size(), 0);
        EXPECT_EQ(icoWithHoleMeshData.BoundaryCycles.size(), 0);
    }

    TEST_F(ReferencedMeshGeometry_DataValidity_TestFixture, HoleMeshData_DataMoveAssignment_DataMoveAssigned)
    {
        // Arrange
        auto icoWithHoleMeshData = m_IcosahedronWithHole->GetMeshData();

        // Act
        const auto copiedData = std::move(icoWithHoleMeshData);

        // Assert
        EXPECT_EQ(copiedData.Faces.size(), 18);
        EXPECT_EQ(copiedData.BoundaryCycles.size(), 1);
        EXPECT_DOUBLE_EQ(ComputeArea(copiedData.Faces[0]), ico_triangle_area);
        // original data should lose its values
        EXPECT_EQ(icoWithHoleMeshData.Faces.size(), 0);  
        EXPECT_EQ(icoWithHoleMeshData.BoundaryCycles.size(), 0);
    }

    TEST_F(ReferencedMeshGeometry_DataValidity_TestFixture, HoleMeshData_DataRepeatedCopyConstructor_DataCopyConstructed)
    {
        // Arrange
        const auto& icoWithHoleMeshData = m_IcosahedronWithHole->GetMeshData();

        // Act
        const ReferencedMeshGeometryData copiedData0(icoWithHoleMeshData);
        const ReferencedMeshGeometryData copiedData1(copiedData0);

        // Assert
        EXPECT_EQ(copiedData0.Faces.size(), 18);
        EXPECT_EQ(copiedData0.BoundaryCycles.size(), 1);
        EXPECT_DOUBLE_EQ(ComputeArea(copiedData0.Faces[0]), ico_triangle_area);
        EXPECT_EQ(copiedData1.Faces.size(), 18);
        EXPECT_EQ(copiedData1.BoundaryCycles.size(), 1);
        EXPECT_DOUBLE_EQ(ComputeArea(copiedData1.Faces[0]), ico_triangle_area);
        // original data should keep its values
        EXPECT_EQ(icoWithHoleMeshData.Faces.size(), 18);
        EXPECT_EQ(icoWithHoleMeshData.BoundaryCycles.size(), 1);
        EXPECT_DOUBLE_EQ(ComputeArea(icoWithHoleMeshData.Faces[0]), ico_triangle_area);
    }

} // Symplektis::UnitTests