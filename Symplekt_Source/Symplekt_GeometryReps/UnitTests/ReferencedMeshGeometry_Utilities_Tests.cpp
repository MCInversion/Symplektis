/*! \file  ReferencedMeshGeometry_Utilities_Tests.cpp
 *  \brief Mesh utilities unit tests for icosahedron ReferencedMeshGeometry
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   25.9.2021
 *
 */

#include "gtest/gtest.h"

#include "Symplekt_GeometryBase/VertexUtils.h"
#include "Symplekt_GeometryBase/FaceUtils.h"
#include "Symplekt_GeometryBase/HalfEdgeUtils.h"
#include "Symplekt_GeometryBase/Vertex.h"
#include "Symplekt_GeometryBase/Vector3.h"
#include "Symplekt_GeometryBase/Vector2.h"

#include "Symplekt_UtilityGeneral/NumericUtils.h"
#include "Symplekt_UtilityGeneral/ToleranceSettings.h"

#include "Symplekt_GeometryReps/ReferencedMeshGeometry.h"

#include "MeshGeometryDataForTesting.h"

#include <corecrt_math_defines.h>
#include <algorithm>
#include <tuple>
#include <numeric>

namespace Symplektis::UnitTests
{
    using namespace GeometryBase;
    using namespace GeometryReps;

    // ------- Test data construction utils ----------------------
    //

    std::vector<VertexIterator> ConstructVertexIteratorVectorForTesting(std::vector<Vertex>& vertices)
    {
        std::vector<VertexIterator> result;
        result.reserve(vertices.size());
        for (auto vertIt = vertices.begin(); vertIt != vertices.end(); ++vertIt)
            result.emplace_back(vertIt);

        return result;
    }

    ReferencedMeshGeometry& ConstructSingleFaceGeometryDataForTestingFromVertices(const std::vector<Vector3>& vertices, ReferencedMeshGeometry& geom)
    {
        std::vector<std::vector<unsigned int>> vertexIndices{ 1 };
        vertexIndices[0] = std::vector<unsigned int>(vertices.size());
    	std::iota(vertexIndices[0].begin(), vertexIndices[0].end(), 0);

        const BasePolygonalGeometryData baseData = {L"singleFace", vertices, vertexIndices};
        geom = ReferencedMeshGeometry{ baseData };
        geom.BuildGeometry();

        return geom;
    }

    ReferencedMeshGeometry& ConstructTriangle1RingGeometryDataForTestingFromVertices(const Vector3& centralVertex, std::vector<Vector3>& ringVerts, ReferencedMeshGeometry& geom)
    {
        const size_t nVerts = ringVerts.size() + 1;
        std::vector vertices = { centralVertex };
        vertices.reserve(nVerts);

    	const size_t nFaces = nVerts - 1;
        std::vector<std::vector<unsigned int>> vertexIndices{nFaces};
        for (unsigned int i = 0; i < nFaces; i++)
        {
            vertices.emplace_back(ringVerts[i]);
        	const unsigned int iCurr = i + 1;
            const unsigned int iNext = ((i + static_cast<size_t>(1)) % nFaces) + 1;
            vertexIndices[i] = { 0, iCurr, iNext };
        }

        const BasePolygonalGeometryData baseData = { L"oneRing", vertices, vertexIndices};
        geom = ReferencedMeshGeometry{ baseData };
        geom.BuildGeometry();

        return geom;
    }

    //
    // ===========================================================
    //

    const double SQRT3_3 = sqrt(3.0) / 3.0;

    const unsigned int test_ring_verts_count = 5;

    //
    // ===========================================================
    //

	class ReferencedMeshGeometry_UtilitiesTestFixture : public ::testing::Test
	{
	protected:

