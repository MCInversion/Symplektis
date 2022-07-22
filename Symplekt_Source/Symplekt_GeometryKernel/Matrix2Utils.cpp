/*! \file Matrix2Utils.cpp
*   \brief Implmentation of the external 2x2 matrix utilities
*
\verbatim
-------------------------------------------------------------------------------
created  : 26.6.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/
#include "Matrix2Utils.h"

namespace Symplektis::GeometryKernel
{

	Matrix2 operator*(const double& scalar, const Matrix2& mat)
	{
		return mat * scalar;
	}

	Matrix2 Transpose(const Matrix2& mat)
	{
		Matrix2 result(mat);
		result.Transpose();
		return result;
	}

	Matrix2 Inverse(const Matrix2& mat)
	{
		Matrix2 result(mat);
		result.Inverse();
		return result;
	}

} // Symplektis::GeometryKernel