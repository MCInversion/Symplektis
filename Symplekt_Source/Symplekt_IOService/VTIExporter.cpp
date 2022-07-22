/*! \file  VTIExporter.cpp
 *  \brief Implementation of an object for exporting 3D volume geometry polydata to Kitware VTI (*.vti) files
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   6.10.2021
 *
 */

#include "VTIExporter.h"

#include <fstream>

namespace Symplektis::IOService
{
	//!> \brief precision for double values written into .vti image data file
	constexpr unsigned int stream_precision = 16;

	//-----------------------------------------------------------------------------
	/*! \brief Finds scalar field range min-max values.
	 *  \param[in] data           Input ScalarGridData.
	 *  \return pair {min, max}
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   24.10.2021
	*/
	//-----------------------------------------------------------------------------
	static std::pair<double, double> EvaluateScalarFieldRangeBounds(const GeometryKernel::ScalarGridData& data)
	{
		double min = DBL_MAX;
		double max = DBL_MIN;
		for (const auto& value : data.CellData)
		{
			if (value < min) min = value;
			if (value > max) max = value;
		}

		return { min, max };
	}

    ExportStatus VTIExporter::Export(const GeometryKernel::ScalarGridData& data, const std::filesystem::path& exportedFileName)
    {
		std::filesystem::path resultPath = exportedFileName;

		if (exportedFileName.extension().empty())
			resultPath += ".vti";

		else if (exportedFileName.extension() != ".vti")
			return ExportStatus::InvalidExtension;

		std::ofstream fileOStream(resultPath.c_str());
		if (!fileOStream.is_open())
			return ExportStatus::FileNotCreated;

		fileOStream << VTI_ImageDataHeader;

		const auto& gridOrigin = data.BoundingBox.Min();
		const auto cellSize = data.CellSize;

		const size_t Nx = data.XCellCount - 1;
		const size_t Ny = data.YCellCount - 1;
		const size_t Nz = data.ZCellCount - 1;

		const auto [valMin, valMax] = EvaluateScalarFieldRangeBounds(data);

		fileOStream << "	<ImageData WholeExtent=\"0 " << Nx << " 0 " << Ny << " 0 " << Nz <<
			"\" Origin=\""	<< gridOrigin.X() + 0.5 * cellSize << " " << gridOrigin.Y() + 0.5 * cellSize << " " << gridOrigin.Z() + 0.5 * cellSize <<
			"\" Spacing=\"" << cellSize << " " << cellSize << " " << cellSize << "\">\n";
		fileOStream << "		<Piece Extent=\"0 " << Nx << " 0 " << Ny << " 0 " << Nz << "\">\n";
		fileOStream << "			<PointData Scalars=\"Scalars_\">\n";
		fileOStream << "				<DataArray type=\"Float32\" Name=\"Scalars_\" format=\"ascii\" RangeMin=\"" << valMin << "\" RangeMax=\"" << valMax << "\">\n";

		fileOStream.precision(stream_precision);
		for (const auto& value : data.CellData)
			fileOStream << value << "\n";

		fileOStream << VTI_ImageDataScopeClose;

		fileOStream.close();
		return ExportStatus::Complete;
    }

} // Symplektis::IOService