/*! \file ContainerTypes.h
*   \brief Types and templates to be used for linear containers of geometry and other referenced data items.
*   
*   \author M. Cavarga (MCInversion)
*   \date 17.6.2022
*
\verbatim
   Previous attempts with referenced geometry and binary tree implementations used iterators, but as it turns out: \n
   iterators of container elements after the insertion/erasure position are invalidated. This renders them useless \n
   for applications involving topological adjustments to referenced geometry because a substantial portion of iterators\n
   used in GeometryBase types (e.g. Vertex, HalfEdge, Face...) would need to be re-validated (reset) after adding or \n
   removing an element from container.

   The current implementation involves global index types, container indices, unique containers, and index handles.  \n
   The following rules must apply: \n
   1) Referencing after completion & validation: \n
     > A container element can only be retrieved after it is complete and of its all handles are valid. \n
   2) Containers are uniquely identified by their UUID upon construction. \n
     > Unless explicitly specified upon construction, containers have unique identifiers, so that handle indices can be suitably comparable. \n

   TODO: Consider using pre-validation upon every use of data stored using these handles.
\endverbatim
*/

#pragma once

#include "NamedValue.h"
#include "Exceptions.h"

#include "UUIDTools.h"

#include <algorithm>
#include <cstdint>
#include <vector>

namespace Symplektis::Util
{
	///=============================================================================
	/// Global definition of index types
	/// 
	/// Inspired by PMP (Polygon Mesh Processing) library Types.h/IndexType
	/// Copyright 2011-2021 the Polygon Mesh Processing Library developers.
	/// Copyright 2001-2005 by Computer Graphics Group, RWTH Aachen
	///
	///=============================================================================
#ifdef SYMPLEKT_64BIT_INDEX
	using Symplekt_IndexType = std::int_least64_t;
	constexpr Symplekt_IndexType SYMPLEKT_MAX_INDEX = INT_LEAST64_MAX;
#else
	using Symplekt_IndexType = std::int_least32_t;
	constexpr Symplekt_IndexType SYMPLEKT_MAX_INDEX = INT_LEAST32_MAX;
#endif
	
	//=============================================================================
	/// \class ContainerIndex
	/// \brief Array index value.
	///
	/// \ingroup UTILITY_GENERAL
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   17.6.2022
	//=============================================================================
	class ContainerIndex : public NamedValue<Symplekt_IndexType, ContainerIndex>
	{
	public:
		using NamedValue::NamedValue;

		/// @{
		/// \name Constructors

		//-----------------------------------------------------------------------------
		/*! \brief Constructor. Initialized from a size_t value.
		 *  \param[in] value       size_t value.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   29.11.2021
		 */
		 //-----------------------------------------------------------------------------
		explicit ContainerIndex(const size_t& value)
			: ContainerIndex(static_cast<Symplekt_IndexType>(value)) { }

		//-----------------------------------------------------------------------------
		/*! \brief Constructor. Initialized from an unsigned int value.
		 *  \param[in] value       unsigned int value.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   29.11.2021
		 */
		 //-----------------------------------------------------------------------------
		explicit ContainerIndex(const unsigned int& value)
			: ContainerIndex(static_cast<Symplekt_IndexType>(value)) { }

		//-----------------------------------------------------------------------------
		/*! \brief Constructor. Initialized from an long int value.
		 *  \param[in] value       long int value.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   29.11.2021
		 */
		 //-----------------------------------------------------------------------------
		explicit ContainerIndex(const long int& value)
			: ContainerIndex(static_cast<Symplekt_IndexType>(value)) { }

		/// @{
		/// \name Flags

