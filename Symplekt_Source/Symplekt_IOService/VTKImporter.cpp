/*! \file  VTKImporter.cpp
 *  \brief Implementation of an object for importing 3D geometry polydata from Kitware VTK (*.vtk) files
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   6.10.2021
 *
 */

#include "VTKImporter.h"

#include "../Symplekt_UtilityGeneral/Assert.h"

#include <string>
#include <fstream>

namespace Symplektis::IOService
{
	using namespace GeometryBase;
	
	//-----------------------------------------------------------------------------
	/*! \brief Parse mesh file name from the imported file path.
	 *  \param[in] importedFilePath     path to the imported file.
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   9.6.2022
	*/
	//-----------------------------------------------------------------------------
	static std::wstring GetGeometryNameFromFilePath(const std::filesystem::path& importedFilePath)
	{
		const auto stem = importedFilePath.stem();
		return stem.wstring();
	}

	//-----------------------------------------------------------------------------
	/*! \brief Verifies whether the given line string begins with a token.
	 *  \param[in] line     evaluated line string.
	 *  \param[in] token    evaluated token.
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   10.6.2022
	*/
	//-----------------------------------------------------------------------------
	static bool LineBeginsWithToken(const std::string line, const std::string token)
	{
		if (line.empty())
			return false;

		std::stringstream sStream{ line };
		std::string lineToken;
		sStream >> lineToken;
		return lineToken == token;
	}
	
    ImportStatus VTKImporter::Import(const std::filesystem::path& importedFilePath)
    {
		if (importedFilePath.empty() || !exists(importedFilePath))
			return ImportStatus::FileNotFound;

		if (!importedFilePath.has_extension() || importedFilePath.extension() != ".vtk")
			return ImportStatus::InvalidExtension;

		std::ifstream fileInStream(importedFilePath.c_str(), std::ios::in);
		if (!fileInStream.is_open())
			return ImportStatus::FileNotOpened;

		ClearIOData();
		m_Data.Name = GetGeometryNameFromFilePath(importedFilePath);

		// iterate towards the points header
		std::string line;
		while (!LineBeginsWithToken(line, "POINTS"))
		{
			if (!std::getline(fileInStream, line))
			{
				fileInStream.close();
				MSG_CHECK(false, "VTKImporter::Import, (iterate towards the points header): Unexpected end of file!\n");
				return ImportStatus::InternalError;
			}
		}

		//
		// ======= load points header =========
		//

		std::stringstream pointsHeaderLineStream{ line };
		std::string ptsToken;
		pointsHeaderLineStream >> ptsToken;
		pointsHeaderLineStream >> ptsToken;

		const size_t nVertices = std::stoi(ptsToken);
		ASSERT(nVertices > 0, "VTKImporter::Import, Load points header: invalid number of vertices!\n");
		m_Data.Vertices.reserve(nVertices);

		// iterate towards the points block
		do
		{
			if (!std::getline(fileInStream, line))
			{
				fileInStream.close();
				MSG_CHECK(false, "VTKImporter::Import, (iterate towards the points block): Unexpected end of file!\n");
				return ImportStatus::InternalError;
			}
		} while (line.empty());

		//
		// ======= load points =========
		//

		for (size_t i = 0; i < nVertices; i++)
		{			
			std::stringstream sStream{ line };
			double x, y, z;
			sStream >> x >> y >> z;

			m_Data.Vertices.emplace_back(Vector3(x, y, z));

			if (!std::getline(fileInStream, line))
			{
				fileInStream.close();
				MSG_CHECK(false, "VTKImporter::Import, Load points: Unexpected end of file!\n");
			}
		}

		// iterate towards the polygons header
		while (!LineBeginsWithToken(line, "POLYGONS"))
		{
			if (!std::getline(fileInStream, line))
			{
				fileInStream.close();
				MSG_CHECK(false, "VTKImporter::Import, (iterate towards the polygons header): Unexpected end of file!\n");
				return ImportStatus::InternalError;
			}
		}

		//
		// ======= load polygons header =========
		//

		std::stringstream polygonsHeaderLineStream{ line };
		std::string polysToken;
		polygonsHeaderLineStream >> polysToken;
		polygonsHeaderLineStream >> polysToken;

		const size_t nPolygons = std::stoi(polysToken);
		ASSERT(nPolygons > 0, "VTKImporter::Import, Load polygons: invalid number of polygons!\n");
		m_Data.VertexIndices.reserve(nPolygons);

		// iterate towards the polygons block
		do
		{
			if (!std::getline(fileInStream, line))
			{
				fileInStream.close();
				MSG_CHECK(false, "VTKImporter::Import, (iterate towards the polygons block): Unexpected end of file!\n");
				return ImportStatus::InternalError;
			}
		} while (line.empty());

		//
		// ======= load polygons block =========
		//

		for (size_t i = 0; i < nPolygons; i++)
		{
			std::stringstream sStream{ line };
			std::string token;
			sStream >> token;

			const size_t nIndicesInPolygon = std::stoi(token);
			ASSERT(nIndicesInPolygon > 2, "VTKImporter::Import, Load polygons: invalid number of indices in polygon!\n");

			std::vector<unsigned int> indicesInPolygon{};
			indicesInPolygon.reserve(nIndicesInPolygon);

			for (size_t j = 0; j < nIndicesInPolygon; j++)
			{
				sStream >> token;
				const int idInPoly = std::stoi(token);
				if (idInPoly < 0 || idInPoly > nVertices - 1)
				{
					MSG_CHECK(false, "VTKImporter::Import, Load polygons: invalid polygon index!\n");
					continue;
				}

				indicesInPolygon.push_back(idInPoly);
			}

			m_Data.VertexIndices.push_back(indicesInPolygon);

			if (!std::getline(fileInStream, line) && i < nPolygons - 1)
			{
				fileInStream.close();
				MSG_CHECK(false, "VTKImporter::Import, Load polygons: Unexpected end of file!\n");
			}
		}

		// TODO: vertex scalars

		fileInStream.close();
		return ImportStatus::Complete;
    }
} // Symplektis::IOService