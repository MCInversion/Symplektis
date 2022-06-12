/*! \file  MeshGeometryDataTypes.h
 *  \brief A gallery of data container types (mostly structs) for mesh geometry data.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   7.10.2021
 *
 */

#pragma once


#include "Symplekt_GeometryBase/HalfEdge.h"
#include "Symplekt_GeometryBase/Vertex.h"
#include "Symplekt_GeometryBase/VertexNormal.h"
#include "Symplekt_GeometryBase/Edge.h"
#include "Symplekt_GeometryBase/Face.h"
#include "Symplekt_GeometryBase/Vector3.h"

#include <string>
#include <vector>

namespace Symplektis::GeometryReps
{
    //=============================================================================
    /// \struct BasePolygonalGeometryData
    /// \brief A base data container for polygonal geometry data containing only vertices, polygon vertex indices, and vertex normals .
    ///
    /// \ingroup GEOMETRY_REPS
    ///
    /// \author M. Cavarga (MCInversion)
    /// \date   7.10.2021
    //=============================================================================
	struct BasePolygonalGeometryData
	{
		std::wstring                             Name;
		std::vector<GeometryBase::Vector3>       Vertices{};
		std::vector<std::vector<unsigned int>>   PolyVertexIndices{};
		std::vector<GeometryBase::Vector3>       VertexNormals{};

		/// \brief Returns the byte size of this geometry container.
		[[nodiscard]] size_t Size() const;
	};

	//=============================================================================
	/// \struct BufferMeshGeometryData
	/// \brief A data container for geometry data containing raw vertex and vertex normal coordinates, vertex indices, and triangulation indices.
	///
	/// \ingroup GEOMETRY_REPS
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   30.9.2021
	//=============================================================================
	struct BufferMeshGeometryData
	{
		std::wstring                           Name;
		std::vector<double>                    VertexCoords{};
		std::vector<double>                    VertexNormalCoords{};
		std::vector<unsigned int>              VertexIndices{};
		std::vector<std::vector<unsigned int>> TriangulationIndices{};

		/// \brief Returns the byte size of this geometry container.
		[[nodiscard]] size_t Size() const;

		/// \brief Construct data with a name
		explicit BufferMeshGeometryData(std::wstring name)
			: Name(name)
		{ }
	};

	//=============================================================================
	/// \struct ReferencedMeshGeometryData
	/// \brief A data container for referenced geometry data. Requires special copy & copy-assignment\n
	///        implementations for iterator members of buffer items (mesh elements, e.g.: HalfEdge) \n
	///        pointing to previous instance items (e.g. copied HalfEdge->NextHalfEdge() still points\n
	///        to previous ReferencedMeshGeometryData.HalfEdges item).
	///
	/// \ingroup GEOMETRY_REPS
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   14.9.2021
	//=============================================================================
	struct ReferencedMeshGeometryData
	{
		std::wstring Name;
		
		//
		// =============== Data containers ========================================================
		//
		
		std::vector<GeometryBase::HalfEdge>       HalfEdges{};
		std::vector<GeometryBase::Vertex>         Vertices{};
		std::vector<GeometryBase::Edge>           Edges{};
		std::vector<GeometryBase::Face>           Faces{};
		std::vector<GeometryBase::Face>           BoundaryCycles{};
		std::vector<GeometryBase::VertexNormal>   VertexNormals{};

		/// \brief Returns the byte size of this geometry container.
		[[nodiscard]] size_t Size() const;

		//
		// =============== Constructors & Setters =================================================
		//

		//-----------------------------------------------------------------------------
		/*! \brief Destructor
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.10.2021
		*/
		//-----------------------------------------------------------------------------
        ~ReferencedMeshGeometryData() = default;

		//-----------------------------------------------------------------------------
		/*! \brief Constructor. Construct named mesh data.
		*   \param[in] name      Name string for this mesh data.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.6.2022
		*/
		//-----------------------------------------------------------------------------
		explicit ReferencedMeshGeometryData(std::wstring name)
			: Name(name)
		{
		}

		//-----------------------------------------------------------------------------
		/*! \brief Copy constructor
		*   \param[in] other      ReferencedMeshGeometryData to be copied.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.10.2021
		*/
		//-----------------------------------------------------------------------------
        ReferencedMeshGeometryData(const ReferencedMeshGeometryData& other);

