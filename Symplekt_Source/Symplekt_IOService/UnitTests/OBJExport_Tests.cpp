/*! \file  OBJExport_Tests.cpp
 *  \brief Tests for exporting geometry data to Wavefront OBJ (*.obj) files.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   10.6.2022
 *
 */

#include "gtest/gtest.h"

#include "Symplekt_GeometryReps/UnitTests/MeshGeometryDataForTesting.h"

#include "Symplekt_IOService/OBJExporter.h"
#include "Symplekt_IOService/OBJImporter.h"

#include <fstream>

namespace Symplektis::UnitTests
{
	using namespace IOService;

	// set up root directory
	const std::filesystem::path symplektRootPath = DSYMPLEKTIS_ROOT_DIR;

	static bool LineBeginsWithToken(const std::string line, const std::string token)
	{
		if (line.empty())
			return false;

		std::stringstream sStream{ line };
		std::string lineToken;
		sStream >> lineToken;
		return lineToken == token;
	}

	static std::tuple<int, int, int> ParsePolygonIndexForTesting(const std::string& token)
	{
		std::stringstream sStreamIn{ token };
		std::string indexString;

		int indices[3] = { -1, -1, -1 };
		unsigned int i = 0;

		while (std::getline(sStreamIn, indexString))
		{
			std::stringstream sStream{ indexString };
			sStream >> indices[i++];
		}

		return std::tuple{ indices[0] - 1, indices[1] - 1, indices[2] - 1 };
	}
	
	static std::vector<unsigned int> ReadVertexIndicesForTesting(std::stringstream& sStream)
	{
		std::vector<unsigned int> polyIndices;
		std::vector<unsigned int> textureIndices;
		std::vector<unsigned int> normalIndices;
		std::string currentToken;

		while (sStream >> currentToken)
		{
			const auto [iPoly, iTexture, iNormal] = ParsePolygonIndexForTesting(currentToken);
			polyIndices.push_back(iPoly);
			if (iTexture > -1) textureIndices.push_back(iTexture);
			if (iNormal > -1) normalIndices.push_back(iNormal);
		}

		return polyIndices;
	}

	static void ValidateOBJFile(const std::filesystem::path& filePath, const GeometryIOData& data)
	{
		//
		// ===== File Validation ================
		//

		EXPECT_FALSE(filePath.extension().empty());
		EXPECT_FALSE(filePath.extension() != ".obj");

		std::ifstream fileInStream(filePath.c_str(), std::ios::in);
		EXPECT_TRUE(fileInStream.is_open());

		// iterate towards the vertices block
		std::string line;
		while (!LineBeginsWithToken(line, "v"))
		{
			if (!std::getline(fileInStream, line))
			{
				fileInStream.close();
				std::wstring msg = L"[" + data.Name + L"] ValidateOBJFile (iterate towards the vertices block): Unexpected end of file!";
				FAIL() << msg;
			}
		}

		//
		// ===== Vertices Validation ================
		//

		for (const auto& vert : data.Vertices)
		{
			std::stringstream sStream{ line };
			std::string token;
			sStream >> token;

			EXPECT_TRUE(token == "v");

			double x, y, z;
			sStream >> x >> y >> z;

			EXPECT_DOUBLE_EQ(x, vert.X());
			EXPECT_DOUBLE_EQ(y, vert.Y());
			EXPECT_DOUBLE_EQ(z, vert.Z());
			
			if (!std::getline(fileInStream, line))
			{
				fileInStream.close();
				std::wstring msg = L"[" + data.Name + L"] ValidateOBJFile (Vertices Validation): Unexpected end of file!";
				FAIL() << msg;
			}
		}

		// iterate towards the faces block
		while (!LineBeginsWithToken(line, "f"))
		{
			if (!std::getline(fileInStream, line))
			{
				fileInStream.close();
				std::wstring msg = L"[" + data.Name + L"] ValidateOBJFile (iterate towards the faces block): Unexpected end of file!";
				FAIL() << msg;
			}
		}

		//
		// ===== Faces Validation ================
		//

		for (size_t polyCount = 0; const auto& polyIds : data.VertexIndices)
		{
			std::stringstream sStream{ line };
			std::string token;
			sStream >> token;

			EXPECT_TRUE(token == "f");

			const auto readIndices = ReadVertexIndicesForTesting(sStream);
			const auto nVerts = static_cast<unsigned int>(readIndices.size());
			EXPECT_EQ(nVerts, polyIds.size());
			if (nVerts != polyIds.size())
			{
				if (!std::getline(fileInStream, line) && polyCount != data.VertexIndices.size() - 1)
				{
					fileInStream.close();
					std::wstring msg = L"[" + data.Name + L"] ValidateOBJFile (Faces Validation): Unexpected end of file!";
					FAIL() << msg;
				}
				polyCount++;
				continue; // skip to avoid access violation
			}
			
			for (unsigned int j = 0; j < nVerts; j++)
			{
				EXPECT_EQ(readIndices[j], polyIds[j]);
			}
			
			if (!std::getline(fileInStream, line) && polyCount != data.VertexIndices.size() - 1)
			{
				fileInStream.close();
				std::wstring msg = L"[" + data.Name + L"] ValidateOBJFile (Faces Validation): Unexpected end of file!";
				FAIL() << msg;
			}
			polyCount++;
		}

		if (std::getline(fileInStream, line))
		{
			fileInStream.close();
			std::wstring msg = L"[" + data.Name + L"] ValidateOBJFile: Expecting end of file, but more data is found!";
			FAIL() << msg;
		}

		//
		// ===== Close ================
		//

		fileInStream.close();
	}

