/*! \file  BaseGeometryHandle_Tests.cpp
 *  \brief Tests for importing files of Wavefront OBJ format.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   10.10.2021
 *
 */

#include "gtest/gtest.h"

#include "../../Symplekt_GeometryReps/MeshGeometryDataTypes.h"

#include "../OBJImporter.h"
#include "../BaseGeometryImportHandle.h"

namespace Symplektis::UnitTests
{
	using namespace IOService;
	
	TEST(BaseGeometryImportHandle_Suite, SFBunnyOBJFile_ImportAndConvertToRefGeom_ReferencedGeometrySFBunnyData)
	{
		// Arrange
		const auto currPath = std::filesystem::current_path(); // assumed "{SymplektisRepo_root}\\build\\Symplekt_IOService\\UnitTests\\{Release | Debug}"
		const auto parentPath = currPath.parent_path().parent_path().parent_path().parent_path();
		const auto fileFullPath = parentPath / "Symplekt_ResourceData\\" / "bunnySimple.obj";

		// Act
		const auto importStatus = OBJImporter::GetInstance().Import(fileFullPath);
		const auto& geomData = OBJImporter::GetInstance().Data();
		const auto& meshData = ConvertIODataToReferencedMeshGeometryData(geomData);

		// Assert
		EXPECT_EQ(importStatus, ImportStatus::Complete);
		EXPECT_EQ(meshData.Name, L"bunnySimple");
		EXPECT_EQ(meshData.Vertices.size(), 2503);
		EXPECT_EQ(meshData.HalfEdges.size(), 14946);
		EXPECT_EQ(meshData.Edges.size(), 7473);
		EXPECT_EQ(meshData.VertexNormals.size(), 0);
		EXPECT_EQ(meshData.Faces.size(), 4968);
		EXPECT_EQ(meshData.BoundaryCycles.size(), 4);
	}

	TEST(BaseGeometryImportHandle_Suite, SFBunnyWithoutHolesOBJFile_ImportAndConvertToRefGeom_ReferencedGeometrySFBunnyWithoutHolesData)
	{
		// Arrange
		const auto currPath = std::filesystem::current_path(); // assumed "{SymplektisRepo_root}\\build\\Symplekt_IOService\\UnitTests\\{Release | Debug}"
		const auto parentPath = currPath.parent_path().parent_path().parent_path().parent_path();
		const auto fileFullPath = parentPath / "Symplekt_ResourceData\\" / "bunnySimple_no_holes.obj";

		// Act
		const auto importStatus = OBJImporter::GetInstance().Import(fileFullPath);
		const auto& geomData = OBJImporter::GetInstance().Data();
		const auto& meshData = ConvertIODataToReferencedMeshGeometryData(geomData);

		// Assert
		EXPECT_EQ(importStatus, ImportStatus::Complete);
		EXPECT_EQ(meshData.Name, L"bunnySimple_no_holes");
		EXPECT_EQ(meshData.Vertices.size(), 2503);
		EXPECT_EQ(meshData.HalfEdges.size(), 15006);
		EXPECT_EQ(meshData.Edges.size(), 7503);
		EXPECT_EQ(meshData.VertexNormals.size(), 2503);
		EXPECT_EQ(meshData.Faces.size(), 5002);
		EXPECT_EQ(meshData.BoundaryCycles.size(), 0);
	}

	TEST(BaseGeometryImportHandle_Suite, ArcOBJFile_ImportAndConvertToRefGeom_ReferencedGeometryArcData)
	{
		// Arrange
		const auto currPath = std::filesystem::current_path(); // assumed "{SymplektisRepo_root}\\build\\Symplekt_IOService\\UnitTests\\{Release | Debug}"
		const auto parentPath = currPath.parent_path().parent_path().parent_path().parent_path();
		const auto fileFullPath = parentPath / "Symplekt_ResourceData\\" / "arc.obj";

		// Act
		const auto importStatus = OBJImporter::GetInstance().Import(fileFullPath);
		const auto& geomData = OBJImporter::GetInstance().Data();
		const auto& meshData = ConvertIODataToReferencedMeshGeometryData(geomData);

		// Assert
		EXPECT_EQ(importStatus, ImportStatus::Complete);
		EXPECT_EQ(meshData.Name, L"arc");
		EXPECT_EQ(meshData.Vertices.size(), 594);
		EXPECT_EQ(meshData.HalfEdges.size(), 2368);
		EXPECT_EQ(meshData.Edges.size(), 1184);
		EXPECT_EQ(meshData.VertexNormals.size(), 594);
		EXPECT_EQ(meshData.Faces.size(), 592);
		EXPECT_EQ(meshData.BoundaryCycles.size(), 0);
	}

	TEST(BaseGeometryImportHandle_Suite, BentChairOBJFile_ImportAndConvertToRefGeom_ReferencedGeometryBentChairData)
	{
		// Arrange
		const auto currPath = std::filesystem::current_path(); // assumed "{SymplektisRepo_root}\\build\\Symplekt_IOService\\UnitTests\\{Release | Debug}"
		const auto parentPath = currPath.parent_path().parent_path().parent_path().parent_path();
		const auto fileFullPath = parentPath / "Symplekt_ResourceData\\" / "BentChair.obj";

		// Act
		const auto importStatus = OBJImporter::GetInstance().Import(fileFullPath);
		const auto& geomData = OBJImporter::GetInstance().Data();
		const auto& meshData = ConvertIODataToReferencedMeshGeometryData(geomData);

		// Assert
		EXPECT_EQ(importStatus, ImportStatus::Complete);
		EXPECT_EQ(meshData.Name, L"BentChair");
		EXPECT_EQ(meshData.Vertices.size(), 179);
		EXPECT_EQ(meshData.HalfEdges.size(), 968);
		EXPECT_EQ(meshData.Edges.size(), 484);
		EXPECT_EQ(meshData.VertexNormals.size(), 179);
		EXPECT_EQ(meshData.Faces.size(), 304);
		EXPECT_EQ(meshData.BoundaryCycles.size(), 3);
	}

