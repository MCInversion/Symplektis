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
	/// \brief A reference data container for half-edge data structure
	///
	/// \ingroup GEOMETRY_BASE
	///
	/// \author M. Cavarga (MCInversion)
	/// \date 26.8.2021
	//=============================================================================
	struct HalfEdgeReferenceData
	{
		//!< Refers to the next HalfEdge around current polygonal face.
		HalfEdgeIterator NextHalfEdge;

		//!< Refers to the oppositely oriented HalfEdge with identical 
		//!< endpoints corresponding to an adjacent polygonal face.
		HalfEdgeIterator OppositeHalfEdge;

		//!< Refers to the tail (start) Vertex of this HalfEdge.
		VertexIterator TailVertex;

		//!< Refers to the Edge associated with this HalfEdge.
		EdgeIterator Edge;

		//!< Refers to the Face adjacent to this HalfEdge.
		FaceIterator AdjacentFace;
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
		/// \name Default Members

		//-----------------------------------------------------------------------------
		/*! \brief Default constructor
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		HalfEdge() = default;

		//-----------------------------------------------------------------------------
		/*! \brief Default move constructor
		*   \param[in] other  HalfEdge to be moved.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		HalfEdge(HalfEdge&& other) = default;

		//-----------------------------------------------------------------------------
		/*! \brief Default destructor
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		~HalfEdge() = default;

		//-----------------------------------------------------------------------------
		/*! \brief Default copy-assignment operator
		*   \param[in] other  HalfEdge to be copy-assigned.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		HalfEdge& operator=(const HalfEdge& other) = default;

		//-----------------------------------------------------------------------------
		/*! \brief Default move-assignment operator
		*   \param[in] other  HalfEdge to be move-assigned.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		HalfEdge& operator=(HalfEdge&& other) = default;

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
		/*! \brief Sets the `m_RefData.AdjacentFace` iterator of this HalfEdge
		*   \param[in] face      iterator to an adjacent face
		*   \return reference to this HalfEdge
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   16.9.2021
		*/
		//-----------------------------------------------------------------------------
		HalfEdge& SetAdjacentFace(const FaceIterator& face)
		{
			m_RefData.AdjacentFace = face;
			return *this;
		}

		/// @{
		/// \name Getters

		//-----------------------------------------------------------------------------
		/*! \brief Get const_iterator to NextHalfEdge.
		*   \return const HalfEdgeConstIterator to NextHalfEdge.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] const HalfEdgeConstIterator& NextHalfEdge() const
		{
			return m_RefData.NextHalfEdge;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get iterator to NextHalfEdge.
		*   \return HalfEdgeIterator to NextHalfEdge.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		HalfEdgeIterator& NextHalfEdge()
		{
			return m_RefData.NextHalfEdge;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get const_iterator to OppositeHalfEdge.
		*   \return const HalfEdgeConstIterator to OppositeHalfEdge.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] const HalfEdgeConstIterator& OppositeHalfEdge() const
		{
			return m_RefData.OppositeHalfEdge;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get iterator to OppositeHalfEdge.
		*   \return HalfEdgeIterator to OppositeHalfEdge.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		HalfEdgeIterator& OppositeHalfEdge()
		{
			return m_RefData.OppositeHalfEdge;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get const_iterator to TailVertex.
		*   \return const VertexConstIterator to TailVertex.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] const VertexConstIterator& TailVertex() const
		{
			return m_RefData.TailVertex;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get iterator to TailVertex.
		*   \return VertexIterator to TailVertex.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		VertexIterator& TailVertex()
		{
			return m_RefData.TailVertex;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get const_iterator to Edge.
		*   \return const EdgeConstIterator to Edge.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] const EdgeConstIterator& Edge() const
		{
			return m_RefData.Edge;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get iterator to Edge.
		*   \return EdgeIterator to Edge.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		EdgeIterator& Edge()
		{
			return m_RefData.Edge;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get iterator to AdjacentFace.
		*   \return FaceIterator to AdjacentFace.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		FaceIterator& AdjacentFace()
		{
			return m_RefData.AdjacentFace;
		}
		
		//-----------------------------------------------------------------------------
		/*! \brief Get const_iterator to AdjacentFace.
		*   \return const FaceConstIterator to AdjacentFace.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] const FaceConstIterator& AdjacentFace() const
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