		void SetUp() override
		{
            std::vector vertices{
                Vector3{-1.0, phi, 0.0}, Vector3{-phi, 0.0, 1.0}, Vector3{0, 1.0, phi}
            };
            ConstructSingleFaceGeometryDataForTestingFromVertices(vertices, m_TestSingleTriangle);

            vertices = {
                Vector3{-1.0, phi, 0.0}, Vector3{1.0, phi, 0.0}, Vector3{0, 1.0, -phi}
            };
            ConstructSingleFaceGeometryDataForTestingFromVertices(vertices, m_TestSingleSecondTriangle);

            vertices = {
                Vector3{-1.0, phi, 0.0}, Vector3{-phi, 0.0, 1.0}, Vector3{0, 1.0, phi}, Vector3{1.0, phi, 0.0}
            };
            ConstructSingleFaceGeometryDataForTestingFromVertices(vertices, m_TestSingleQuad);

            /* =========================================
                  v2
                   | \
                   |  \
                   |   \
                   |    \
              ^ y  |     \
              |    v0 --- v1
               -> x
               ======================================== */
            vertices = {
                Vector3(), Vector3(1.0, 0.0, 0.0), Vector3(0.0, 1.0, 0.0)
            };
            ConstructSingleFaceGeometryDataForTestingFromVertices(vertices, m_TestSinglePseudoplanarTriangle);

            /* =========================================
                  v3 ----- v2
                   |       |
                   |       |
                   |       |
                   |       |                  _ .v2
              ^ y  |       |      ^ z      _ .   |
              |    v0 ---- v1     |      v0 ---- v1
               -> x               -> x
               ======================================== */
            vertices = {
                Vector3(), Vector3(1.0, 0.0, 0.0), Vector3(1.0, 1.0, 0.5), Vector3(0.0, 1.0, 0.0)
            };
            ConstructSingleFaceGeometryDataForTestingFromVertices(vertices, m_TestSinglePseudoplanarQuad);

            /*  ==================================================
                         v3
                       /    \
                      /      \
                     /        \
                    /          \
                   v4           v2
                   |            /
                   |           /
                   |          /
                   |         /                    _ v1,v3 _
             ^ y   |        /        ^ z         /         \
             |     v0 _ _ v1         |       v0,v4         v2
              -> x                    -> x
                ==================================================
             */
            vertices = {
                Vector3(), Vector3(1.0, 0.0, 0.5), Vector3(phi, 1.0, 0.0), Vector3(1.0, phi, 0.5), Vector3(0.0, 1.0, 0.0)
            };
            ConstructSingleFaceGeometryDataForTestingFromVertices(vertices, m_TestSinglePentagon);

            const auto centralVertex = Vector3{ -1.0, phi, 0.0 };
            std::vector ringVertices = {
                Vector3{1.0, phi, 0.0}, Vector3{0, 1.0, -phi}, Vector3{-phi, 0.0, -1.0},
                Vector3{-phi, 0.0, 1.0}, Vector3{0, 1.0, phi}
            };
            ConstructTriangle1RingGeometryDataForTestingFromVertices(centralVertex, ringVertices, m_TestTriangle1Ring);
		}

        /// \brief triangles and quads originating from icosahedron
        ReferencedMeshGeometry m_TestSingleTriangle;
        ReferencedMeshGeometry m_TestSingleSecondTriangle;
        ReferencedMeshGeometry m_TestSingleQuad;
        ReferencedMeshGeometry m_TestTriangle1Ring;

        /// \brief pseudo-planar polygons
        ReferencedMeshGeometry m_TestSinglePseudoplanarTriangle;
        ReferencedMeshGeometry m_TestSinglePseudoplanarQuad;
        ReferencedMeshGeometry m_TestSinglePentagon;
	};

    //
    // ===========================================================
    // ------  HalfEdge ------------------------------------------

    TEST_F(ReferencedMeshGeometry_UtilitiesTestFixture, HalfEdge_ComputeOppositeAngleCotan_OppositeAngleCotan)
    {
        // Arrange
        const auto& meshData = m_TestSingleTriangle.GetMeshData();
        const auto& halfEdge = meshData.HalfEdges[0];

        // Act
        const double cotan = ComputeOppositeAngleCotan(halfEdge);

        // Assert
        EXPECT_DOUBLE_EQ(cotan, SQRT3_3);
    }

    TEST_F(ReferencedMeshGeometry_UtilitiesTestFixture, HalfEdge_ComputeRotatedEdgeVector_RotatedEdgeVector)
    {
        // Arrange
        const auto& meshData = m_TestSingleQuad.GetMeshData();
        const auto& halfEdge = meshData.HalfEdges[0];

        // Act
        const Vector3 edgeVec = ComputeRotatedEdgeVector(halfEdge);

        // Assert
        EXPECT_DOUBLE_EQ(edgeVec.X(), phi);
        EXPECT_TRUE(Util::EqualsWithTolerance(edgeVec.Y(), 0.0, Util::GetProductTolerance()));
        EXPECT_DOUBLE_EQ(edgeVec.Z(), 1.0);
    }

    //
    // ===========================================================
    // ------  Face ----------------------------------------------

