/*! \file ToleranceSettings.h
*   \brief Settings for tolerance in numerical computation
*
\verbatim
-------------------------------------------------------------------------------
created  : 6.5.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim

*/
#pragma once

#include "Assert.h"

namespace Symplektis::Util
{
	/// \brief maximum possible tolerance allowed. Having more than this tolerance value for any calculations sacrifices too much precision.
	#define MAX_ALLOWED_TOLERANCE 0.01

	//-----------------------------------------------------------------------------
	/*! \brief checking macro for setting a particular tolerance setting value (for void methods only)
	*   \param[in] value  (double value to be set)
	*	\param[in] context - c-string to denote context of the set method upon ASSERT failure
	*
	*   \ingroup UTILITY_GENERAL
	*
	*   \author M.Cavarga (MCInversion)
	*   \date 6.5.2021
	*/
	//-----------------------------------------------------------------------------
	#define CHECK_TOLERANCE_VALUE_SETTING_AND_RETURN(value, context)									\
		if (value == 0.0)																				\
		{																								\
		    std::string contextStr = context;                                                           \
			ASSERT(false, contextStr + ": zero tolerance setting!\n");									\
			return;																						\
		}																								\
		if (value > MAX_ALLOWED_TOLERANCE)																\
		{																								\
			std::string contextStr = context;                                                           \
			ASSERT(false, contextStr + ": tolerance setting value exceeds MAX_ALLOWED_TOLERANCE!\n");	\
			return;																						\
		}																								\
    /**/

	//-----------------------------------------------------------------------------
	/*! \brief set tolerance value for vector coordinates
	*
	*   \ingroup UTILITY_GENERAL
	*
	*   \author M.Cavarga (MCInversion)
	*   \date 6.5.2021
	*/
	//-----------------------------------------------------------------------------
	void SetCoordinateTolerance(const double& value);

    //-----------------------------------------------------------------------------
	/*! \brief get tolerance for vector coordinates
	*   \return tolerance
	*
	*   \ingroup UTILITY_GENERAL
	*
	*   \author M.Cavarga (MCInversion)
	*   \date 6.5.2021
	*/
	//-----------------------------------------------------------------------------
	double GetCoordinateTolerance();

	//-----------------------------------------------------------------------------
	/*! \brief set tolerance value for vector coordinate products
	*
	*   \ingroup UTILITY_GENERAL
	*
	*   \author M.Cavarga (MCInversion)
	*   \date 6.5.2021
	*/
	//-----------------------------------------------------------------------------
	void SetProductTolerance(const double& value);

	//-----------------------------------------------------------------------------
	/*! \brief get tolerance for vector coordinate products
	*   \return tolerance
	*
	*   \ingroup UTILITY_GENERAL
	*
	*   \author M.Cavarga (MCInversion)
	*   \date 6.5.2021
	*/
	//-----------------------------------------------------------------------------
	double GetProductTolerance();

	//-----------------------------------------------------------------------------
	/*! \brief set tolerance value for numerics vector coordinates
	*
	*   \ingroup UTILITY_GENERAL
	*
	*   \author M.Cavarga (MCInversion)
	*   \date 6.5.2021
	*/
	//-----------------------------------------------------------------------------
	void SetNumericsCoordTolerance(const double& value);

	//-----------------------------------------------------------------------------
	/*! \brief get tolerance for numerics vector coordinates
	*   \return tolerance
	*
	*   \ingroup UTILITY_GENERAL
	*
	*   \author M.Cavarga (MCInversion)
	*   \date 6.5.2021
	*/
	//-----------------------------------------------------------------------------
	double GetNumericsCoordTolerance();

	//-----------------------------------------------------------------------------
	/*! \brief set tolerance value for numerics vector norm convergence
	*
	*   \ingroup UTILITY_GENERAL
	*
	*   \author M.Cavarga (MCInversion)
	*   \date 6.5.2021
	*/
	//-----------------------------------------------------------------------------
	void SetNumericsConvergenceTolerance(const double& value);

	//-----------------------------------------------------------------------------
	/*! \brief get tolerance for numerics vector norm convergence
	*   \return tolerance
	*
	*   \ingroup UTILITY_GENERAL
	*
	*   \author M.Cavarga (MCInversion)
	*   \date 6.5.2021
	*/
	//-----------------------------------------------------------------------------
	double GetNumericsConvergenceTolerance();

} // Symplektis::Util