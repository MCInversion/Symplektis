/*! \file  Assert.h
*  \brief Assertion utils: AssertUtil & Macros declaration
*
\verbatim
-------------------------------------------------------------------------------
created  : 11.6.2021 : M. Cavarga (MCInversion)    :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/

#pragma once

#include <iosfwd>
#include <sstream>
#include <iostream>

//---------------------------------------------------------------------------
/*!
 *   \brief Assert macro with a message
 *
 *  This macro is defined in Assert.h.
 */
//---------------------------------------------------------------------------
#ifndef NDEBUG
#   define ASSERT(condition, message)                                            \
    do {                                                                         \
        if (! (condition)) {                                                     \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__     \
                      << " line " << __LINE__ << ": " << (message) << std::endl; \
            std::terminate();                                                    \
        }                                                                        \
    } while (false)
#else
#   define ASSERT(condition, message) do { } while (false)
#endif


namespace Symplektis::Util
{
	//-----------------------------------------------------------------------------
	///  \class AssertUtil
	///  \brief Custom assertion facility
	///  \ingroup UTILITY_GENERAL
	///
	///  \author M.Cavarga (MCInversion)
	///  \date 11.6.2009
	///
	//-----------------------------------------------------------------------------
	class AssertUtil
	{
	public:
		//-----------------------------------------------------------------------------
		/// \brief Main routine for handling assertion
		/// 
		/// \param[in]  expr  Expression as a string
		/// \param[in]  file  Name of file the assertion is located in
		/// \param[in]  line  Line number the assertion is located on
		/// \param[out] ignoreLine  Flag for ignoring this assert next time
		/// 
		/// \return False if execution is to be broken into the debugger, true otherwise
		///
		//-----------------------------------------------------------------------------
		virtual bool Handle(const char* expr, const char* file, const char* line, bool& ignoreLine) const;

		//-----------------------------------------------------------------------------
		///   \brief Tests if the assertion failed
		///   
		///   \return True if assertion failed, false if assertion holds
		///
		//-----------------------------------------------------------------------------
		[[nodiscard]] virtual bool Failed() const
		{
			return !m_Holds;
		}

		//-----------------------------------------------------------------------------
		/// \brief Logs that an assert occurred
		/// 
		/// \param[in]  expr  Expression as a string
		/// \param[in]  file  Name of file the assertion is located in
		/// \param[in]  line  Line number the assertion is located on
		///
		//-----------------------------------------------------------------------------
		virtual void Log(const char* expr, const char* file, const char* line) const;

		//-----------------------------------------------------------------------------
		/// \brief Set/Append string to the assert message
		/// 
		/// \tparam MsgType Type of data to be converted and stored as string
		/// \param[in]  msg  Message to be set/appended. Must be convertible to string
		/// 
		/// \return Reference to the AssertUtil instance
		///
		//-----------------------------------------------------------------------------
		template<class MsgType>
		AssertUtil& Msg(const MsgType& msg)
		{
			if (Failed())
			{
				// Here we have time; no need to be super-efficient //
				std::stringstream woss;
				woss << std::string(msg);
				m_Msg += woss.str();
			}
			return *this;
		}

		//-----------------------------------------------------------------------------
		/// \brief Returns assert message
		///
		/// \return Assert message
		///
		//-----------------------------------------------------------------------------
		[[nodiscard]] const char* Msg() const
		{
			return m_Msg.c_str();
		}

		//-----------------------------------------------------------------------------
		/// \brief Factory for AssertUtil
		/// 
		/// \param[in]  cond  Condition
		/// 
		/// \return     AssertUtil instance
		/// 
		/// \ingroup UTILITY_GENERAL
		///
		//-----------------------------------------------------------------------------
		static AssertUtil Create(bool cond)
		{
			return AssertUtil(cond);
		}

		//-----------------------------------------------------------------------------
		/// \brief Enables/disables assertions globally
		/// 
		/// \param[in]  enable  True if assertions are to be enabled, false if disabled
		/// 
		/// \ingroup UTILITY_GENERAL
		///
		//-----------------------------------------------------------------------------
		static void Enable(bool enable);

		//-----------------------------------------------------------------------------
		/// \brief Tests if assertions are globally enabled or disabled
		///
		/// \return  True if assertions are enabled, false if disabled
		///  
		/// \ingroup UTILITY_GENERAL
		///
		//-----------------------------------------------------------------------------
		static bool IsEnabled();

	private:
		//-----------------------------------------------------------------------------
		/// \brief Constructor
		/// 
		/// \param[in]  cond  Condition
		/// 
		/// \param[in]  msg   Message
		///
		//-----------------------------------------------------------------------------
		explicit AssertUtil(bool cond, const char* msg = "")
			: m_Msg(msg)
			, m_Holds(cond)
		{
		}

		//-----------------------------------------------------------------------------
		/// \brief  Enumeration for an action chosen by user                         
		enum class Action
		{
			  eGiveUp
			, eIgnore
			, eIgnoreLine
			, eIgnoreAll
			, eDebug
		};

