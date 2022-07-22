/*! \file  ScalarGridInit.h
 *  \brief An initialization util for ScalarGridData
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   23.10.2021
 *
 */

#pragma once

#include "Symplekt_GeometryKernel/RectilinearGridBox3.h"

#include "ImplicitGeometryDataTypes.h"


namespace Symplektis::GeometryKernel
{
	//-----------------------------------------------------------------------------
	/*! \brief An initialization util for ScalarGridData from BaseScalarGridInputData.\n
	 *         preferred call:\n
	 *         auto gridData = InitializeScalarGridData({boundingBox, cellSize, initValue});
	 *
	 *	\param[in] inputData           input data struct {boundingBox, cellSize, initValue}
	 *
	 *  \author M. Cavarga (MCInversion)
	 *  \date   23.10.2021
	 */
	 //-----------------------------------------------------------------------------
	inline ScalarGridData InitializeScalarGridData(const BaseScalarGridInputData& inputData)
	{
		ScalarGridData resultData;

		resultData.Name = inputData.Name;
		resultData.CellSize = inputData.CellSize;
		resultData.BoundingBox = GeometryKernel::RectilinearGridBox3{ inputData.CellSize, inputData.BoundingBox };
		const auto boxSize = resultData.BoundingBox.GetSize();

		resultData.XCellCount = static_cast<size_t>(boxSize.X() / inputData.CellSize);
		resultData.YCellCount = static_cast<size_t>(boxSize.Y() / inputData.CellSize);
		resultData.ZCellCount = static_cast<size_t>(boxSize.Z() / inputData.CellSize);

		const size_t totalCellCount = resultData.XCellCount * resultData.YCellCount * resultData.ZCellCount;

		resultData.CellData = std::vector<double>(totalCellCount, inputData.InitValue);
		resultData.CellIsFrozen = std::vector<bool>(totalCellCount, false);

		return resultData;
	}

} // Symplektis::GeometryKernel