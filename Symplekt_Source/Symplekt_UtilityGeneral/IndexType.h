/*! \file IndexType.h
*   \brief Value type for geometry container indices.
*   
*   \author M. Cavarga (MCInversion)
*   \date 17.6.2022
*/

#pragma once

#include "NamedValue.h"

#include <algorithm>
#include <cstdint>
#include <memory>
#include <vector>

namespace Symplektis::Util
{
	// Global definition of index types
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
		/// \name Default Special Members

		/// \brief Default constructor.
		ContainerIndex() = default;

		/// \brief Default copy constructor.
		ContainerIndex(const ContainerIndex& other) = default;

		/// \brief Default move constructor.
		ContainerIndex(ContainerIndex&& other) = default;

		/// \brief Default copy-assignment operator.
		ContainerIndex& operator=(const ContainerIndex& other) = default;

		/// \brief Default move-assignment operator.
		ContainerIndex& operator=(ContainerIndex&& other) = default;

		/// \brief Default destructor.
		virtual ~ContainerIndex() = default;

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
		 *  \return true if the value is non-negative.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   29.11.2021
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] constexpr bool IsValid() const noexcept
		{
			return (m_value >= 0);
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
		virtual ContainerIndex& operator= (const int& value)
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

	};

	/// \brief null index pointing no a non-existent position in an array.
	constexpr ContainerIndex NULL_INDEX{ -1 };

	/// \brief maximum possible ContainerIndex.
	constexpr ContainerIndex MAX_INDEX{ SYMPLEKT_MAX_INDEX };

	///=============================================================================
	/// \class ContainerIndexHandle
	/// \brief A handle object for ContainerIndex.
	///
	/// \ingroup UTILITY_GENERAL
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   17.6.2022
	///
	/// Inspired by PMP (Polygon Mesh Processing) library SurfaceMesh.h
	/// Copyright 2011-2021 the Polygon Mesh Processing Library developers.
	/// Copyright 2001-2005 by Computer Graphics Group, RWTH Aachen
	/// 
	///=============================================================================
	template <typename T>
	class ContainerIndexHandle
	{
	public:
		explicit ContainerIndexHandle(ContainerIndex id = NULL_INDEX, const std::shared_ptr<std::vector<T>>& container = nullptr)
			: m_Index(std::move(id)), m_Container(container)
		{ }

		ContainerIndex& GetIndex()
		{
			return m_Index;
		}
		
		[[nodiscard]] const ContainerIndex& GetIndex() const
		{
			return m_Index;
		}

		void Reset()
		{
			m_Index = NULL_INDEX;
		}

		[[nodiscard]] bool IsValid() const
		{
			return m_Index > NULL_INDEX;
		}

		bool operator==(const ContainerIndexHandle& other) const
		{
			return m_Index == other.m_Index;
		}

		bool operator!=(const ContainerIndexHandle& other) const
		{
			return m_Index != other.m_Index;
		}

		bool operator<(const ContainerIndexHandle& other) const
		{
			return m_Index < other.m_Index;
		}

		std::shared_ptr<T>& Get()
		{
			if (!IsValid())
				return nullptr;
			
			return std::shared_ptr<T>(m_Container[m_Index]);
		}
	
	private:
		ContainerIndex m_Index = NULL_INDEX;
		std::shared_ptr<std::vector<T>> m_Container = nullptr;
	};
	
} // namespace Symplektis::Util