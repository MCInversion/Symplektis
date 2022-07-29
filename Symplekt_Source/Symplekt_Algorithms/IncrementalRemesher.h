/*!  \file IncrementalRemesher.h
 *   \brief An object for incremental remeshing of mesh geometry data.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   26.7.2022
*/

#pragma once

#include "Symplekt_GeometryKernel/MeshGeometryDataTypes.h"

#include "AlgorithmHelperTypes.h"

namespace Symplektis::Algorithms
{
	//=============================================================================
	/// \struct IncrementalRemeshingSettings
	/// \brief A data container for all major settings for IncrementalRemesher.
	///
	/// \ingroup ALGORITHM
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   28.7.2022
	//=============================================================================
	struct IncrementalRemeshingSettings
	{
		unsigned int NIterations = 10;            //>! number of incremental remeshing steps/
		unsigned int NTanSmoothingSteps = 5;      //>! number of tangential smoothing steps.
		double TargetEdgeLength = 1.0;            //>! base edge length preference for the remesher.
		bool IsAdaptive{ true };                  //>! if true, target edge lengths differ depending on principal curvatures.
		bool UseBackProjection{ true };           //>! if true, as the final step, vertices will be projected back to the original surface (onto a triangle).
		bool ForceMeshTypeVerification{ false };  //>! if true, and input mesh type is PolyMeshType::Arbitrary a check for triangular mesh type will be forced.
	};

	//=============================================================================
	/// \struct IncrementalRemesher
	/// \brief A singleton object implementing the top-level functionality behind a process of "isotropic remeshing" [Botsch et al. PMP, 2010]\n
	///	       adjusted to additional means with respect to principal curvatures and their values.
	///
	/// \ingroup ALGORITHM
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   28.7.2022
	//=============================================================================
	class IncrementalRemesher
	{
	public:
		/// @{
		/// \name Functionality

		//-----------------------------------------------------------------------------
		/*! \brief Processes a referenced mesh geometry data object using the "incremental remeshing" approach according to the provided settings.
		 *  \param[in] meshData          reference to the data of the referenced mesh geometry to be processed.
		 *	\param[in] settings          settings for the incremental remeshing algorithm.
		 *  \return Processing status
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   28.7.2022
		*/
		//-----------------------------------------------------------------------------
		static [[nodiscard]] MeshProcessingStatus Process(GeometryKernel::ReferencedMeshGeometryData& meshData, const IncrementalRemeshingSettings& settings);

		//-----------------------------------------------------------------------------
		/*! \brief Processes a buffer mesh geometry data object using the "incremental remeshing" approach according to the provided settings.
		 *  \param[in] meshData          reference to the data of the buffer mesh geometry to be processed.
		 *	\param[in] settings          settings for the incremental remeshing algorithm.
		 *  \return Processing status
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   28.7.2022
		*/
		//-----------------------------------------------------------------------------
		static [[nodiscard]] MeshProcessingStatus Process(GeometryKernel::BufferMeshGeometryData& meshData, const IncrementalRemeshingSettings& settings);
	};
} // namespace Symplektis::Algorithms