    TEST(ReferencedMeshGeometry_Utilities_Tests, TriangleVertices_ConstructFace_TriangleFace)
    {
        // Arrange
        std::vector vertices{
            Vertex(), Vertex(1.0, 0.0, 0.0), Vertex(0.0, 1.0, 0.0)
        };
        const auto vertexIters = ConstructVertexIteratorVectorForTesting(vertices);

        // Act
        const Face testTriangle(vertexIters);

        // Assert
        const auto& triangulation = testTriangle.GetTriangulation();
        EXPECT_EQ(triangulation.size(), 1);
        EXPECT_TRUE(std::get<0>(triangulation[0])->Position() == vertices[0].Position());
        EXPECT_TRUE(std::get<1>(triangulation[0])->Position() == vertices[1].Position());
        EXPECT_TRUE(std::get<2>(triangulation[0])->Position() == vertices[2].Position());
    }

    TEST(ReferencedMeshGeometry_Utilities_Tests, QuadVertices_ConstructQuadFaceFromCCWVertices_QuadFace)
    {
        // Arrange
        std::vector vertices{
            Vertex(), Vertex(1.0, 0.0, 0.0), Vertex(1.0, 1.0, 0.5), Vertex(0.0, 1.0, 0.0)
        };
        /* =========================================

          v3 ----- v2
           |     / |
           | t1 /  |
           |   /   |
           |  / t0 |
           | /     |
           v0 ---- v1
           ======================================== */
        const auto vertexIters = ConstructVertexIteratorVectorForTesting(vertices);

        // Act
        const Face testQuad(vertexIters);

        // Assert
        const auto& triangulation = testQuad.GetTriangulation();
        EXPECT_EQ(triangulation.size(), 2);
        EXPECT_TRUE(std::get<0>(triangulation[0])->Position() == vertices[0].Position());
        EXPECT_TRUE(std::get<1>(triangulation[0])->Position() == vertices[1].Position());
        EXPECT_TRUE(std::get<2>(triangulation[0])->Position() == vertices[2].Position());

        EXPECT_TRUE(std::get<0>(triangulation[1])->Position() == vertices[0].Position());
        EXPECT_TRUE(std::get<1>(triangulation[1])->Position() == vertices[2].Position());
        EXPECT_TRUE(std::get<2>(triangulation[1])->Position() == vertices[3].Position());
    }

    TEST(ReferencedMeshGeometry_Utilities_Tests, QuadVertices_ConstructQuadFaceFromAlternatingVertices_QuadFace)
    {
        // Arrange
        std::vector vertices{
            Vertex(), Vertex(1.0, 1.0, 0.5), Vertex(1.0, 0.0, 0.0), Vertex(0.0, 1.0, 0.0)
        };
        /* =========================================
          v3 ----- v1 => 2
           | \     |
           |  \ t1 |
           |   \   |
           | t0 \  |
           |     \ |
           v0 ---- v2 => 1
           ======================================== */
        const auto vertexIters = ConstructVertexIteratorVectorForTesting(vertices);

        // Act
        const Face testQuad(vertexIters);

        // Assert
        const auto& triangulation = testQuad.GetTriangulation();
        EXPECT_EQ(triangulation.size(), 2);
        EXPECT_TRUE(std::get<0>(triangulation[0])->Position() == vertices[0].Position());
        EXPECT_TRUE(std::get<1>(triangulation[0])->Position() == vertices[1].Position());
        EXPECT_TRUE(std::get<2>(triangulation[0])->Position() == vertices[3].Position());

        EXPECT_TRUE(std::get<0>(triangulation[1])->Position() == vertices[1].Position());
        EXPECT_TRUE(std::get<1>(triangulation[1])->Position() == vertices[2].Position());
        EXPECT_TRUE(std::get<2>(triangulation[1])->Position() == vertices[3].Position());
    }

