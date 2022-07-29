/*! \file  BaseGeometryHandle_Tests.cpp
 *  \brief Tests for importing files of Wavefront OBJ format.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   10.10.2021
 *
 */

#include "gtest/gtest.h"

#include "Symplekt_GeometryKernel/MeshGeometryDataTypes.h"

#include "Symplekt_IOService/OBJImporter.h"
#include "Symplekt_IOService/BaseGeometryImportHandle.h"

namespace Symplektis::UnitTests
{
	using namespace IOService;

	// set up root directory
	const std::filesystem::path symplektRootPath = DSYMPLEKTIS_ROOT_DIR;
	
	TEST(BaseGeometryImportHandle_Suite, SFBunnyOBJFile_ImportAndConvertToRefGeom_CorrectReferencedGeometrySFBunnyData)
	{
		// Arrange
		const auto fileFullPath = symplektRootPath / "Symplekt_ResourceData\\" / "bunnySimple.obj";

		// Act
		const auto importStatus = OBJImporter::Import(fileFullPath);
		const auto& geomData = OBJImporter::Data();
		const auto& meshData = ConvertIODataToReferencedMeshGeometryData(geomData);

		// Assert
		EXPECT_EQ(importStatus, ImportStatus::Complete);
		EXPECT_EQ(meshData.Name, L"bunnySimple");
		EXPECT_EQ(meshData.Type, GeometryKernel::PolyMeshType::Triangular);
		EXPECT_EQ(meshData.Vertices.size(), 2503);
		EXPECT_EQ(meshData.HalfEdges.size(), 14946);
		EXPECT_EQ(meshData.Edges.size(), 7473);
		EXPECT_EQ(meshData.VertexNormals.size(), 0);
		EXPECT_EQ(meshData.Faces.size(), 4968);
		EXPECT_EQ(meshData.BoundaryCycles.size(), 4);
	}

	TEST(BaseGeometryImportHandle_Suite, SFBunnyWithoutHolesOBJFile_ImportAndConvertToRefGeom_CorrectReferencedGeometrySFBunnyWithoutHolesData)
	{
		// Arrange
		const auto fileFullPath = symplektRootPath / "Symplekt_ResourceData\\" / "bunnySimple_no_holes.obj";

		// Act
		const auto importStatus = OBJImporter::Import(fileFullPath);
		const auto& geomData = OBJImporter::Data();
		const auto& meshData = ConvertIODataToReferencedMeshGeometryData(geomData);

		// Assert
		EXPECT_EQ(importStatus, ImportStatus::Complete);
		EXPECT_EQ(meshData.Name, L"bunnySimple_no_holes");
		EXPECT_EQ(meshData.Type, GeometryKernel::PolyMeshType::Triangular);
		EXPECT_EQ(meshData.Vertices.size(), 2503);
		EXPECT_EQ(meshData.HalfEdges.size(), 15006);
		EXPECT_EQ(meshData.Edges.size(), 7503);
		EXPECT_EQ(meshData.VertexNormals.size(), 2503);
		EXPECT_EQ(meshData.Faces.size(), 5002);
		EXPECT_EQ(meshData.BoundaryCycles.size(), 0);
	}

	TEST(BaseGeometryImportHandle_Suite, ArcOBJFile_ImportAndConvertToRefGeom_CorrectReferencedGeometryArcData)
	{
		// Arrange
		const auto fileFullPath = symplektRootPath / "Symplekt_ResourceData\\" / "arc.obj";

		// Act
		const auto importStatus = OBJImporter::Import(fileFullPath);
		const auto& geomData = OBJImporter::Data();
		const auto& meshData = ConvertIODataToReferencedMeshGeometryData(geomData);

		// Assert
		EXPECT_EQ(importStatus, ImportStatus::Complete);
		EXPECT_EQ(meshData.Name, L"arc");
		EXPECT_EQ(meshData.Type, GeometryKernel::PolyMeshType::Quadrilateral);
		EXPECT_EQ(meshData.Vertices.size(), 594);
		EXPECT_EQ(meshData.HalfEdges.size(), 2368);
		EXPECT_EQ(meshData.Edges.size(), 1184);
		EXPECT_EQ(meshData.VertexNormals.size(), 594);
		EXPECT_EQ(meshData.Faces.size(), 592);
		EXPECT_EQ(meshData.BoundaryCycles.size(), 0);
	}

