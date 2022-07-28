/*!  \file AlgorithmHelperTypes.h
 *   \brief A collection of types useful for Symplektis algorithms.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   28.7.2022
*/

#pragma once

namespace Symplektis::Algorithms
{
	//=============================================================================
	/// \enum MeshProcessingStatus
	/// \brief Enumerates the status of a mesh processing algorithm.
	///
	/// \ingroup ALGORITHM
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   28.7.2022
	//=============================================================================
	enum class [[nodiscard]] MeshProcessingStatus
	{
		Complete              = 0, //!< a mesh processing step is complete without errors.
		InvalidInput          = 1, //!< input mesh data is invalid.
		InternalError         = 2, //!< an internal error in the processing algorithm took place.
		AlgorithmInProgress   = 3, //!< the algorithm is still in progress.
		ImplementationPending = 4  //!< the algorithm has not been implemented yet.
	};
} // namespace Symplektis::Algorithms

///---------------------------------------------------------------------------
///  \brief A macro evaluating a MeshProcessingStatus within a function that returns it.
///  \param[in] status     a MeshProcessingStatus to be verified.
///---------------------------------------------------------------------------
#define VERIFY_MESH_PROCESSING_STATUS(status)                                           \
	if ((status) != Symplektis::Algorithms::MeshProcessingStatus::AlgorithmInProgress)  \
		return status