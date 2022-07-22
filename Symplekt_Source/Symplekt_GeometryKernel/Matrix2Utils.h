/*! \file Matrix2Utils.h
*   \brief Declaration of various external methods for Matrix2
*
\verbatim
-------------------------------------------------------------------------------
created  : 26.6.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/

#pragma once

#include "Matrix2.h"

namespace Symplektis::GeometryKernel
{
	//-----------------------------------------------------------------------------
	/*! \brief Left scalar multiplication operator for Matrix2
	*   \param[in] scalar        Scalar value.
	*   \param[in] vec           Multiplied matrix.
	*   \return new multiplied matrix
	*
	*   \author M. Cavarga (MCInversion)
	*   \date  26.6.2021
	*/
	//-----------------------------------------------------------------------------
	Matrix2 operator*(const double& scalar, const Matrix2& mat);

	//-----------------------------------------------------------------------------
	/*! \brief Copies & transposes a matrix
	*	\param[in] mat     matrix ref to copy & transpose
	*   \return new matrix (transposed)
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   26.6.2021
	*/
	//-----------------------------------------------------------------------------
	Matrix2 Transpose(const Matrix2& mat);

	//-----------------------------------------------------------------------------
	/*! \brief Copies & inverts a matrix
	*	\param[in] mat     matrix ref to copy & invert
	*   \return new matrix (inverted)
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   26.6.2021
	*/
	//-----------------------------------------------------------------------------
	Matrix2 Inverse(const Matrix2& mat);


} // Symplektis::GeometryKernel