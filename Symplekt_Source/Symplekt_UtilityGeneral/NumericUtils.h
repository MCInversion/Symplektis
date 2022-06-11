/*! \file NumericUtils.h
*   \brief Generic utils for numerical computations (not covered by any STL method)
*
\verbatim
-------------------------------------------------------------------------------
created  : 6.5.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/
#pragma once

namespace Symplektis::Util
{
	//-----------------------------------------------------------------------------
	/*! \brief equals operator for double values with tolerance
	*   \param[in] val1  - value to be compared
	*   \param[in] val2  - value to be compared against
	*   \param[in] tol   - tolerance
	*	\return true if val1 == val2 with tolerance tol
	*
	*   \ingroup UTILITY_GENERAL
	*
	*   \author M.Cavarga (MCInversion)
	*   \date 6.5.2021
	*/
	//-----------------------------------------------------------------------------
	bool EqualsWithTolerance(const double& val1, const double& val2, const double& tol);

	//-----------------------------------------------------------------------------
	/*! \brief Clamp (cut off) double value in interval [lowerBound, upperBound]
	*   \param[in] val          - value to be clamped
	*   \param[in] lowerBound   - lower bound
	*   \param[in] upperBound   - upper bound
	*	\return clamped value
	*
	*   \ingroup UTILITY_GENERAL
	*
	*   \author M.Cavarga (MCInversion)
	*   \date 6.5.2021
	*/
	//-----------------------------------------------------------------------------
	double Clamp(const double& val, const double& lowerBound, const double& upperBound);

	//-----------------------------------------------------------------------------
	/*! \brief Fast inverse square root\n
			   originally implemented as Q_rsqrt() for 32-bit floats in Quake III: Arena engine
			   see: https://cs.uwaterloo.ca/~m32rober/rsqrt.pdf
	*   \param[in] val          - value
	*	\return 1 / sqrt(val)
	*
	*   \ingroup UTILITY_GENERAL
	*
	*   \author M.Cavarga (MCInversion)
	*   \date 3.6.2021
	*/
	//-----------------------------------------------------------------------------
	double FastInverseSqrt(const double& val);

} // Symplektis::Util