/*! \file  ReferencedToBufferMeshGeometryConverter.h
 *  \brief A converter object for transforming ReferencedMeshGeometryData to BufferMeshGeometryData
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   2.10.2021
 *
 */

#pragma once

#include "ReferencedMeshGeometry.h"
#include "BufferMeshGeometry.h"

#include <memory>

namespace Symplektis::GeometryReps
{
	//=============================================================================
	/// \class ReferencedToBufferMeshGeometryConverter
	/// \brief A converter object for transforming ReferencedMeshGeometry to BufferMeshGeometry
	///
	/// \ingroup GEOMETRY_REPS
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   2.10.2021
	//=============================================================================
	class ReferencedToBufferMeshGeometryConverter
	{
	public:
        /// @{
        /// \name Constructors

		//-----------------------------------------------------------------------------
		/*! \brief Constructor.
		*   \param[in] geomIn          input ReferencedMeshGeometry
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   2.10.2021
		*/
		//-----------------------------------------------------------------------------
		explicit ReferencedToBufferMeshGeometryConverter(const ReferencedMeshGeometry& geomIn);

        /// @{
        /// \name Functionality

		//-----------------------------------------------------------------------------
		/*! \brief Prepares base geometry data from m_DataIn and builds m_DataOut
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   8.10.2021
		 */
		 //-----------------------------------------------------------------------------
		void ConvertGeometry();

        /// @{
        /// \name Getters

		//-----------------------------------------------------------------------------
		/*! \brief Converted geometry getter
		 *  \return converted referenced to buffer mesh geometry data
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   2.10.2021
		 */
		//-----------------------------------------------------------------------------
		BufferMeshGeometry& GetResultGeometry()
		{
			return *m_GeomOut;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Converted const geometry getter
		 *  \return converted referenced to buffer mesh geometry ResultMesh const reference
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   2.10.2021
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] const BufferMeshGeometry& GetResultGeometry() const
		{
			return *m_GeomOut;
		}

	private:

		//-----------------------------------------------------------------------------
		/*! \brief Prepares base geometry data from m_DataIn.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   8.10.2021
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] BasePolygonalGeometryData PrepareBaseGeometryData() const;

        //
        // =============== Data ========================================================
        //

        //!> Result geometry
		std::unique_ptr<BufferMeshGeometry>           m_GeomOut;

		//!> Source geometry
		std::unique_ptr<ReferencedMeshGeometry>       m_GeomIn;
	};
	
} // Symplektis::GeometryReps