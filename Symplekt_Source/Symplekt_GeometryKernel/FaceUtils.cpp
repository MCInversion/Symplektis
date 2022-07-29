/*! \file FaceUtils.cpp
*   \brief Implementation of computational utilities for Face-type objects of referenced mesh geometry objects
*
\verbatim
-------------------------------------------------------------------------------
created  : 30.8.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/

#include "FaceUtils.h"

#include "Symplekt_UtilityGeneral/Assert.h"
#include "Symplekt_UtilityGeneral/ToleranceSettings.h"

#include "Face.h"
#include "HalfEdge.h"
#include "HalfEdgeUtils.h"
#include "Vertex.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector3Utils.h"
#include "QuaternionUtils.h"
#include "Poly2Tri_CDT.h"

#include <ctime>

namespace Symplektis::GeometryKernel
{
	Vector3 ComputeCircumcenter(const Face& tri, const ReferencedMeshGeometryData& meshData)
	{
		ASSERT(!meshData.Vertices.empty() && !meshData.HalfEdges.empty(), "ComputeCircumcenter: invalid meshData!");
		if (tri.GetTriangulation().size() != 1)
		{
			MSG_CHECK(false, "ComputeCircumcenter: Attempting to compute circumcenter of a non-triangle Face!\n");
			return {};
		}
		
		const Vector3 p0 = meshData.Vertices[meshData.HalfEdges[tri.HalfEdge().get()].TailVertex().get()].Position();
		const Vector3 p1 = meshData.Vertices[meshData.HalfEdges[meshData.HalfEdges[tri.HalfEdge().get()].NextHalfEdge().get()].TailVertex().get()].Position();
		const Vector3 n = ComputeRotatedEdgeVector(meshData.HalfEdges[tri.HalfEdge().get()], meshData);
		const double h = 0.5 * ComputeOppositeAngleCotan(meshData.HalfEdges[tri.HalfEdge().get()], meshData);

		return 0.5 * (p0 + p1) + h * n;
	}

	double ComputeArea(const Face& poly, const ReferencedMeshGeometryData& meshData)
	{
		ASSERT(!meshData.Vertices.empty(), "ComputeArea: invalid meshData!");
		double result = 0.0;
		for (const auto& triangle : poly.GetTriangulation())
		{
			const Vector3 v0 = meshData.Vertices[std::get<0>(triangle).get()].Position();
			const Vector3 v1 = meshData.Vertices[std::get<1>(triangle).get()].Position();
			const Vector3 v2 = meshData.Vertices[std::get<2>(triangle).get()].Position();

			result += ComputeTriangleArea(v0, v1, v2);
		}

		return result;
	}

	Vector3 ComputeNormal(const Face& poly, const ReferencedMeshGeometryData& meshData)
	{
		ASSERT(!meshData.Vertices.empty(), "ComputeNormal: invalid meshData!");
		Vector3 result;
		for (const auto& triangle : poly.GetTriangulation())
		{
			const Vector3 v0 = meshData.Vertices[std::get<0>(triangle).get()].Position();
			const Vector3 v1 = meshData.Vertices[std::get<1>(triangle).get()].Position();
			const Vector3 v2 = meshData.Vertices[std::get<2>(triangle).get()].Position();

			result += CrossProduct(v1 - v0, v2 - v0);
		}

		if (result.IsZero())
			return result;

		return result.Normalize();
	}

	Vector3 ComputeNormal(const std::vector<VertexIndex>& vertexIndices, const ReferencedMeshGeometryData& meshData)
	{
		ASSERT(meshData.Vertices.size() >= vertexIndices.size(), "ComputeNormal: invalid number of vertices.");
		Vector3 result;
		for (unsigned int i = 0; i < vertexIndices.size(); i++)
		{
			const auto iNext = (static_cast<size_t>(i) + 1) % vertexIndices.size();
			const Vector3 fromNext = meshData.Vertices[vertexIndices[i].get()].Position() - meshData.Vertices[vertexIndices[iNext].get()].Position();
			const Vector3 plusNext = meshData.Vertices[vertexIndices[i].get()].Position() + meshData.Vertices[vertexIndices[iNext].get()].Position();

			result.X() += fromNext.Y() * plusNext.Z();
			result.Y() += fromNext.Z() * plusNext.X();
			result.Z() += fromNext.X() * plusNext.Y();
		}

		if (result.IsZero())
			return result;

		return result.Normalize();
	}

	Vector3 ComputeBarycenter(const Face& poly, const ReferencedMeshGeometryData& meshData)
	{
		ASSERT(!meshData.Vertices.empty() && !meshData.HalfEdges.empty(), "ComputeBarycenter: invalid meshData!");
		unsigned int vertCounter = 0;
		Vector3 result;
		auto halfEdgeId = poly.HalfEdge();

		do
		{
			vertCounter++;
			result += meshData.Vertices[meshData.HalfEdges[halfEdgeId.get()].TailVertex().get()].Position();
			halfEdgeId = meshData.HalfEdges[halfEdgeId.get()].NextHalfEdge();
		}
		while (halfEdgeId != poly.HalfEdge());

		return result / vertCounter;
	}

	double ComputeTriangleArea(const Vector3& v0, const Vector3& v1, const Vector3& v2)
	{
		return CrossProduct(v1 - v0, v2 - v0).GetLength() * 0.5;
	}

    Vector3 ComputeTriangleNormal(const Vector3& v0, const Vector3& v1, const Vector3& v2)
    {
		Vector3 result = CrossProduct(v1 - v0, v2 - v0);

        if (result.IsZero())
            return result;

        return result.Normalize();
    }

	Vector3 ComputeVectorContourNormal(const std::vector<Vector3>& vertices)
	{
		Vector3 result;
		for (unsigned int i = 0; i < vertices.size(); i++)
		{
			const auto iNext = (static_cast<size_t>(i) + 1) % vertices.size();
			
			Vector3 fromNext = vertices[i] - vertices[iNext];
			Vector3 plusNext = vertices[i] + vertices[iNext];
			
			result.X() += fromNext.Y() * plusNext.Z();
			result.Y() += fromNext.Z() * plusNext.X();
			result.Z() += fromNext.X() * plusNext.Y();
		}
		
		if (result.IsZero())
			return result;

		return result.Normalize();
	}

	std::vector<Vector2> ComputeVectorContourProjectionsAlongNormal(const std::vector<Vector3>& vertices)
	{
		const Vector3 normal = ComputeVectorContourNormal(vertices);
		const Vector3 refPoint = vertices[0];

		return ComputeVectorContourProjectionsAlongNormal(vertices, normal, refPoint);
	}

	std::vector<Vector2> ComputeVectorContourProjectionsAlongNormal(const std::vector<Vector3>& vertices, const Vector3& normal, const Vector3& refPoint)
	{
		const auto quat = ComputeLookAtQuaternion(normal, Vector3(0.0, 0.0, 1.0));
		const auto projX = Vector3(0.0, 1.0, 0.0).ApplyQuaternion(quat);
		const auto projY = Vector3(0.0, 0.0, 1.0).ApplyQuaternion(quat);

		std::vector<Vector2> projections{};
		projections.reserve(vertices.size());
		for (const auto& vert : vertices)
		{
			const Vector3 vec = vert - refPoint;
			projections.emplace_back(Vector2(vec.DotProduct(projX), vec.DotProduct(projY)));
		}

		return projections;
	}

	std::vector<Vector2> ComputeProjectionsAlongNormal(const std::vector<VertexIndex>& vertexIndices, const ReferencedMeshGeometryData& meshData)
	{
		ASSERT(meshData.Vertices.size() >= vertexIndices.size(), "ComputeProjectionsAlongNormal: invalid number of vertices.");
		const Vector3 normal = ComputeNormal(vertexIndices, meshData);
		const Vector3 refPoint = meshData.Vertices[vertexIndices[0].get()].Position();

		return ComputeProjectionsAlongNormal(vertexIndices, normal, refPoint, meshData);
	}

	std::vector<Vector2> ComputeProjectionsAlongNormal(const std::vector<VertexIndex>& vertexIndices, const Vector3& normal, const Vector3& refPoint, const ReferencedMeshGeometryData& meshData)
	{
		ASSERT(meshData.Vertices.size() >= vertexIndices.size(), "ComputeProjectionsAlongNormal: invalid number of vertices.");
		const auto quat = ComputeLookAtQuaternion(normal, Vector3(0.0, 0.0, 1.0));
		const auto projX = Vector3(0.0, 1.0, 0.0).ApplyQuaternion(quat);
		const auto projY = Vector3(0.0, 0.0, 1.0).ApplyQuaternion(quat);

		std::vector<Vector2> projections{};
		projections.reserve(vertexIndices.size());
		for (const auto& vertId : vertexIndices)
		{
			const Vector3 vec = meshData.Vertices[vertId.get()].Position() - refPoint;
			projections.emplace_back(Vector2(vec.DotProduct(projX), vec.DotProduct(projY)));
		}

		return projections;
	}

	std::pair<TriangulationFaceIndices, TriangulationVertexIndices>	ConstructFaceTriangulationFromVertices(
		const std::vector<unsigned int>& vertexIdTuple, unsigned int& faceIndex,
		const std::vector<Vector3>& vertexData)
	{
		TriangulationFaceIndices triangulationFaceIds;
		TriangulationVertexIndices triangulationVertexIds;

		if (vertexIdTuple.size() < 3) // degenerate (single-line or single-point) Face
		{
			MSG_CHECK(false, "ConstructFaceTriangulationFromVertices: Attempting to triangulate a Face with < 3 vertices!\n");
			return { triangulationFaceIds, triangulationVertexIds };
		}

		if (vertexIdTuple.size() == 3) // triangle (trivial)
		{
			triangulationFaceIds = { faceIndex++ };
			triangulationVertexIds = { vertexIdTuple[0], vertexIdTuple[1], vertexIdTuple[2] };
			
			return { triangulationFaceIds, triangulationVertexIds };
		}

		if (vertexIdTuple.size() == 4) // quad: v0 v1 v2 v3
		{
			triangulationFaceIds = { faceIndex++, faceIndex++ };
			
			const Vector3 e1 = vertexData[vertexIdTuple[1]] - vertexData[vertexIdTuple[0]];
			const Vector3 e2 = vertexData[vertexIdTuple[2]] - vertexData[vertexIdTuple[0]];
			const Vector3 e3 = vertexData[vertexIdTuple[3]] - vertexData[vertexIdTuple[0]];
			const Vector3 c12 = CrossProduct(e1, e2);
			const Vector3 c13 = CrossProduct(e1, e3);
			const Vector3 c23 = CrossProduct(e2, e3);

			const double tol = Util::GetProductTolerance();

			if (c12.GetLengthSquared() < tol)
			{
				// collinearity detected between vertices 0, 1, and 2
				if (DotProduct(e1, e2) > 0.0)
				{
					if (e2.GetLengthSquared() < e1.GetLengthSquared())
					{
						/* [v0 v2 v1]  */
						triangulationVertexIds = {
							vertexIdTuple[0], vertexIdTuple[2], vertexIdTuple[3],
							vertexIdTuple[2], vertexIdTuple[1], vertexIdTuple[3]
						};
						return { triangulationFaceIds, triangulationVertexIds };						
					}

					/* [v0 v1 v2]  */
					triangulationVertexIds = {
						vertexIdTuple[0], vertexIdTuple[1], vertexIdTuple[3],
						vertexIdTuple[1], vertexIdTuple[2], vertexIdTuple[3]
					};
					return { triangulationFaceIds, triangulationVertexIds };
				}

				/* [v2 v0 v1]  */
				triangulationVertexIds = {
					vertexIdTuple[2], vertexIdTuple[0], vertexIdTuple[3],
					vertexIdTuple[0], vertexIdTuple[1], vertexIdTuple[3]
				};
				return { triangulationFaceIds, triangulationVertexIds };
			}

			if (c13.GetLengthSquared() < tol)
			{
				// collinearity detected between vertices 0, 1, and 3
				if (DotProduct(e1, e3) > 0.0)
				{
					if (e3.GetLengthSquared() < e1.GetLengthSquared())
					{
						/* [v0 v3 v1]  */
						triangulationVertexIds = {
							vertexIdTuple[0], vertexIdTuple[3], vertexIdTuple[2],
							vertexIdTuple[3], vertexIdTuple[1], vertexIdTuple[2]
						};
						return { triangulationFaceIds, triangulationVertexIds };						
					}

					/* [v0 v1 v3]  */
					triangulationVertexIds = {
						vertexIdTuple[0], vertexIdTuple[1], vertexIdTuple[2],
						vertexIdTuple[1], vertexIdTuple[3], vertexIdTuple[2]
					};
					return { triangulationFaceIds, triangulationVertexIds };
				}

				/* [v3 v0 v1]  */
				triangulationVertexIds = {
					vertexIdTuple[0], vertexIdTuple[2], vertexIdTuple[3],
					vertexIdTuple[0], vertexIdTuple[1], vertexIdTuple[2]
				};
				return { triangulationFaceIds, triangulationVertexIds };
			}

			if (c23.GetLengthSquared() < tol)
			{
				// collinearity detected between vertices 0, 2, and 3
				if (DotProduct(e2, e3) > 0.0)
				{
					if (e3.GetLengthSquared() < e2.GetLengthSquared())
					{
						/* [v0 v3 v2]  */
						triangulationVertexIds = {
							vertexIdTuple[0], vertexIdTuple[1], vertexIdTuple[3],
							vertexIdTuple[1], vertexIdTuple[2], vertexIdTuple[3]
						};
						return { triangulationFaceIds, triangulationVertexIds };						
					}

					/* [v0 v2 v3]  */
					triangulationVertexIds = {
						vertexIdTuple[0], vertexIdTuple[2], vertexIdTuple[1],
						vertexIdTuple[2], vertexIdTuple[3], vertexIdTuple[1]
					};
					return { triangulationFaceIds, triangulationVertexIds };
				}

				/* [v3 v0 v2]  */
				triangulationVertexIds = {
					vertexIdTuple[3], vertexIdTuple[0], vertexIdTuple[1],
					vertexIdTuple[0], vertexIdTuple[2], vertexIdTuple[1]
				};
				return { triangulationFaceIds, triangulationVertexIds };
			}
			
			if (DotProduct(c12, c23) < 0.0)
			{
				triangulationVertexIds = {
					vertexIdTuple[0], vertexIdTuple[1], vertexIdTuple[3],
					vertexIdTuple[1], vertexIdTuple[2], vertexIdTuple[3]
				};
				return { triangulationFaceIds, triangulationVertexIds };
			}

			triangulationVertexIds = {
				vertexIdTuple[0], vertexIdTuple[1], vertexIdTuple[2],
				vertexIdTuple[0], vertexIdTuple[2], vertexIdTuple[3]
			};

			return { triangulationFaceIds, triangulationVertexIds };
		}

		// ============= initializing a "penta-or-more-gon" ((n > 4)-gon): =============
		// ============= Note: using Poly2Tri util library for triangulation ===========
	
		const auto projections = ComputeVectorContourProjectionsAlongNormal(vertexData);
		Poly2Tri::CDT* constrainedDelaunay = nullptr;

		// poly2tri doesn't work well with duplicate or collinear points. it is possible that it will fail on certain inputs
		// if it fails, we retry with increasingly higher jitter. it usually works on first retry
		// if it doesn't work with 42 retries, there is no hope
		std::vector<Poly2Tri::Point> points{};

		std::srand(static_cast<unsigned int>(std::time(nullptr)));
		for (unsigned int triesUtilized = 0; triesUtilized < TRIANG_MAX_TRIES; triesUtilized++)
		{
			points.clear();
			points.reserve(projections.size());
			for (unsigned int i = 0; i < projections.size(); i++)
			{
				auto pt = Poly2Tri::Point(
					projections[i].X() + (triesUtilized * (static_cast<double>(std::rand()) / RAND_MAX * 0.001 - 0.0005)),
					projections[i].Y() + (triesUtilized * (static_cast<double>(std::rand()) / RAND_MAX * 0.001 - 0.0005))
				);
				pt._vIdx = i;
				points.emplace_back(pt);
			}

			try
			{
				std::vector<Poly2Tri::Point*> contour{};
				contour.reserve(points.size());
				for (auto& pt : points)
					contour.emplace_back(&pt);

				constrainedDelaunay = new Poly2Tri::CDT(contour);
				if (constrainedDelaunay == nullptr)
				{
					throw(std::runtime_error("ConstructFaceTriangulationFromVertices: Failed triangulation! constrainedDelaunay == nullptr\n"));
				}
				constrainedDelaunay->Triangulate();
				break; // assuming it all goes well
			}
			catch (const std::runtime_error& err)
			{
				std::string msg = std::string(err.what()) +
					"\nConstructFaceTriangulationFromVertices: Triangulation was not able to finish with " +
					std::to_string(TRIANG_MAX_TRIES) + " tries!\n";
				MSG_CHECK(false, msg);
				continue;
			}
		}

        if (constrainedDelaunay == nullptr)
        {
            throw(std::runtime_error("ConstructFaceTriangulationFromVertices: Failed triangulation! constrainedDelaunay == nullptr\n"));
        }
		auto triangles = constrainedDelaunay->GetTriangles();

		triangulationVertexIds.reserve(triangles.size());
		triangulationFaceIds.reserve(triangles.size());
		for (const auto& tri : triangles)
		{
			for (int i = 0; i < 3; i++)
				triangulationVertexIds.emplace_back(vertexIdTuple[tri->GetPoint(i)->_vIdx]);
			triangulationFaceIds.emplace_back(faceIndex++);
		}

		delete constrainedDelaunay;
		
		return { triangulationFaceIds, triangulationVertexIds };
	}

	//-----------------------------------------------------------------------------
	/*! \brief Get indices of triangulated polygon's contour vertices from triangle vertex indices
	*   \param[in] triangles     vertex indices of polygon triangles
	*   \return polygon contour's vertex indices
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   3.10.2021
	*
	*/
	//-----------------------------------------------------------------------------
	static std::vector<unsigned int> GetPolygonIndicesFromTriangles(std::vector<std::vector<unsigned int>>&& triangles)
	{
		if (triangles.empty())
			return {};

		if (triangles.size() == 1)
			return triangles[0];

		std::vector<std::vector<unsigned int>> triangleEdgeVertIndices(3 * triangles.size());

		for (unsigned int i = 0; i < triangles.size(); i++)
		{
			triangleEdgeVertIndices[3 * static_cast<size_t>(i)    ] = { triangles[i][0], triangles[i][1] };
			triangleEdgeVertIndices[3 * static_cast<size_t>(i) + 1] = { triangles[i][1], triangles[i][2] };
			triangleEdgeVertIndices[3 * static_cast<size_t>(i) + 2] = { triangles[i][2], triangles[i][0] };
		}
		
		for (unsigned int i = 0; i < triangleEdgeVertIndices.size() - 1; i++) 
		{
			for (unsigned int j = i + 1; j < triangleEdgeVertIndices.size(); j++)
			{
				if ((triangleEdgeVertIndices[i][0] == triangleEdgeVertIndices[j][0] && triangleEdgeVertIndices[i][1] == triangleEdgeVertIndices[j][1]) ||
					(triangleEdgeVertIndices[i][0] == triangleEdgeVertIndices[j][1] && triangleEdgeVertIndices[i][1] == triangleEdgeVertIndices[j][0]))
				{
					triangleEdgeVertIndices.erase(triangleEdgeVertIndices.begin() + j);
					triangleEdgeVertIndices.erase(triangleEdgeVertIndices.begin() + i);
					i--;
					break;
				}
			}
		}

		std::vector polygonVertIndices = { triangleEdgeVertIndices[0][1] };
		auto edgeIdsSet = triangleEdgeVertIndices;
		edgeIdsSet.erase(edgeIdsSet.begin());

		for (unsigned int i = 1; i < triangleEdgeVertIndices.size(); i++)
		{
			for (unsigned int j = 0; j < edgeIdsSet.size(); j++) 
			{
				if (edgeIdsSet[j][0] == polygonVertIndices[polygonVertIndices.size() - 1])
				{
					polygonVertIndices.push_back(edgeIdsSet[j][1]);
					edgeIdsSet.erase(edgeIdsSet.begin() + j);
					break;
				}
			}
		}

		return polygonVertIndices;
	}

	std::vector<unsigned int> GetPolygonIndicesFromTriangulation(
		const TriangulationFaceIndices& triangleIndices, const std::vector<unsigned int>& vertexIndices)
	{
		if (vertexIndices.size() < 3)
			return vertexIndices;
		
		std::vector<std::vector<unsigned int>> triangles{ triangleIndices.size() };
		for (unsigned int i = 0; i < triangleIndices.size(); i++)
		{
			if (3 * static_cast<size_t>(triangleIndices[i]) + 2 >= vertexIndices.size())
				continue;
			
			triangles[i] = std::vector{
				vertexIndices[3 * static_cast<size_t>(triangleIndices[i])],
				vertexIndices[3 * static_cast<size_t>(triangleIndices[i]) + 1],
				vertexIndices[3 * static_cast<size_t>(triangleIndices[i]) + 2],
			};
		}
		
		return GetPolygonIndicesFromTriangles(std::move(triangles));
	}

	bool IsATriangle(const Face& face)
	{
		return face.GetTriangulation().size() == 1;
	}

	bool IsAQuadrilateral(const Face& face)
	{
		return face.GetTriangulation().size() == 2;
	}
} // Symplektis::GeometryKernel