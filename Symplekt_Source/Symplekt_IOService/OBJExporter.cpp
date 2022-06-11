/*! \file  OBJExporter.cpp
 *  \brief Implementation of an object for exporting 3D geometry data to Wavefront OBJ (*.obj) files
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   6.10.2021
 *
 */

#include "OBJExporter.h"

#include "../Symplekt_UtilityGeneral/Assert.h"

#include <fstream>
#include <locale>

namespace Symplektis::IOService
{
	//!> \brief precision for double values written into .obj file
	constexpr unsigned int stream_precision = 16;
	
	ExportStatus OBJExporter::Export(const GeometryIOData& data, const std::filesystem::path& exportedFileName) const
	{
		std::filesystem::path resultPath = exportedFileName;

		if (exportedFileName.extension().empty())
			resultPath += ".obj";

		else if (exportedFileName.extension() != ".obj")
			return ExportStatus::InvalidExtension;

		std::ofstream fileOStream(resultPath.c_str());
		if (!fileOStream.is_open())
			return ExportStatus::FileNotCreated;

		// OBJ without vertices or vertex indices is invalid
		if (data.Vertices.empty() || data.VertexIndices.empty())
		{
			MSG_CHECK(false, "OBJExporter::Export: Exporting data without vertices or vertex indices!\n");
			fileOStream.close();
			return ExportStatus::InternalError;
		}

		// vertices
		fileOStream.precision(stream_precision);
		for (const auto& vert : data.Vertices)
			fileOStream << std::fixed << "v " << vert.X() << " " << vert.Y() << " " << vert.Z() << "\n";

		fileOStream << "\n";

		// TODO: texture coords

		// faces
		for (const auto& indexTuple : data.VertexIndices)
		{
			fileOStream << "f ";
			for (const auto& id : indexTuple) fileOStream << std::to_string(id + 1) + " ";
			fileOStream << "\n";
		}

		fileOStream.close();
		return ExportStatus::Complete;
	}
} // Symplektis::IOService