/*! \file Face.h
*   \brief 3D face for structured geometry objects
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

namespace Symplektis::GeometryKernel
{
	//!< List of triples of vertices
	using Triangulation = std::vector<std::tuple<VertexIndex, VertexIndex, VertexIndex>>;

	//=============================================================================
	/// \class Face
	/// \brief A class acting as a (Triangle or Polygon) face of a 3D mesh.
	///
	/// \ingroup GEOMETRY_BASE
	///
	/// \author M. Cavarga (MCInversion)
	/// \date 26.8.2021
	//=============================================================================
	class Face
	{
	public:
		/// @{
		/// \name Default Special Members

		///-----------------------------------------------------------------------------
		/// \brief Default constructor
		///-----------------------------------------------------------------------------
		Face() = default;

		///-----------------------------------------------------------------------------
		/// \brief Default copy constructor
		///-----------------------------------------------------------------------------
		Face(const Face&) = default;

		///-----------------------------------------------------------------------------
		/// \brief Default move constructor
		///-----------------------------------------------------------------------------
		Face(Face&&) = default;

		///-----------------------------------------------------------------------------
		/// \brief Default destructor
		///-----------------------------------------------------------------------------
		~Face() = default;

		///-----------------------------------------------------------------------------
		/// \brief Default move-assignment operator.
		///-----------------------------------------------------------------------------
		Face& operator=(Face&&) = default;
		
		/// @{
		/// \name Constructors

		//-----------------------------------------------------------------------------
		/*! \brief Set constructor
		*   \param[in] halfEdge     half-edge to initialize from
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.8.2021
		*
		*   Initialize from given HalfEdge
		*/
		//-----------------------------------------------------------------------------
		explicit Face(const HalfEdgeIndex& halfEdge)
			: m_HalfEdge(halfEdge)
		{
		}

		//-----------------------------------------------------------------------------
		/*! \brief Set constructor with a face index
		*   \param[in] edge     half-edge to initialize from
		*   \param[in] id       a unique (unsigned) face id
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.8.2021
		*
		*   Initialize from given HalfEdge and id
		*/
		//-----------------------------------------------------------------------------
		explicit Face(const HalfEdgeIndex& edge, const unsigned int& id) 
			: m_HalfEdge(edge), m_UniqueFaceIndex(id)
		{
		}

		//-----------------------------------------------------------------------------
		/*! \brief Set constructor
		*   \param[in] triang     Triangulation (list of triples of VertexIndex's)
		*   \param[in] halfEdge   HalfEdgeIndex to be initialized from
		*   \param[in] id         Face index
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   31.8.2021
		*/
		//-----------------------------------------------------------------------------
		Face(const Triangulation& triang, const HalfEdgeIndex& halfEdge, const unsigned int& id)
			: Face(halfEdge, id)
		{
			SetTriangulation(triang);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Set constructor
		*   \param[in] triang     Triangulation (list of triples of VertexIndex's)
		*   \param[in] halfEdge   HalfEdgeIndex to be initialized from
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   31.8.2021
		*/
		//-----------------------------------------------------------------------------
		Face(const Triangulation& triang, const HalfEdgeIndex& halfEdge)
			: Face(halfEdge)
		{
			SetTriangulation(triang);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Construct (triangulate) from vertices.
		*   \param[in] vertices   Vertex's to be initialized from
		*   \param[in] halfEdge   HalfEdgeIndex to be initialized from
		*   \param[in] id         Face index
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   31.8.2021
		*
		*   This setter uses Poly2Tri library for triangulating n-gons with n > 4
		*/
		//-----------------------------------------------------------------------------
		Face(const std::vector<VertexIndex>& vertices, const HalfEdgeIndex& halfEdge, const unsigned int& id)
			: Face(halfEdge, id)
		{
			Set(vertices);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Construct (triangulate) from vertices and a half-edge.
		*   \param[in] vertices   Vertex's to be initialized from
		*   \param[in] halfEdge   HalfEdgeIndex to be initialized from
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   31.8.2021
		*
		*   This setter uses Poly2Tri library for triangulating n-gons with n > 4
		*/
		//-----------------------------------------------------------------------------
		Face(const std::vector<VertexIndex>& vertices, const HalfEdgeIndex& halfEdge)
			: Face(halfEdge)
		{
			Set(vertices);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Construct (triangulate) from vertices.
		*   \param[in] vertices   Vertex's to be initialized from
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   31.8.2021
		*
		*   This setter uses Poly2Tri library for triangulating n-gons with n > 4
		*/
		//-----------------------------------------------------------------------------
		explicit Face(const std::vector<VertexIndex>& vertices)
		{
			Set(vertices);
		}

		/// @{
		/// \name Operators
		
		//-----------------------------------------------------------------------------
		/*! \brief Standard assignment operator.
		*   \param[in] face      Face to be copied.
		*   \return Reference to this Face.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		Face& operator=(const Face& face)
		{
			if (this == &face)
				return *this;

			Set(face);
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Comparison of Face's. Compares HalfEdgeIndex's.
		*   \param[in] face     Compared Face.
		*   \return True when faces are equal, otherwise false.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   29.8.2021
		*/
		//-----------------------------------------------------------------------------
		bool operator==(const Face& face) const;

		/// @{
		/// \name Getters
		
		//-----------------------------------------------------------------------------
		/*! \brief HalfEdge getter. Gets a Index to one of the face's half-edges. 
		*   \return m_HalfEdge
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.8.2021
		*/
		//-----------------------------------------------------------------------------
		HalfEdgeIndex& HalfEdge()
		{
			return m_HalfEdge;
		}

		//-----------------------------------------------------------------------------
		/*! \brief A const HalfEdge getter. Gets a const Index to one of the face's half-edges.
		*   \return const reference to m_HalfEdge (HalfEdgeIndex)
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.8.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] const HalfEdgeIndex& HalfEdge() const
		{
			return m_HalfEdge;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Face index getter
		*   \return m_UniqueFaceIndex reference
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.8.2021
		*/
		//-----------------------------------------------------------------------------
		unsigned int& Index()
		{
			return m_UniqueFaceIndex;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Const face index getter
		*   \return const m_UniqueFaceIndex reference
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.8.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] const unsigned int& Index() const
		{
			return m_UniqueFaceIndex;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Triangulation getter. Gets a const reference to one the face's Triangulation.
		*   \return m_Triangulation
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   30.8.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] const Triangulation& GetTriangulation() const
		{
			return m_Triangulation;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Triangulation getter. Gets a reference to one the face's Triangulation.
		*   \return m_Triangulation
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   30.8.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] Triangulation& GetTriangulation()
		{
			return m_Triangulation;
		}

		/// @{
		/// \name Setters

		//-----------------------------------------------------------------------------
		/*! \brief Initialize (triangulate) from vertices.
		*   \param[in] vertices   Vertex's to be initialized from
		*   \return reference to this Polygon
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   30.8.2021
		*
		*   This setter uses Poly2Tri library for triangulating n-gons with n > 4
		*/
		//-----------------------------------------------------------------------------
		Face& Set(const std::vector<VertexIndex>& vertices);
		
		//-----------------------------------------------------------------------------
		/*! \brief Initialize from another Face
		*   \param[in] face   Face
		*   \return reference to this Face
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   2.8.2021
		*/
		//-----------------------------------------------------------------------------
		Face& Set(const Face& face)
		{
			m_HalfEdge = face.m_HalfEdge;
			m_UniqueFaceIndex = face.m_UniqueFaceIndex;
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Set HalfEdge
		*   \param[in] edge   HalfEdgeIndex to be initialized from
		*   \return reference to this Face
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   2.8.2021
		*/
		//-----------------------------------------------------------------------------
		Face& SetHalfEdge(const HalfEdgeIndex& edge)
		{
			m_HalfEdge = edge;
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Initialize from a HalfEdge and face id
		*   \param[in] edge     HalfEdgeIndex to be initialized from
		*   \param[in] id       a unique (unsigned) face id
		*   \return reference to this Face
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.8.2021
		*/
		//-----------------------------------------------------------------------------
		Face& Set(const HalfEdgeIndex& edge, const unsigned int& id)
		{
			m_HalfEdge = edge;
			m_UniqueFaceIndex = id;
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Set a face id
		*   \param[in] id       a unique (unsigned) face id
		*   \return reference to this Face
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.8.2021
		*/
		//-----------------------------------------------------------------------------
		Face& SetIndex(const unsigned int& id)
		{
			m_UniqueFaceIndex = id;
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Set triangulation
		*   \param[in] triang    Triangulation to be set from
		*   \return reference to this Face
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   30.8.2021
		*/
		//-----------------------------------------------------------------------------
		Face& SetTriangulation(const Triangulation& triang)
		{
			m_Triangulation = triang;
			return *this;
		}

		/// @{
		/// \name Flags
		
		//-----------------------------------------------------------------------------
		/*! \brief Gets the isBoundary flag of this face
		*   \return true if this Face is a boundary face
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.8.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] bool IsBoundary() const;

	private:
		//!< Refers to one of the HalfEdge's associated with this Face
		HalfEdgeIndex m_HalfEdge;

		//!< A unique index from 0, ..., nFaces - 1
		unsigned int m_UniqueFaceIndex{ 0 };

		//!< List of triples of Vertex references
		Triangulation m_Triangulation;
	};

} // Symplektis::GeometryKernel