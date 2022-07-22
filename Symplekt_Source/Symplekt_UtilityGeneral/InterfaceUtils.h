/*! \file  InterfaceUtils.h
 *  \brief Helper templates for interfaces.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   17.11.2021
 *
 */

#pragma once

#include <memory>

namespace Symplektis::Util
{
	//=============================================================================
	/// \class ISymplektBaseObject
	/// \brief Base interface object
	///
	/// \ingroup UTILITY_GENERAL
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   17.11.2021
	//=============================================================================
	class ISymplektBaseObject
	{
	public:
		/// @{
		/// \name Default Special Members

		/// \brief Default constructor.
		ISymplektBaseObject() = default;
		
		/// \brief Default copy constructor.
		ISymplektBaseObject(const ISymplektBaseObject&) = default;

		/// \brief Default move constructor.
		ISymplektBaseObject(ISymplektBaseObject&&) = default;

		/// \brief Default copy-assignment operator.
		ISymplektBaseObject& operator=(const ISymplektBaseObject&) = default;

		/// \brief Default move-assignment operator.
		ISymplektBaseObject& operator=(ISymplektBaseObject&&) = default;
		
		/// \brief Default destructor.
		virtual ~ISymplektBaseObject() = default;

		//-----------------------------------------------------------------------------
		/*! \brief Create a new instance of pointer to this object. Make sure to override and return concrete instances.
		 * \return cloned pointer.
		 *
		 * \author M. Cavarga (MCInversion)
		 * \date   17.11.2021
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] virtual ISymplektBaseObject* Clone() const = 0;
	};


	 
	//=============================================================================
	/// \class SymplektUnknownObject
	/// \brief Unknown object type storing a pointer to another object's interface derived from ISymplektBaseObject.
	///
	/// \ingroup UTILITY_GENERAL
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   17.11.2021
	//=============================================================================
	class SymplektUnknownObject
	{
	public:

		/// @{
		/// \name Default Special Members

		/// \brief Default constructor.
		SymplektUnknownObject() = default;

		/// @{
		/// \name Constructors

		//-----------------------------------------------------------------------------
		/*! \brief Copy constructor.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   17.11.2021
		 */
		 //-----------------------------------------------------------------------------
		SymplektUnknownObject(const SymplektUnknownObject& from);

		//-----------------------------------------------------------------------------
		/*! \brief Move constructor.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   17.11.2021
		 */
		 //-----------------------------------------------------------------------------
		SymplektUnknownObject(SymplektUnknownObject&& from) noexcept;

		//-----------------------------------------------------------------------------
		/*! \brief Constructor. Initialize from ISymplektBaseObject instance
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   17.11.2021
		 */
		 //-----------------------------------------------------------------------------
		explicit SymplektUnknownObject(const ISymplektBaseObject& from);

		//-----------------------------------------------------------------------------
		/*! \brief Constructor. Initialize from ISymplektBaseObject instance pointer
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   17.11.2021
		 */
		 //-----------------------------------------------------------------------------
		explicit SymplektUnknownObject(ISymplektBaseObject* from)
		{
			SetPointer(from);
		}

		/// @{
		/// \name Destructor

		//-----------------------------------------------------------------------------
		/*! \brief Destructor
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   17.11.2021
		 */
		 //-----------------------------------------------------------------------------
		virtual ~SymplektUnknownObject()
		{
			DeletePointer();
		}

		/// @{
		/// \name Static Members
		
		//-----------------------------------------------------------------------------
		/*! \brief Static interface deleter
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   17.11.2021
		 *
		 */
		 //-----------------------------------------------------------------------------
		static void DeleteInterface(SymplektUnknownObject& obj);
		
		/// @{
		/// \name Template Functions
		