	TEST(OBJExport_TestSuite, IcosahedronMeshData_ExportOBJ_CorrectlyExportedOBJData)
	{
		// Arrange
		const auto fileFullPath = symplektRootPath / "Symplekt_OutputData\\UnitTests" / "icosahedronExported.obj";
		const auto geomIOData = GeometryIOData{
			L"icosahedron",
			icosahedronDataVertices,
			icosahedronDataVertexIndices,
			{} // no normals
		};

		// Act
		const auto exportStatus = OBJExporter::Export(geomIOData, fileFullPath);

		// Assert
		EXPECT_EQ(exportStatus, ExportStatus::Complete);
		ValidateOBJFile(fileFullPath, geomIOData);
	}

	TEST(OBJExport_TestSuite, ImportedBentChairOBJData_ExportOBJ_CorrectlyExportedOBJData)
	{
		// Arrange
		const auto importFilePath = symplektRootPath / "Symplekt_ResourceData\\" / "BentChair.obj";
		const auto importStatus = OBJImporter::Import(importFilePath);
		const auto& geomIOData = OBJImporter::Data();
		const auto exportFilePath = symplektRootPath / "Symplekt_OutputData\\UnitTests" / "BentChairExported.obj";

		// Act
		const auto exportStatus = OBJExporter::Export(geomIOData, exportFilePath);

		// Assert
		EXPECT_EQ(importStatus, ImportStatus::Complete);
		EXPECT_EQ(exportStatus, ExportStatus::Complete);
		ValidateOBJFile(exportFilePath, geomIOData);
	}

	TEST(OBJExport_TestSuite, ImportedArcOBJData_ExportOBJ_CorrectlyExportedOBJData)
	{
		// Arrange
		const auto importFilePath = symplektRootPath / "Symplekt_ResourceData\\" / "arc.obj";
		const auto importStatus = OBJImporter::Import(importFilePath);
		const auto& geomIOData = OBJImporter::Data();
		const auto exportFilePath = symplektRootPath / "Symplekt_OutputData\\UnitTests" / "arcExported.obj";

		// Act
		const auto exportStatus = OBJExporter::Export(geomIOData, exportFilePath);

		// Assert
		EXPECT_EQ(importStatus, ImportStatus::Complete);
		EXPECT_EQ(exportStatus, ExportStatus::Complete);
		ValidateOBJFile(exportFilePath, geomIOData);
	}

} // namespace Symplektis::UnitTests