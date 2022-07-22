/*! \file HalfEdgeUtils.h
*   \brief Computational utilities for HalfEdge-type objects of referenced mesh geometry objects
*
\verbatim
-------------------------------------------------------------------------------
created  : 23.9.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/
#pragma once

#include "GeometryHelperTypes.h"

namespace Symplektis::GeometryKernel
{
	// forward declarations
	class Vector3;
	class HalfEdge;
	
	//-----------------------------------------------------------------------------
	/*! \brief Computes the cotangent of angle opposite to this edge
	*   \return opposite angle cotangent
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   28.8.2021
	*/
	//-----------------------------------------------------------------------------
	[[nodiscard]] double ComputeOppositeAngleCotan(const HalfEdge& halfEdge);

	//-----------------------------------------------------------------------------
	/*! \brief Computes edge vector rotated by +PI/2
	*   \return perpendicular edge vector
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   28.8.2021
	*/
	//-----------------------------------------------------------------------------
	[[nodiscard]] Vector3 ComputeRotatedEdgeVector(const HalfEdge& halfEdge);
	
} // Symplektis::GeometryKernel