    TEST(ReferencedMeshGeometry_Utilities_Tests, QuadVertices_ConstructPentagonFaceFromVertices_PentagonFace)
    {
        // Arrange
        std::vector vertices{
            Vertex(), Vertex(1.0, 0.0, 0.5), Vertex(phi, 1.0, 0.0), Vertex(1.0, phi, 0.5), Vertex(0.0, 1.0, 0.0)
        };
        /*   ==================================================
                 v3
               /    \
              /      \
             /   t0   \
            /          \
           v4 _ _ _ _ _ v2
           | \          /
           |  \   t1   /
           |   \      /
           | t2 \    /
           |     \  /
           v0 _ _ v1
             ==================================================
         */
        const auto vertexIters = ConstructVertexIteratorVectorForTesting(vertices);

        // Act
        const Face testPolygon(vertexIters);

        // Assert
        const auto& triangulation = testPolygon.GetTriangulation();
        EXPECT_EQ(triangulation.size(), 3);

        EXPECT_TRUE(std::get<0>(triangulation[0])->Position() == vertices[2].Position());
        EXPECT_TRUE(std::get<1>(triangulation[0])->Position() == vertices[3].Position());
        EXPECT_TRUE(std::get<2>(triangulation[0])->Position() == vertices[4].Position());

        EXPECT_TRUE(std::get<0>(triangulation[1])->Position() == vertices[1].Position());
        EXPECT_TRUE(std::get<1>(triangulation[1])->Position() == vertices[2].Position());
        EXPECT_TRUE(std::get<2>(triangulation[1])->Position() == vertices[4].Position());

        EXPECT_TRUE(std::get<0>(triangulation[2])->Position() == vertices[4].Position());
        EXPECT_TRUE(std::get<1>(triangulation[2])->Position() == vertices[0].Position());
        EXPECT_TRUE(std::get<2>(triangulation[2])->Position() == vertices[1].Position());
    }

    // TODO: More triangulation tests for (n>=5)-gons

    TEST_F(ReferencedMeshGeometry_UtilitiesTestFixture, Triangle_ComputeArea_TriangleArea)
    {
        // Arrange
        const auto& meshData = m_TestSingleTriangle.GetMeshData();
        const auto& testTriangle = meshData.Faces[0];

        // Act
        const double area = ComputeArea(testTriangle);

        // Assert
        EXPECT_DOUBLE_EQ(area, ico_triangle_area);
    }

    TEST_F(ReferencedMeshGeometry_UtilitiesTestFixture, Quad_ComputeArea_QuadArea)
    {
        // Arrange
        const auto& meshData = m_TestSingleQuad.GetMeshData();
        const auto& testFace = meshData.Faces[0];

        // Act
        const double area = ComputeArea(testFace);

        // Assert
        EXPECT_DOUBLE_EQ(area, 2 * ico_triangle_area);
    }

    TEST_F(ReferencedMeshGeometry_UtilitiesTestFixture, Triangle_ComputeCircumcenter_TriangleCircumcenter)
    {
        // Arrange
        const auto& meshData = m_TestSingleSecondTriangle.GetMeshData();
        const Face& testTriangle = meshData.Faces[0];

        // Act
        const Vector3 circumCenter = ComputeCircumcenter(testTriangle);

        // Assert
        EXPECT_DOUBLE_EQ(circumCenter.X(), 1.1102230246251565e-16);
        EXPECT_DOUBLE_EQ(circumCenter.Y(), 1.4120226591665965);
        EXPECT_DOUBLE_EQ(circumCenter.Z(), -0.53934466291663163);
    }

    TEST_F(ReferencedMeshGeometry_UtilitiesTestFixture, Triangle_ComputeNormal_TriangleNormal)
    {
        // Arrange
        const auto& meshData = m_TestSingleSecondTriangle.GetMeshData();
        const Face& testTriangle = meshData.Faces[0];

        // Act
        const Vector3 normal = ComputeNormal(testTriangle);

        // Assert
        EXPECT_DOUBLE_EQ(normal.X(), 0.0);
        EXPECT_DOUBLE_EQ(normal.Y(), 0.93417235896271578);
        EXPECT_DOUBLE_EQ(normal.Z(), -0.35682208977308999);
    }

    TEST_F(ReferencedMeshGeometry_UtilitiesTestFixture, Quad_ComputeNormal_QuadNormal)
    {
        // Arrange
        const auto& meshData = m_TestSingleQuad.GetMeshData();
        const Face& testQuad = meshData.Faces[0];

        // Act
        const Vector3 normal = ComputeNormal(testQuad);

        // Assert
        EXPECT_DOUBLE_EQ(normal.X(), -0.3090169943749475);
        EXPECT_DOUBLE_EQ(normal.Y(), 0.8090169943749473);
        EXPECT_DOUBLE_EQ(normal.Z(), 0.5);
    }

    TEST(ReferencedMeshGeometry_Utilities_Tests, Triangle_ComputeTriangleNormalFromVertices_TriangleNormal)
    {
        // Arrange
        std::vector vertices{
            Vertex(), Vertex(1.0, 0.0, 0.0), Vertex(0.0, 1.0, 0.0)
        };
        /* =========================================
              v2
               | \
               |  \
               |   \
               |    \
          ^ y  |     \
          |    v0 --- v1
           -> x
           ======================================== */
        const auto vertexIters = ConstructVertexIteratorVectorForTesting(vertices);

        // Act
        const Vector3 normal = ComputeNormal(vertexIters);

        // Assert
        EXPECT_DOUBLE_EQ(normal.X(), 0.0);
        EXPECT_DOUBLE_EQ(normal.Y(), 0.0);
        EXPECT_DOUBLE_EQ(normal.Z(), 1.0);
    }

