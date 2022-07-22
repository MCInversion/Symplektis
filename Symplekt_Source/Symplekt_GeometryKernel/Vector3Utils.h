/*! \file Vector3Utils.h
*   \brief Declaration of various external methods for Vector3
*
\verbatim
-------------------------------------------------------------------------------
created  : 6.5.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/
#pragma once

#include "Vector3.h"

namespace Symplektis::GeometryKernel
{
	//-----------------------------------------------------------------------------
	/*! \brief Left scalar multiplication operator for Vector3
	*   \param[in] scalar        Scalar value.
	*   \param[in] vec           Multiplied vector.
	*   \return new multiplied vector
	*
	*   \author M. Cavarga (MCInversion)
	*   \date  2.6.2021
	*/
	//-----------------------------------------------------------------------------
	Vector3 operator*(const double& scalar, const Vector3& vec);

	//-----------------------------------------------------------------------------
	/*! \brief External dot product for Vector3's
	*   \param[in] vec1          first Vector3
	*   \param[in] vec2          second Vector3
	*   \return double value of dot product
	*
	*   \author M. Cavarga (MCInversion)
	*   \date  3.6.2021
	*/
	//-----------------------------------------------------------------------------
	double DotProduct(const Vector3& vec1, const Vector3& vec2);

	//-----------------------------------------------------------------------------
	/*! \brief External cross product for Vector3's
	*   \param[in] vec1          first Vector3
	*   \param[in] vec2          second Vector3
	*   \return New multiplied vector
	*
	*   \author M. Cavarga (MCInversion)
	*   \date  3.6.2021
	*/
	//-----------------------------------------------------------------------------
	Vector3 CrossProduct(const Vector3& vec1, const Vector3& vec2);

	//-----------------------------------------------------------------------------
	/*! \brief Computes a linear interpolation between vector vec1, and vec2.\n
	*          The interpolation parameter is not required to be within [0,1]!
	*   \param[in] vec1    Vector3
	*   \param[in] vec2    Vector3
	*   \param[in] param   interpolation parameter, for convex hull choose param from [0,1]
	*   \return    interpolated Vector3
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   11.6.2021
	*/
	//-----------------------------------------------------------------------------
	Vector3 LinearInterpolate(const Vector3& vec1, const Vector3& vec2, const double& param);

	//-----------------------------------------------------------------------------
	/*! \brief Computes a unit vector perpendicular to vec, such that it is a +Pi/2 rotation of \n
	*          the direction of vec's projection in the x,y-plane.
	*   \param[in] vec    Vector3
	*   \return    unit Vector3 perpendicular to vec
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   31.8.2021
	*/
	//-----------------------------------------------------------------------------
	Vector3 ComputePerpendicularUnitVector(const Vector3& vec);

} // Symplektis::GeometryKernel