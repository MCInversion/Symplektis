/*! \file VertexNormal.h
*   \brief Vertex normal vector object for referenced mesh geometry objects.
*
\verbatim
-------------------------------------------------------------------------------
created  : 12.10.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/
#pragma once

#include "Vector3.h"
#include "GeometryHelperTypes.h"

namespace Symplektis::GeometryBase
{
	//=============================================================================
	/// \class VertexNormal
	/// \brief A class acting as a vertex normal.
	///
	/// \ingroup GEOMETRY_BASE
	///
	/// \author M. Cavarga (MCInversion)
	/// \date 12.10.2021
	//=============================================================================
	class VertexNormal
	{
	public:
		/// @{
		/// \name Default Special Members

		//-----------------------------------------------------------------------------
		/*! \brief Default constructor
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   12.10.2021
		*/
		//-----------------------------------------------------------------------------
		VertexNormal() = default;

		//-----------------------------------------------------------------------------
		/*! \brief Default move constructor
		*   \param[in] other  VertexNormal to be moved.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   12.10.2021
		*/
		//-----------------------------------------------------------------------------
		VertexNormal(VertexNormal&& other) = default;

		//-----------------------------------------------------------------------------
		/*! \brief Default destructor
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   12.10.2021
		*/
		//-----------------------------------------------------------------------------
		~VertexNormal() = default;

		//-----------------------------------------------------------------------------
		/*! \brief Default move-assignment operator
		*   \param[in] other  VertexNormal to be move-assigned.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   12.10.2021
		*/
		//-----------------------------------------------------------------------------
		VertexNormal& operator=(VertexNormal&& other) = default;
		
		/// @{
		/// \name Constructors
		
		//-----------------------------------------------------------------------------
		/*! \brief Constructor. Creates a normal vector instance with vector vec and reference to Vertex vert.
		 *  \param[in] vec             normal Vector3
		 *  \param[in] vert            Vertex iterator of ReferencedMeshGeometryData.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   12.10.2021
		*/
		//-----------------------------------------------------------------------------
		VertexNormal(const Vector3& vec, const VertexIterator& vert)
		{
			Set(vec);
			SetVertex(vert);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Copy constructor.
		 *  \param[in] other        VertexNormal to be copied.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   12.10.2021
		*/
		//-----------------------------------------------------------------------------
		VertexNormal(const VertexNormal& other)
		{
			Set(other);
		}

		/// @{
		/// \name Operators

		//-----------------------------------------------------------------------------
		/*! \brief Standard copy-assignment operator.
		*   \param[in] other      VertexNormal to be copied.
		*   \return Reference to this VertexNormal.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   12.10.2021
		*/
		//-----------------------------------------------------------------------------
		VertexNormal& operator=(const VertexNormal& other)
		{
			if (this == &other)
				return *this;

			Set(other);
			return *this;
		}

		/// @{
		/// \name Setters

		//-----------------------------------------------------------------------------
		/*! \brief Sets this VertexNormal from another VertexNormal.
		 *  \param[in] other             vertex normal to be copied.
		 *  \return reference to this VertexNormal
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   12.10.2021
		*/
		//-----------------------------------------------------------------------------
		VertexNormal& Set(const VertexNormal& other)
		{
			m_Vector = other.m_Vector;
			m_Vertex = other.m_Vertex;
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Sets normal vector.
		 *  \param[in] vec             normal Vector3.
		 *  \return reference to this VertexNormal
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   12.10.2021
		*/
		//-----------------------------------------------------------------------------
		VertexNormal& Set(const Vector3& vec)
		{
			m_Vector = vec;
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Sets vertex reference (iterator).
		 *  \param[in] vert            Vertex iterator of ReferencedMeshGeometryData.
		 *  \return reference to this VertexNormal
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   12.10.2021
		*/
		//-----------------------------------------------------------------------------
		VertexNormal& SetVertex(const VertexIterator& vert)
		{
			m_Vertex = vert;
			return *this;
		}

		/// @{
		/// \name Getters

		//-----------------------------------------------------------------------------
		/*! \brief Gets m_Vector reference.
		 *  \return normal vector reference
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   12.10.2021
		*/
		//-----------------------------------------------------------------------------
		Vector3& Get()
		{
			return m_Vector;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Gets a const m_Vector reference.
		 *  \return const normal vector reference
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   12.10.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] const Vector3& Get() const
		{
			return m_Vector;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Gets m_Vertex iterator reference (iterator to Vertices vector)
		 *  \return vertex iterator.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   12.10.2021
		*/
		//-----------------------------------------------------------------------------
		VertexIterator& Vertex()
		{
			return m_Vertex;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Gets const m_Vertex iterator reference (iterator to Vertices vector)
		 *  \return const vertex iterator.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   12.10.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] const VertexIterator& Vertex() const
		{
			return m_Vertex;
		}
	
	private:

		Vector3 m_Vector; //!< Normal Vector3

		VertexIterator m_Vertex;  //!< Iterator to base Vertex object
	};
	
} // Symplektis::GeometryBase