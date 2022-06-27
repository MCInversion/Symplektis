/*! \file  ReferencedGeometryBuilder.h
 *  \brief Object for constructing ReferencedMeshGeometryData from vertex data and vertex index data.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   9.9.2021
 *
 */

#pragma once

#include "MeshGeometryDataTypes.h"

#include <vector>
#include <memory>
#include <map>

namespace Symplektis::GeometryReps
{

    //=============================================================================
	/// \class ReferencedMeshGeometryBuilder
	/// \brief A builder object for constructing ReferencedMeshGeometryData from vertices\n
	///        and vertex indices data.
	///
	/// \ingroup GEOMETRY_REPS
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   14.9.2021
	///
	/// Inspired by "DDG-Exercises" repo: https://github.com/GeometryCollective/ddg-exercises
	/// Copyright 2021-2022 Geometry Collective, Nicole Feng, and Marek Marchlewicz, Carnegie Mellon University (CMU).
	/// 
	//=============================================================================
	class ReferencedMeshGeometryBuilder
	{
    public:
		/// @{
		/// \name Constructors
		
        //-----------------------------------------------------------------------------
        /*! \brief Constructor.
		*   \param[in] inputData        BasePolygonalGeometryData to construct a referenced geometry data from
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   14.9.2021
        */
        //-----------------------------------------------------------------------------
        explicit ReferencedMeshGeometryBuilder(BasePolygonalGeometryData& inputData);

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
		 *  \return constructed referenced mesh geometry data
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   14.9.2021
		 *
		 */
		//-----------------------------------------------------------------------------
		ReferencedMeshGeometryData& Data()
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
		[[nodiscard]] const ReferencedMeshGeometryData& Data() const
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
		/*! \brief Sets result referenced geometry data (from another referenced geometry instance)
		*   \param[in] data        Input referenced geometry data
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   8.10.2021
		*/
		//-----------------------------------------------------------------------------
		//void SetResultData(ReferencedMeshGeometryData&& data)
		//{
		//	m_ResultData = std::make_unique<ReferencedMeshGeometryData>(data);
		//}

	private:
		//-----------------------------------------------------------------------------
		/*! \brief A preallocation subroutine for mesh geometry data buffer containers.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   14.9.2021
		*/
		//-----------------------------------------------------------------------------
		void PreallocateMeshGeometryContainers();

		//-----------------------------------------------------------------------------
		/*! \brief Fills the vertex buffer and a vertexIndex->vertex map.
		*   \param[out] vertIndexToVertexHandle        a vertexIndex -> vertexHandle map for associating vertex indices with inserted vertices.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   8.10.2021
		*/
		//-----------------------------------------------------------------------------
		void FillVertexBufferAndIndexMap(std::map<unsigned int, GeometryBase::VertexHandle>& vertIndexToVertexHandle) const;

		//-----------------------------------------------------------------------------
		/*! \brief Fills half-edge, edge, and face buffers + helper containers.
		*   \param[out] vertIndexToVertexHandle           a vertexIndex->vertexHandle map for associating vertex indices with vertex handles.
		*   \param[out] halfEdgeHasOpposite               a halfEdgeHandle->hasOpposite map storing information about halfEdges having their opposites.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   8.10.2021
		*/
		//-----------------------------------------------------------------------------
		bool FillHalfEdgesAndFaces(
			std::map<unsigned int, GeometryBase::VertexHandle>&      vertIndexToVertexHandle,
			std::map<GeometryBase::HalfEdgeHandle, bool>&            halfEdgeHasOpposite) const;

		//-----------------------------------------------------------------------------
		/*! \brief Fills the boundary cycles buffers from half-edges that do not have opposites.
		*   \param[out] halfEdgeHasOpposite        a halfEdgeHandle->hasOpposite map storing information about halfEdges having their opposites.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   8.10.2021
		*/
		//-----------------------------------------------------------------------------
		void FillBoundaryCycles(std::map<GeometryBase::HalfEdgeHandle, bool>& halfEdgeHasOpposite) const;

		//-----------------------------------------------------------------------------
		/*! \brief A checking method for isolated vertices
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   14.9.2021
		*/
		//-----------------------------------------------------------------------------
        void PerformIsolatedVertexCheck() const;
		
		//-----------------------------------------------------------------------------
		/*! \brief A checking method for non-manifold vertices and geometry handle validity.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   14.9.2021
		*/
		//-----------------------------------------------------------------------------
        void PerformNonManifoldVertexCheck() const;

		//
		// =============== Data ========================================================
		//

		//!> Built data container
		std::unique_ptr<ReferencedMeshGeometryData> m_ResultData;

		//!> Initial data fields
		std::unique_ptr<BasePolygonalGeometryData> m_BaseData;

		//!> flag for built referenced geometry having vertex normals from an external source.
		bool m_HasNormals = false;
	};

} // Symplektis::GeometryReps