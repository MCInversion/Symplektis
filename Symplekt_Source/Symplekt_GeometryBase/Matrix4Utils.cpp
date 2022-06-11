/*! \file Matrix4Utils.cpp
*   \brief Implmentation of the external 4x4 matrix utilities
*
\verbatim
-------------------------------------------------------------------------------
created  : 19.6.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/
#include "Matrix4Utils.h"

namespace Symplektis::GeometryBase
{

	Matrix4 operator*(const double& scalar, const Matrix4& mat)
	{
		return mat * scalar;
	}

	Matrix4 Transpose(const Matrix4& mat)
	{
		Matrix4 result(mat);
		result.Transpose();
		return result;
	}

	Matrix4 Inverse(const Matrix4& mat)
	{
		Matrix4 result(mat);
		result.Inverse();
		return result;
	}

} // Symplektis::GeometryBase