		//-----------------------------------------------------------------------------
		/*! \brief Retrieve arbitrary interface
		 *
		 * \tparam Interface     retrieved interface type
		 *
		 * \return const pointer to an interface given by the template param, nullptr if not found.
		 *
		 * \author M. Cavarga (MCInversion)
		 * \date   17.11.2021
		 */
		//-----------------------------------------------------------------------------
		template<class Interface>
		[[nodiscard]] const Interface* RetrieveInterface() const
		{
			if (!m_pObject)
				return nullptr;

			return dynamic_cast<const Interface*>(m_pObject);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Retrieve arbitrary interface
		 *
		 * \tparam Interface      retrieved interface type
		 *
		 * \return pointer to an interface given by the template param, nullptr if not found.
		 *
		 * \author M. Cavarga (MCInversion)
		 * \date   17.11.2021
		 */
		 //-----------------------------------------------------------------------------
		template<class Interface>
		Interface* RetrieveInterface()
		{
			if (!m_pObject)
				return nullptr;

			return dynamic_cast<Interface*>(m_pObject);
		}

		/// @{
		/// \name Operators

		//-----------------------------------------------------------------------------
		/*! \brief Copy-assignment operator
		 * \param[in] other         object to be copy-assigned.
		 * \return reference to this object.
		 *
		 * \author M. Cavarga (MCInversion)
		 * \date   17.11.2021
		 */
		 //-----------------------------------------------------------------------------
		SymplektUnknownObject& operator=(const SymplektUnknownObject& other);

		//-----------------------------------------------------------------------------
		/*! \brief Move-assignment operator
		 * \param[in] other         object to be move-assigned.
		 * \return reference to this object.
		 *
		 * \author M. Cavarga (MCInversion)
		 * \date   17.11.2021
		 */
		 //-----------------------------------------------------------------------------
		SymplektUnknownObject& operator=(SymplektUnknownObject&& other) noexcept;


		/// @{
		/// \name Flags

		//-----------------------------------------------------------------------------
		/*! \brief Null flag for this object.
		 * \return true if m_pObject is a nullptr
		 *
		 * \author M. Cavarga (MCInversion)
		 * \date   17.11.2021
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] bool IsNull() const
		{
			return m_pObject == nullptr;
		}

		/// @{
		/// \name Setters

		//-----------------------------------------------------------------------------
		/*! \brief Set m_pObject to nullptr.
		 *
		 * \author M. Cavarga (MCInversion)
		 * \date   17.11.2021
		 */
		 //-----------------------------------------------------------------------------
		void SetNull();

	protected:

		/// @{
		/// \name Protected Getters

		//-----------------------------------------------------------------------------
		/*! \brief Interface object const pointer getter.
		 * \return const pointer to ISymplektBaseObject.
		 *
		 * \author M. Cavarga (MCInversion)
		 * \date   17.11.2021
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] virtual const ISymplektBaseObject* GetPointer() const
		{
			return m_pObject;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Interface object pointer getter.
		 * \return pointer to ISymplektBaseObject.
		 *
		 * \author M. Cavarga (MCInversion)
		 * \date   17.11.2021
		 */
		 //-----------------------------------------------------------------------------
		virtual ISymplektBaseObject* GetPointer()
		{
			return m_pObject;
		}

		/// @{
		/// \name Protected Setters

		//-----------------------------------------------------------------------------
		/*! \brief Interface object pointer setter.
		 * \param[in] pObject       pointer to be set in m_pObject
		 *
		 * \author M. Cavarga (MCInversion)
		 * \date   17.11.2021
		 */
		 //-----------------------------------------------------------------------------
		void SetPointer(ISymplektBaseObject* pObject)
		{
			m_pObject = pObject;
		}

		/// @{
		/// \name Protected Deleters

		//-----------------------------------------------------------------------------
		/*! \brief Interface object pointer deleter.
		 *
		 * \author M. Cavarga (MCInversion)
		 * \date   17.11.2021
		 */
		 //-----------------------------------------------------------------------------
		void DeletePointer() const
		{
			delete m_pObject;
		}

	private:

		//>! stored raw pointer to object
		ISymplektBaseObject* m_pObject = nullptr;
	};

	//=============================================================================
	/// \class SymplektObjectInterface
	/// \brief Concrete Symplektis object interface.
	///
	/// \tparam Interface     interface type
	///
	/// \ingroup UTILITY_GENERAL
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   17.11.2021
	//=============================================================================
	template <class Interface>
	class SymplektObjectInterface final : public SymplektUnknownObject
	{
	public:

		/// @{
		/// \name Default Special Members

		/// \brief Default constructor.
		SymplektObjectInterface() = default;
		
