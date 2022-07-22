/*! \file Matrix3Utils.cpp
*   \brief Implmentation of the external 3x3 matrix utilities
*
\verbatim
-------------------------------------------------------------------------------
created  : 15.6.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/
#include "Matrix3Utils.h"

namespace Symplektis::GeometryKernel
{
	
	Matrix3 operator*(const double& scalar, const Matrix3& mat)
	{
		return mat * scalar;
	}

	Matrix3 Transpose(const Matrix3& mat)
	{
		Matrix3 result(mat);
		result.Transpose();
		return result;
	}

	Matrix3 Inverse(const Matrix3& mat)
	{
		Matrix3 result(mat);
		result.Inverse();
		return result;
	}
	
} // Symplektis::GeometryKernel