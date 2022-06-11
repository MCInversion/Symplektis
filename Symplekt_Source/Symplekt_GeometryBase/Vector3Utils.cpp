/*! \file Vector3Utils.cpp
*   \brief Implmentation of the external 3D vector utilities
*
\verbatim
-------------------------------------------------------------------------------
created  : 6.5.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/
#include "Vector3Utils.h"

#include <cmath>

namespace Symplektis::GeometryBase
{
	Vector3 operator*(const double& scalar, const Vector3& vec)
	{
		return vec * scalar;
	}

	double DotProduct(const Vector3& vec1, const Vector3& vec2)
	{
		return vec1.DotProduct(vec2);
	}

	Vector3 CrossProduct(const Vector3& vec1, const Vector3& vec2)
	{
		Vector3 result(vec1);
		result.CrossProduct(vec2);
		return result;
	}

	Vector3 LinearInterpolate(const Vector3& vec1, const Vector3& vec2, const double& param)
	{
		Vector3 result(vec1);
		return result.LinearInterpolate(vec2, param);
	}

	Vector3 ComputePerpendicularUnitVector(const Vector3& vec)
	{
		if (std::fabs(vec.X()) < std::fabs(vec.Y()) && std::fabs(vec.X()) < std::fabs(vec.Z()))
		{
			return Vector3(1.0, 0.0, 0.0).CrossProduct(vec).Normalize();
		}
		else if (std::fabs(vec.Y()) < std::fabs(vec.Z()))
		{
			return Vector3(0.0, 1.0, 0.0).CrossProduct(vec).Normalize();
		}

		return Vector3(0.0, 0.0, 1.0).CrossProduct(vec).Normalize();
	}

} // Symplektis::GeometryBase