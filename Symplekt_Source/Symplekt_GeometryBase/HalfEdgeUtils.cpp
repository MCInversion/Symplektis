/*! \file FaceUtils.cpp
*   \brief Implementation of computational utilities for Face-type objects of referenced mesh geometry objects
*
\verbatim
-------------------------------------------------------------------------------
created  : 23.9.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/

#include "HalfEdgeUtils.h"

#include "HalfEdge.h"
#include "Vector3.h"
#include "Vector3Utils.h"
#include "Vertex.h"
#include "FaceUtils.h"

namespace Symplektis::GeometryBase
{
	double ComputeOppositeAngleCotan(const HalfEdge& halfEdge)
	{
		// boundary half-edges are supposed to return 0 angle
		if (halfEdge.IsBoundary())
			return 0.0;

		const Vector3 p0 = halfEdge.NextHalfEdge()->NextHalfEdge()->TailVertex()->Position();
		const Vector3 p1 = halfEdge.TailVertex()->Position();
		const Vector3 p2 = halfEdge.NextHalfEdge()->TailVertex()->Position();

		const Vector3 u = p1 - p0;
		const Vector3 v = p2 - p0;

		return DotProduct(u, v) / CrossProduct(u, v).GetLength();
	}

	Vector3 ComputeRotatedEdgeVector(const HalfEdge& halfEdge)
	{
		// boundary half-edges are supposed to return zero rotated edge vector
		if (halfEdge.IsBoundary())
			return Vector3();

		const Vector3 n = ComputeNormal(*halfEdge.AdjacentFace());
		const Vector3 p0 = halfEdge.TailVertex()->Position();
		const Vector3 p1 = halfEdge.OppositeHalfEdge()->TailVertex()->Position();

		return CrossProduct(n, p1 - p0);
	}
	
} // Symplektis::GeometryBase