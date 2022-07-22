/*! \file  BufferToReferencedMeshGeometryConverter.h
 *  \brief A converter object for transforming BufferMeshGeometryData to ReferencedMeshGeometryData
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   2.10.2021
 *
 */

#pragma once

#include "ReferencedMeshGeometry.h"
#include "BufferMeshGeometry.h"

namespace Symplektis::GeometryKernel
{
	//=============================================================================
	/// \class BufferToReferencedMeshGeometryConverter
	/// \brief A converter object for transforming BufferMeshGeometryData to ReferencedMeshGeometryData
	///
	/// \ingroup GEOMETRY_REPS
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   2.10.2021
	//=============================================================================
	class BufferToReferencedMeshGeometryConverter
	{
	public:

		/// @{
		/// \name Constructors
		
		//-----------------------------------------------------------------------------
		/*! \brief Constructor.
		*   \param[in] geomIn          input BufferMeshGeometry
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   2.10.2021
		*/
		//-----------------------------------------------------------------------------
		explicit BufferToReferencedMeshGeometryConverter(const BufferMeshGeometry& geomIn);

		/// @{
		/// \name Functionality

		//-----------------------------------------------------------------------------
		/*! \brief Prepares base geometry data from m_DataIn and builds m_DataOut
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   10.10.2021
		 */
		 //-----------------------------------------------------------------------------
		void ConvertGeometry();

		/// @{
		/// \name Getters

		//-----------------------------------------------------------------------------
		/*! \brief Converted geometry getter
		 *  \return converted buffer to referenced mesh geometry data
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   2.10.2021
		 */
		 //-----------------------------------------------------------------------------
		ReferencedMeshGeometry& GetResultGeometry()
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
		[[nodiscard]] const ReferencedMeshGeometry& GetResultGeometry() const
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

		std::unique_ptr<BufferMeshGeometry>     m_GeomIn;
		std::unique_ptr<ReferencedMeshGeometry> m_GeomOut;
	};
	
} // Symplektis::GeometryKernel