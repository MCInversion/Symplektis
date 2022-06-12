/*! \file  VTIExporter.h
 *  \brief Object for exporting 3D volume geometry data to Kitware VTI (*.vti) files
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   6.10.2021
 *
 */

#pragma once

#include "Symplekt_GeometryReps/ImplicitGeometryDataTypes.h" // TODO: use a local struct instead of GeometryReps::ScalarGridData
#include "IOHelperTypes.h"

#include <filesystem>

namespace Symplektis::IOService
{
	//!> \brief Header string for VTI image data file.
	const std::string VTI_ImageDataHeader{ "<VTKFile type=\"ImageData\" version=\"1.0\" byte_order=\"LittleEndian\" header_type=\"UInt64\">" };
	//!> \brief Scope-close string for VTI image data file.
	const std::string VTI_ImageDataScopeClose{ "				</DataArray>\n			</PointData>\n		<CellData>\n		</CellData>\n	</Piece>\n	</ImageData>\n</VTKFile>" };

	//=============================================================================
	/// \class VTIExporter
	/// \brief An exporter singleton object for exporting scalar grid data to a *.vti image data file.
	///
	/// \ingroup IO_SERVICE
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   23.10.2021
	//=============================================================================
	class VTIExporter
	{
	public:
		/// @{
		/// \name Functionality

		//-----------------------------------------------------------------------------
		/*! \brief Exports a *.vti image data file to a given path.
		 *  \param[in] data                      exported ScalarGridData
		 *  \param[in] exportedFileName          *.vti file name.
		 *  \return Import status
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   24.10.2021
		*/
		//-----------------------------------------------------------------------------
		static [[nodiscard]] ExportStatus Export(const GeometryReps::ScalarGridData& data, const std::filesystem::path& exportedFileName);		
	};

} // Symplektis::IOService