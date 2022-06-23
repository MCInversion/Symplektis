/*! \file Exceptions.h
*   \brief Exception types for Symplektis.
*
*   \author M. Cavarga (MCInversion)
*   \date 20.6.2022
*/

#pragma once

#include <stdexcept>

namespace Symplektis
{
	///=============================================================================
	/// \class InvalidInputException
	/// \brief Extension of std::invalid_argument. \n
	///        Meant to be thrown when at least one of the inputs is invalid.
	///
	/// \ingroup UTILITY_GENERAL
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   20.6.2022
	///
	/// Inspired by PMP (Polygon Mesh Processing) library Exceptions.h/InvalidInputException
	/// Copyright 2011-2021 the Polygon Mesh Processing Library developers.
	/// Copyright 2001-2005 by Computer Graphics Group, RWTH Aachen
	/// 
	///=============================================================================
	class InvalidInputException final : public std::invalid_argument
	{
	public:
		/// \brief Construct from a given message.
		explicit InvalidInputException(const std::string& what) :
			std::invalid_argument(what)	{ }
	};

	///=============================================================================
	/// \class IncompatibleInputException
	/// \brief Extension of std::invalid_argument. \n
	///        Meant to be thrown when all inputs are valid, \n
	///        but at least one of the inputs is incompatible with some other inputs.
	///
	/// \ingroup UTILITY_GENERAL
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   20.6.2022
	///
	/// Inspired by PMP (Polygon Mesh Processing) library Exceptions.h/InvalidInputException
	/// Copyright 2011-2021 the Polygon Mesh Processing Library developers.
	/// Copyright 2001-2005 by Computer Graphics Group, RWTH Aachen
	/// 
	///=============================================================================
	class IncompatibleInputException final : public std::invalid_argument
	{
	public:
		/// \brief Construct from a given message.
		explicit IncompatibleInputException(const std::string& what) :
			std::invalid_argument(what) { }
	};

	///=============================================================================
	/// \class InvalidHandleException
	/// \brief Extension of std::logic_error. \n
	///        Meant to be thrown when a Symplektis handle object is invalid\n
	///        and cannot be used to access an element potentially handled by this handle.
	///
	/// \ingroup UTILITY_GENERAL
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   20.6.2022
	/// 
	///=============================================================================
	class InvalidHandleException final : public std::logic_error
	{
	public:
		/// \brief Construct from a given message.
		explicit InvalidHandleException(const std::string& what) :
			std::logic_error(what) { }
	};
	
} // namespace Util
