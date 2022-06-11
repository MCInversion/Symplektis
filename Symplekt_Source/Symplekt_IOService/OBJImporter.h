/*! \file  OBJImporter.h
 *  \brief Object for importing 3D geometry data from Wavefront OBJ (*.obj) files
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
	/// \class OBJImporter
	/// \brief An importer singleton object for importing geometry data from a Wavefront *.obj file and storing it as GeometryIOData.
	///
	/// \ingroup IO_SERVICE
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   2.10.2021
	//=============================================================================
	class OBJImporter
	{
	public:
		/// @{
		/// \name Default special members
		
		// ------------------------------------------------------------------------------
		/// \brief Default and deleted special member functions of OBJImporter singleton
		/// 
		OBJImporter() = default;
		~OBJImporter() = default;
		OBJImporter(const OBJImporter&) = delete;
		OBJImporter(const OBJImporter&&) = delete;
		OBJImporter& operator=(const OBJImporter&) = delete;
		OBJImporter& operator=(const OBJImporter&&) = delete;
		/// 
		// ------------------------------------------------------------------------------

		/// @{
		/// \name Static Members

		//-----------------------------------------------------------------------------
		/*! \brief Singleton instance getter
		 *  \return OBJImporter instance.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   10.10.2021
		*/
		//-----------------------------------------------------------------------------
		static OBJImporter& GetInstance()
		{
			static OBJImporter instance{};
			return instance;
		}

		/// @{
		/// \name Functionality

		//-----------------------------------------------------------------------------
		/*! \brief Imports *.obj file from a given path.
		 *  \param[in] importedFilePath          path to an *.obj file.
		 *  \return Import status
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   10.10.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] ImportStatus Import(const std::filesystem::path& importedFilePath);

		/// @{
		/// \name Getters

		//-----------------------------------------------------------------------------
		/*! \brief Imported data getter
		 *  \return reference to m_Data
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   10.10.2021
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
		*   \date   10.10.2021
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
		*   \date   11.10.2021
		*/
		//-----------------------------------------------------------------------------
		void ClearIOData()
		{
			m_Data.Clear();
		}

	private:

		//-----------------------------------------------------------------------------
		/*! \brief Re-defines vertex normal array if normal indices were found.
		 *  \param[in] collectedNormalIndices       normal indices [n] collected from "p/[t]/[n]" tokens.
		 *  \param[in] nonIndexedVertexNormals      raw normal buffer not indexed yet (may be of different size than vertices buffer).
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   13.10.2021
		*/
		//-----------------------------------------------------------------------------
		void PostProcessVertexNormalsFromIndices(
			const std::vector<std::vector<unsigned int>>&  collectedNormalIndices,
			const std::vector<GeometryBase::Vector3>&      nonIndexedVertexNormals);
		
		GeometryIOData m_Data{}; //!> imported geometry data
	};
	
} // Symplektis::IOService