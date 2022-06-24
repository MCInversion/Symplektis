/*! \file NamedValue.h
*   \brief Named value type template
*
*   \date 31.5.2021
*   \author M.Cavarga (MCInversion)
*/
#pragma once

namespace Symplektis::Util
{
	///////////////////////////////////////////////////////////
	/// \class NamedValue
	/// \brief Strong type template for value types.
	///
	/// \ingroup UTILITY_GENERAL
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   31.5.2021
	///
	/// See: https://www.fluentcpp.com/2016/12/08/strong-types-for-strong-interfaces/
	/// 
	///////////////////////////////////////////////////////////
	template<typename T, typename PhantomType>
	class NamedValue
	{
	public:

		/// @{
		/// \name Constructors

		///-----------------------------------------------------------------------------
		/// \brief Default constructor.
		///-----------------------------------------------------------------------------
		constexpr NamedValue() = default;

		///-----------------------------------------------------------------------------
		/// \brief Explicit constructor.
		/// \param[in] value      value to be initialized from.
		///-----------------------------------------------------------------------------
		constexpr explicit NamedValue(T value) noexcept
			: m_value(value)
		{
		}

		///-----------------------------------------------------------------------------
		/// \brief Explicit getter operator.
		///-----------------------------------------------------------------------------
		constexpr explicit operator T() const noexcept
		{
			return m_value;
		}

		///-----------------------------------------------------------------------------
		/// \brief Equals comparison operator.
		/// \param[in] otherValue       value to be compared
		/// \return true if values are equal.
		///-----------------------------------------------------------------------------
		constexpr bool operator==(const NamedValue<T, PhantomType>& otherValue) const noexcept
		{
			return m_value == otherValue.m_value;
		}

		///-----------------------------------------------------------------------------
		/// \brief Not equal comparison operator.
		/// \param[in] otherValue       value to be compared
		/// \return true if values are not equal.
		///-----------------------------------------------------------------------------
		constexpr bool operator!=(const NamedValue<T, PhantomType>& otherValue) const noexcept
		{
			return m_value != otherValue.m_value;
		}

		///-----------------------------------------------------------------------------
		/// \brief Less-than comparison operator.
		/// \param[in] otherValue       value to be compared
		/// \return true if this value is less than otherValue.
		///-----------------------------------------------------------------------------
		constexpr bool operator<(const NamedValue<T, PhantomType>& otherValue) const noexcept
		{
			return m_value < otherValue.m_value;
		}

		///-----------------------------------------------------------------------------
		/// \brief More-than comparison operator.
		/// \param[in] otherValue       value to be compared
		/// \return true if this value is more than otherValue.
		///-----------------------------------------------------------------------------
		constexpr bool operator>(const NamedValue<T, PhantomType>& otherValue) const noexcept
		{
			return m_value > otherValue.m_value;
		}

		///-----------------------------------------------------------------------------
		/// \brief Less-than-or-equal comparison operator.
		/// \param[in] otherValue       value to be compared
		/// \return true if this value is less than or equal to otherValue.
		///-----------------------------------------------------------------------------
		constexpr bool operator<=(const NamedValue<T, PhantomType>& otherValue) const noexcept
		{
			return m_value <= otherValue.m_value;
		}

		///-----------------------------------------------------------------------------
		/// \brief More-than-or-equal comparison operator.
		/// \param[in] otherValue       value to be compared
		/// \return true if this value is more than or equal to otherValue.
		///-----------------------------------------------------------------------------
		constexpr bool operator>=(const NamedValue<T, PhantomType>& otherValue) const noexcept
		{
			return m_value >= otherValue.m_value;
		}

		///-----------------------------------------------------------------------------
		/// \brief Value getter.
		/// \return the value of this named value type.
		///-----------------------------------------------------------------------------
		[[nodiscard]] constexpr T get() const noexcept
		{
			return m_value;
		}

	protected:
		T m_value{}; //>! stored value.
	};

} // Symplektis::Util