		//-----------------------------------------------------------------------------
		/*! \brief Default move constructor
		*   \param[in] other      ReferencedMeshGeometryData to be moved.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.10.2021
		*/
		//-----------------------------------------------------------------------------
		ReferencedMeshGeometryData(ReferencedMeshGeometryData&& other) = default;

		//-----------------------------------------------------------------------------
		/*! \brief Copy-assignment operator.
		*   \param[in] other      ReferencedMeshGeometryData to be copied.
		*   \return Reference to this ReferencedMeshGeometryData.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.10.2021
		*/
		//-----------------------------------------------------------------------------
        ReferencedMeshGeometryData& operator=(const ReferencedMeshGeometryData& other);

		//-----------------------------------------------------------------------------
		/*! \brief Default move-assignment operator.
		*   \param[in] other      ReferencedMeshGeometryData to be moved.
		*   \return Reference to this ReferencedMeshGeometryData.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.10.2021
		*/
		//-----------------------------------------------------------------------------
		ReferencedMeshGeometryData& operator=(ReferencedMeshGeometryData&& other) = default;

		//-----------------------------------------------------------------------------
		/*! \brief Safe data setter for writing data buffers with proper (new) std::vector iterators based on position index.
		*   \param[in] other      ReferencedMeshGeometryData to be set.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.10.2021
		*/
		//-----------------------------------------------------------------------------
		void SetDataSafely(const ReferencedMeshGeometryData& other);
	
	private:

		//-----------------------------------------------------------------------------
		/*! \brief Trivial copy-set
		*   \param[in] otherData      ReferencedMeshGeometryData to be set.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.10.2021
		*/
		//-----------------------------------------------------------------------------
		void TrivialCopySet(const ReferencedMeshGeometryData& otherData) noexcept;

		//-----------------------------------------------------------------------------
		/*! \brief Safe half-edge data buffer setter for writing the half-edge buffer with proper (new) std::vector iterators based on position index.
		*   \param[in] otherData      ReferencedMeshGeometryData to be set.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.10.2021
		*/
		//-----------------------------------------------------------------------------
        void SetHalfEdgesBuffer(const ReferencedMeshGeometryData& otherData);

		//-----------------------------------------------------------------------------
		/*! \brief Safe vertices data buffer setter for writing the vertex buffer with proper (new) std::vector iterators based on position index.
		*   \param[in] otherData      ReferencedMeshGeometryData to be set.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.10.2021
		*/
		//-----------------------------------------------------------------------------
        void SetVerticesBuffer(const ReferencedMeshGeometryData& otherData);

		//-----------------------------------------------------------------------------
		/*! \brief Safe edges data buffer setter for writing the edge buffer with proper (new) std::vector iterators based on position index.
		*   \param[in] otherData      ReferencedMeshGeometryData to be set.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.10.2021
		*/
		//-----------------------------------------------------------------------------
        void SetEdgesBuffer(const ReferencedMeshGeometryData& otherData);

		//-----------------------------------------------------------------------------
		/*! \brief Safe faces data buffer setter for writing the face buffer with proper (new) std::vector iterators based on position index.
		*   \param[in] otherData      ReferencedMeshGeometryData to be set.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.10.2021
		*/
		//-----------------------------------------------------------------------------
        void SetFacesBuffer(const ReferencedMeshGeometryData& otherData);

		//-----------------------------------------------------------------------------
		/*! \brief Safe boundary cycle (face) data buffer setter for writing the boundary cycle buffer with proper (new) std::vector iterators based on position index.
		*   \param[in] otherData      ReferencedMeshGeometryData to be set.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.10.2021
		*/
		//-----------------------------------------------------------------------------
		void SetBoundaryCyclesBuffer(const ReferencedMeshGeometryData& otherData);

		//-----------------------------------------------------------------------------
		/*! \brief Safe vertex normal data buffer setter for writing the vertex normal buffer with proper (new) std::vector iterators based on position index.
		*   \param[in] otherData      ReferencedMeshGeometryData to be set.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.10.2021
		*/
		//-----------------------------------------------------------------------------
		void SetVertexNormalsBuffer(const ReferencedMeshGeometryData& otherData);
	};

} // Symplektis::GeometryReps