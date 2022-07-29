/*! \file  IncrementalRemeshing_Tests.cpp
 *  \brief Unit tests for the "incremental remeshing" functionality.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   29.7.2022
 *
 */

#include "gtest/gtest.h"

#include "Symplekt_GeometryKernel/MeshGeometryDataTypes.h"

#include "Symplekt_Algorithms/IncrementalRemesher.h"

namespace Symplektis::UnitTests
{
	using namespace GeometryKernel;
	using namespace Algorithms;

	TEST(IncrementalRemeshing_Tests, QuadReferencedMesh_Process_MeshInvalid)
	{
		// Arrange
		ReferencedMeshGeometryData meshData{ L"InvalidData" };
		meshData.Type = PolyMeshType::Quadrilateral;

		// Act
		const auto resultState = IncrementalRemesher::Process(meshData, IncrementalRemeshingSettings());

		// Assert
		EXPECT_EQ(resultState, MeshProcessingStatus::InvalidInput);
	}

	TEST(IncrementalRemeshing_Tests, MixedReferencedMesh_Process_MeshInvalid)
	{
		// Arrange
		ReferencedMeshGeometryData meshData{ L"InvalidData" };
		meshData.Type = PolyMeshType::TriAndQuadMixed;

		// Act
		const auto resultState = IncrementalRemesher::Process(meshData, IncrementalRemeshingSettings());

		// Assert
		EXPECT_EQ(resultState, MeshProcessingStatus::InvalidInput);
	}

	TEST(IncrementalRemeshing_Tests, QuadBufferMesh_Process_MeshInvalid)
	{
		// Arrange
		BufferMeshGeometryData meshData{ L"InvalidData" };
		meshData.Type = PolyMeshType::Quadrilateral;

		// Act
		const auto resultState = IncrementalRemesher::Process(meshData, IncrementalRemeshingSettings());

		// Assert
		EXPECT_EQ(resultState, MeshProcessingStatus::InvalidInput);
	}

	TEST(IncrementalRemeshing_Tests, MixedBufferMesh_Process_MeshInvalid)
	{
		// Arrange
		BufferMeshGeometryData meshData{ L"InvalidData" };
		meshData.Type = PolyMeshType::TriAndQuadMixed;

		// Act
		const auto resultState = IncrementalRemesher::Process(meshData, IncrementalRemeshingSettings());

		// Assert
		EXPECT_EQ(resultState, MeshProcessingStatus::InvalidInput);
	}

} // namespace Symplektis::UnitTests