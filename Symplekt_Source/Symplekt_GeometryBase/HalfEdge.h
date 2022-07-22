/*! \file HalfEdge.h
*   \brief 3D half-edge for structured mesh geometry objects
*
\verbatim
-------------------------------------------------------------------------------
created  : 29.7.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/
#pragma once

#include "GeometryHelperTypes.h"

namespace Symplektis::GeometryBase
{
	// forward declarations
	class Vector3;

	//=============================================================================
	/// \struct HalfEdgeReferenceData
	/// \brief A reference data item for half-edge data structure
	///
	/// \ingroup GEOMETRY_BASE
	///
	/// \author M. Cavarga (MCInversion)
	/// \date 26.8.2021
	//=============================================================================
	struct HalfEdgeReferenceData
	{
		//!< Refers to the next HalfEdge around current polygonal face.
		HalfEdgeIndex NextHalfEdge{NULL_HALF_EDGE};

		//!< Refers to the oppositely oriented HalfEdge with identical 
		//!< endpoints corresponding to an adjacent polygonal face.
		HalfEdgeIndex OppositeHalfEdge{NULL_HALF_EDGE};

		//!< Refers to the tail (start) Vertex of this HalfEdge.
		VertexIndex TailVertex{NULL_VERTEX};

		//!< Refers to the Edge associated with this HalfEdge.
		EdgeIndex Edge{NULL_EDGE};

		//!< Refers to the Face adjacent to this HalfEdge.
		FaceIndex AdjacentFace{NULL_FACE};
	};

	///=============================================================================
	/// \class HalfEdge
	/// \brief A class acting as a half-edge of a 3D mesh geometry with an interface. Reference data is stored in HalfEdgeReferenceData structure.
	///
	/// \ingroup GEOMETRY_BASE
	///
	/// \author M. Cavarga (MCInversion)
	/// \date 26.8.2021
	///=============================================================================
	class HalfEdge
	{
	public:

		/// @{
		/// \name Default Special Members

		//-----------------------------------------------------------------------------
		/// \brief Default constructor
		//-----------------------------------------------------------------------------
		HalfEdge() = default;

		//-----------------------------------------------------------------------------
		/// \brief Default move constructor
		//-----------------------------------------------------------------------------
		HalfEdge(HalfEdge&& ) = default;

		//-----------------------------------------------------------------------------
		/// \brief Default destructor
		//-----------------------------------------------------------------------------
		~HalfEdge() = default;

		//-----------------------------------------------------------------------------
		/// \brief Default copy-assignment operator
		//-----------------------------------------------------------------------------
		HalfEdge& operator=(const HalfEdge& ) = default;

		//-----------------------------------------------------------------------------
		/// \brief Default move-assignment operator
		//-----------------------------------------------------------------------------
		HalfEdge& operator=(HalfEdge&& ) = default;

		/// @{
		/// \name Constructors

		//-----------------------------------------------------------------------------
		/*! \brief Copy constructor.
		*   \param[in] he  HalfEdge to be copied.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		HalfEdge(const HalfEdge& he)
		{
			Set(he.m_RefData);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Constructor. Initialize from HalfEdgeReferenceData
		*   \param[in] data     reference data to be initialized from
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		* 
		*  Use for example:
		*      `auto myHalfEdge = HalfEdge({nextHalfEdge, oppositeHalfEdge, tailVertex, edge, adjacentFace});`
		*/
		//-----------------------------------------------------------------------------
		explicit HalfEdge(const HalfEdgeReferenceData& data)
		{
			Set(data);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Constructor. Initialize from HalfEdgeReferenceData and isBoundary flag.
		*   \param[in] data          reference data to be initialized from
		*   \param[in] isBoundary    flag for whether this half-edge belongs to a boundary cycle
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		* 
        *  Use for example:
        *      `auto myHalfEdge = HalfEdge({nextHalfEdge, oppositeHalfEdge, tailVertex, edge, adjacentFace}, isBoundary);`
		*/
		//-----------------------------------------------------------------------------
		HalfEdge(const HalfEdgeReferenceData& data, const bool& isBoundary)
		{
			Set(data, isBoundary);
		}

		/// @{
		/// \name Setters

		//-----------------------------------------------------------------------------
		/*! \brief Initialize from HalfEdgeReferenceData and isBoundary flag.
		*   \param[in] data        half-edge data
		*   \param[in] isBoundary  true if this half-edge is to be set as boundary
		*   \return reference to this HalfEdge
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		HalfEdge& Set(const HalfEdgeReferenceData& data, const bool& isBoundary)
		{
			m_RefData = data;
			m_IsOnBoundaryLoop = isBoundary;
			return *this;
		}
		//-----------------------------------------------------------------------------
		/*! \brief Initialize from HalfEdgeReferenceData `{nextHalfEdge, oppositeHalfEdge, tailVertex, edge, adjacentFace}`.
		*   \param[in] data        half-edge data
		*   \return reference to this HalfEdge
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		HalfEdge& Set(const HalfEdgeReferenceData& data)
		{
			m_RefData = data;
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Sets the `m_IsOnBoundaryLoop` flag of this HalfEdge
		*   \param[in] isBoundary     is boundary boolean flag
		*   \return reference to this HalfEdge
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.8.2021
		*/
		//-----------------------------------------------------------------------------
		HalfEdge& SetIsBoundary(const bool& isBoundary)
		{
			m_IsOnBoundaryLoop = isBoundary;
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Sets the `m_RefData.AdjacentFace` index of this HalfEdge
		*   \param[in] face      index to an adjacent face
		*   \return reference to this HalfEdge
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   16.9.2021
		*/
		//-----------------------------------------------------------------------------
		HalfEdge& SetAdjacentFace(const FaceIndex& face)
		{
			m_RefData.AdjacentFace = face;
			return *this;
		}

		/// @{
		/// \name Getters

		//-----------------------------------------------------------------------------
		/*! \brief Get a const index to NextHalfEdge.
		*   \return const HalfEdgeIndex to NextHalfEdge.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] const HalfEdgeIndex& NextHalfEdge() const
		{
			return m_RefData.NextHalfEdge;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get an index to NextHalfEdge.
		*   \return HalfEdgeIndex to NextHalfEdge.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		HalfEdgeIndex& NextHalfEdge()
		{
			return m_RefData.NextHalfEdge;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get a const index to OppositeHalfEdge.
		*   \return const HalfEdgeIndex to OppositeHalfEdge.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] const HalfEdgeIndex& OppositeHalfEdge() const
		{
			return m_RefData.OppositeHalfEdge;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get an index to OppositeHalfEdge.
		*   \return HalfEdgeIndex to OppositeHalfEdge.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		HalfEdgeIndex& OppositeHalfEdge()
		{
			return m_RefData.OppositeHalfEdge;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get a const index to TailVertex.
		*   \return const VertexIndex to TailVertex.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] const VertexIndex& TailVertex() const
		{
			return m_RefData.TailVertex;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get an index to TailVertex.
		*   \return VertexIndex to TailVertex.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		VertexIndex& TailVertex()
		{
			return m_RefData.TailVertex;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get a const index to Edge.
		*   \return const EdgeIndex to Edge.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] const EdgeIndex& Edge() const
		{
			return m_RefData.Edge;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get an index to Edge.
		*   \return EdgeIndex to Edge.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		EdgeIndex& Edge()
		{
			return m_RefData.Edge;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get an index to AdjacentFace.
		*   \return FaceIndex to AdjacentFace.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		FaceIndex& AdjacentFace()
		{
			return m_RefData.AdjacentFace;
		}
		
		//-----------------------------------------------------------------------------
		/*! \brief Get a const index to AdjacentFace.
		*   \return const FaceIndex to AdjacentFace.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] const FaceIndex& AdjacentFace() const
		{
			return m_RefData.AdjacentFace;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Gets the m_IsOnBoundaryLoop flag of this HalfEdge
		*   \return true if this HalfEdge belongs to a boundary face
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.8.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] bool IsBoundary() const
		{
			return m_IsOnBoundaryLoop;
		}

	private:
		//!< Reference data: `{nextHalfEdge, oppositeHalfEdge, tailVertex, edge, adjacentFace}`
		HalfEdgeReferenceData m_RefData;

		//!< True if this HalfEdge belongs to a boundary loop enclosing a
		//!< boundary Face.
		bool m_IsOnBoundaryLoop = false;
	};

} // Symplektis::GeometryBase