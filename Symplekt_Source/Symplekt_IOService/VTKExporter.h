/*! \file  VTKExporter.h
 *  \brief Object for exporting 3D geometry data to Kitware VTK (*.vtk) files
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   18.10.2021
 *
 */

#pragma once

#include "GeometryIOData.h"
#include "IOHelperTypes.h"

#include <filesystem>

namespace Symplektis::IOService
{
	//!> \brief Header string for VTK polydata file.
	const auto VTK_Polydata_Header_Str =
		std::string("# vtk DataFile Version 4.2\n") +
		"vtk output\n" +
		"ASCII\n" +
		"DATASET POLYDATA\n\n";

	//=============================================================================
	/// \class VTKExporter
	/// \brief An exporter singleton object for exporting geometry data to a *.vtk polydata file.
	///
	/// \ingroup IO_SERVICE
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   18.10.2021
	//=============================================================================
	class VTKExporter
	{
	public:
		/// @{
		/// \name Default special members

		// ------------------------------------------------------------------------------
		/// \brief Default and deleted special member functions of VTKExporter singleton
		/// 
		VTKExporter() = default;
		~VTKExporter() = default;
		VTKExporter(const VTKExporter&) = delete;
		VTKExporter(const VTKExporter&&) = delete;
		VTKExporter& operator=(const VTKExporter&) = delete;
		VTKExporter& operator=(const VTKExporter&&) = delete;
		/// 
		// ------------------------------------------------------------------------------

		/// @{
		/// \name Static Members

		//-----------------------------------------------------------------------------
		/*! \brief Singleton instance getter
		 *  \return VTKExporter instance.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   10.10.2021
		*/
		//-----------------------------------------------------------------------------
		static VTKExporter& GetInstance()
		{
			static VTKExporter instance{};
			return instance;
		}

		/// @{
		/// \name Functionality

		//-----------------------------------------------------------------------------
		/*! \brief Exports a *.vtk polydata file to a given path.
		 *  \param[in] data                      exported GeometryIOData
		 *  \param[in] exportedFileName          *.vtk file name.
		 *  \return Import status
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   18.10.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] ExportStatus Export(const GeometryIOData& data, const std::filesystem::path& exportedFileName) const;
	};

} // Symplektis::IOService