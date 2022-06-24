/*! \file Vertex.h
*   \brief 3D vertex for referenced mesh geometry objects
*
\verbatim
-------------------------------------------------------------------------------
created  : 27.8.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/
#pragma once

#include "GeometryHelperTypes.h"
#include "Vector3.h"

namespace Symplektis::GeometryBase
{
	// forward declarations
	class Vector3;
	
	//=============================================================================
	/// \class Vertex
	/// \brief A class acting as a vertex of 3D mesh geometry.
	///
	/// \ingroup GEOMETRY_BASE
	///
	/// \author M. Cavarga (MCInversion)
	/// \date 29.8.2021
	//=============================================================================
 	class Vertex
	{
	public:
		/// @{
		/// \name Default Special Members

		//-----------------------------------------------------------------------------
		/*! \brief Default constructor
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		Vertex() = default;

		//-----------------------------------------------------------------------------
		/*! \brief Default move constructor
		*   \param[in] other  Vertex to be moved.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		Vertex(Vertex&& other) = default;

		//-----------------------------------------------------------------------------
		/*! \brief Default destructor
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		~Vertex() = default;

		//-----------------------------------------------------------------------------
		/*! \brief Default move-assignment operator
		*   \param[in] other  Vertex to be move-assigned.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		Vertex& operator=(Vertex && other) = default;

		/// @{
		/// \name Constructors

		//-----------------------------------------------------------------------------
		/*! \brief Copy constructor.
		*   \param[in] vert    Vertex to be copied
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		Vertex(const Vertex& vert)
		{
			Set(vert);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Constructor. Initialize from position vector.
		*   \param[in] position    Position Vector3
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		explicit Vertex(const Vector3& position)
		{
			Set(position);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Constructor. Initialize from position vector coordinates.
		*   \param[in] x    position coordinate X.
		*   \param[in] y    position coordinate Y.
		*   \param[in] z    position coordinate Z.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.8.2021
		*/
		//-----------------------------------------------------------------------------
		Vertex(const double& x, const double& y, const double& z)
		{
			Set(x, y, z);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Constructor. Initialize this Vertex from halfEdge ref, and position vector
		*   \param[in] halfEdge        iterator to HalfEdge coming out of this Vertex
		*   \param[in] pos             position 3D vector
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   29.8.2021
		*
		*/
		//-----------------------------------------------------------------------------
		Vertex(const HalfEdgeHandle& halfEdge, const Vector3& pos)
		{
			Set(halfEdge, pos);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Constructor. Initialize this Vertex from halfEdge ref, position vector, and unique index
		*   \param[in] halfEdge        iterator to HalfEdge coming out of this Vertex
		*   \param[in] pos             position 3D vector
		*   \param[in] index           a unique index from 0, ..., nVertices - 1
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   29.8.2021
		*
		*/
		//-----------------------------------------------------------------------------
		Vertex(const HalfEdgeHandle& halfEdge, const Vector3& pos, const unsigned int& index)
		{
			Set(halfEdge, pos, index);
		}

		/// @{
		/// \name Operators

		//-----------------------------------------------------------------------------
		/*! \brief Standard copy-assignment operator.
		*   \param[in] vert      Vertex to be copied.
		*   \return Reference to this Vertex.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   29.8.2021
		*/
		//-----------------------------------------------------------------------------
		Vertex& operator=(const Vertex& vert)
		{
			if (this == &vert)
				return *this;

			Set(vert);
			return *this;
		}

		/// @{
		/// \name Getters

		//-----------------------------------------------------------------------------
		/*! \brief Get iterator to outgoing HalfEdge.
		*   \return HalfEdgeHandle to the outgoing HalfEdge.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   29.8.2021
		*/
		//-----------------------------------------------------------------------------
		HalfEdgeHandle& HalfEdge()
		{
			return m_HalfEdge;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get const_iterator to the outgoing HalfEdge.
		*   \return const HalfEdgeHandle to outgoing HalfEdge.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   29.8.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] const HalfEdgeHandle& HalfEdge() const
		{
			return m_HalfEdge;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get reference to this Vertex's position vector.
		*   \return Vector3 reference
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   29.8.2021
		*/
		//-----------------------------------------------------------------------------
		Vector3& Position()
		{
			return m_Position;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get const reference to this Vertex's position vector.
		*   \return const Vector3 reference of this Vertex's position
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   29.8.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] const Vector3& Position() const
		{
			return m_Position;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get this Vertex's m_IsBoundary flag
		*   \return true if this Vertex is a boundary vertex
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   25.9.2021
		*/
		//-----------------------------------------------------------------------------
 		[[nodiscard]] bool IsBoundary() const
		{
			return m_IsBoundary;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get this Vertex's m_UniqueVertexIndex
		*   \return vertex index
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   25.9.2021
		*/
		//-----------------------------------------------------------------------------
 		[[nodiscard]] unsigned int Index() const
		{
			return m_UniqueVertexIndex;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get reference to this Vertex's unit normal vector.
		*   \return Vector3 reference
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   29.8.2021
		*/
		//-----------------------------------------------------------------------------
		VertexNormalHandle& Normal()
		{
			return m_Normal;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get const reference to this Vertex's unit normal vector.
		*   \return const VertexNormalHandle reference of this Vertex's normal
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   29.8.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] const VertexNormalHandle& Normal() const
		{
			return m_Normal;
		}

		/// @{
		/// \name Setters
		
		//-----------------------------------------------------------------------------
		/*! \brief Sets this Vertex from halfEdge ref, and position vector
		*   \param[in] halfEdge        iterator to HalfEdge coming out of this Vertex
		*   \param[in] position        position 3D vector
		*   \return reference to this Vertex
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   29.8.2021
		*/
		//-----------------------------------------------------------------------------
		Vertex& Set(const HalfEdgeHandle& halfEdge, const Vector3& position)
		{
			m_HalfEdge = halfEdge;
			m_Position = position;
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Sets this Vertex from halfEdge ref, position, and vertex index
		*   \param[in] halfEdge        iterator to HalfEdge coming out of this Vertex
		*   \param[in] position        position 3D vector
		*   \param[in] index           a unique index from 0, ..., nVertices - 1
		*   \return reference to this Vertex
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   29.8.2021
		*/
		//-----------------------------------------------------------------------------
		Vertex& Set(const HalfEdgeHandle& halfEdge, const Vector3& position, const unsigned int& index)
		{
			m_HalfEdge = halfEdge;
			m_Position = position;
			m_UniqueVertexIndex = index;
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Sets this Vertex from another Vertex
		*   \param[in] other        source vertex
		*   \return reference to this Vertex
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   29.8.2021
		*/
		//-----------------------------------------------------------------------------
		Vertex& Set(const Vertex& other)
		{
			m_HalfEdge = other.m_HalfEdge;
			m_Position = other.m_Position;
			m_UniqueVertexIndex = other.m_UniqueVertexIndex;
			m_IsBoundary = other.m_IsBoundary;
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Sets this Vertex from vertex position
		*   \param[in] position       position Vector3
		*   \return reference to this Vertex
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   29.8.2021
		*/
		//-----------------------------------------------------------------------------
		Vertex& Set(const Vector3& position)
		{
			m_Position = position;
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Sets this Vertex from vertex position coordinates
		*   \param[in] x    position coordinate X.
		*   \param[in] y    position coordinate Y.
		*   \param[in] z    position coordinate Z.
		*   \return reference to this Vertex
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   29.8.2021
		*/
		//-----------------------------------------------------------------------------
		Vertex& Set(const double& x, const double& y, const double& z)
		{
			m_Position = Vector3(x, y, z);
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Sets this Vertex's HalfEdge reference
		*   \param[in] halfEdge        source HalfEdge reference
		*   \return reference to this Vertex
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   29.8.2021
		*/
		//-----------------------------------------------------------------------------
		Vertex& SetHalfEdge(const HalfEdgeHandle& halfEdge)
		{
			m_HalfEdge = halfEdge;
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Sets this Vertex's position vector
		*   \param[in] pos        source position vector
		*   \return reference to this Vertex
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   29.8.2021
		*/
		//-----------------------------------------------------------------------------
		Vertex& SetPosition(const Vector3& pos)
		{
			m_Position = pos;
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Sets this Vertex's index
		*   \param[in] id        a unique index from 0, ..., nVertices - 1
		*   \return reference to this Vertex
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   29.8.2021
		*/
		//-----------------------------------------------------------------------------
		Vertex& SetIndex(const unsigned int& id)
		{
			m_UniqueVertexIndex = id;
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Sets this Vertex's m_IsBoundary flag
		*   \param[in] value      true or false
		*   \return reference to this Vertex
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   25.9.2021
		*/
		//-----------------------------------------------------------------------------
 		Vertex& SetIsBoundary(const bool& value)
		{
			m_IsBoundary = value;
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Sets this Vertex's m_Normal.
		*   \param[in] vertNormal      handle to VertexNormal.
		*   \return reference to this Vertex
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   12.10.2021
		*/
		//----------------------------------------------------------------------------- 		
 		Vertex& SetNormal(const VertexNormalHandle& vertNormal)
		{
			m_Normal = vertNormal;
			return *this;
		}

	private:
		//!< Refers to the HalfEdge coming out of this Vertex.
		HalfEdgeHandle m_HalfEdge;

		//!< 3D Euclidean position of this Vertex.
		Vector3 m_Position;

		//!< A unique index from 0, ..., nVertices - 1
		unsigned int m_UniqueVertexIndex{ 0 };

 		//!< True if this vertex is a boundary vertex
		bool m_IsBoundary = false;

		//!< Refers to this Vertex's outward-pointing unit normal.
		VertexNormalHandle m_Normal;
	};

} // Symplektis::GeometryBase