    TEST(ReferencedMeshGeometry_Utilities_Tests, Quad_ComputeQuadNormalFromVertices_QuadNormal)
    {
        // Arrange
        std::vector vertices{
            Vertex(), Vertex(1.0, 0.0, 0.0), Vertex(1.0, 1.0, 0.5), Vertex(0.0, 1.0, 0.0)
        };
        /* =========================================
              v3 ----- v2
               |       |
               |       |
               |       |
               |       |                  _ .v2
          ^ y  |       |      ^ z      _ .   |
          |    v0 ---- v1     |      v0 ---- v1
           -> x               -> x
           ======================================== */
        const auto vertexIters = ConstructVertexIteratorVectorForTesting(vertices);

        // Act
        const Vector3 normal = ComputeNormal(vertexIters);

        // Assert
        EXPECT_DOUBLE_EQ(normal.X(), -0.23570226039551587);
        EXPECT_DOUBLE_EQ(normal.Y(), -0.23570226039551587);
        EXPECT_DOUBLE_EQ(normal.Z(), 0.94280904158206347);
    }

    TEST(ReferencedMeshGeometry_Utilities_Tests, Pentagon_ComputeNormalFromVertices_PentagonNormal)
    {
        // Arrange
        std::vector vertices{
            Vertex(), Vertex(1.0, 0.0, 0.5), Vertex(phi, 1.0, 0.0), Vertex(1.0, phi, 0.5), Vertex(0.0, 1.0, 0.0)
        };
        /*  ==================================================
                     v3
                   /    \
                  /      \
                 /        \
                /          \
               v4           v2
               |            /
               |           /
               |          /
               |         /                    _ v1,v3 _
         ^ y   |        /        ^ z         /         \
         |     v0 _ _ v1         |       v0,v4         v2
          -> x                    -> x
            ==================================================
         */
        const auto vertexIters = ConstructVertexIteratorVectorForTesting(vertices);

        // Act
        const Vector3 normal = ComputeNormal(vertexIters);

        // Assert
        EXPECT_DOUBLE_EQ(normal.X(), -0.13689554756676869);
        EXPECT_DOUBLE_EQ(normal.Y(), 0.0);
        EXPECT_DOUBLE_EQ(normal.Z(), 0.99058548801019419);
    }

    TEST(ReferencedMeshGeometry_Utilities_Tests, Triangle_ComputeProjectionsAlongNormalFromVerticesNormalAndRefPt_ProjectionsAlongTriangleNormal)
    {
        // Arrange
        std::vector vertices{
            Vertex(), Vertex(1.0, 0.0, 0.0), Vertex(0.0, 1.0, 0.0)
        };
        /* =========================================
          3D:                       2D:
               v2                            p1
               | \                          |  \
               |  \                         |   \
               |   \       =====>           |    \
               |    \                       |     \
          ^ y  |     \              ^ y     |      \
          |    v0 --- v1            |       p1 ---- p0
           -> x                      -> x
           ======================================== */
        const auto vertexIters = ConstructVertexIteratorVectorForTesting(vertices);
        const auto& refPt = vertices[0].Position();
        const auto& normal = Vector3(0.0, 0.0, 1.0);

        // Act
        const auto& projections = ComputeProjectionsAlongNormal(vertexIters, normal, refPt);

        // Assert
        EXPECT_EQ(projections.size(), 3);
        EXPECT_DOUBLE_EQ(projections[0].X(), 0.0);
        EXPECT_DOUBLE_EQ(projections[0].Y(), 0.0);

        EXPECT_DOUBLE_EQ(projections[1].X(), 0.0);
        EXPECT_DOUBLE_EQ(projections[1].Y(), 1.0);

        EXPECT_DOUBLE_EQ(projections[2].X(), -1.0);
        EXPECT_DOUBLE_EQ(projections[2].Y(), 0.0);
    }

