/*! \file  VTKExport_Tests.cpp
 *  \brief Tests for exporting polygonal geometry data to VTK Polydata (*.vtk) files.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   18.10.2021
 *
 */

#include "gtest/gtest.h"

#include "Symplekt_GeometryReps/UnitTests/MeshGeometryDataForTesting.h"

#include "Symplekt_IOService/VTKExporter.h"
#include "Symplekt_IOService/OBJImporter.h"

#include <fstream>

namespace Symplektis::UnitTests
{
	using namespace IOService;

	// set up root directory
	const std::filesystem::path symplektRootPath = DSYMPLEKTIS_ROOT_DIR;

	static void ValidateVTKPolydataFile(const std::filesystem::path& filePath, const GeometryIOData& data)
	{
		//
		// ===== File Validation ================
		//

		EXPECT_FALSE(filePath.extension().empty());
		EXPECT_FALSE(filePath.extension() != ".vtk");

		std::ifstream fileInStream(filePath.c_str(), std::ios::in);
		EXPECT_TRUE(fileInStream.is_open());

		//
		// ===== Header Validation ================
		//

		constexpr size_t nExpectedHeaderLines = 4;

		std::string headerString;
		std::string line;
		for (unsigned int i = 0; i < nExpectedHeaderLines; i++)
		{
			std::getline(fileInStream, line);
			headerString += line + "\n";
		}
		headerString += "\n";

		EXPECT_TRUE(headerString == VTK_Polydata_Header_Str);

		//
		// ===== Points Validation ================
		//

		std::getline(fileInStream, line); // empty line
		std::getline(fileInStream, line); // read polydata POINTS header
		std::stringstream sStream{ line };
		std::string token;
		sStream >> token;
		EXPECT_TRUE(token == "POINTS");
		sStream >> token;

		const size_t nPoints = std::stoi(token);
		EXPECT_TRUE(nPoints == data.Vertices.size());
		sStream >> token;
		EXPECT_TRUE(token == "float");
		std::getline(fileInStream, line); // empty line

		//const double tol = Util::GetCoordinateTolerance();
		for (const auto& dataVert : data.Vertices)
		{
			// point coord line
			if (!std::getline(fileInStream, line))
			{
				fileInStream.close();
				std::wstring msg = L"[" + data.Name + L"] ValidateVTKPolydataFile (point coord line): Unexpected end of file!";
				FAIL() << msg;
			}
			sStream = std::stringstream{ line };
			double x, y, z;
			sStream >> x >> y >> z;
			EXPECT_DOUBLE_EQ(x, dataVert.X());
			EXPECT_DOUBLE_EQ(y, dataVert.Y());
			EXPECT_DOUBLE_EQ(z, dataVert.Z());
		}

		//
		// ===== Polygons Validation ================
		//

		std::getline(fileInStream, line); // empty line
		std::getline(fileInStream, line); // read polydata POLYGONS header
		sStream = std::stringstream{ line };
		sStream >> token;
		EXPECT_TRUE(token == "POLYGONS");
		sStream >> token;

		const size_t nPolygons = std::stoi(token);
		EXPECT_EQ(nPolygons, data.VertexIndices.size());
		sStream >> token;
		const size_t nPolygonEntries = std::stoi(token);
		size_t polygonLineEntries = 0;
		for (const auto& idTuple : data.VertexIndices) polygonLineEntries += (idTuple.size() + 1);
		EXPECT_EQ(nPolygonEntries, polygonLineEntries);

		std::getline(fileInStream, line); // empty line
		for (const auto& polyIds : data.VertexIndices)
		{
			// vertex index line
			if (!std::getline(fileInStream, line))
			{
				fileInStream.close();
				std::wstring msg = L"[" + data.Name + L"] ValidateVTKPolydataFile (vertex index line): Unexpected end of file!";
				FAIL() << msg;
			}
			sStream = std::stringstream{ line };
			unsigned int nVerts;
			sStream >> nVerts;
			EXPECT_EQ(nVerts, polyIds.size());
			if (nVerts >= polyIds.size())
				continue; // skip to avoid access violation

			for (unsigned int j = 0; j < nVerts; j++)
			{
				unsigned int id;
				sStream >> id;
				EXPECT_EQ(id, polyIds[j]);
			}
		}

		if (std::getline(fileInStream, line))
		{
			fileInStream.close();
			std::wstring msg = L"[" + data.Name + L"] ValidateVTKPolydataFile: Expecting end of file, but more data is found!";
			FAIL() << msg;
		}

		//
		// ===== Close ================
		//

		fileInStream.close();
	}

