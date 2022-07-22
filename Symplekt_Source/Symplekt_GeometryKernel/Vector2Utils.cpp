/*! \file Vector2Utils.cpp
*   \brief Implmentation of the external 2D vector utilities
*
\verbatim
-------------------------------------------------------------------------------
created  : 6.5.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/
#include "Vector2Utils.h"

namespace Symplektis::GeometryKernel
{

	Vector2 operator*(const double& scalar, const Vector2& vec)
	{
		Vector2 result(vec);
		result *= scalar;
		return result;
	}

	double DotProduct(const Vector2& vec1, const Vector2& vec2)
	{
		return vec1.DotProduct(vec2);
	}

	double CrossProduct(const Vector2& vec1, const Vector2& vec2)
	{
		Vector2 result(vec1);
		return result.CrossProduct(vec2);
	}

	Symplektis::GeometryKernel::Vector2 LinearInterpolate(const Vector2& vec1, const Vector2& vec2, const double& param)
	{
		Vector2 result(vec1);
		return result.LinearInterpolate(vec2, param);
	}

} // Symplektis::GeometryKernel