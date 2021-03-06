/*! \file VertexUtils.h
*   \brief Computational utilities for Vertex-type objects of referenced mesh geometry objects
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
	class Vertex;
	
	//-----------------------------------------------------------------------------
	/*! \brief Computes unit normal vector from adjacent face normals
	*   \param[in] vertex         vertex at which the normal is to be computed.
	*	\param[in] meshData       data object containing mesh elements.
	*   \return normalized Vector3 normal
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   29.8.2021
	*/
	//-----------------------------------------------------------------------------
	[[nodiscard]] Vector3 ComputeVertexNormal(const Vertex& vertex, const ReferencedMeshGeometryData& meshData);

	//-----------------------------------------------------------------------------
	/*! \brief Computes area of the barycentric dual neighborhood in this Vertex's 1-ring neighborhood
	 *  \param[in] vertex        Vertex to compute dual neighborhood area of.
	 *	\param[in] meshData      data object containing mesh elements.
	*   \return neighborhood area
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   29.8.2021
	*/
	//-----------------------------------------------------------------------------
	[[nodiscard]] double ComputeDualNeighborhoodArea(const Vertex& vertex, const ReferencedMeshGeometryData& meshData);

	//-----------------------------------------------------------------------------
	/*! \brief Computes this Vertex's valence (number of vertices connected to this Vertex)\n
	 *         in its 1-ring neighborhood
	 *  \param[in] vertex         Vertex to compute valence of.
	 *	\param[in] meshData       data object containing mesh elements.
	 *  \return valence of this vertex
	 *
	 *  \author M. Cavarga (MCInversion)
	 *  \date   29.8.2021
	 */
	 //-----------------------------------------------------------------------------
	[[nodiscard]] unsigned int GetValence(const Vertex& vertex, const ReferencedMeshGeometryData& meshData);
	
} // Symplektis::GeometryKernel