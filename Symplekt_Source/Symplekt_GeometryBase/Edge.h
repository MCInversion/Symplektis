/*! \file Edge.h
*   \brief 3D edge for structured geometry objects
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
	class Edge
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
		Edge() = default;

		//-----------------------------------------------------------------------------
		/*! \brief Default copy constructor
		*   \param[in] other  Edge to be copied.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		Edge(Edge& other) = default;

		//-----------------------------------------------------------------------------
		/*! \brief Default move constructor
		*   \param[in] other  Edge to be moved.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		Edge(Edge&& other) = default;

		//-----------------------------------------------------------------------------
		/*! \brief Default destructor
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		~Edge() = default;

		//-----------------------------------------------------------------------------
		/*! \brief Default move-assignment operator
		*   \param[in] other  Edge to be move-assigned.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		Edge& operator=(Edge&& other) = default;

		/// @{
		/// \name Constructors

		//-----------------------------------------------------------------------------
		/*! \brief Set constructor
		*   \param[in] he     half-edge to initialize from
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   30.8.2021
		*
		*   Initialize from given HalfEdge
		*/
		//-----------------------------------------------------------------------------
		explicit Edge(const HalfEdgeHandle& he)
			: m_HalfEdge(he)
		{
		}

		//-----------------------------------------------------------------------------
		/*! \brief Set constructor with an edge index
		*   \param[in] he       half-edge to initialize from
		*   \param[in] id       a unique (unsigned) face id
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   30.8.2021
		*
		*   Initialize from given HalfEdge and id
		*/
		//-----------------------------------------------------------------------------
		Edge(const HalfEdgeHandle& he, const unsigned int& id)
			: m_HalfEdge(he), m_UniqueEdgeIndex(id)
		{
		}

		/// @{
		/// \name Operators

		//-----------------------------------------------------------------------------
		/*! \brief Standard assignment operator.
		*   \param[in] edge      Edge to be copied.
		*   \return Reference to this Edge.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   30.8.2021
		*/
		//-----------------------------------------------------------------------------
		Edge& operator=(const Edge& edge)
		{
			if (this == &edge)
				return *this;

			Set(edge);
			return *this;
		}

		/// @{
		/// \name Getters

		//-----------------------------------------------------------------------------
		/*! \brief Get const handle to HalfEdge.
		*   \return HalfEdgeHandle to HalfEdge.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   30.8.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] const HalfEdgeHandle& HalfEdge() const
		{
			return m_HalfEdge;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get handle to HalfEdge.
		*   \return HalfEdgeHandle to HalfEdge.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   30.8.2021
		*/
		//-----------------------------------------------------------------------------
		HalfEdgeHandle& HalfEdge()
		{
			return m_HalfEdge;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Edge index getter
		*   \return m_UniqueEdgeIndex reference
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   30.8.2021
		*/
		//-----------------------------------------------------------------------------
		unsigned int& Index()
		{
			return m_UniqueEdgeIndex;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Const Edge index getter
		*   \return const m_UniqueEdgeIndex reference
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   30.8.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] const unsigned int& Index() const
		{
			return m_UniqueEdgeIndex;
		}

		/// @{
		/// \name Setters

		//-----------------------------------------------------------------------------
		/*! \brief Initialize from another Edge
		*   \param[in] edge   Edge
		*   \return reference to this Edge
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   30.8.2021
		*/
		//-----------------------------------------------------------------------------
		Edge& Set(const Edge& edge)
		{
			m_HalfEdge = edge.m_HalfEdge;
			m_UniqueEdgeIndex = edge.m_UniqueEdgeIndex;
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Initialize from a HalfEdge
		*   \param[in] halfEdge   HalfEdge(Iterator) to be initialized from
		*   \return reference to this Edge
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   30.8.2021
		*/
		//-----------------------------------------------------------------------------
		Edge& Set(const HalfEdgeHandle& halfEdge)
		{
			m_HalfEdge = halfEdge;
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Initialize from a HalfEdge and Edge id
		*   \param[in] halfEdge     HalfEdge(Iterator) to be initialized from
		*   \param[in] id       a unique (unsigned) Edge id
		*   \return reference to this Edge
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   30.8.2021
		*/
		//-----------------------------------------------------------------------------
		Edge& Set(const HalfEdgeHandle& halfEdge, const unsigned int& id)
		{
			m_HalfEdge = halfEdge;
			m_UniqueEdgeIndex = id;
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Set a Edge id
		*   \param[in] id       a unique (unsigned) Edge id
		*   \return reference to this Edge
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   30.8.2021
		*/
		//-----------------------------------------------------------------------------
		Edge& SetIndex(const unsigned int& id)
		{
			m_UniqueEdgeIndex = id;
			return *this;
		}

	private:
		//!< Refers to the HalfEdge associated with this Edge
		HalfEdgeHandle m_HalfEdge;

		//!< A unique index from 0, ..., nEdges - 1
		unsigned int m_UniqueEdgeIndex{ 0 };
	};

} // Symplektis::GeometryBase