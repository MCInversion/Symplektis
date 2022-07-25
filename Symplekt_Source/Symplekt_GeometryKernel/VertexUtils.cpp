/*! \file VertexUtils.cpp
*   \brief Implementation of computational utilities for Vertex-type objects of referenced mesh geometry objects
*
\verbatim
-------------------------------------------------------------------------------
created  : 23.9.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/

#include "VertexUtils.h"

#include "Vertex.h"
#include "Vector3.h"
#include "HalfEdge.h"
#include "FaceUtils.h"

namespace Symplektis::GeometryKernel
{

	Vector3 ComputeVertexNormal(const Vertex& vertex, const ReferencedMeshGeometryData& meshData)
	{
		Vector3 result{};
		auto he = vertex.HalfEdge();

		do
		{   // 1-ring neighborhood iteration
			if (!meshData.HalfEdges[he.get()].IsBoundary())
			{
				result += ComputeNormal(meshData.Faces[meshData.HalfEdges[he.get()].AdjacentFace().get()], meshData);
			}
			he = meshData.HalfEdges[meshData.HalfEdges[he.get()].OppositeHalfEdge().get()].NextHalfEdge();
		} while (he != vertex.HalfEdge());

		return result.Normalize();
	}

	double ComputeDualNeighborhoodArea(const Vertex& vertex, const ReferencedMeshGeometryData& meshData)
	{
		double result = 0.0;
		auto he = vertex.HalfEdge();

		do
		{   // 1-ring neighborhood iteration
			if (!meshData.HalfEdges[he.get()].IsBoundary())
			{
				result += ComputeArea(meshData.Faces[meshData.HalfEdges[he.get()].AdjacentFace().get()], meshData);
			}
			he = meshData.HalfEdges[meshData.HalfEdges[he.get()].OppositeHalfEdge().get()].NextHalfEdge();
		} while (he != vertex.HalfEdge());

		return result / 3.0;
	}

	unsigned int GetValence(const Vertex& vertex, const ReferencedMeshGeometryData& meshData)
	{
		unsigned int result = 0;
		auto he = vertex.HalfEdge();

		do
		{   // 1-ring neighborhood iteration
			result++;
			he = meshData.HalfEdges[meshData.HalfEdges[he.get()].OppositeHalfEdge().get()].NextHalfEdge();
		} while (he != vertex.HalfEdge());

		return result;
	}

} // Symplektis::GeometryKernel