	TEST(BaseGeometryImportHandle_Suite, BentChairOBJFile_ImportAndConvertToRefGeom_CorrectReferencedGeometryBentChairData)
	{
		// Arrange
		const auto fileFullPath = symplektRootPath / "Symplekt_ResourceData\\" / "BentChair.obj";

		// Act
		const auto importStatus = OBJImporter::Import(fileFullPath);
		const auto& geomData = OBJImporter::Data();
		const auto& meshData = ConvertIODataToReferencedMeshGeometryData(geomData);

		// Assert
		EXPECT_EQ(importStatus, ImportStatus::Complete);
		EXPECT_EQ(meshData.Name, L"BentChair");
		EXPECT_EQ(meshData.Type, GeometryKernel::PolyMeshType::Triangular);
		EXPECT_EQ(meshData.Vertices.size(), 179);
		EXPECT_EQ(meshData.HalfEdges.size(), 968);
		EXPECT_EQ(meshData.Edges.size(), 484);
		EXPECT_EQ(meshData.VertexNormals.size(), 179);
		EXPECT_EQ(meshData.Faces.size(), 304);
		EXPECT_EQ(meshData.BoundaryCycles.size(), 3);
	}

	TEST(BaseGeometryImportHandle_Suite, SFBunnyOBJFile_ImportAndConvertToBuffGeom_CorrectBufferGeometrySFBunnyData)
	{
		// Arrange
		const auto fileFullPath = symplektRootPath / "Symplekt_ResourceData\\" / "bunnySimple.obj";

		// Act
		const auto importStatus = OBJImporter::Import(fileFullPath);
		const auto& geomData = OBJImporter::Data();
		const auto& meshData = ConvertIODataToBufferMeshGeometryData(geomData);

		// Assert
		EXPECT_EQ(importStatus, ImportStatus::Complete);
		EXPECT_EQ(meshData.Name, L"bunnySimple");
		EXPECT_EQ(meshData.Type, GeometryKernel::PolyMeshType::Triangular);
		EXPECT_EQ(meshData.VertexCoords.size(), 7509);
		EXPECT_EQ(meshData.VertexNormalCoords.size(), 0);
		EXPECT_EQ(meshData.VertexIndices.size(), 14904);
	}

	TEST(BaseGeometryImportHandle_Suite, SFBunnyWithoutHolesOBJFile_ImportAndConvertToBuffGeom_CorrectBufferGeometrySFBunnyWithoutHolesData)
	{
		// Arrange
		const auto fileFullPath = symplektRootPath / "Symplekt_ResourceData\\" / "bunnySimple_no_holes.obj";

		// Act
		const auto importStatus = OBJImporter::Import(fileFullPath);
		const auto& geomData = OBJImporter::Data();
		const auto& meshData = ConvertIODataToBufferMeshGeometryData(geomData);

		// Assert
		EXPECT_EQ(importStatus, ImportStatus::Complete);
		EXPECT_EQ(meshData.Name, L"bunnySimple_no_holes");
		EXPECT_EQ(meshData.Type, GeometryKernel::PolyMeshType::Triangular);
		EXPECT_EQ(meshData.VertexCoords.size(), 7509);
		EXPECT_EQ(meshData.VertexNormalCoords.size(), 7509);
		EXPECT_EQ(meshData.VertexIndices.size(), 15006);
	}

	TEST(BaseGeometryImportHandle_Suite, ArcOBJFile_ImportAndConvertToBuffGeom_CorrectBufferGeometryArcData)
	{
		// Arrange
		const auto fileFullPath = symplektRootPath / "Symplekt_ResourceData\\" / "arc.obj";

		// Act
		const auto importStatus = OBJImporter::Import(fileFullPath);
		const auto& geomData = OBJImporter::Data();
		const auto& meshData = ConvertIODataToBufferMeshGeometryData(geomData);

		// Assert
		EXPECT_EQ(importStatus, ImportStatus::Complete);
		EXPECT_EQ(meshData.Name, L"arc");
		EXPECT_EQ(meshData.Type, GeometryKernel::PolyMeshType::Quadrilateral);
		EXPECT_EQ(meshData.VertexCoords.size(), 1782);
		EXPECT_EQ(meshData.VertexNormalCoords.size(), 1782);
		EXPECT_EQ(meshData.VertexIndices.size(), 3552);
	}

	TEST(BaseGeometryImportHandle_Suite, BentChairOBJFile_ImportAndConvertToBuffGeom_CorrectBufferGeometryBentChairData)
	{
		// Arrange
		const auto fileFullPath = symplektRootPath / "Symplekt_ResourceData\\" / "BentChair.obj";

		// Act
		const auto importStatus = OBJImporter::Import(fileFullPath);
		const auto& geomData = OBJImporter::Data();
		const auto& meshData = ConvertIODataToBufferMeshGeometryData(geomData);

		// Assert
		EXPECT_EQ(importStatus, ImportStatus::Complete);
		EXPECT_EQ(meshData.Name, L"BentChair");
		EXPECT_EQ(meshData.Type, GeometryKernel::PolyMeshType::Triangular);
		EXPECT_EQ(meshData.VertexCoords.size(), 537);
		EXPECT_EQ(meshData.VertexNormalCoords.size(), 537);
		EXPECT_EQ(meshData.VertexIndices.size(), 912);
	}
	
} // Symplektis::UnitTests