	TEST(VTKExport_TestSuite, IcosahedronMeshData_ExportVTK_CorrectlyExportedPolyData)
	{
		// Arrange
		const auto fileFullPath = symplektRootPath / "Symplekt_OutputData\\UnitTests" / "icosahedron.vtk";
		const auto geomIOData = GeometryIOData{
			L"icosahedron",
			icosahedronDataVertices,
			icosahedronDataVertexIndices,
			{} // no normals
		};

		// Act
		const auto exportStatus = VTKExporter::Export(geomIOData, fileFullPath);

		// Assert
		EXPECT_EQ(exportStatus, ExportStatus::Complete);
		ValidateVTKPolydataFile(fileFullPath, geomIOData);
	}

	TEST(VTKExport_TestSuite, ImportedSFBunnyOBJData_ExportVTK_CorrectlyExportedPolyData)
	{
		// Arrange
		const auto importFilePath = symplektRootPath / "Symplekt_ResourceData\\" / "bunnySimple.obj";
		const auto importStatus = OBJImporter::Import(importFilePath);
		const auto& geomIOData = OBJImporter::Data();
		const auto exportFilePath = symplektRootPath / "Symplekt_OutputData\\UnitTests" / "bunnySimple.vtk";

		// Act
		const auto exportStatus = VTKExporter::Export(geomIOData, exportFilePath);

		// Assert
		EXPECT_EQ(importStatus, ImportStatus::Complete);
		EXPECT_EQ(exportStatus, ExportStatus::Complete);
		ValidateVTKPolydataFile(exportFilePath, geomIOData);
	}

	TEST(VTKExport_TestSuite, ImportedBentChairOBJData_ExportVTK_CorrectlyExportedPolyData)
	{
		// Arrange
		const auto importFilePath = symplektRootPath / "Symplekt_ResourceData\\" / "BentChair.obj";
		const auto importStatus = OBJImporter::Import(importFilePath);
		const auto& geomIOData = OBJImporter::Data();
		const auto exportFilePath = symplektRootPath / "Symplekt_OutputData\\UnitTests" / "BentChair.vtk";

		// Act
		const auto exportStatus = VTKExporter::Export(geomIOData, exportFilePath);

		// Assert
		EXPECT_EQ(importStatus, ImportStatus::Complete);
		EXPECT_EQ(exportStatus, ExportStatus::Complete);
		ValidateVTKPolydataFile(exportFilePath, geomIOData);
	}

	TEST(VTKExport_TestSuite, ImportedArcOBJData_ExportVTK_CorrectlyExportedPolyData)
	{
		// Arrange
		const auto importFilePath = symplektRootPath / "Symplekt_ResourceData\\" / "arc.obj";
		const auto importStatus = OBJImporter::Import(importFilePath);
		const auto& geomIOData = OBJImporter::Data();
		const auto exportFilePath = symplektRootPath / "Symplekt_OutputData\\UnitTests" / "arc.vtk";

		// Act
		const auto exportStatus = VTKExporter::Export(geomIOData, exportFilePath);

		// Assert
		EXPECT_EQ(importStatus, ImportStatus::Complete);
		EXPECT_EQ(exportStatus, ExportStatus::Complete);
		ValidateVTKPolydataFile(exportFilePath, geomIOData);
	}


} // Symplektis::UnitTests