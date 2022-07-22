/*! \file Vector2Utils.h
*   \brief Declaration of various external methods for Vector2
*
\verbatim
-------------------------------------------------------------------------------
created  : 6.5.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/
#pragma once

#include "Vector2.h"

namespace Symplektis::GeometryKernel
{

	//-----------------------------------------------------------------------------
	/*! \brief Left scalar multiplication operator for Vector2
	*   \param[in] scalar        Scalar value.
	*   \param[in] vec           Multiplied vector.
	*   \return Reference to the multiplied vector
	*
	*   \author M. Cavarga (MCInversion)
	*   \date  2.6.2021
	*/
	//-----------------------------------------------------------------------------
	Vector2 operator*(const double& scalar, const Vector2& vec);

	//-----------------------------------------------------------------------------
	/*! \brief External dot product for Vector2's
	*   \param[in] vec1          first Vector2
	*   \param[in] vec2          second Vector2
	*   \return double value of dot product
	*
	*   \author M. Cavarga (MCInversion)
	*   \date  3.6.2021
	*/
	//-----------------------------------------------------------------------------
	double DotProduct(const Vector2& vec1, const Vector2& vec2);

	//-----------------------------------------------------------------------------
	/*! \brief External cross product for Vector2's
	*   \param[in] vec1          first Vector2
	*   \param[in] vec2          second Vector2
	*   \return New multiplied vector
	*
	*   \author M. Cavarga (MCInversion)
	*   \date  3.6.2021
	*/
	//-----------------------------------------------------------------------------
	double CrossProduct(const Vector2& vec1, const Vector2& vec2);

	//-----------------------------------------------------------------------------
	/*! \brief Computes a linear interpolation between vector vec1, and vec2.\n
	*          The interpolation parameter is not required to be within [0,1]!
	*   \param[in] vec1    Vector2
	*   \param[in] vec2    Vector2
	*   \param[in] param   interpolation parameter, for convex hull choose param from [0,1]
	*   \return    interpolated Vector2
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   11.6.2021
	*/
	//-----------------------------------------------------------------------------
	Vector2 LinearInterpolate(const Vector2& vec1, const Vector2& vec2, const double& param);

} // Symplektis::GeometryKernel