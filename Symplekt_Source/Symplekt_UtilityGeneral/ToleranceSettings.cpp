#include "ToleranceSettings.h"

static double s_CoordinateTolerance = 1e-5;             //<! tolerance for 2,3,4-D vector & matrix coordinate + and - operations
static double s_ProductTolerance = 1e-4;				//<! tolerance for 2,3,4-D vector & matrix coordinate product operations
static double s_NumericsCoordinateTolerance = 1e-8;     //<! tolerance for n-D vector & matrix coordinate addition/product operations in numeric solvers
static double s_NumericsConvergenceTolerance = 1e-6;    //<! tolerance for n-D vector & matrix norm convergence tolerance in numeric solvers

namespace Symplektis::Util
{
	void SetCoordinateTolerance(const double& value)
	{
		CHECK_TOLERANCE_VALUE_SETTING_AND_RETURN(value, "Symplektis::Util::SetCoordinateTolerance");
		s_CoordinateTolerance = value;
	}

	double GetCoordinateTolerance()
	{
		return s_CoordinateTolerance;
	}

	void SetProductTolerance(const double& value)
	{
		CHECK_TOLERANCE_VALUE_SETTING_AND_RETURN(value, "Symplektis::Util::SetProductTolerance");
		s_ProductTolerance = value;
	}

	double GetProductTolerance()
	{
		return s_ProductTolerance;
	}

	void SetNumericsCoordTolerance(const double& value)
	{
		CHECK_TOLERANCE_VALUE_SETTING_AND_RETURN(value, "Symplektis::Util::SetNumericsCoordTolerance");
		s_NumericsCoordinateTolerance = value;
	}

	double GetNumericsCoordTolerance()
	{
		return s_NumericsCoordinateTolerance;
	}

	void SetNumericsConvergenceTolerance(const double& value)
	{
		CHECK_TOLERANCE_VALUE_SETTING_AND_RETURN(value, "Symplektis::Util::SetNumericsConvergenceTolerance");
		s_NumericsConvergenceTolerance = value;
	}

	double GetNumericsConvergenceTolerance()
	{
		return s_NumericsConvergenceTolerance;
	}
}  // Symplektis::Util