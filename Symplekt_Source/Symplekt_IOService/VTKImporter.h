/*! \file  VTKImporter.h
 *  \brief Object for importing 3D geometry polydata from Kitware VTK (*.vtk) files
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
	/// \class VTKImporter
	/// \brief An importer singleton object for importing geometry data from a VTK Polydata (*.vtk) file and storing it as GeometryIOData.
	///
	/// \ingroup IO_SERVICE
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   10.6.2022
	//=============================================================================
	class VTKImporter
	{
	public:
		/// @{
		/// \name Default special members

		// ------------------------------------------------------------------------------
		/// \brief Default and deleted special member functions of VTKImporter singleton
		/// 
		VTKImporter() = default;
		~VTKImporter() = default;
		VTKImporter(const VTKImporter&) = delete;
		VTKImporter(const VTKImporter&&) = delete;
		VTKImporter& operator=(const VTKImporter&) = delete;
		VTKImporter& operator=(const VTKImporter&&) = delete;
		/// 
		// ------------------------------------------------------------------------------

		/// @{
		/// \name Static Members

		//-----------------------------------------------------------------------------
		/*! \brief Singleton instance getter
		 *  \return VTKImporter instance.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   10.6.2022
		*/
		//-----------------------------------------------------------------------------
		static VTKImporter& GetInstance()
		{
			static VTKImporter instance{};
			return instance;
		}

		/// @{
		/// \name Functionality

		//-----------------------------------------------------------------------------
		/*! \brief Imports *.vtk file from a given path.
		 *  \param[in] importedFilePath          path to an *.obj file.
		 *  \return Import status
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   10.6.2022
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] ImportStatus Import(const std::filesystem::path & importedFilePath);

		/// @{
		/// \name Getters

		//-----------------------------------------------------------------------------
		/*! \brief Imported data getter
		 *  \return reference to m_Data
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   10.6.2022
		*/
		//-----------------------------------------------------------------------------
		GeometryIOData& Data()
		{
			return m_Data;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Const imported data getter
		 *  \return const reference to m_Data
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   10.6.2022
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] const GeometryIOData& Data() const
		{
			return m_Data;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Simple data clear
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   10.6.2022
		*/
		//-----------------------------------------------------------------------------
		void ClearIOData()
		{
			m_Data.Clear();
		}

	private:

		GeometryIOData m_Data{}; //!> imported geometry data
	};

} // Symplektis::IOService