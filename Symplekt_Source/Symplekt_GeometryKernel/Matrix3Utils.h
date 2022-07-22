/*! \file Matrix3Utils.h
*   \brief Declaration of various external methods for Matrix3
*
\verbatim
-------------------------------------------------------------------------------
created  : 15.6.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/

#pragma once

#include "Matrix3.h"

namespace Symplektis::GeometryKernel
{
	//-----------------------------------------------------------------------------
	/*! \brief Left scalar multiplication operator for Matrix3
	*   \param[in] scalar        Scalar value.
	*   \param[in] vec           Multiplied matrix.
	*   \return new multiplied matrix
	*
	*   \author M. Cavarga (MCInversion)
	*   \date  15.6.2021
	*/
	//-----------------------------------------------------------------------------
	Matrix3 operator*(const double& scalar, const Matrix3& mat);

	//-----------------------------------------------------------------------------
	/*! \brief Copies & transposes a matrix
	*	\param[in] mat     matrix ref to copy & transpose
	*   \return new matrix (transposed)
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   19.6.2021
	*/
	//-----------------------------------------------------------------------------
	Matrix3 Transpose(const Matrix3& mat);

	//-----------------------------------------------------------------------------
	/*! \brief Copies & inverts a matrix
	*	\param[in] mat     matrix ref to copy & invert
	*   \return new matrix (inverted)
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   19.6.2021
	*/
	//-----------------------------------------------------------------------------
	Matrix3 Inverse(const Matrix3& mat);

	
} // Symplektis::GeometryKernel