		//-----------------------------------------------------------------------------
		/*! \brief Validity flag based on the value sign.
		 *  \return true if the value is non-negative and below max value.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   29.11.2021
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] constexpr bool IsValid() const noexcept
		{
			return (m_value >= 0 && m_value < SYMPLEKT_MAX_INDEX);
		}

		/// @{
		/// \name Operators

		//-----------------------------------------------------------------------------
		/*! \brief Not operator. Returns true if this index value is negative.
		 *  \return true if the value is negative.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   29.11.2021
		 */
		 //-----------------------------------------------------------------------------
		bool operator!() const
		{
			return m_value < 0;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Explicit bool conversion operator.
		 *  \return true if this index's value is more than or equal to 0.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   5.12.2021
		 */
		 //-----------------------------------------------------------------------------
		explicit operator bool() const
		{
			return m_value >= 0;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Explicit int conversion operator.
		 *  \return int value of this index.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   26.6.2022
		 */
		 //-----------------------------------------------------------------------------
		explicit operator int() const
		{
			return m_value;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Copy-assignment operator with size_t value.
		 *  \param[in] value          size_t value to be assigned.
		 *  \return reference to this ContainerIndex.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   29.11.2021
		 */
		 //-----------------------------------------------------------------------------
		ContainerIndex& operator= (const size_t& value)
		{
			m_value = static_cast<Symplekt_IndexType>(value);
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Copy-assignment operator with int value.
		 *  \param[in] value          int value to be assigned.
		 *  \return reference to this ContainerIndex.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   29.11.2021
		 */
		 //-----------------------------------------------------------------------------
		ContainerIndex& operator= (const int& value) noexcept
		{
			m_value = static_cast<Symplekt_IndexType>(value);
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Copy-assignment operator with unsigned int value.
		 *  \param[in] value          unsigned int value to be assigned.
		 *  \return reference to this ContainerIndex.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   29.11.2021
		 */
		 //-----------------------------------------------------------------------------
		ContainerIndex& operator= (const unsigned int& value)
		{
			m_value = static_cast<Symplekt_IndexType>(value);
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief More-than-or-equal operator with size_t value.
		 *  \param[in] value          size_t value to be compared.
		 *  \return true if this index's value is more than or equal to the compared value.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   29.11.2021
		 */
		 //-----------------------------------------------------------------------------
		bool operator>= (const size_t& value) const
		{
			return m_value >= static_cast<Symplekt_IndexType>(value);
		}

		//-----------------------------------------------------------------------------
		/*! \brief More-than-or-equal operator with ContainerIndex value.
		 *  \param[in] other          ContainerIndex to be compared.
		 *  \return true if this index's value is more than or equal to the compared value.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   29.11.2021
		 */
		 //-----------------------------------------------------------------------------
		bool operator>= (const ContainerIndex& other) const
		{
			return m_value >= other.m_value;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Less-than operator for size_t value.
		 *  \param[in] value          value to be compared.
		 *  \return true if this index's value is less than the compared value.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   29.11.2021
		 */
		 //-----------------------------------------------------------------------------
		bool operator< (const size_t& value) const
		{
			return m_value < static_cast<Symplekt_IndexType>(value);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Less-than operator for size_t value.
		 *  \param[in] value          value to be compared.
		 *  \return true if this index's value is less than the compared value.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   29.11.2021
		 */
		 //-----------------------------------------------------------------------------
		bool operator< (const ContainerIndex& value) const
		{
			return m_value < value.get();
		}

		//-----------------------------------------------------------------------------
		/*! \brief Comparison equal operator with another ContainerIndex.
		 *  \param[in] other          ContainerIndex to be compared.
		 *  \return true if this index's value is equal to the compared ContainerIndex's value.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   20.1.2022
		 */
		 //-----------------------------------------------------------------------------
		bool operator== (const ContainerIndex& other) const
		{
			return m_value == other.m_value;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Comparison equal operator with size_t value.
		 *  \param[in] value          size_t value to be compared.
		 *  \return true if this index's value is equal to the compared value.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   20.1.2022
		 */
		 //-----------------------------------------------------------------------------
		bool operator== (const size_t& value) const
		{
			if (m_value < 0)
				return false;

			return static_cast<size_t>(m_value) == value;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Comparison equal operator with int value.
		 *  \param[in] value          int value to be compared.
		 *  \return true if this index's value is equal to the compared value.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   5.12.2021
		 */
		 //-----------------------------------------------------------------------------
		bool operator== (const int& value) const
		{
			return m_value == static_cast<Symplekt_IndexType>(value);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Prefix incrementation operator.
		 *  \return reference to this ContainerIndex.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   26.6.2022
		 */
		 //-----------------------------------------------------------------------------
		ContainerIndex& operator++()
		{
			++m_value;
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Prefix decrementation operator.
		 *  \return reference to this ContainerIndex.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   26.6.2022
		 */
		 //-----------------------------------------------------------------------------
		ContainerIndex& operator--()
		{
			--m_value;
			return *this;
		}

	};

	/// \brief null index pointing no a non-existent position in an array.
	constexpr ContainerIndex NULL_INDEX{ -1 };

	/// \brief maximum possible ContainerIndex.
	constexpr ContainerIndex MAX_INDEX{ SYMPLEKT_MAX_INDEX };
	
} // namespace Symplektis::Util