    TEST(ReferencedMeshGeometry_Utilities_Tests, Triangle_ComputeProjectionsAlongNormalFromVertices_ProjectionsAlongTriangleNormal)
    {
        // Arrange
        std::vector vertices{
            Vertex(), Vertex(1.0, 0.0, 0.0), Vertex(0.0, 1.0, 0.0)
        };
        /* =========================================
          3D:                       2D:
               v2                                  p1
               | \                                / |
               |  \                              /  |
               |   \       =====>               /   |
               |    \                          /    |
          ^ y  |     \              ^ y       /     |
          |    v0 --- v1            |       p2 ---- p0
           -> x                      -> x
           ======================================== */
        const auto vertexIters = ConstructVertexIteratorVectorForTesting(vertices);

        // Act
        const auto& projections = ComputeProjectionsAlongNormal(vertexIters);

        // Assert
        EXPECT_EQ(projections.size(), 3);
        EXPECT_DOUBLE_EQ(projections[0].X(), 0.0);
        EXPECT_DOUBLE_EQ(projections[0].Y(), 0.0);

        EXPECT_DOUBLE_EQ(projections[1].X(), 0.0);
        EXPECT_DOUBLE_EQ(projections[1].Y(), 1.0);

        EXPECT_DOUBLE_EQ(projections[2].X(), -1.0);
        EXPECT_DOUBLE_EQ(projections[2].Y(), 0.0);
    }

    TEST(ReferencedMeshGeometry_Utilities_Tests, Quad_ComputeProjectionsAlongNormalFromVertices_ProjectionsAlongNormal)
    {
        // Arrange
        std::vector vertices{
            Vertex(), Vertex(1.0, 0.0, 0.0), Vertex(1.0, 1.0, 0.5), Vertex(0.0, 1.0, 0.0)
        };
        /* =========================================
          3D:                    2D:  p2
                                    / <- \
              v3 ----- v2          /      \
               |       |          /        \
               |       |         /        ^ \
               |       |  ===>  p3 |      | p1
               |       |         \ v        /
          ^ y  |       |          \        /
          |    v0 ---- v1          \      /
           -> x                     \ -> /
                    _ .v2             p0
                 _ .   |
          ^ z  v0 ---- v1
          |
           -> x
           ======================================== */
        const auto vertexIters = ConstructVertexIteratorVectorForTesting(vertices);

        // Act
        const auto& projections = ComputeProjectionsAlongNormal(vertexIters);

        // Assert
        EXPECT_EQ(projections.size(), 4);
        EXPECT_DOUBLE_EQ(projections[0].X(), 0.0);
        EXPECT_DOUBLE_EQ(projections[0].Y(), 0.0);

        EXPECT_DOUBLE_EQ(projections[1].X(), M_SQRT1_2);
        EXPECT_DOUBLE_EQ(projections[1].Y(), 2.0 / 3.0);

        EXPECT_TRUE(Util::EqualsWithTolerance(projections[2].X(), 0.0, Util::GetProductTolerance()));
        EXPECT_DOUBLE_EQ(projections[2].Y(), 1.5);

        EXPECT_DOUBLE_EQ(projections[3].X(), -M_SQRT1_2);
        EXPECT_DOUBLE_EQ(projections[3].Y(), 2.0 / 3.0);
    }

    TEST(ReferencedMeshGeometry_Utilities_Tests, Quad_ComputeProjectionsAlongNormalFromVerticesRefPtAndNormal_ProjectionsAlongNormal)
    {
        // Arrange
        std::vector vertices{
            Vertex(), Vertex(1.0, 0.0, 0.0), Vertex(1.0, 1.0, 0.5), Vertex(0.0, 1.0, 0.0)
        };
        /* =========================================
          3D:                    2D:

              v3 ----- v2            p2 ----- p1
               |       |              |       |
               |       |              |       |
               |       |  ===>        |       |
               |       |              |       |
          ^ y  |       |         ^ y  |       |
          |    v0 ---- v1        |    p3 ---- p0
           -> x                   -> x
                    _ .v2
                 _ .   |
          ^ z  v0 ---- v1
          |
           -> x
           ======================================== */
        const auto vertexIters = ConstructVertexIteratorVectorForTesting(vertices);
        const auto& refPt = vertices[0].Position();
        const auto& normal = Vector3(0.0, 0.0, 1.0);

        // Act
        const auto& projections = ComputeProjectionsAlongNormal(vertexIters, normal, refPt);

        // Assert
        EXPECT_EQ(projections.size(), 4);
        EXPECT_DOUBLE_EQ(projections[0].X(), 0.0);
        EXPECT_DOUBLE_EQ(projections[0].Y(), 0.0);

        EXPECT_DOUBLE_EQ(projections[1].X(), 0.0);
        EXPECT_DOUBLE_EQ(projections[1].Y(), 1.0);

        EXPECT_DOUBLE_EQ(projections[2].X(), -1.0);
        EXPECT_DOUBLE_EQ(projections[2].Y(), 1.0);

        EXPECT_DOUBLE_EQ(projections[3].X(), -1.0);
        EXPECT_DOUBLE_EQ(projections[3].Y(), 0.0);
    }

