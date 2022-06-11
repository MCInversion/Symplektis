/*! \file Quaternion.cpp
*   \brief Implmentation of the external Quaternion utilities
*
\verbatim
-------------------------------------------------------------------------------
created  : 6.5.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/
#include "QuaternionUtils.h"

#include "Vector3.h"
#include "Vector3Utils.h"
#include "Matrix3.h"

#include "../Symplekt_UtilityGeneral/ToleranceSettings.h"

#include <cmath>

namespace Symplektis::GeometryBase
{

	Quaternion operator*(const double& scalar, const Quaternion& quat)
	{
		Quaternion result(quat);
		result *= scalar;
		return result;
	}

	Quaternion operator*(const Quaternion& quat1, const Quaternion& quat2)
	{
		Quaternion result(quat1);
		result *= quat2;
		return result;
	}

	Quaternion ComputeLookAtQuaternion(const Vector3& direction, const Vector3& up)
	{
		Vector3 dirVect{ direction }, upVect{ up };

		if (!dirVect.IsNormalized())
			dirVect.Normalize();

		if (!upVect.IsNormalized())
			upVect.Normalize();

		// in case dirVect is collinear with upVect (CrossProduct(upVect, dirVect) == 0.0)
		if (std::fabs(dirVect.DotProduct(upVect)) >= 1.0 - Symplektis::Util::GetProductTolerance())
		{
			upVect = ComputePerpendicularUnitVector(dirVect);
		}

		auto crossProd = CrossProduct(upVect, dirVect).Normalize();
		auto pseudoUp = CrossProduct(dirVect, crossProd).Normalize();

		Matrix3 transform{
			dirVect.X(), crossProd.X(), pseudoUp.X(),
			dirVect.Y(), crossProd.Y(), pseudoUp.Y(),
			dirVect.Z(), crossProd.Z(), pseudoUp.Z()
		};
		return Quaternion(transform);
	}

} // Symplektis::GeometryBase