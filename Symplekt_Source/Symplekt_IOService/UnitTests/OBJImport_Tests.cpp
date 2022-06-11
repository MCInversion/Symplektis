/*! \file  OBJImport_Tests.cpp
 *  \brief Tests for importing files of Wavefront OBJ format.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   10.10.2021
 *
 */

#include "gtest/gtest.h"

#include "../OBJImporter.h"

namespace Symplektis::UnitTests
{
	using namespace IOService;
	TEST(OBJImport_TestSuite, SFBunnyOBJFile_Import_ImportedSFBunnyData)
	{
		// Arrange
		const auto currPath = std::filesystem::current_path(); // assumed "{SymplektisRepo_root}\\build\\Symplekt_IOService\\UnitTests\\{Release | Debug}"
		const auto parentPath = currPath.parent_path().parent_path().parent_path().parent_path();
		const auto fileFullPath = parentPath / "Symplekt_ResourceData\\" / "bunnySimple.obj";

		// Act
		const auto importStatus = OBJImporter::GetInstance().Import(fileFullPath);
		const auto& geomData = OBJImporter::GetInstance().Data();

		// Assert
		EXPECT_EQ(importStatus, ImportStatus::Complete);
		EXPECT_EQ(geomData.Name, L"bunnySimple");
		EXPECT_EQ(geomData.Vertices.size(), 2503);
		EXPECT_EQ(geomData.VertexIndices.size(), 4968);
		EXPECT_EQ(geomData.VertexNormals.size(), 0);
	}

	TEST(OBJImport_TestSuite, SFBunnyWithoutHolesOBJFile_Import_ImportedSFBunnyWithoutHolesData)
	{
		// Arrange
		const auto currPath = std::filesystem::current_path(); // assumed "{SymplektisRepo_root}\\build\\Symplekt_IOService\\UnitTests\\{Release | Debug}"
		const auto parentPath = currPath.parent_path().parent_path().parent_path().parent_path();
		const auto fileFullPath = parentPath / "Symplekt_ResourceData\\" / "bunnySimple_no_holes.obj";

		// Act
		const auto importStatus = OBJImporter::GetInstance().Import(fileFullPath);
		const auto& geomData = OBJImporter::GetInstance().Data();

		// Assert
		EXPECT_EQ(importStatus, ImportStatus::Complete);
		EXPECT_EQ(geomData.Name, L"bunnySimple_no_holes");
		EXPECT_EQ(geomData.Vertices.size(), 2503);
		EXPECT_EQ(geomData.VertexIndices.size(), 5002);
		EXPECT_EQ(geomData.VertexNormals.size(), 2503);
	}

	TEST(OBJImport_TestSuite, ArcOBJFile_Import_ImportedArcData)
	{
		// Arrange
		const auto currPath = std::filesystem::current_path(); // assumed "{SymplektisRepo_root}\\build\\Symplekt_IOService\\UnitTests\\{Release | Debug}"
		const auto parentPath = currPath.parent_path().parent_path().parent_path().parent_path();
		const auto fileFullPath = parentPath / "Symplekt_ResourceData\\" / "arc.obj";

		// Act
		const auto importStatus = OBJImporter::GetInstance().Import(fileFullPath);
		const auto& geomData = OBJImporter::GetInstance().Data();

		// Assert
		EXPECT_EQ(importStatus, ImportStatus::Complete);
		EXPECT_EQ(geomData.Name, L"arc");
		EXPECT_EQ(geomData.Vertices.size(), 594);
		EXPECT_EQ(geomData.VertexIndices.size(), 592);
		EXPECT_EQ(geomData.VertexNormals.size(), 594);
	}

	TEST(OBJImport_TestSuite, BentChairOBJFile_Import_ImportedBentChairData)
	{
		// Arrange
		const auto currPath = std::filesystem::current_path(); // assumed "{SymplektisRepo_root}\\build\\Symplekt_IOService\\UnitTests\\{Release | Debug}"
		const auto parentPath = currPath.parent_path().parent_path().parent_path().parent_path();
		const auto fileFullPath = parentPath / "Symplekt_ResourceData\\" / "BentChair.obj";

		// Act
		const auto importStatus = OBJImporter::GetInstance().Import(fileFullPath);
		const auto& geomData = OBJImporter::GetInstance().Data();

		// Assert
		EXPECT_EQ(importStatus, ImportStatus::Complete);
		EXPECT_EQ(geomData.Name, L"BentChair");
		EXPECT_EQ(geomData.Vertices.size(), 179);
		EXPECT_EQ(geomData.VertexIndices.size(), 304);
		EXPECT_EQ(geomData.VertexNormals.size(), 179);
	}
}