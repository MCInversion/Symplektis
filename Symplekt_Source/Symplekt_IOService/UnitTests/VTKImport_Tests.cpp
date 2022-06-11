/*! \file  VTKImport_Tests.cpp
 *  \brief Tests for importing files of VTK POLYDATA (.*vtk) format.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   10.6.2022
 *
 */

#include "gtest/gtest.h"

#include "../VTKImporter.h"

namespace Symplektis::UnitTests
{
	using namespace IOService;
	TEST(VTKImport_TestSuite, SFBunnyVTKFile_Import_ImportedSFBunnyData)
	{
		// Arrange
		const auto currPath = std::filesystem::current_path(); // assumed "{SymplektisRepo_root}\\build\\Symplekt_IOService\\UnitTests\\{Release | Debug}"
		const auto parentPath = currPath.parent_path().parent_path().parent_path().parent_path();
		const auto fileFullPath = parentPath / "Symplekt_ResourceData\\" / "bunnySimple.vtk";

		// Act
		const auto importStatus = VTKImporter::GetInstance().Import(fileFullPath);
		const auto& geomData = VTKImporter::GetInstance().Data();

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
		const auto currPath = std::filesystem::current_path(); // assumed "{SymplektisRepo_root}\\build\\Symplekt_IOService\\UnitTests\\{Release | Debug}"
		const auto parentPath = currPath.parent_path().parent_path().parent_path().parent_path();
		const auto fileFullPath = parentPath / "Symplekt_ResourceData\\" / "arc.vtk";

		// Act
		const auto importStatus = VTKImporter::GetInstance().Import(fileFullPath);
		const auto& geomData = VTKImporter::GetInstance().Data();

		// Assert
		EXPECT_EQ(importStatus, ImportStatus::Complete);
		EXPECT_EQ(geomData.Name, L"arc");
		EXPECT_EQ(geomData.Vertices.size(), 594);
		EXPECT_EQ(geomData.VertexIndices.size(), 592);
		EXPECT_EQ(geomData.VertexNormals.size(), 0);
	}
}