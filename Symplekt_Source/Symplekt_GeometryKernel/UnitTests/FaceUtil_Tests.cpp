/*! \file  FaceUtil_Tests.cpp
 *  \brief Unit tests for FaceUtils
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   1.10.2021
 *
 */

#include "gtest/gtest.h"

#include "Symplekt_GeometryKernel/Vector2.h"
#include "Symplekt_GeometryKernel/Vector3.h"

#include "Symplekt_GeometryKernel/Vertex.h"
#include "Symplekt_GeometryKernel/VertexNormal.h"
#include "Symplekt_GeometryKernel/HalfEdge.h"
#include "Symplekt_GeometryKernel/Face.h"
#include "Symplekt_GeometryKernel/Edge.h"

#include "Symplekt_GeometryKernel/FaceUtils.h"

#include "Symplekt_UtilityGeneral/NumericUtils.h"
#include "Symplekt_UtilityGeneral/ToleranceSettings.h"

#include <corecrt_math_defines.h>

namespace Symplektis::UnitTests
{
    using namespace GeometryKernel;

    const double phi = (1.0 + sqrt(5.0)) / 2.0;
    TEST(FaceUtilities_Tests, TriangleVertices_ComputeTriangleAreaFromVertices_TriangleArea)
    {
        // Arrange
        const Vector3 v0;
        const Vector3 v1{ 1.0, 0.0, 0.0 };
        const Vector3 v2{ 0.0, 1.0, 0.0 };
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

        // Act
        const auto triArea = ComputeTriangleArea(v0, v1, v2);

        // Assert
        EXPECT_DOUBLE_EQ(triArea, 0.5);
    }
    TEST(FaceUtilities_Tests, TriangleVertices_ComputeTriangleNormalFromVertices_TriangleNormal)
    {
        // Arrange
        const Vector3 v0;
        const Vector3 v1{ 1.0, 0.0, 0.0 };
        const Vector3 v2{ 0.0, 1.0, 0.0 };
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

        // Act
        const auto triNormal = ComputeTriangleNormal(v0, v1, v2);

        // Assert
        EXPECT_DOUBLE_EQ(triNormal.X(), 0.0);
        EXPECT_DOUBLE_EQ(triNormal.Y(), 0.0);
        EXPECT_DOUBLE_EQ(triNormal.Z(), 1.0);
    }
    TEST(FaceUtilities_Tests, TriangleVertices_ComputeDegenerateTriangleNormalFromVertices_ZeroNormal)
    {
        // Arrange
        const Vector3 v0;
        const Vector3 v1{ 1.0, 1.0, 0.0 };
        const Vector3 v2{ 2.0, 2.0, 0.0 };
        /* =========================================

                     v2
                    //
                   //
                  /v1
                 //
          ^ y   //
          |    v0
           -> x

           ======================================== */

        // Act
        const auto triNormal = ComputeTriangleNormal(v0, v1, v2);

        // Assert
        EXPECT_DOUBLE_EQ(triNormal.X(), 0.0);
        EXPECT_DOUBLE_EQ(triNormal.Y(), 0.0);
        EXPECT_DOUBLE_EQ(triNormal.Z(), 0.0);
    }
    TEST(FaceUtilities_Tests, TriangleVertices_ComputeContourNormal_TriangleNormal)
    {
        // Arrange
        std::vector vertices{
            Vector3(), Vector3(1.0, 0.0, 0.0), Vector3(0.0, 1.0, 0.0)
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

        // Act
        const auto triNormal = ComputeVectorContourNormal(vertices);

        // Assert
        EXPECT_DOUBLE_EQ(triNormal.X(), 0.0);
        EXPECT_DOUBLE_EQ(triNormal.Y(), 0.0);
        EXPECT_DOUBLE_EQ(triNormal.Z(), 1.0);
    }
    TEST(FaceUtilities_Tests, QuadVertices_ComputeContourNormal_QuadNormal)
    {
        // Arrange
        std::vector vertices{
            Vector3(), Vector3(1.0, 0.0, 0.0), Vector3(1.0, 1.0, 0.5), Vector3(0.0, 1.0, 0.0)
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

        // Act
        const auto quadNormal = ComputeVectorContourNormal(vertices);

        // Assert
        EXPECT_DOUBLE_EQ(quadNormal.X(), -0.23570226039551587);
        EXPECT_DOUBLE_EQ(quadNormal.Y(), -0.23570226039551587);
        EXPECT_DOUBLE_EQ(quadNormal.Z(), 0.94280904158206347);
    }

    TEST(FaceUtilities_Tests, PentagonVertices_ComputeContourNormal_PentagonNormal)
    {
        // Arrange
        std::vector vertices{
            Vector3(), Vector3(1.0, 0.0, 0.5), Vector3(phi, 1.0, 0.0), Vector3(1.0, phi, 0.5), Vector3(0.0, 1.0, 0.0)
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

        // Act
        const auto pentagonNormal = ComputeVectorContourNormal(vertices);

        // Assert
        EXPECT_DOUBLE_EQ(pentagonNormal.X(), -0.13689554756676869);
        EXPECT_DOUBLE_EQ(pentagonNormal.Y(), 0.0);
        EXPECT_DOUBLE_EQ(pentagonNormal.Z(), 0.99058548801019419);
    }

    TEST(FaceUtilities_Tests, Triangle_ComputeVectorContourProjectionsAlongNormalFromVerticesNormalAndRefPt_ProjectionsAlongTriangleNormal)
    {
        // Arrange
        std::vector vertices{
            Vector3(), Vector3(1.0, 0.0, 0.0), Vector3(0.0, 1.0, 0.0)
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
        const auto& refPt = vertices[0];
        const auto& normal = Vector3(0.0, 0.0, 1.0);

        // Act
        const auto& projections = ComputeVectorContourProjectionsAlongNormal(vertices, normal, refPt);

        // Assert
        EXPECT_EQ(projections.size(), 3);
        EXPECT_DOUBLE_EQ(projections[0].X(), 0.0);
        EXPECT_DOUBLE_EQ(projections[0].Y(), 0.0);

        EXPECT_DOUBLE_EQ(projections[1].X(), 0.0);
        EXPECT_DOUBLE_EQ(projections[1].Y(), 1.0);

        EXPECT_DOUBLE_EQ(projections[2].X(), -1.0);
        EXPECT_DOUBLE_EQ(projections[2].Y(), 0.0);
    }

    TEST(FaceUtilities_Tests, Triangle_ComputeVectorContourProjectionsAlongNormalFromVertices_ProjectionsAlongTriangleNormal)
    {
        // Arrange
        std::vector vertices{
            Vector3(), Vector3(1.0, 0.0, 0.0), Vector3(0.0, 1.0, 0.0)
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

        // Act
        const auto& projections = ComputeVectorContourProjectionsAlongNormal(vertices);

        // Assert
        EXPECT_EQ(projections.size(), 3);
        EXPECT_DOUBLE_EQ(projections[0].X(), 0.0);
        EXPECT_DOUBLE_EQ(projections[0].Y(), 0.0);

        EXPECT_DOUBLE_EQ(projections[1].X(), 0.0);
        EXPECT_DOUBLE_EQ(projections[1].Y(), 1.0);

        EXPECT_DOUBLE_EQ(projections[2].X(), -1.0);
        EXPECT_DOUBLE_EQ(projections[2].Y(), 0.0);
    }

    TEST(FaceUtilities_Tests, Quad_ComputeVectorContourProjectionsAlongNormalFromVertices_ProjectionsAlongNormal)
    {
        // Arrange
        std::vector vertices{
            Vector3(), Vector3(1.0, 0.0, 0.0), Vector3(1.0, 1.0, 0.5), Vector3(0.0, 1.0, 0.0)
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

        // Act
        const auto& projections = ComputeVectorContourProjectionsAlongNormal(vertices);

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

    TEST(FaceUtilities_Tests, Quad_ComputeVectorContourProjectionsAlongNormalFromVerticesRefPtAndNormal_ProjectionsAlongNormal)
    {
        // Arrange
        std::vector vertices{
            Vector3(), Vector3(1.0, 0.0, 0.0), Vector3(1.0, 1.0, 0.5), Vector3(0.0, 1.0, 0.0)
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
       const auto& refPt = vertices[0];
        const auto& normal = Vector3(0.0, 0.0, 1.0);

        // Act
        const auto& projections = ComputeVectorContourProjectionsAlongNormal(vertices, normal, refPt);

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

    TEST(FaceUtilities_Tests, Pentagon_ComputeVectorContourProjectionsAlongNormalFromVertices_PentagonProjectionsAlongNormal)
    {
        // Arrange
        std::vector vertices{
            Vector3(), Vector3(1.0, 0.0, 0.5), Vector3(phi, 1.0, 0.0), Vector3(1.0, phi, 0.5), Vector3(0.0, 1.0, 0.0)
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
        // Act
        const auto& projections = ComputeVectorContourProjectionsAlongNormal(vertices);

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

    TEST(FaceUtilities_Tests, Pentagon_ComputeVectorContourProjectionsAlongNormalFromVerticesRefPtAndNormal_PentagonProjectionsAlongNormal)
    {
        // Arrange
        std::vector vertices{
            Vector3(), Vector3(1.0, 0.0, 0.5), Vector3(phi, 1.0, 0.0), Vector3(1.0, phi, 0.5), Vector3(0.0, 1.0, 0.0)
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
       const auto& refPt = vertices[0];
        const auto& normal = Vector3(0.0, 0.0, 1.0);

        // Act
        const auto& projections = ComputeVectorContourProjectionsAlongNormal(vertices, normal, refPt);

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

    TEST(FaceUtilities_Tests, TriangleVertices_ConstructTriangleTriangulationFromCCWVertices_TriangleTriangulation)
    {
        // Arrange
        std::vector vertices{
            Vector3(), Vector3(1.0, 0.0, 0.0), Vector3(0.0, 1.0, 0.0)
        };
        /* =========================================

              v2
               | \
               |  \
               |   \
               | t0 \
          ^ y  |     \
          |    v0 --- v1
           -> x

           ======================================== */
        unsigned int triangleId = 0;

        // Act
        const auto& [triFaceIndices, triVertIndices] = ConstructFaceTriangulationFromVertices({0, 1, 2}, triangleId, vertices);

        // Assert
        EXPECT_EQ(triangleId, 1);
        EXPECT_EQ(triFaceIndices.size(), 1);
        EXPECT_EQ(triVertIndices.size(), 3);
        EXPECT_EQ(triVertIndices[0], 0);
        EXPECT_EQ(triVertIndices[1], 1);
        EXPECT_EQ(triVertIndices[2], 2);
    }

    TEST(FaceUtilities_Tests, QuadVertices_ConstructQuadTriangulationFromCCWVertices_QuadTriangulation)
    {
        // Arrange
        std::vector vertices{
            Vector3(), Vector3(1.0, 0.0, 0.0), Vector3(1.0, 1.0, 0.5), Vector3(0.0, 1.0, 0.0)
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
        unsigned int triangleId = 0;

        // Act
        const auto& [triFaceIndices, triVertIndices] = ConstructFaceTriangulationFromVertices(
            { 0, 1, 2, 3 }, triangleId, vertices);

        // Assert
        EXPECT_EQ(triangleId, 2);
        EXPECT_EQ(triFaceIndices.size(), 2);
        EXPECT_EQ(triVertIndices.size(), 6);
        EXPECT_EQ(triVertIndices[0], 0);
        EXPECT_EQ(triVertIndices[1], 1);
        EXPECT_EQ(triVertIndices[2], 2);
        EXPECT_EQ(triVertIndices[3], 0);
        EXPECT_EQ(triVertIndices[4], 2);
        EXPECT_EQ(triVertIndices[5], 3);
    }

    TEST(FaceUtilities_Tests, QuadVertices_ConstructQuadTriangulationFromAlternatingVertices_QuadTriangulation)
    {
        // Arrange
        std::vector vertices{
            Vector3(), Vector3(1.0, 1.0, 0.5), Vector3(1.0, 0.0, 0.0), Vector3(0.0, 1.0, 0.0)
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
        unsigned int triangleId = 0;

        // Act
        const auto& [triFaceIndices, triVertIndices] = ConstructFaceTriangulationFromVertices(
            { 0, 1, 2, 3 }, triangleId, vertices);

        // Assert
        EXPECT_EQ(triangleId, 2);
        EXPECT_EQ(triFaceIndices.size(), 2);
        EXPECT_EQ(triVertIndices.size(), 6);
        EXPECT_EQ(triVertIndices[0], 0);
        EXPECT_EQ(triVertIndices[1], 1);
        EXPECT_EQ(triVertIndices[2], 3);
        EXPECT_EQ(triVertIndices[3], 1);
        EXPECT_EQ(triVertIndices[4], 2);
        EXPECT_EQ(triVertIndices[5], 3);
    }

    TEST(FaceUtilities_Tests, QuadVertices_ConstructQuadTriangulationFromConcaveCCWVertices_QuadTriangulation)
    {
        // Arrange
        std::vector vertices{
            Vector3(), Vector3(0.5, 0.0, 0.0), Vector3(1.0, 0.0, 0.0), Vector3(1.0, 1.0, 0.0)
        };
        /* =========================================

                    _ v3
                  _/ / |
                _/  |  |
               /   /   |
              / t0 | t1|
             /    /    |
           v0 -- v1 -- v2

           ======================================== */
        unsigned int triangleId = 0;

        // Act
        const auto& [triFaceIndices, triVertIndices] = ConstructFaceTriangulationFromVertices(
            { 0, 1, 2, 3 }, triangleId, vertices);

        // Assert
        EXPECT_EQ(triangleId, 2);
        EXPECT_EQ(triFaceIndices.size(), 2);
        EXPECT_EQ(triVertIndices.size(), 6);
        EXPECT_EQ(triVertIndices[0], 0);
        EXPECT_EQ(triVertIndices[1], 1);
        EXPECT_EQ(triVertIndices[2], 3);
        EXPECT_EQ(triVertIndices[3], 1);
        EXPECT_EQ(triVertIndices[4], 2);
        EXPECT_EQ(triVertIndices[5], 3);
    }

    TEST(FaceUtilities_Tests, PentagonVertices_ConstructPentagonTriangulationFromVertices_PentagonTriangulation)
    {
        // Arrange
        std::vector vertices{
            Vector3(), Vector3(1.0, 0.0, 0.5), Vector3(phi, 1.0, 0.0), Vector3(1.0, phi, 0.5), Vector3(0.0, 1.0, 0.0)
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
        unsigned int triangleId = 0;

        // Act
        const auto& [triFaceIndices, triVertIndices] = ConstructFaceTriangulationFromVertices(
            { 0, 1, 2, 3, 4 }, triangleId, vertices);

        // Assert
        EXPECT_EQ(triangleId, 3);
        EXPECT_EQ(triFaceIndices.size(), 3);
        EXPECT_EQ(triVertIndices.size(), 9);
        EXPECT_EQ(triVertIndices[0], 2);
        EXPECT_EQ(triVertIndices[1], 3);
        EXPECT_EQ(triVertIndices[2], 4);
        EXPECT_EQ(triVertIndices[3], 1);
        EXPECT_EQ(triVertIndices[4], 2);
        EXPECT_EQ(triVertIndices[5], 4);
        EXPECT_EQ(triVertIndices[6], 4);
        EXPECT_EQ(triVertIndices[7], 0);
        EXPECT_EQ(triVertIndices[8], 1);
    }

    TEST(FaceUtilities_Tests, DegenerateVertexIndices_GetPolygonIndicesFromTriangulation_DegeneratePolygonIndicesOutput)
    {
        // Arrange
        const std::vector<unsigned int> vertexIndices1 = { 0, 1 };
        const std::vector<unsigned int> vertexIndices2 = { 0, 1, 2 };

        // Act
        const auto degenerateIndices1 = GetPolygonIndicesFromTriangulation({ 0 }, vertexIndices1);
        const auto degenerateIndices2 = GetPolygonIndicesFromTriangulation({}, vertexIndices1);
        const auto degenerateIndices3 = GetPolygonIndicesFromTriangulation({ 0 }, vertexIndices2);
        const auto degenerateIndices4 = GetPolygonIndicesFromTriangulation({}, vertexIndices2);

        // Assert
        EXPECT_EQ(degenerateIndices1.size(), 2);
        EXPECT_EQ(degenerateIndices2.size(), 2);
        EXPECT_EQ(degenerateIndices3.size(), 3);
        EXPECT_EQ(degenerateIndices4.size(), 0);
    }
    TEST(FaceUtilities_Tests, TriangleTrivialTriangulatedVertexIndices_GetPolygonIndicesFromTriangulation_TriangleTrivialContourIndices)
    {
        // Arrange
        const std::vector<unsigned int> vertexIndices = { 0, 1, 2 };
        const std::vector<unsigned int> triangleIndices = { 0 };

        // Act
        const auto triIndices = GetPolygonIndicesFromTriangulation(triangleIndices, vertexIndices);

        // Assert
        EXPECT_EQ(triIndices.size(), 3);
        EXPECT_EQ(triIndices[0], 0);
        EXPECT_EQ(triIndices[1], 1);
        EXPECT_EQ(triIndices[2], 2);
    }

    TEST(FaceUtilities_Tests, QuadTriangulatedVertexIndices_GetPolygonIndicesFromTriangulation_QuadContourIndices)
    {
	    // Arrange
        const std::vector<unsigned int> vertexIndices = {
            /* t0 */  0, 1, 2,    /* t1 */  0, 2, 3
        };
        const std::vector<unsigned int> triangleIndices = { 0, 1 };

        // Act
        const auto quadIndices = GetPolygonIndicesFromTriangulation(triangleIndices, vertexIndices);

        // Assert
        EXPECT_EQ(quadIndices.size(), 4);
        EXPECT_EQ(quadIndices[0], 1);
        EXPECT_EQ(quadIndices[1], 2);
        EXPECT_EQ(quadIndices[2], 3);
        EXPECT_EQ(quadIndices[3], 0);
    }

	TEST(FaceUtilities_Tests, PentagonTriangulatedVertexIndices_GetPolygonIndicesFromTriangulation_PentagonContourIndices)
    {
    	// Arrange
        const std::vector<unsigned int> vertexIndices = {
            /* t2 */  4, 0, 1,    /* t0 */  2, 3, 4,   /* t1 */  1, 2, 4
        };
        const std::vector<unsigned int> triangleIndices = { 0, 1, 2 };

    	// Act
        const auto pentagonIndices = GetPolygonIndicesFromTriangulation(triangleIndices, vertexIndices);

    	// Assert
        EXPECT_EQ(pentagonIndices.size(), 5);
        EXPECT_EQ(pentagonIndices[0], 0);
        EXPECT_EQ(pentagonIndices[1], 1);
        EXPECT_EQ(pentagonIndices[2], 2);
        EXPECT_EQ(pentagonIndices[3], 3);
        EXPECT_EQ(pentagonIndices[4], 4);
    }

} // Symplektis::UnitTests