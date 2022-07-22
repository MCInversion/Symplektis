/*! \file  BufferGeometryBuilder.h
 *  \brief Object for constructing the most condensed form of mesh data: BufferGeometryData from vertex data and vertex index data.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   30.9.2021
 *
 */

#pragma once

#include "MeshGeometryDataTypes.h"

#include <memory>

namespace Symplektis::GeometryKernel
{
	//=============================================================================
	/// \class BufferMeshGeometryBuilder
	/// \brief A builder object for constructing BufferMeshGeometryData from vertices\n
	///        and vertex indices data.
	///
	/// \ingroup GEOMETRY_REPS
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   30.9.2021
	//=============================================================================
	class BufferMeshGeometryBuilder
	{
	public:
        /// @{
		/// \name Constructors

		//-----------------------------------------------------------------------------
		/*! \brief Constructor.
		*   \param[in] inputData        BasePolygonalGeometryData to construct a buffer geometry data from
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   7.10.2021
		*/
		//-----------------------------------------------------------------------------
		explicit BufferMeshGeometryBuilder(BasePolygonalGeometryData& inputData);

        /// @{
		/// \name Functionality

		//-----------------------------------------------------------------------------
		/*! \brief Builds m_ResultData from m_BaseData. Both instances exist before this core method is called.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   7.10.2021
		 */
		 //-----------------------------------------------------------------------------
		void BuildGeometry();

        /// @{
        /// \name Getters

		//-----------------------------------------------------------------------------
		/*! \brief Built data getter
		 *  \return constructed geometry data
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   30.9.2021
		 */
		 //-----------------------------------------------------------------------------
		BufferMeshGeometryData& Data()
		{
			return *m_ResultData;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Built const data getter
		 *  \return constructed geometry data const reference
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   2.10.2021
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] const BufferMeshGeometryData& Data() const
		{
			return *m_ResultData;
		}

		/// @{
		/// \name Setters

		//-----------------------------------------------------------------------------
		/*! \brief Sets base geometry data
		*   \param[in] data        Input base polygonal geometry data
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   8.10.2021
		*/
		//-----------------------------------------------------------------------------
		void SetBaseData(BasePolygonalGeometryData&& data)
		{
			m_BaseData = std::make_unique<BasePolygonalGeometryData>(data);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Sets result buffer geometry data (from another buffer geometry instance)
		*   \param[in] data        Input referenced geometry data
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   8.10.2021
		*/
		//-----------------------------------------------------------------------------
		//void SetResultData(BufferMeshGeometryData&& data)
		//{
		//	m_ResultData = std::make_unique<BufferMeshGeometryData>(data);
		//}
	
	private:

		//-----------------------------------------------------------------------------
		/*! \brief A preallocation subroutine for mesh geometry data buffer containers.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   30.9.2021
		*/
		//-----------------------------------------------------------------------------
		void PreallocateMeshGeometryContainers();

		//-----------------------------------------------------------------------------
		/*! \brief Fills VertexCoords buffer with coordinates of base data's vertices
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   7.10.2021
		*/
		//-----------------------------------------------------------------------------
		void FillVertexCoordinateBuffer() const;

		//-----------------------------------------------------------------------------
		/*! \brief Fills result data's VertexIndices and TriangulationIndices buffers.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   7.10.2021
		* 
		*   Prerequisites to this step are: Preallocated and filled VertexCoords buffer.
		*/
		//-----------------------------------------------------------------------------
		void FillVertexAndTriangulationIndexBuffers() const;

		//
		// =============== Data ========================================================
		//

		//!> Built data container
		std::unique_ptr<BufferMeshGeometryData> m_ResultData;

		//!> Initial data fields
		std::unique_ptr<BasePolygonalGeometryData> m_BaseData;

		//!> flag for built buffer geometry having vertex normals from an external source.
		bool m_HasNormals = false;
	};

	//-----------------------------------------------------------------------------
	/*! \brief Obtain vertices (Vector3's) of a triangle marked by triangleId in given buffer mesh geometry data.
	*   \param[in] triangleId          index of a triangle from data triangulation
	*   \param[in] data                buffer mesh geometry data ref
	*   \return triple of triangle vertices {v0, v1, v2} (Vector3)
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   3.10.2021
	*/
	//-----------------------------------------------------------------------------
	std::tuple<GeometryKernel::Vector3, GeometryKernel::Vector3, GeometryKernel::Vector3>
		ObtainTriangleVerticesFromTriangulationIndices(const unsigned int& triangleId, const BufferMeshGeometryData& data);
	
} // Symplektis::GeometryKernel