    TEST(ReferencedMeshGeometry_Utilities_Tests, Pentagon_ComputeProjectionsAlongNormalFromVertices_PentagonProjectionsAlongNormal)
    {
        // Arrange
        std::vector vertices{
            Vertex(), Vertex(1.0, 0.0, 0.5), Vertex(phi, 1.0, 0.0), Vertex(1.0, phi, 0.5), Vertex(0.0, 1.0, 0.0)
        };
        /*  ===========================================================================================
             3D:                                                       2D:

                      v3                                                  p2
                    /   \                                              /  <-  \
                  /      \                                            /         \
                 /        \                                          /            \
                /          \                                        /               \
               v4           v2                         ========>   p3 |           ^  p1
               |            /                                        \ \           \  |
               |           /                                          \ v             |
               |          /                                            \              |
               |         /                    _ v1,v3 _                 \ \         ^ |
         ^ y   |        /        ^ z         /         \                 \  ->     _| |
         |     v0 _ _ v1         |       v0,v4         v2                 p4 _ _ _ _ p0
          -> x                    -> x
            ===========================================================================================
         */
        const auto vertexIters = ConstructVertexIteratorVectorForTesting(vertices);

        // Act
        const auto& projections = ComputeProjectionsAlongNormal(vertexIters);

        // Assert
        EXPECT_EQ(projections.size(), 5);
        EXPECT_DOUBLE_EQ(projections[0].X(), 0.0);
        EXPECT_DOUBLE_EQ(projections[0].Y(), 0.0);

        EXPECT_DOUBLE_EQ(projections[1].X(), 0.0);
        EXPECT_DOUBLE_EQ(projections[1].Y(), 1.0590332617935787);

        EXPECT_DOUBLE_EQ(projections[2].X(), -1.0);
        EXPECT_DOUBLE_EQ(projections[2].Y(), 1.6028009883628958);

        EXPECT_DOUBLE_EQ(projections[3].X(), -1.6180339887498949);
        EXPECT_DOUBLE_EQ(projections[3].Y(), 1.0590332617935787);

        EXPECT_DOUBLE_EQ(projections[4].X(), -1.0);
        EXPECT_DOUBLE_EQ(projections[4].Y(), 0.0);
    }

    TEST(ReferencedMeshGeometry_Utilities_Tests, Pentagon_ComputeProjectionsAlongNormalFromVerticesRefPtAndNormal_PentagonProjectionsAlongNormal)
    {
        // Arrange
        std::vector vertices{
            Vertex(), Vertex(1.0, 0.0, 0.5), Vertex(phi, 1.0, 0.0), Vertex(1.0, phi, 0.5), Vertex(0.0, 1.0, 0.0)
        };
        /*  ===========================================================================================
             3D:                                                       2D:
                      v3                                                         p3
                    /   \                                                      /   \
                  /      \                                                   /      \
                 /        \                                                 /        \
                /          \                                               /          \
               v4           v2                         ========>          p4           p2
               |            /                                             |            /
               |           /                                              |           /
               |          /                                               |          /
               |         /                    _ v1,v3 _                   |         /
         ^ y   |        /        ^ z         /         \            ^ y   |        /
         |     v0 _ _ v1         |       v0,v4         v2           |     p0 _ _ p1
          -> x                    -> x                               -> x
            ===========================================================================================
         */
        const auto vertexIters = ConstructVertexIteratorVectorForTesting(vertices);
        const auto& refPt = vertices[0].Position();
        const auto& normal = Vector3(0.0, 0.0, 1.0);

        // Act
        const auto& projections = ComputeProjectionsAlongNormal(vertexIters, normal, refPt);

        // Assert
        EXPECT_EQ(projections.size(), 5);
        EXPECT_DOUBLE_EQ(projections[0].X(), 0.0);
        EXPECT_DOUBLE_EQ(projections[0].Y(), 0.0);

        EXPECT_DOUBLE_EQ(projections[1].X(), 0.0);
        EXPECT_DOUBLE_EQ(projections[1].Y(), 1.0);

        EXPECT_DOUBLE_EQ(projections[2].X(), -1.0);
        EXPECT_DOUBLE_EQ(projections[2].Y(), phi);

        EXPECT_DOUBLE_EQ(projections[3].X(), -phi);
        EXPECT_DOUBLE_EQ(projections[3].Y(), 1.0);

        EXPECT_DOUBLE_EQ(projections[4].X(), -1.0);
        EXPECT_DOUBLE_EQ(projections[4].Y(), 0.0);
    }

