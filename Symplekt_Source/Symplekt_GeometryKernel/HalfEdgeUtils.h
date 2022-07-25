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
#include "MeshGeometryDataTypes.h"

namespace Symplektis::GeometryKernel
{
	// forward declarations
	class Vector3;
	class HalfEdge;
	
	//-----------------------------------------------------------------------------
	/*! \brief Computes the cotangent of angle opposite to this edge
	*   \param[in] halfEdge      half edge whose opposite angle cotangent is to be computed.
	*	\param[in] meshData      data object containing mesh elements.
	*   \return opposite angle cotangent
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   28.8.2021
	*/
	//-----------------------------------------------------------------------------
	[[nodiscard]] double ComputeOppositeAngleCotan(const HalfEdge& halfEdge, const ReferencedMeshGeometryData& meshData);

	//-----------------------------------------------------------------------------
	/*! \brief Computes edge vector rotated by +PI/2
	*   \param[in] halfEdge      half edge whose rotated edge vector is to be computed.
	*	\param[in] meshData      data object containing mesh elements.
	*   \return perpendicular edge vector
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   28.8.2021
	*/
	//-----------------------------------------------------------------------------
	[[nodiscard]] Vector3 ComputeRotatedEdgeVector(const HalfEdge& halfEdge, const ReferencedMeshGeometryData& meshData);
	
} // Symplektis::GeometryKernel