		/// \brief Informs user of an assertion and asks what to do
		/// 
		/// \param[in]  expr  Expression as a string
		/// \param[in]  file  Name of file the assertion is located in
		/// \param[in]  line  Line number the assertion is located on
		///
		/// \return     Action to be performed
		///
		//-----------------------------------------------------------------------------
		Action AskUser(const char* expr, const char* file, const char* line) const;

		//-----------------------------------------------------------------------------
		/// \brief Perform given action
		///
		/// \param[in]  action  Action the user has chosen
		/// \param[out] ignoreLine  Flag for ignoring this assert next time
		///   
		/// \return     False if execution should break into the debugger, true otherwise
		///
		//-----------------------------------------------------------------------------
		bool DoHandle(Action action, bool& ignoreLine) const;

		//-----------------------------------------------------------------------------
		/// \brief Builds formatted string from function parameters
		///
		/// \param[in]  expr  Expression as a string
		/// \param[in]  file  Name of file the assertion is located in
		/// \param[in]  line  Line number the assertion is located on
		/// \param[in]  gui   Flag meaning whether a message for the Assert Message box is requested
		///
		/// \return     Formatted assertion location string
		///
		//-----------------------------------------------------------------------------
		std::string GetFormattedMsg(const char* expr, const char* file, const char* line, bool gui = true) const;

	public:
		static bool m_IgnoreAll;

	private:
		std::string m_Msg;
		bool        m_Holds;
	};

} // Symplektis::Util

///-----------------------------------------------------------------------------
/// \brief Diagnostic macro for assertion checking also in release.
///   \param[in]  expression  Specifies an expression (including pointer values) that evaluates to true or false.
///	  \param[in]  msg         message
///   \ingroup UTILITY_GENERAL
///
///   \b Usage:
///   \code
///       MSG_CHECK(p != NULL, "p is NULL and it surely shouldn't be!");
///   \endcode
///
///   Behavior of the MSG_CHECK macro:
///   In \b debug, the expression is evaluated, and if the result is false, the macro fires an assert. \n
///   In \b release, the expression is evaluated, and if the result is false, the macro just logs the occurrence of assert.
///
///-----------------------------------------------------------------------------
#define MSG_CHECK(expression, msg)		\
	VERIFY_CHECK(expression).Msg(msg)	\
	/**/

//-----------------------------------------------------------------------------
/// \brief Diagnostic macro for assertion checking also in release.
///   \param[in]  expression  Specifies an expression (including pointer values) that evaluates to true or false.
///   \ingroup UTILITY_GENERAL
///
///   \b Usage:
///   \code
///       VERIFY_CHECK(p != NULL);
///       // or, supplying an additional message...
///       VERIFY_CHECK(p != NULL).Msg(L"p is NULL and it surely shouldn't!");
///   \endcode
///
///   Behavior of the VERIFY_CHECK macro:
///   In \b debug, the expression is evaluated, and if the result is false, the macro fires an assert. \n
///   In \b release, the expression is evaluated, and if the result is false, the macro just logs the occurrence of assert.
///
//-----------------------------------------------------------------------------
#define VERIFY_CHECK(expression)  \
    VERIFY_CHECK_IMPL(expression) \
    /**/


// Helper macros for stringization
#define STRINGIZE(something) STRINGIZE_HELPER(something)
#define STRINGIZE_HELPER(something) #something

#ifndef DEBUG
#define VERIFY_CHECK_IMPL(expression)                                                                       \
    if (bool __asrt_result = (expression))                                                                  \
        ;                                                                                                   \
    else                                                                                                    \
        struct Local                                                                                        \
        {                                                                                                   \
            Local(const Symplektis::Util::AssertUtil& asrt)                                                 \
            {                                                                                               \
                static bool _ignore_asrt_check = false;                                                     \
                if (!asrt.Failed())                                                                         \
                    return;                                                                                 \
                asrt.Log(STRINGIZE(expression), __FILE__, STRINGIZE(__LINE__));                             \
                if (!_ignore_asrt_check &&                                                                  \
                    !asrt.Handle(STRINGIZE(expression), __FILE__, STRINGIZE(__LINE__), _ignore_asrt_check)) \
                    __debugbreak();                                                                         \
            }                                                                                               \
        } localAssertUtil = Symplektis::Util::AssertUtil::Create(__asrt_result)                             \
    /**/
#else
#define VERIFY_CHECK_IMPL(expression)                                             \
    if (bool __asrt_result = (expression))                                        \
        ;                                                                         \
    else                                                                          \
        struct Local                                                              \
        {                                                                         \
            Local(const Symplektis::Util::AssertUtil& asrt)                       \
            {                                                                     \
                if (!asrt.Failed())                                               \
                    return;                                                       \
                asrt.Log(STRINGIZE(expression), __FILE__, STRINGIZE(__LINE__));   \
            }                                                                     \
        } localAssertUtil = Symplektis::Util::AssertUtil::Create(__asrt_result)   \
    /**/

#endif