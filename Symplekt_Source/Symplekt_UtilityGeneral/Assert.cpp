/*! \file  Assert.cpp
*  \brief Assertion utils: AssertUtil class implementation
*
\verbatim
-------------------------------------------------------------------------------
created  : 11.6.2021 : M. Cavarga (MCInversion)    :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/

#include "Assert.h"

#include <windows.h>
#include <processenv.h>
#include <string>

namespace Symplektis::Util
{
	// TODO: Extend to generic asserts for Unix

	namespace
	{
		//------------------------------------------------------------------------------
		/// \brief Displays Assertion message box
		///
		/// \param [in] text        message to be displayed
		/// \param [in] caption     dialog box title
		/// \param [in] type        determine the contents and behavior of the dialog box
		///
		/// \return         If the function fails, the return value is zero, otherwise returns value as API function MessageBox
		///
		//------------------------------------------------------------------------------
		int AssertMessageBox(const char* text, const char* caption, unsigned int type)
		{
			HWND hWndParent = ::GetActiveWindow();
			if (hWndParent != nullptr)
			{
				hWndParent = GetLastActivePopup(hWndParent);
			}
			return MessageBoxA(hWndParent, text, caption, type);
		}
		
		#define _LOG_OUT std::cout

		const std::string& PrepareCmdLine()
		{
			static std::string cmdLine(GetCommandLineA());
			return cmdLine;
		}
		
	} // namespace

	bool AssertUtil::m_IgnoreAll = false;

	bool AssertUtil::Handle(const char* expr, const char* file, const char* line, bool& ignoreLine) const
	{
		if (m_Holds || !IsEnabled())
			return true;
		return DoHandle(AskUser(expr, file, line), ignoreLine);
	}

	void AssertUtil::Log(const char* expr, const char* file, const char* line) const
	{
		static bool firstAssert = true;

		if (m_Holds)
			return;

		if (firstAssert)
		{
			_LOG_OUT << "Program running: " << PrepareCmdLine().c_str() << "\n" << "\n";
			firstAssert = false;
		}

		const std::string message = GetFormattedMsg(expr, file, line, false);

		_LOG_OUT << "Assertion failed!\n" << message.c_str() << "\n" << "\n";
	}

	AssertUtil::Action AssertUtil::AskUser(const char* expr, const char* file, const char* line) const
	{
		const std::string message = GetFormattedMsg(expr, file, line, true);

		switch (AssertMessageBox(message.c_str(), "Assertion failed!", MB_ICONERROR | MB_ABORTRETRYIGNORE | MB_SETFOREGROUND | MB_TASKMODAL))
		{
		case IDABORT:
			return Action::eGiveUp;
		case IDRETRY:
			return Action::eDebug;
		case IDIGNORE:
			if (GetKeyState(VK_SHIFT) & 0x8000)
			{
				if (GetKeyState(VK_CONTROL) & 0x8000)
					return Action::eIgnoreAll;
				
				return Action::eIgnoreLine;
			}

			return Action::eIgnore;
		}
		return Action::eDebug;
	}

	bool AssertUtil::DoHandle(Action action, bool& ignoreLine) const
	{
		switch (action)
		{
		case Action::eGiveUp:
			abort();
		case Action::eIgnoreLine:
			ignoreLine = true;
			break;
		case Action::eIgnoreAll:
			Enable(false);
			break;
		case Action::eIgnore:
			break;
		default:
			return false;
		}
		return true;
	}

	std::string AssertUtil::GetFormattedMsg(const char* expr, const char* file, const char* line, bool gui /*= true*/) const
	{
		std::string formattedMsg;

		bool isExpression = std::string(expr) != "false";
		bool isMessage = !m_Msg.empty();
		if (isExpression || isMessage)
		{
			if (isExpression)
				formattedMsg += "Expression: " + std::string(expr) + "\n";
			if (isMessage)
				formattedMsg += "Message: " + std::string(m_Msg) + "\n";
			if (gui)
				formattedMsg += "\n";
		}

		/* formattedMsg += boost::str(boost::wformat(L"ThreadID: %d\nFile: %s\nLine: %s\n")
			% GetCurrentThreadId()
			% file
			% line); */
		formattedMsg += "ThreadID: " + std::to_string(static_cast<int>(GetCurrentThreadId())) + "\n";
		formattedMsg += "File: " + std::string(file) + "\n";
		formattedMsg += "Line: " + std::string(line) + "\n";

		if (gui)
		{
			formattedMsg += "\nPress Abort to terminate the application. ";
			formattedMsg += "Press Retry to debug. ";
			formattedMsg += "Press Ignore to ignore this assert.\n";
			formattedMsg += "Press [Shift] + Ignore to ignore all occurrences of this assert. ";
			formattedMsg += "Press [Shift] + [Ctrl] + Ignore to ignore all asserts.";
		}
		else
		{
			formattedMsg += std::string(file);
			formattedMsg += "(" + std::string(line) + "): ";
			formattedMsg += std::string(expr) + " (" + std::string(m_Msg) + ") \n";
		}

		return formattedMsg;
	}

	bool AssertUtil::IsEnabled()
	{
		return !m_IgnoreAll;
	}

	void AssertUtil::Enable(bool enable)
	{
		// Log this action //
		if (m_IgnoreAll == enable)
			_LOG_OUT << "\nAssertions turned " << (enable ? "on " : "off ") << "globally" << "\n";
		m_IgnoreAll = !enable;
	}

} // Symplektis::Util
