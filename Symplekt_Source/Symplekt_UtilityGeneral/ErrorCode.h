#pragma once

#include "Assert.h"

//=============================================================================
/// \class ErrorCode
/// \brief Smart error value
///
//
/// Smart error value that asserts when error code wasn't checked
//
/// \ingroup DUMMY_GROUP
//
// \author M.Cavarga (MCInversion)
// \date 4.5.2021
//=============================================================================
template<typename _IntType>
struct [[nodiscard]] ErrorCode
{
    using errorType = _IntType;

    constexpr ErrorCode(_IntType returnValue) noexcept
        : m_value(returnValue)
    {
    }

    ~ErrorCode() noexcept
    {
        ASSERT(Checked(), "Error code is not checked");
    }

    //=============================================================================
    /** \brief Set error code to returnValue
     *
     *  \param[in] returnValue The return value of a function as error code
     *  \return
     *
     *  \ingroup DUMMY_GROUP
     *  \author M.Cavarga (MCInversion)
     *  \date 4.5.2021
     */
     //=============================================================================
    ErrorCode& operator=(_IntType returnValue) noexcept
    {
        m_value = returnValue;
        m_checked = false;
        return *this;
    }

    //=============================================================================
    /** \brief Implicit cast to _IntType
    *
    *  \return The return value of a function as error code
    *
    *  \ingroup DUMMY_GROUP
    *  \author M.Cavarga (MCInversion)
    *  \date 4.5.2021
    */
    //=============================================================================
    operator _IntType() noexcept
    {
        m_checked = true;
        return m_value;
    }

    bool operator==(_IntType value) noexcept
    {
        m_checked = true;
        return m_value == value;
    }

    bool operator!=(_IntType value) noexcept
    {
        m_checked = true;
        return m_value != value;
    }

    constexpr bool Checked() const noexcept
    {
        return m_checked;
    }

    ErrorCode(ErrorCode& err)
        : m_value(err.m_value)
        , m_checked(false)
    {
        err.m_checked = true;
    }

    ErrorCode& operator=(ErrorCode& err)
    {
        m_value = err.m_value;
        m_checked = false;
        err.m_checked = true;
        return *this;
    }

private:
    static_assert(std::is_enum<_IntType>::value || std::is_integral<_IntType>::value, "Non allowed template type is used");

    _IntType m_value{};
    bool m_checked{ false };
};