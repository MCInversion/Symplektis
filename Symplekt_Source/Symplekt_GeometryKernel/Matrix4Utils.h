/*! \file Matrix4Utils.h
*   \brief Declaration of various external methods for Matrix4
*
\verbatim
-------------------------------------------------------------------------------
created  : 19.6.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/

#pragma once

#include "Matrix4.h"

namespace Symplektis::GeometryKernel
{
	//-----------------------------------------------------------------------------
	/*! \brief Left scalar multiplication operator for Matrix4
	*   \param[in] scalar        Scalar value.
	*   \param[in] vec           Multiplied matrix.
	*   \return new multiplied matrix
	*
	*   \author M. Cavarga (MCInversion)
	*   \date  15.6.2021
	*/
	//-----------------------------------------------------------------------------
	Matrix4 operator*(const double& scalar, const Matrix4& mat);

	//-----------------------------------------------------------------------------
	/*! \brief Copies & transposes a matrix
	*	\param[in] mat     matrix ref to copy & transpose
	*   \return new matrix (transposed)
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   19.6.2021
	*/
	//-----------------------------------------------------------------------------
	Matrix4 Transpose(const Matrix4& mat);

	//-----------------------------------------------------------------------------
	/*! \brief Copies & inverts a matrix
	*	\param[in] mat     matrix ref to copy & invert
	*   \return new matrix (inverted)
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   19.6.2021
	*/
	//-----------------------------------------------------------------------------
	Matrix4 Inverse(const Matrix4& mat);


} // Symplektis::GeometryKernel