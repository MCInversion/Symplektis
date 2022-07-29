/*! \file FaceUtils.h
*   \brief Computational utilities for Face-type objects of referenced mesh geometry objects
*
\verbatim
-------------------------------------------------------------------------------
created  : 30.8.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/
#pragma once

#include "GeometryHelperTypes.h"
#include "MeshGeometryDataTypes.h"

namespace Symplektis::GeometryKernel
{
	// forward declarations
	class Face;
	class Vector2;
	class Vector3;

	//
	// ==============  Independent from any geometry representation (e.g.: referenced or buffer mesh geometry) ===========
	//

	//-----------------------------------------------------------------------------
	/*! \brief Computes area of a general triangle
	*   \param[in] v0      first triangle vertex
	*   \param[in] v1      second triangle vertex
	*   \param[in] v2      third triangle vertex
	*   \return area
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   30.8.2021
	*/
	//-----------------------------------------------------------------------------
	[[nodiscard]] double ComputeTriangleArea(const Vector3& v0, const Vector3& v1, const Vector3& v2);

	//-----------------------------------------------------------------------------
	/*! \brief Computes the unit normal of a general triangle
	*   \param[in] v0      first triangle vertex
	*   \param[in] v1      second triangle vertex
	*   \param[in] v2      third triangle vertex
	*   \return normal
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   1.10.2021
	*/
	//-----------------------------------------------------------------------------
	[[nodiscard]] Vector3 ComputeTriangleNormal(const Vector3& v0, const Vector3& v1, const Vector3& v2);

	//-----------------------------------------------------------------------------
	/*! \brief Computes normal to a general polygon
	*   \param[in] vertices        Polygon contour Vector3 list
	*   \return polygon normal
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   30.9.2021
	*/
	//-----------------------------------------------------------------------------
	[[nodiscard]] Vector3 ComputeVectorContourNormal(const std::vector<Vector3>& vertices);

	//-----------------------------------------------------------------------------
	/*! \brief Computes projections along normal of a general polygon
	*   \param[in] vertices        Polygon contour Vector3 list
	*   \return list of 2D projections along normal
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   30.9.2021
	*/
	//-----------------------------------------------------------------------------
	[[nodiscard]] std::vector<Vector2> ComputeVectorContourProjectionsAlongNormal(const std::vector<Vector3>& vertices);

	//-----------------------------------------------------------------------------
	/*! \brief Computes projections along normal of a general polygon
	*   \param[in] vertices        Polygon contour Vector3 list
	*   \param[in] normal          Polygon normal (Vector3)
	*   \param[in] refPoint        reference point (Vector3)
	*   \return list of 2D projections along normal
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   30.9.2021
	*/
	//-----------------------------------------------------------------------------
	[[nodiscard]] std::vector<Vector2> ComputeVectorContourProjectionsAlongNormal(const std::vector<Vector3>& vertices, const Vector3& normal, const Vector3& refPoint);

	/// \brief triangulation helpers for BufferMeshGeometry polygon triangulation
	using TriangulationFaceIndices = std::vector<unsigned int>;
	using TriangulationVertexIndices = std::vector<unsigned int>;

	/// \brief maximum (magic) number of triangulation attempts
	constexpr unsigned int TRIANG_MAX_TRIES = 42;

	//-----------------------------------------------------------------------------
	/*! \brief Initialize (triangulate) from vertices.
	*   \param[in] vertexIdTuple   vertex indices to be initialized from
	*   \param[in] faceIndex       index of the previous triangulated face (will be incremented by this method)
	*   \param[in] vertexData      Vector3 buffer of vertex data
	*   \return pair { triangulation face indices (individual triangle ids) , triangulation vertex indices (ids of vertices for triangles) }
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   30.9.2021
	*
	*   This function uses Poly2Tri library for triangulating n-gons with n > 4
	*/
	//-----------------------------------------------------------------------------
	[[nodiscard]] std::pair<TriangulationFaceIndices, TriangulationVertexIndices> ConstructFaceTriangulationFromVertices(
		const std::vector<unsigned int>& vertexIdTuple, unsigned int& faceIndex,
		const std::vector<Vector3>& vertexData);

	//-----------------------------------------------------------------------------
	/*! \brief Get vertex indices of polygon contour from triangulation face indices and vertex indices
	*   \param[in] triangleIndices     indices of triangles in a polygon
	*   \param[in] vertexIndices   vertex indices buffer
	*   \return polygon contour's vertex indices
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   3.10.2021
	*
	*/
	//-----------------------------------------------------------------------------
	[[nodiscard]] std::vector<unsigned int> GetPolygonIndicesFromTriangulation(
		const TriangulationFaceIndices& triangleIndices, const std::vector<unsigned int>& vertexIndices);

	//
	// ==============  Requires a vector of vertices to construct iterator instances ===========
	//
	
	//-----------------------------------------------------------------------------
	/*! \brief Computes normal to a general polygon
	*   \param[in] vertexIndices     Polygon contour Vertex list.
	*	\param[in] meshData          data object containing mesh elements.
	*   \return polygon normal
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   30.8.2021
	*/
	//-----------------------------------------------------------------------------
	[[nodiscard]] Vector3 ComputeNormal(const std::vector<VertexIndex>& vertexIndices, const ReferencedMeshGeometryData& meshData);

	//-----------------------------------------------------------------------------
	/*! \brief Computes projections along normal of a general polygon
	*   \param[in] vertexIndices        Polygon contour Vertex list
	*	\param[in] meshData             data object containing mesh elements.
	*   \return list of 2D projections along normal
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   30.8.2021
	*/
	//-----------------------------------------------------------------------------
	[[nodiscard]] std::vector<Vector2> ComputeProjectionsAlongNormal(
		const std::vector<VertexIndex>& vertexIndices, const ReferencedMeshGeometryData& meshData);

	//-----------------------------------------------------------------------------
	/*! \brief Computes projections along normal of a general polygon
	*   \param[in] vertexIndices     Polygon contour Vertex list
	*   \param[in] normal            Polygon normal (Vector3)
	*   \param[in] refPoint          reference point (Vector3)
	*	\param[in] meshData          data object containing mesh elements.
	*   \return list of 2D projections along normal
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   30.8.2021
	*/
	//-----------------------------------------------------------------------------
	[[nodiscard]] std::vector<Vector2> ComputeProjectionsAlongNormal(
		const std::vector<VertexIndex>& vertexIndices, 
		const Vector3& normal, 
		const Vector3& refPoint, 
		const ReferencedMeshGeometryData& meshData);

    //
    // ==============  Requires a valid geometry representation data (referenced mesh geometry) ===========
    //

	//-----------------------------------------------------------------------------
	/*! \brief Computes the barycenter of a general polygon
	*   \param[in] poly        polygon to have its barycenter computed.
	*	\param[in] meshData    data object containing mesh elements.
	*   \return polygon barycenter
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   30.8.2021
	*/
	//-----------------------------------------------------------------------------
	[[nodiscard]] Vector3 ComputeBarycenter(const Face& poly, const ReferencedMeshGeometryData& meshData);

	//-----------------------------------------------------------------------------
	/*! \brief Computes the circumcenter of a triangle Face
	*   \param[in] tri         polygon to have its circumcenter computed.
	*	\param[in] meshData    data object containing mesh elements.
	*   \return triangle circumcenter
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   30.8.2021
	*/
	//-----------------------------------------------------------------------------
	[[nodiscard]] Vector3 ComputeCircumcenter(const Face& tri, const ReferencedMeshGeometryData& meshData);

	//-----------------------------------------------------------------------------
	/*! \brief Computes area of a general polygon
	*   \param[in] poly     polygon to have its area computed.
	*	\param[in] meshData    data object containing mesh elements.
	*   \return area
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   30.8.2021
	*/
	//-----------------------------------------------------------------------------
	[[nodiscard]] double ComputeArea(const Face& poly, const ReferencedMeshGeometryData& meshData);

	//-----------------------------------------------------------------------------
	/*! \brief Computes normal to a general polygon
	*   \param[in] poly        polygon to have its normal computed.
	*	\param[in] meshData    data object containing mesh elements.
	*   \return polygon normal
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   30.8.2021
	*/
	//-----------------------------------------------------------------------------
	[[nodiscard]] Vector3 ComputeNormal(const Face& poly, const ReferencedMeshGeometryData& meshData);

	//-----------------------------------------------------------------------------
	/*! \brief Evaluates whether input face is a triangle face.
	*   \param[in] face      Face to be evaluated.
	*   \return true if the number of triangulations of the input face is 1.
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   29.7.2022
	*/
	//-----------------------------------------------------------------------------
	[[nodiscard]] bool IsATriangle(const Face& face);

	//-----------------------------------------------------------------------------
	/*! \brief Evaluates whether input face is a quadrilateral face.
	*   \param[in] face      Face to be evaluated.
	*   \return true if the number of triangulations of the input face is 2.
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   29.7.2022
	*/
	//-----------------------------------------------------------------------------
	[[nodiscard]] bool IsAQuadrilateral(const Face& face);

} // Symplektis::GeometryKernel