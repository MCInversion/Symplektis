/*! \file Quaternion.h
*   \brief Declaration of various external methods for Quaternion
*
\verbatim
-------------------------------------------------------------------------------
created  : 6.5.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/
#pragma once

#include "Quaternion.h"

namespace Symplektis::GeometryKernel
{
	//-----------------------------------------------------------------------------
	/*! \brief Left scalar multiplication operator for Quaternion
	*   \param[in] scalar        Scalar value.
	*   \param[in] vec           Multiplied quaternion.
	*   \return New multiplied quaternion
	*
	*   \author M. Cavarga (MCInversion)
	*   \date  2.6.2021
	*/
	//-----------------------------------------------------------------------------
	Quaternion operator*(const double& scalar, const Quaternion& quat);

	//-----------------------------------------------------------------------------
	/*! \brief Quaternion product operator.\n
	*          see http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/code/index.htms
	*   \param[in] quat Quaternion(Qa).
	*   \param[in] quat Quaternion(Qb).
	*   \return new Quaternion Qc.
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   19.6.2021
	*
	*   Formula: Qc = Qa * Qb \n
	*/
	//-----------------------------------------------------------------------------
	Quaternion operator*(const Quaternion& quat1, const Quaternion& quat2);

	//-----------------------------------------------------------------------------
	/*! \brief Computes an orientation with given up and direction unit vectors.\n
	*          see https://www.euclideanspace.com/maths/algebra/vectors/lookat/index.htm
	*   \param[in] direction     Direction (unit) vector.
	*   \param[in] up            Up (unit) vector.
	*   \return orientation quaternion
	*
	*   \author M. Cavarga (MCInversion)
	*   \date  31.8.2021
	*/
	//-----------------------------------------------------------------------------
	Quaternion ComputeLookAtQuaternion(const Vector3& direction, const Vector3& up);

} // Symplektis::GeometryKernel