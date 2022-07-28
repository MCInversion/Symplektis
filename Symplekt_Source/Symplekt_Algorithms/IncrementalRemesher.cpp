/*!  \file IncrementalRemesher.cpp
 *   \brief Implementation of an object for incremental remeshing of a mesh geometry data.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   26.7.2022
*/

#include "IncrementalRemesher.h"

using namespace Symplektis::GeometryKernel;

namespace Symplektis::Algorithms
{
	MeshProcessingStatus IncrementalRemesher::Process(ReferencedMeshGeometryData& meshData, const IncrementalRemeshingSettings& settings)
	{
		/*
		if (!IsTriangular(meshData))
		{
			return MeshProcessingStatus::InvalidInput;
		}		 
		*/

		auto processingStatus = MeshProcessingStatus::AlgorithmInProgress;

		// Preprocess(); // compute normals if meshData.VertexNormals.empty()
		// if settings.UseBackProjection, save a reference mesh.

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
				// BackProjectVerticesOntoOriginalSurfacePositions(meshData, processingStatus);
			}
		}

		return MeshProcessingStatus::ImplementationPending;
	}

	MeshProcessingStatus IncrementalRemesher::Process(BufferMeshGeometryData& meshData, const IncrementalRemeshingSettings& settings)
	{
		/*
		if (!IsTriangular(meshData))
		{
			return MeshProcessingStatus::InvalidInput;
		}
		*/
		return MeshProcessingStatus::ImplementationPending;
	}

} // namespace Symplektis::Algorithms