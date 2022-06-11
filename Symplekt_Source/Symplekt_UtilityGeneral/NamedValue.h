/*! \file NamedValue.h
*   \brief Named value type template
*
\verbatim
-------------------------------------------------------------------------------
created  : 31.5.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/
#pragma once

namespace Symplektis::Util
{
	///////////////////////////////////////////////////////////
	/// \class NamedValue
	/// \brief Strong type template for value types
	///
	///////////////////////////////////////////////////////////
	template<typename T, typename PhantomType>
	class NamedValue
	{
	public:
		constexpr NamedValue() = default;

		constexpr explicit NamedValue(T value) noexcept
			: m_value(value)
		{
		}

		constexpr explicit operator T() const noexcept
		{
			return m_value;
		}

		constexpr bool operator==(const NamedValue<T, PhantomType>& otherValue) const noexcept
		{
			return m_value == otherValue.m_value;
		}

		constexpr bool operator!=(const NamedValue<T, PhantomType>& otherValue) const noexcept
		{
			return m_value != otherValue.m_value;
		}

		constexpr bool operator<(const NamedValue<T, PhantomType>& otherValue) const noexcept
		{
			return m_value < otherValue.m_value;
		}

		constexpr bool operator>(const NamedValue<T, PhantomType>& otherValue) const noexcept
		{
			return m_value > otherValue.m_value;
		}

		constexpr bool operator<=(const NamedValue<T, PhantomType>& otherValue) const noexcept
		{
			return m_value <= otherValue.m_value;
		}

		constexpr bool operator>=(const NamedValue<T, PhantomType>& otherValue) const noexcept
		{
			return m_value >= otherValue.m_value;
		}

		constexpr T get() const noexcept
		{
			return m_value;
		}

	protected:
		T m_value{};
	};

} // Symplektis::Util