    TEST_F(ReferencedMeshGeometry_UtilitiesTestFixture, Triangle_ComputeBarycenter_TriangleBarycenter)
    {
        // Arrange
        const auto& meshData = m_TestSinglePseudoplanarTriangle.GetMeshData();
        const Face testTriangle = meshData.Faces[0];

        // Act
        const Vector3 barycenter = ComputeBarycenter(testTriangle);

        // Assert
        const double oneOver3 = 1.0 / 3.0;
        EXPECT_DOUBLE_EQ(barycenter.X(), oneOver3);
        EXPECT_DOUBLE_EQ(barycenter.Y(), oneOver3);
        EXPECT_DOUBLE_EQ(barycenter.Z(), 0.0);
    }

    TEST_F(ReferencedMeshGeometry_UtilitiesTestFixture, Quad_ComputeBarycenter_QuadBarycenter)
    {
        // Arrange
        const auto& meshData = m_TestSinglePseudoplanarQuad.GetMeshData();
        const Face testQuad = meshData.Faces[0];

        // Act
        const Vector3 barycenter = ComputeBarycenter(testQuad);

        // Assert
        EXPECT_DOUBLE_EQ(barycenter.X(), 0.5);
        EXPECT_DOUBLE_EQ(barycenter.Y(), 0.5);
        EXPECT_DOUBLE_EQ(barycenter.Z(), 0.125);
    }

    TEST_F(ReferencedMeshGeometry_UtilitiesTestFixture, Pentagon_ComputeBarycenter_PentagonBarycenter)
    {
        // Arrange
        const auto& meshData = m_TestSinglePentagon.GetMeshData();
        const Face testPentagon = meshData.Faces[0];

        // Act
        const Vector3 barycenter = ComputeBarycenter(testPentagon);

        // Assert
        const double phiPlus2Over5 = (2.0 + phi) / 5.0;
        EXPECT_DOUBLE_EQ(barycenter.X(), phiPlus2Over5);
        EXPECT_DOUBLE_EQ(barycenter.Y(), phiPlus2Over5);
        EXPECT_DOUBLE_EQ(barycenter.Z(), 0.2);
    }

    //
    // ===========================================================
    // ------  Vertex --------------------------------------------

    TEST_F(ReferencedMeshGeometry_UtilitiesTestFixture, Vertex_GetValenceOf1RingVertex_ValenceIs5)
    {
        // Arrange
        const auto& meshData = m_TestTriangle1Ring.GetMeshData();
        const Vertex testVertex0 = meshData.Vertices[0];

        // Act
        const unsigned int vertex0valence = GetValence(testVertex0);

        // Assert
        EXPECT_EQ(vertex0valence, 5);
    }

    TEST_F(ReferencedMeshGeometry_UtilitiesTestFixture, Vertex_ComputeVertexNormal_1RingVertexNormal)
    {
        // Arrange
        const auto& meshData = m_TestTriangle1Ring.GetMeshData();
        const Vertex testVertex0 = meshData.Vertices[0];

        // Act
        const Vector3 vertexNormal = ComputeVertexNormal(testVertex0);

        // Assert
        EXPECT_DOUBLE_EQ(vertexNormal.X(), -0.52573111211913359);
        EXPECT_DOUBLE_EQ(vertexNormal.Y(), 0.85065080835203999);
        EXPECT_DOUBLE_EQ(vertexNormal.Z(), -1.3971141714250944e-17);
    }

    TEST_F(ReferencedMeshGeometry_UtilitiesTestFixture, Vertex_ComputeDualNeighborhoodArea_DualNeighborhoodAreaOf1Ring)
    {
        // Arrange
        const auto& meshData = m_TestTriangle1Ring.GetMeshData();
        const Vertex testVertex0 = meshData.Vertices[0];

        // Act
        const double coVolumeArea = ComputeDualNeighborhoodArea(testVertex0);

        // Assert
        EXPECT_EQ(coVolumeArea, test_ring_verts_count * ico_triangle_area / 3.0);
    }

} // Symplektis::UnitTests