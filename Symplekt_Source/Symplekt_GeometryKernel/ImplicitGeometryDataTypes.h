/*! \file  ImplicitGeometryDataTypes.h
 *  \brief A gallery of data container types (mostly structs) for implicit (FRep) geometry data.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   23.10.2021
 *
 */

#pragma once

#include "Symplekt_GeometryKernel/Box3.h"
#include "Symplekt_GeometryKernel/RectilinearGridBox3.h"

#include <vector>

namespace Symplektis::GeometryKernel
{
	//=============================================================================
	/// \struct BaseScalarGridInputData
	/// \brief Base input data object for ScalarGridData construction.
	///
	/// \ingroup GEOMETRY_REPS
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   23.10.2021
	//=============================================================================
	struct BaseScalarGridInputData
	{
		std::wstring       Name;
		GeometryKernel::Box3 BoundingBox{};
		double             CellSize{0.0};
		double             InitValue{0.0};
	};

	//=============================================================================
	/// \struct ScalarGridData
	/// \brief A data container for regular scalar grid voxel data defined in a bounding volume given by the BoundingBox and CellSize;
	///
	/// \ingroup GEOMETRY_REPS
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   20.10.2021
	//=============================================================================
	struct ScalarGridData
	{
		std::wstring                          Name;
		GeometryKernel::RectilinearGridBox3     BoundingBox;

		// ---- cell counts (for voxel-wise iterating) ----------------------------------
		size_t                                XCellCount{ 0 };
		size_t                                YCellCount{ 0 };
		size_t                                ZCellCount{ 0 };
		// -------------------------------------------------------------------

		double                                CellSize{ 0.0 };

		// ----------- data fields -------------------------------------------
		std::vector<double>                   CellData;
		std::vector<bool>                     CellIsFrozen;
	};

} // Symplektis::GeometryKernel