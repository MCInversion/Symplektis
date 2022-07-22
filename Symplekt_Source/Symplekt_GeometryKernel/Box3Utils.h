/*! \file Box3Utils.cpp          
*   \brief Declaration of various external methods for Box3
*
\verbatim
-------------------------------------------------------------------------------
created  : 3.6.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/
#pragma once

#include "Box3.h"

namespace Symplektis::GeometryKernel
{
	//-----------------------------------------------------------------------------
	/*! \brief Sets the vector coordinates to the coordinates of the given box's size
	*   \param[in] vector        Vector3 to be modified
	*   \param[in] box           Box3 to provide size
	*   \return Reference to box-sized vector
	*
	*   \author M. Cavarga (MCInversion)
	*   \date  3.6.2021
	*/
	//-----------------------------------------------------------------------------
	Vector3& SetVectorToBoxSize(Vector3& vector, const Box3& box);

	//-----------------------------------------------------------------------------
	/*! \brief Sets the vector coordinates to the coordinates of the given box's half size
	*   \param[in] vector        Vector3 to be modified
	*   \param[in] box           Box3 to provide size
	*   \return Reference to box-half-sized vector
	*
	*   \author M. Cavarga (MCInversion)
	*   \date  3.6.2021
	*/
	//-----------------------------------------------------------------------------
	Vector3& SetVectorToBoxHalfSize(Vector3& vector, const Box3& box);

	//-----------------------------------------------------------------------------
	/*! \brief Sets the vector coordinates to the coordinates of the given box's center
	*   \param[in] vector        Vector3 to be modified
	*   \param[in] box           Box3 to provide center
	*   \return Reference to vector set as box center
	*
	*   \author M. Cavarga (MCInversion)
	*   \date  3.6.2021
	*/
	//-----------------------------------------------------------------------------
	Vector3& SetVectorToBoxCenter(Vector3& vector, const Box3& box);

	//-----------------------------------------------------------------------------
	/*! \brief Tests if 3D vector is inside 3D bounding box
	*   \param[in] vector   Vector3 to be tested
	*   \param[in] box      Box3 to be tested
	*   \return true if vector is inside box
	*
	*   \author M. Cavarga (MCInversion)
	*   \date  3.6.2021
	*/
	//-----------------------------------------------------------------------------
	bool IsPointInsideBox(const Vector3& vector, const Box3& box);

} // Symplektis::GeometryKernel