	TEST(BaseGeometryImportHandle_Suite, SFBunnyOBJFile_ImportAndConvertToBuffGeom_BufferGeometrySFBunnyData)
	{
		// Arrange
		const auto currPath = std::filesystem::current_path(); // assumed "{SymplektisRepo_root}\\build\\Symplekt_IOService\\UnitTests\\{Release | Debug}"
		const auto parentPath = currPath.parent_path().parent_path().parent_path().parent_path();
		const auto fileFullPath = parentPath / "Symplekt_ResourceData\\" / "bunnySimple.obj";

		// Act
		const auto importStatus = OBJImporter::GetInstance().Import(fileFullPath);
		const auto& geomData = OBJImporter::GetInstance().Data();
		const auto& meshData = ConvertIODataToBufferMeshGeometryData(geomData);

		// Assert
		EXPECT_EQ(importStatus, ImportStatus::Complete);
		EXPECT_EQ(meshData.Name, L"bunnySimple");
		EXPECT_EQ(meshData.VertexCoords.size(), 7509);
		EXPECT_EQ(meshData.VertexNormalCoords.size(), 0);
		EXPECT_EQ(meshData.VertexIndices.size(), 14904);
	}

	TEST(BaseGeometryImportHandle_Suite, SFBunnyWithoutHolesOBJFile_ImportAndConvertToBuffGeom_BufferGeometrySFBunnyWithoutHolesData)
	{
		// Arrange
		const auto currPath = std::filesystem::current_path(); // assumed "{SymplektisRepo_root}\\build\\Symplekt_IOService\\UnitTests\\{Release | Debug}"
		const auto parentPath = currPath.parent_path().parent_path().parent_path().parent_path();
		const auto fileFullPath = parentPath / "Symplekt_ResourceData\\" / "bunnySimple_no_holes.obj";

		// Act
		const auto importStatus = OBJImporter::GetInstance().Import(fileFullPath);
		const auto& geomData = OBJImporter::GetInstance().Data();
		const auto& meshData = ConvertIODataToBufferMeshGeometryData(geomData);

		// Assert
		EXPECT_EQ(importStatus, ImportStatus::Complete);
		EXPECT_EQ(meshData.Name, L"bunnySimple_no_holes");
		EXPECT_EQ(meshData.VertexCoords.size(), 7509);
		EXPECT_EQ(meshData.VertexNormalCoords.size(), 7509);
		EXPECT_EQ(meshData.VertexIndices.size(), 15006);
	}

	TEST(BaseGeometryImportHandle_Suite, ArcOBJFile_ImportAndConvertToBuffGeom_BufferGeometryArcData)
	{
		// Arrange
		const auto currPath = std::filesystem::current_path(); // assumed "{SymplektisRepo_root}\\build\\Symplekt_IOService\\UnitTests\\{Release | Debug}"
		const auto parentPath = currPath.parent_path().parent_path().parent_path().parent_path();
		const auto fileFullPath = parentPath / "Symplekt_ResourceData\\" / "arc.obj";

		// Act
		const auto importStatus = OBJImporter::GetInstance().Import(fileFullPath);
		const auto& geomData = OBJImporter::GetInstance().Data();
		const auto& meshData = ConvertIODataToBufferMeshGeometryData(geomData);

		// Assert
		EXPECT_EQ(importStatus, ImportStatus::Complete);
		EXPECT_EQ(meshData.Name, L"arc");
		EXPECT_EQ(meshData.VertexCoords.size(), 1782);
		EXPECT_EQ(meshData.VertexNormalCoords.size(), 1782);
		EXPECT_EQ(meshData.VertexIndices.size(), 3552);
	}

	TEST(BaseGeometryImportHandle_Suite, BentChairOBJFile_ImportAndConvertToBuffGeom_BufferGeometryBentChairData)
	{
		// Arrange
		const auto currPath = std::filesystem::current_path(); // assumed "{SymplektisRepo_root}\\build\\Symplekt_IOService\\UnitTests\\{Release | Debug}"
		const auto parentPath = currPath.parent_path().parent_path().parent_path().parent_path();
		const auto fileFullPath = parentPath / "Symplekt_ResourceData\\" / "BentChair.obj";

		// Act
		const auto importStatus = OBJImporter::GetInstance().Import(fileFullPath);
		const auto& geomData = OBJImporter::GetInstance().Data();
		const auto& meshData = ConvertIODataToBufferMeshGeometryData(geomData);

		// Assert
		EXPECT_EQ(importStatus, ImportStatus::Complete);
		EXPECT_EQ(meshData.Name, L"BentChair");
		EXPECT_EQ(meshData.VertexCoords.size(), 537);
		EXPECT_EQ(meshData.VertexNormalCoords.size(), 537);
		EXPECT_EQ(meshData.VertexIndices.size(), 912);
	}
	
} // Symplektis::UnitTests