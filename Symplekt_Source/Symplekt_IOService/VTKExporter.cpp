/*! \file  VTKExporter.cpp
 *  \brief Implementation of an object for exporting 3D geometry polydata to Kitware VTK (*.vtk) files
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   6.10.2021
 *
 */

#include "VTKExporter.h"

#include "../Symplekt_UtilityGeneral/Assert.h"

#include <fstream>
#include <locale>
#include <numeric>

namespace Symplektis::IOService
{
	//!> \brief precision for double values written into .vtk polydata file
	constexpr unsigned int stream_precision = 16;

	//-----------------------------------------------------------------------------
	/*! \brief Generates a polydata points header based on point count.
	 *  \param[in] data           Input GeometryIOData.
	 *  \return polydata points header string
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   18.10.2021
	*/
	//-----------------------------------------------------------------------------
	static std::string GenerateVTKPolydataPointsHeaderFromData(const GeometryIOData& data)
	{
		std::string result;
		result += "POINTS " + std::to_string(data.Vertices.size()) + " float\n\n";
		return result;
	}

	//-----------------------------------------------------------------------------
	/*! \brief Generates a polydata polygons header based on vertex indices counts.
	 *  \param[in] data           Input GeometryIOData.
	 *  \return polydata polygons header string
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   18.10.2021
	*/
	//-----------------------------------------------------------------------------
	static std::string GenerateVTKPolydataPolygonsHeaderFromData(const GeometryIOData& data)
	{
		std::string result;
		size_t vertIdsCount = 0;
		for (const auto& idTuple : data.VertexIndices) vertIdsCount += (idTuple.size() + 1);

		// each row is (vertIdsCount + 1) entries long
		result += "POLYGONS " + std::to_string(data.VertexIndices.size()) + " " + std::to_string(vertIdsCount) + "\n\n";
		return result;
	}

	//
	// ===========================================================================
	//

	ExportStatus VTKExporter::Export(const GeometryIOData& data, const std::filesystem::path& exportedFileName) const
	{
		std::filesystem::path resultPath = exportedFileName;

		if (exportedFileName.extension().empty())
			resultPath += ".vtk";

		else if (exportedFileName.extension() != ".vtk")
			return ExportStatus::InvalidExtension;

		std::ofstream fileOStream(resultPath.c_str());
		if (!fileOStream.is_open())
			return ExportStatus::FileNotCreated;

		fileOStream << VTK_Polydata_Header_Str;

		// polydata without vertices or vertex indices is invalid
		if (data.Vertices.empty() || data.VertexIndices.empty())
		{
			MSG_CHECK(false, "VTKExporter::Export: Exporting data without vertices or vertex indices!\n");
			fileOStream.close();
			return ExportStatus::InternalError;
		}

		fileOStream << GenerateVTKPolydataPointsHeaderFromData(data);
		fileOStream.precision(stream_precision);

		for (const auto& vert : data.Vertices)
			fileOStream << std::fixed << vert.X() << " " << vert.Y() << " " << vert.Z() << "\n";

		fileOStream << "\n";

		fileOStream << GenerateVTKPolydataPolygonsHeaderFromData(data);

		for (const auto& indexTuple : data.VertexIndices)
		{
			fileOStream << std::to_string(indexTuple.size()) + " ";
			for (const auto& id : indexTuple) fileOStream << std::to_string(id) + " ";
			fileOStream << "\n";
		}

		fileOStream.close();
		return ExportStatus::Complete;
	}

} // Symplektis::IOService