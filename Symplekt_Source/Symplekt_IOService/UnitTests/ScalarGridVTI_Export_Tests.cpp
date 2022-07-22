/*! \file  ScalarGridVTI_Export_Tests.cpp
 *  \brief Tests for exporting scalar field image data to *.vti files
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   24.10.2021
 *
 */

#include "gtest/gtest.h"

#include "Symplekt_GeometryKernel/Box3.h"
#include "Symplekt_GeometryKernel/ImplicitGeometryDataTypes.h"
#include "Symplekt_GeometryKernel/ScalarGridInit.h"

#include "Symplekt_IOService/VTIExporter.h"

#include <functional>
#include <cmath>
#include <corecrt_math_defines.h>

namespace Symplektis::UnitTests
{
	using namespace IOService;
	using namespace GeometryKernel;

	// set up root directory
	const std::filesystem::path symplektRootPath = DSYMPLEKTIS_ROOT_DIR;

	ScalarGridData InitializeAndFillScalarGridData(const BaseScalarGridInputData& inputData, const std::function<double(double, double, double)>& fXYZ)
	{
		ScalarGridData gridData = InitializeScalarGridData(inputData);

		const auto& gridOrigin = gridData.BoundingBox.Min();
		const auto cellSize = gridData.CellSize;

		const size_t Nx = gridData.XCellCount;
		const size_t Ny = gridData.YCellCount;
		const size_t Nz = gridData.ZCellCount;

		for (unsigned int iz = 0; iz < Nz; iz++)
		{
			for (unsigned int iy = 0; iy < Ny; iy++)
			{
				for (unsigned int ix = 0; ix < Nx; ix++)
				{
					const double X = gridOrigin.X() + ix * cellSize;
					const double Y = gridOrigin.Y() + iy * cellSize;
					const double Z = gridOrigin.Z() + iz * cellSize;

					const auto gridIndexPos = 
						Nx * Ny * static_cast<size_t>(iz) +
						Nx * static_cast<size_t>(iy) + static_cast<size_t>(ix);

					gridData.CellData[gridIndexPos] = fXYZ(X, Y, Z);
				}
			}			
		}

		return gridData;
	}

	TEST(ScalarGridVTIExport_Suite, PolynomialScalarFieldGenerator_ExportVTI_VTIExported)
	{
		// Arrange
		const auto fileFullPath = symplektRootPath / "Symplekt_OutputData\\UnitTests" / "polynomialScalarField.vti";
		auto boundingBox = GeometryKernel::Box3{
			{-20.3, -20.1, 0.21},
			{20.123, 20.35, 29.96}
		};
		const double cellSize = 1.25;
		const auto scalarData = InitializeAndFillScalarGridData(
			BaseScalarGridInputData{ L"polynomialScalarField", boundingBox , cellSize, 0.0},
			[](double x, double y, double z) -> double	{ return x * x  + 2.0 * y * y + 0.5 * z * z; });

		// Act
		const auto exportStatus = VTIExporter::Export(scalarData, fileFullPath);

		// Assert
		EXPECT_EQ(exportStatus, ExportStatus::Complete);
	}

	TEST(ScalarGridVTIExport_Suite, TrigScalarFieldGenerator_ExportVTI_VTIExported)
	{
		// Arrange
		const auto fileFullPath = symplektRootPath / "Symplekt_OutputData\\UnitTests" / "trigScalarField.vti";
		auto boundingBox = GeometryKernel::Box3{
			{-20.3, -20.1, 0.21},
			{20.123, 20.35, 29.96}
		};
		const double cellSize = 1.25;
		const auto scalarData = InitializeAndFillScalarGridData(
			BaseScalarGridInputData{ L"trigScalarField", boundingBox , cellSize, 0.0},
			[](double x, double y, double z) -> double { return sin(x / (2 * M_PI)) * cos(y / (2 * M_PI)) * sin(z / (M_PI)); });

		// Act
		const auto exportStatus = VTIExporter::Export(scalarData, fileFullPath);

		// Assert
		EXPECT_EQ(exportStatus, ExportStatus::Complete);
	}

	TEST(ScalarGridVTIExport_Suite, MaxMinScalarFieldGenerator_ExportVTI_VTIExported)
	{
		// Arrange
		const auto fileFullPath = symplektRootPath / "Symplekt_OutputData\\UnitTests" / "maxMinScalarField.vti";
		auto boundingBox = GeometryKernel::Box3{
			{-20.123, -20.35, -29.96},
			{20.123, 20.35, 29.96}
		};
		const double cellSize = 1.25;
		const auto scalarData = InitializeAndFillScalarGridData(
			BaseScalarGridInputData{ L"maxMinScalarField", boundingBox , cellSize, 0.0},
			[](double x, double y, double z) -> double { return std::max(x, std::min(y, z)); });

		// Act
		const auto exportStatus = VTIExporter::Export(scalarData, fileFullPath);

		// Assert
		EXPECT_EQ(exportStatus, ExportStatus::Complete);
	}

	TEST(ScalarGridVTIExport_Suite, MinMaxScalarFieldGenerator_ExportVTI_VTIExported)
	{
		// Arrange
		const auto fileFullPath = symplektRootPath / "Symplekt_OutputData\\UnitTests" / "minMaxScalarField.vti";
		auto boundingBox = GeometryKernel::Box3{
			{-20.123, -20.35, -29.96},
			{20.123, 20.35, 29.96}
		};
		const double cellSize = 1.25;
		const auto scalarData = InitializeAndFillScalarGridData(
			BaseScalarGridInputData{ L"minMaxScalarField", boundingBox , cellSize, 0.0},
			[](double x, double y, double z) -> double { return std::min(x, std::max(y, z)); });

		// Act
		const auto exportStatus = VTIExporter::Export(scalarData, fileFullPath);

		// Assert
		EXPECT_EQ(exportStatus, ExportStatus::Complete);
	}

} // Symplektis::UnitTests