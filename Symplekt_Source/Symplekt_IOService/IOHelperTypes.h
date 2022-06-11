/*! \file  IOHelperTypes.h
 *  \brief Helper types for Symplektis input/output operations
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   6.10.2021
 *
 */

#pragma once

namespace Symplektis::IOService
{
	//=============================================================================
	/// \enum ImportStatus
	/// \brief Import status for import operations
	///
	/// \ingroup IO_SERVICE
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   6.10.2021
	//=============================================================================
	enum class [[nodiscard]] ImportStatus
	{
		Complete         = 0,      //!< file import is complete without errors.
		FileNotFound     = 1,      //!< file to be imported (given a path) was not found
		FileNotOpened    = 2,      //!< file to be imported (given a path) was not opened
		InvalidExtension = 3,      //!< file to be imported (given a path) has incorrect suffix
		InternalError    = 4,      //!< internal error, outside of external file I/O operations was thrown
	};

	//=============================================================================
	/// \enum ExportStatus
	/// \brief Export status for export operations
	///
	/// \ingroup IO_SERVICE
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   6.10.2021
	//=============================================================================
	enum class [[nodiscard]] ExportStatus
	{
		Complete         = 0,    //!< file import is complete without errors.
		FileNotCreated   = 1,    //!< file to be exported (given a path) was not created
		InternalError    = 2,    //!< internal error, outside of external file I/O operations was thrown
		InvalidExtension = 3,    //!< file to be exported (given a path) has incorrect suffix
	};
	
} // Symplektis::IOService