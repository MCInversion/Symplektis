/*! \file  OBJExporter.h
 *  \brief Object for exporting 3D geometry data to Wavefront OBJ (*.obj) files
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   6.10.2021
 *
 */

#pragma once

#include "GeometryIOData.h"
#include "IOHelperTypes.h"

#include <filesystem>

namespace Symplektis::IOService
{
	//=============================================================================
	/// \class OBJExporter
	/// \brief An exporter singleton object for exporting geometry data to a Wavefront *.obj file.
	///
	/// \ingroup IO_SERVICE
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   9.6.2022
	//=============================================================================
	class OBJExporter
	{
	public:
		/// @{
		/// \name Default special members

		// ------------------------------------------------------------------------------
		/// \brief Default and deleted special member functions of OBJExporter singleton
		/// 
		OBJExporter() = default;
		~OBJExporter() = default;
		OBJExporter(const OBJExporter&) = delete;
		OBJExporter(const OBJExporter&&) = delete;
		OBJExporter& operator=(const OBJExporter&) = delete;
		OBJExporter& operator=(const OBJExporter&&) = delete;
		/// 
		// ------------------------------------------------------------------------------

		/// @{
		/// \name Static Members

		//-----------------------------------------------------------------------------
		/*! \brief Singleton instance getter
		 *  \return OBJExporter instance.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.6.2022
		*/
		//-----------------------------------------------------------------------------
		static OBJExporter& GetInstance()
		{
			static OBJExporter instance{};
			return instance;
		}

		/// @{
		/// \name Functionality

		//-----------------------------------------------------------------------------
		/*! \brief Exports a Wavefront *.obj file to a given path.
		 *  \param[in] data                      exported GeometryIOData
		 *  \param[in] exportedFileName          *.obj file name.
		 *  \return Import status
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.6.2022
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] ExportStatus Export(const GeometryIOData& data, const std::filesystem::path& exportedFileName) const;
	};

} // Symplektis::IOService