		/// \brief Default move-assignment operator.
		SymplektObjectInterface& operator=(SymplektObjectInterface<Interface>&& other) = default;

		/// \brief Default destructor.
		~SymplektObjectInterface() override = default;
		
		/// @{
		/// \name Constructors

		//-----------------------------------------------------------------------------
		/*! \brief Constructor. Initialize from ISymplektBaseObject instance.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   17.11.2021
		 */
		 //-----------------------------------------------------------------------------
		explicit SymplektObjectInterface(const ISymplektBaseObject& other)
			: SymplektUnknownObject(other)
		{			
		}

		//-----------------------------------------------------------------------------
		/*! \brief Constructor. Initialize from ISymplektBaseObject instance pointer.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   17.11.2021
		 */
		 //-----------------------------------------------------------------------------
		explicit SymplektObjectInterface(ISymplektBaseObject* other)
			: SymplektUnknownObject(other)
		{			
		}

		//-----------------------------------------------------------------------------
		/*! \brief Constructor. Initialize from SymplektUnknownObject instance. \n
		 *         If retrieved interface matches with this template instance's interface type, this object is not null.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   17.11.2021
		 */
		 //-----------------------------------------------------------------------------
		explicit SymplektObjectInterface(const SymplektUnknownObject& other)
			: SymplektUnknownObject(other.RetrieveInterface<Interface>() != nullptr ? other : SymplektUnknownObject())
		{			
		}

		//-----------------------------------------------------------------------------
		/*! \brief Constructor. Move-initialize from SymplektUnknownObject instance. \n
		 *         If retrieved interface matches with this template instance's interface type, this object is not null.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   17.11.2021
		 */
		 //-----------------------------------------------------------------------------
		explicit SymplektObjectInterface(SymplektUnknownObject&& other) noexcept
			: SymplektUnknownObject(other.RetrieveInterface<Interface>() != nullptr ? std::move(other) : SymplektUnknownObject())
		{
		}

		//-----------------------------------------------------------------------------
		/*! \brief Copy constructor.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   17.11.2021
		 */
		 //-----------------------------------------------------------------------------
		SymplektObjectInterface(const SymplektObjectInterface<Interface>& other)
			: SymplektUnknownObject(other)
		{
		}

		//-----------------------------------------------------------------------------
		/*! \brief Move constructor.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   17.11.2021
		 */
		 //-----------------------------------------------------------------------------
		SymplektObjectInterface(SymplektObjectInterface<Interface>&& other) noexcept
			: SymplektUnknownObject(std::move(other))
		{
		}

		/// @{
		/// \name Operators

		//-----------------------------------------------------------------------------
		/*! \brief Copy-assignment operator
		 *  \param[in] other     object instance to be copy-assigned to this object.
		 *  \return reference to this object.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   17.11.2021
		 */
		 //-----------------------------------------------------------------------------
		SymplektObjectInterface& operator=(const SymplektObjectInterface<Interface>& other)
		{
			return SymplektUnknownObject::operator=(other);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Arrow operator.
		 *  \return pointer to this object's template type interface, nullptr if null.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   17.11.2021
		 */
		 //-----------------------------------------------------------------------------
		Interface* operator->()
		{
			return GetInterface();
		}

		//-----------------------------------------------------------------------------
		/*! \brief Const arrow operator.
		 *  \return const pointer to this object's template type interface, nullptr if null.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   17.11.2021
		 */
		 //-----------------------------------------------------------------------------
		const Interface* operator->() const
		{
			return GetInterface();
		}
		
		/// @{
		/// \name Getters

		//-----------------------------------------------------------------------------
		/*! \brief Interface getter.
		 *  \return pointer to this object's template type interface, nullptr if null.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   17.11.2021
		 */
		 //-----------------------------------------------------------------------------
		Interface* GetInterface()
		{
			return RetrieveInterface<Interface>();
		}

		//-----------------------------------------------------------------------------
		/*! \brief Const interface getter.
		 *  \return const pointer to this object's template type interface, nullptr if null.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   17.11.2021
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] const Interface* GetInterface() const
		{
			return RetrieveInterface<Interface>();
		}		
	};
	
} // Symplektis::Util