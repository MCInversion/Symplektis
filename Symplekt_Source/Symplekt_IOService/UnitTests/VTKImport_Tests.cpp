/*! \file  VTKImport_Tests.cpp
 *  \brief Tests for importing files of VTK POLYDATA (.*vtk) format.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   10.6.2022
 *
 */

#include "gtest/gtest.h"

#include "Symplekt_IOService/VTKImporter.h"

namespace Symplektis::UnitTests
{
	using namespace IOService;
	
	// set up root directory
	const std::filesystem::path symplektRootPath = DSYMPLEKTIS_ROOT_DIR;
	TEST(VTKImport_TestSuite, SFBunnyVTKFile_Import_ImportedSFBunnyData)
	{
		// Arrange
		const auto fileFullPath = symplektRootPath / "Symplekt_ResourceData\\" / "bunnySimple.vtk";

		// Act
		const auto importStatus = VTKImporter::Import(fileFullPath);
		const auto& geomData = VTKImporter::Data();

		// Assert
		EXPECT_EQ(importStatus, ImportStatus::Complete);
		EXPECT_EQ(geomData.Name, L"bunnySimple");
		EXPECT_EQ(geomData.Vertices.size(), 2503);
		EXPECT_EQ(geomData.VertexIndices.size(), 4968);
		EXPECT_EQ(geomData.VertexNormals.size(), 0);
	}

	TEST(VTKImport_TestSuite, ArcVTKFile_Import_ImportedArcData)
	{
		// Arrange
		const auto fileFullPath = symplektRootPath / "Symplekt_ResourceData\\" / "arc.vtk";

		// Act
		const auto importStatus = VTKImporter::Import(fileFullPath);
		const auto& geomData = VTKImporter::Data();

		// Assert
		EXPECT_EQ(importStatus, ImportStatus::Complete);
		EXPECT_EQ(geomData.Name, L"arc");
		EXPECT_EQ(geomData.Vertices.size(), 594);
		EXPECT_EQ(geomData.VertexIndices.size(), 592);
		EXPECT_EQ(geomData.VertexNormals.size(), 0);
	}
}