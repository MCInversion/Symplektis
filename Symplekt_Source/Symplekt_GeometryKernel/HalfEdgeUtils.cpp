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
#include "Edge.h"
#include "Vector3.h"
#include "Vector3Utils.h"
#include "Vertex.h"
#include "VertexNormal.h"
#include "Face.h"
#include "FaceUtils.h"

namespace Symplektis::GeometryKernel
{
	double ComputeOppositeAngleCotan(const HalfEdge& halfEdge, const ReferencedMeshGeometryData& meshData)
	{
		// boundary half-edges are supposed to return 0 angle
		if (halfEdge.IsBoundary())
			return 0.0;

		const Vector3 p0 = meshData.Vertices[meshData.HalfEdges[meshData.HalfEdges[halfEdge.NextHalfEdge().get()]
			.NextHalfEdge().get()].TailVertex().get()].Position();
		const Vector3 p1 = meshData.Vertices[halfEdge.TailVertex().get()].Position();
		const Vector3 p2 = meshData.Vertices[meshData.HalfEdges[halfEdge.NextHalfEdge().get()]
			.TailVertex().get()].Position();

		const Vector3 u = p1 - p0;
		const Vector3 v = p2 - p0;

		return DotProduct(u, v) / CrossProduct(u, v).GetLength();
	}

	Vector3 ComputeRotatedEdgeVector(const HalfEdge& halfEdge, const ReferencedMeshGeometryData& meshData)
	{
		// boundary half-edges are supposed to return zero rotated edge vector
		if (halfEdge.IsBoundary())
			return {};

		const Vector3 n = ComputeNormal(meshData.Faces[halfEdge.AdjacentFace().get()], meshData);
		const Vector3 p0 = meshData.Vertices[halfEdge.TailVertex().get()].Position();
		const Vector3 p1 = meshData.Vertices[meshData.HalfEdges[halfEdge.OppositeHalfEdge().get()]
			.TailVertex().get()].Position();

		return CrossProduct(n, p1 - p0);
	}
	
} // Symplektis::GeometryKernel