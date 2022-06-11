/*! \file NumericUtils.cpp
*   \brief Implementations of generic utils for numerical computations (not covered by any STL method)
*
\verbatim
-------------------------------------------------------------------------------
created  : 31.5.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/

#include "Assert.h"
#include "NumericUtils.h"

#include <cstdint>

namespace Symplektis::Util
{
	bool EqualsWithTolerance(const double& val1, const double& val2, const double& tol)
	{
        if (tol < 0.0)
        {
		    ASSERT(false, "Symplektis::Util::EqualsWithTolerance: tolerance value is not positive!\n");
            return false;
        }

		return (std::fabs(val1 - val2) < tol);
	}

	double Clamp(const double& val, const double& lowerBound, const double& upperBound)
	{
        if (lowerBound >= upperBound)
        {
		    ASSERT(false, "Symplektis::Util::Clamp: lowerBound >= upperBound!");
            return val;
        }
		return (val < lowerBound) ? lowerBound : (upperBound < val) ? upperBound : val;
	}

    double FastInverseSqrt(const double& val)
    {
        double y = val;
        double x2 = y * 0.5;
        std::int64_t i = *(std::int64_t*)&y;

        // The magic number for doubles is from https://cs.uwaterloo.ca/~m32rober/rsqrt.pdf
        i = 0x5fe6eb50c7b537a9 - (i >> 1);
        y = *(double*)&i;
        y = y * (1.5 - (x2 * y * y));                // 1st iteration
        y = y * (1.5 - (x2 * y * y));                // 2nd iteration
        return y;
    }

}  // Symplektis::Util