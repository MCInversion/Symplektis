/*! \file ContainerTypes.h
*   \brief Types and templates to be used for linear containers of geometry and other referenced data items.
*   
*   \author M. Cavarga (MCInversion)
*   \date 17.6.2022
*/

#pragma once

#include "NamedValue.h"
#include "Exceptions.h"

#include "UUIDTools.h"

#include <algorithm>
#include <cstdint>
#include <memory>
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
	/// \class UniqueIndexedContainer
	/// \tparam T    type of item in this container.
	/// \brief A linear iterable container identified by a UUID.
	///
	/// \ingroup UTILITY_GENERAL
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   20.6.2022
	/// 
	///=============================================================================
	template <typename T>
	class UniqueIndexedContainer : public std::vector<T>
	{
	public:
		///-----------------------------------------------------------------------------
		/// \brief Default constructor. Generates a UUID when an instance of this container is created.
		///-----------------------------------------------------------------------------
		UniqueIndexedContainer()
			: std::vector<T>(),
			  m_ContainerID(CreateUUID())
		{ }
		
		///-----------------------------------------------------------------------------
		/// \brief UUID getter.
		/// \return this container's ID.
		///-----------------------------------------------------------------------------
		UUID& GetID()
		{
			return m_ContainerID;
		}
	
	private:	
		UUID m_ContainerID = GUID_NULL; //>! UUID of this container.
	};

	///=============================================================================
	/// \class ContainerIndexHandle
	/// \tparam T    type of item in m_Container.
	/// \brief A handle object for ContainerIndex also containing a reference to its respective container.\n
	///        This object is meant to be used as a reference object containing index information.
	///
	/// \ingroup UTILITY_GENERAL
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   17.6.2022
	///
	/// Inspired by PMP (Polygon Mesh Processing) library SurfaceMesh.h/Handle
	/// Copyright 2011-2021 the Polygon Mesh Processing Library developers.
	/// Copyright 2001-2005 by Computer Graphics Group, RWTH Aachen
	/// 
	///=============================================================================
	template <typename T>
	class ContainerIndexHandle
	{
	public:
		/// @{
		/// \name Constructors

		//-----------------------------------------------------------------------------
		/*! \brief Construct from a given index and pointer to a container.
		 *  \param[in] id          index value to be initialized from.
		 *  \param[in] container   pointer to a container.
		 *
		 *  \author M. Cavarga (MCInversion)
		 *  \date   20.6.2022
		 */
		 //-----------------------------------------------------------------------------
		explicit ContainerIndexHandle(ContainerIndex                    id = NULL_INDEX, 
			                          UniqueIndexedContainer<T>* container = nullptr)
			: m_Index(std::move(id)),
		      m_Container(container)
		{ }

		/// @{
		/// \name Special Members

		/// \brief Destructor. De-allocates the raw m_Container.
		~ContainerIndexHandle()
		{
			delete m_Container;
		}

		/// \brief Default constructor.
		ContainerIndexHandle() = delete;

		/// \brief Copy constructor.
		ContainerIndexHandle(const ContainerIndexHandle&) = default;

		/// \brief Move constructor.
		ContainerIndexHandle(ContainerIndexHandle&&) = default;

		/// \brief Copy-assignment operator.
		ContainerIndexHandle& operator=(const ContainerIndexHandle&) = default;

		/// \brief Move-assignment operator.
		ContainerIndexHandle& operator=(ContainerIndexHandle&&) = default;
		
		/// @{
		/// \name Operators

		//-----------------------------------------------------------------------------
		/*! \brief Not operator.
		 *  \return true if m_Index is invalid or m_Container is empty or null.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   20.6.2022
		 */
		 //-----------------------------------------------------------------------------
		bool operator!() const
		{
			return !IsValid();
		}

		//-----------------------------------------------------------------------------
		/*! \brief Explicit bool conversion operator.
		 *  \return true if m_Index is valid and m_Container is not empty or null.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   20.6.2022
		 */
		 //-----------------------------------------------------------------------------
		explicit operator bool() const
		{
			return IsValid();
		}

		//-----------------------------------------------------------------------------
		/*! \brief Comparison equal operator.
		 *
		 *  \return true if the contents of this handle are valid, compatible, and equivalent to other.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   20.6.2022
		 */
		 //-----------------------------------------------------------------------------
		bool operator==(const ContainerIndexHandle& other) const
		{
			if (!IsValid() || !other.IsValid())
				return false;

			if (m_Container->GetID() != other.m_Container->GetID())
				return false;
			
			return (m_Index == other.m_Index && m_Container == other.m_Container);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Comparison not-equal operator.
		 *
		 *  \return true if the contents of this handle are invalid, incompatible, or not equivalent to other.
		 *
		 *  \author M. Cavarga (MCInversion)
		 *  \date   20.6.2022
		 */
		//-----------------------------------------------------------------------------
		bool operator!=(const ContainerIndexHandle& other) const
		{
			if (!IsValid() || !other.IsValid())
				return true;

			if (m_Container->GetID() != other.m_Container->GetID())
				return true;

			return (m_Index != other.m_Index || m_Container != other.m_Container);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Comparison less-than operator.
		 *
		 *  \return true if this handle's index is less than other handle's index.
		 *  \throw Symplektis::InvalidInputException if at least one of the compared handles is invalid.
		 *  \throw Symplektis::IncompatibleInputException if the indices belong to different containers.
		 *
		 *  \author M. Cavarga (MCInversion)
		 *  \date   20.6.2022
		 */
		//-----------------------------------------------------------------------------
		bool operator<(const ContainerIndexHandle& other) const
		{
			if (!IsValid() || !other.IsValid())
			{
				throw Symplektis::InvalidInputException(
					"Symplektis exception: ContainerIndexHandle:: at least one of the handles compared by \"<\" is invalid\n");
			}

			if (m_Container->GetID() != other.m_Container->GetID())
			{
				throw Symplektis::IncompatibleInputException(
					"Symplektis exception: ContainerIndexHandle:: containers of the handles compared by \"<\" are incompatible\n");
			}

			return m_Index < other.m_Index;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Comparison less-than-or-equal-to operator.
		 *
		 *  \return true if this handle's index is less than or equal to other handle's index.
		 *  \throw Symplektis::InvalidInputException if at least one of the compared handles is invalid.
		 *  \throw Symplektis::IncompatibleInputException if the indices belong to different containers.
		 *
		 *  \author M. Cavarga (MCInversion)
		 *  \date   20.6.2022
		 */
		 //-----------------------------------------------------------------------------
		bool operator<=(const ContainerIndexHandle& other) const
		{
			if (!IsValid() || !other.IsValid())
			{
				throw Symplektis::InvalidInputException(
					"Symplektis exception: ContainerIndexHandle:: at least one of the handles compared by \"<=\" is invalid\n");
			}

			if (m_Container->GetID() != other.m_Container->GetID())
			{
				throw Symplektis::IncompatibleInputException(
					"Symplektis exception: ContainerIndexHandle:: containers of the handles compared by \"<=\" are incompatible\n");
			}
			
			return m_Index <= other.m_Index;
		}
		
		/// @{
		/// \name Getters

		//-----------------------------------------------------------------------------
		/*! \brief Get non-const reference to this handle's index.
		 *
		 *  \return Reference to the index of this handle.
		 *
		 *  \author M. Cavarga (MCInversion)
		 *  \date   20.6.2022
		 */
		 //-----------------------------------------------------------------------------
		ContainerIndex& GetIndex()
		{
			return m_Index;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get const reference to this handle's index.
		 *
		 *  \return Const reference to the index of this handle.
		 *
		 *  \author M. Cavarga (MCInversion)
		 *  \date   20.6.2022
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] const ContainerIndex& GetIndex() const
		{
			return m_Index;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get a const reference to a container element.
		 *
		 *  \return const reference to a container element.
		 *  \throw InvalidHandleException if this handle is invalid.
		 *
		 *  \author M. Cavarga (MCInversion)
		 *  \date   23.6.2022
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] const T& GetElement() const
		{
			if (!IsValid())
			{
				throw Symplektis::InvalidHandleException("ContainerIndexHandle::GetElement: Invalid handle! Check m_Index or m_Container!\n");
			}

			return m_Container->at(m_Index);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get a reference to a container element.
		 *
		 *  \return reference to a container element.
		 *  \throw InvalidHandleException if this handle is invalid.
		 *
		 *  \author M. Cavarga (MCInversion)
		 *  \date   23.6.2022
		 */
		 //-----------------------------------------------------------------------------
		T& GetElement()
		{
			if (!IsValid())
			{
				throw Symplektis::InvalidHandleException("ContainerIndexHandle::GetElement: Invalid handle! Check m_Index or m_Container!\n");
			}

			return m_Container->at(m_Index);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get raw pointer to the element in m_Container.
		 *
		 *  \return Pointer to the element in m_Container indexed by m_Index, nullptr if m_Index is invalid.
		 *
		 *  \author M. Cavarga (MCInversion)
		 *  \date   20.6.2022
		 */
		 //-----------------------------------------------------------------------------
		T* GetElementPtr()
		{
			if (!IsValid())
				return nullptr;

			return &m_Container->at(m_Index);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get const raw pointer to the element in m_Container.
		 *
		 *  \return Const pointer to the element in m_Container indexed by m_Index, nullptr if m_Index is invalid.
		 *
		 *  \author M. Cavarga (MCInversion)
		 *  \date   20.6.2022
		 */
		 //-----------------------------------------------------------------------------
		const T* GetElementPtr() const
		{
			if (!IsValid())
				return nullptr;

			return &m_Container->at(m_Index);
		}

		/// @{
		/// \name Flags

		//-----------------------------------------------------------------------------
		/*! \brief Verify if m_Container is valid, and then if m_Index is valid for m_Container.
		 *
		 *  \return true if m_Container is not null, and if m_Index is valid for m_Container.
		 *
		 *  \author M. Cavarga (MCInversion)
		 *  \date   20.6.2022
		 */
		//-----------------------------------------------------------------------------
		[[nodiscard]] bool IsValid() const
		{
			if (!m_Container)
				return false;
			
			return (m_Index.IsValid() && m_Index < m_Container->size());
		}

		/// @{
		/// \name Base Functionality
		
		//-----------------------------------------------------------------------------
		/*! \brief Reset this handle to a null handle. Both m_Index and m_Containers are reset to default values.
		 *
		 *  \author M. Cavarga (MCInversion)
		 *  \date   20.6.2022
		 */
		//-----------------------------------------------------------------------------
		void Reset()
		{
			m_Index = NULL_INDEX;
			m_Container = nullptr;
		}
	
	private:

		// ===========================================================================
		//
		
		ContainerIndex m_Index = NULL_INDEX;               //>! index value for an element in m_Container.
		UniqueIndexedContainer<T>* m_Container = nullptr;  //>! raw pointer to a container indexed by m_Index.
	};
	
} // namespace Symplektis::Util