/*!  \file IncrementalRemesher.cpp
 *   \brief Implementation of an object for incremental remeshing of a mesh geometry data.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   26.7.2022
*/

#include "IncrementalRemesher.h"

#include "Symplekt_GeometryKernel/FaceUtils.h"

#include <variant>
#include <algorithm>

using namespace Symplektis::GeometryKernel;

namespace Symplektis::Algorithms
{
	//-----------------------------------------------------------------------------
	/*! \brief Re-evaluates input ReferencedMeshGeometryData for whether all of its faces are triangle faces.
	*   \param[in] meshData    ReferencedMeshGeometryData to be re-evaluated.
	*   \return true if all faces in meshData are triangle faces.
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   29.7.2022
	*/
	//-----------------------------------------------------------------------------
	static bool ReEvaluateReferencedTriangleMeshType(const ReferencedMeshGeometryData& meshData)
	{
		return std::ranges::all_of(meshData.Faces, 
			[](const auto& face) { return IsATriangle(face); });
	}

	//-----------------------------------------------------------------------------
	/*! \brief Re-evaluates input BufferMeshGeometryData for whether all of its triangulations are of size 1.
	*   \param[in] meshData    BufferMeshGeometryData to be re-evaluated.
	*   \return true if all triangulation indices in meshData are of size 1.
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   29.7.2022
	*/
	//-----------------------------------------------------------------------------
	static bool ReEvaluateBufferTriangleMeshType(const BufferMeshGeometryData& meshData)
	{
		return std::ranges::all_of(meshData.TriangulationIndices,
			[](const auto& triIds) { return triIds.size() == 1; });
	}

	//-----------------------------------------------------------------------------
	/*! \brief Evaluates input mesh geometry data for whether it is triangular.
	*   \param[in] meshDataVar              ReferencedMeshGeometryData or BufferMeshGeometryData variant to be re-evaluated.
	*	\param[in] forceTypeVerification    if true, and input mesh type is PolyMeshType::Arbitrary a check for triangular mesh type will be forced.
	*   \return true if input mesh geometry data is triangular.
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   29.7.2022
	*/
	//-----------------------------------------------------------------------------
	static bool IsFullyTriangular(const std::variant<ReferencedMeshGeometryData, BufferMeshGeometryData>& meshDataVar, const bool& forceTypeVerification)
	{
		// read type from variant
		PolyMeshType meshType;
		if (std::holds_alternative<ReferencedMeshGeometryData>(meshDataVar))
			meshType = std::get<ReferencedMeshGeometryData>(meshDataVar).Type;
		else
			meshType = std::get<BufferMeshGeometryData>(meshDataVar).Type;
		// ----------------


		if (meshType == PolyMeshType::Triangular)
			return true;

		if (meshType == PolyMeshType::TriAndQuadMixed || meshType == PolyMeshType::Quadrilateral)
			return false;

		// meshType == PolyMeshType::Arbitrary

		if (forceTypeVerification)
		{
			if (std::holds_alternative<ReferencedMeshGeometryData>(meshDataVar))
				return ReEvaluateReferencedTriangleMeshType(std::get<ReferencedMeshGeometryData>(meshDataVar));

			return ReEvaluateBufferTriangleMeshType(std::get<BufferMeshGeometryData>(meshDataVar));
		}

		return false;
	}

	MeshProcessingStatus IncrementalRemesher::Process(ReferencedMeshGeometryData& meshData, const IncrementalRemeshingSettings& settings)
	{
		if (!IsFullyTriangular(meshData, settings.ForceMeshTypeVerification))
		{
			return MeshProcessingStatus::InvalidInput;
		}

		auto processingStatus = MeshProcessingStatus::AlgorithmInProgress;

		// Preprocess(); // compute normals if meshData.VertexNormals.empty()
		const auto origMeshDataPtr = (settings.UseBackProjection ? std::make_shared<ReferencedMeshGeometryData>(meshData) : nullptr);

		for (unsigned int s = 0; s < settings.NIterations; s++)
		{
			// SplitLongEdges(meshData, settings.TargetEdgeLength, settings.IsAdaptive, processingStatus);
			VERIFY_MESH_PROCESSING_STATUS(processingStatus);

			// CollapseShortEdges(meshData, settings.TargetEdgeLength, settings.IsAdaptive, processingStatus);
			VERIFY_MESH_PROCESSING_STATUS(processingStatus);

			// FlipEdges(meshData, processingStatus);
			VERIFY_MESH_PROCESSING_STATUS(processingStatus);

			// TangentialSmoothing(meshData, settings.NTanSmoothingSteps, processingStatus);
			VERIFY_MESH_PROCESSING_STATUS(processingStatus);

			if (settings.UseBackProjection)
			{
				// BackProjectVerticesOntoOriginalSurfacePositions(meshData, origMeshDataPtr, processingStatus);
			}
		}

		return MeshProcessingStatus::Complete;
	}

	MeshProcessingStatus IncrementalRemesher::Process(BufferMeshGeometryData& meshData, const IncrementalRemeshingSettings& settings)
	{
		if (!IsFullyTriangular(meshData, settings.ForceMeshTypeVerification))
		{
			return MeshProcessingStatus::InvalidInput;
		}

		return MeshProcessingStatus::ImplementationPending;
	}

} // namespace Symplektis::Algorithms