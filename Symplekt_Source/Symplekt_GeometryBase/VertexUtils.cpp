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

namespace Symplektis::GeometryBase
{

	Vector3 ComputeVertexNormal(const Vertex& vertex)
	{
		Vector3 result{};
		HalfEdgeConstIterator he = vertex.HalfEdge();

		do
		{   // 1-ring neighborhood iteration
			if (!he->IsBoundary()) result += ComputeNormal(*he->AdjacentFace());
			he = he->OppositeHalfEdge()->NextHalfEdge();
		} while (he != vertex.HalfEdge());

		return result.Normalize();
	}

	double ComputeDualNeighborhoodArea(const Vertex& vertex)
	{
		double result = 0.0;
		HalfEdgeConstIterator he = vertex.HalfEdge();

		do
		{   // 1-ring neighborhood iteration
			if (!he->IsBoundary()) result += ComputeArea(*he->AdjacentFace());
			he = he->OppositeHalfEdge()->NextHalfEdge();
		} while (he != vertex.HalfEdge());

		return result / 3.0;
	}

	unsigned int GetValence(const Vertex& vertex)
	{
		unsigned int result = 0;
		HalfEdgeConstIterator he = vertex.HalfEdge();

		do
		{   // 1-ring neighborhood iteration
			result++;
			he = he->OppositeHalfEdge()->NextHalfEdge();
		} while (he != vertex.HalfEdge());

		return result;
	}

} // Symplektis::GeometryBase