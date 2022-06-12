/*! \file  GeometryIOData.h
 *  \brief Geometry data for import/export.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   6.10.2021
 *
 */

#pragma once


#include "Symplekt_GeometryBase/Vector3.h"

#include <string>
#include <vector>

namespace Symplektis::IOService
{
	//=============================================================================
	/// \struct GeometryIOData
	/// \brief A data container for imported/exported geometry data
	///
	/// \ingroup IO_SERVICE
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   6.10.2021
	//=============================================================================
	struct GeometryIOData
	{
		std::wstring                              Name;
		std::vector<GeometryBase::Vector3>        Vertices;
		std::vector<std::vector<unsigned int>>    VertexIndices;
		std::vector<GeometryBase::Vector3>        VertexNormals;
		
		// TODO: textures etc

		//-----------------------------------------------------------------------------
		/*! \brief Simple data clear
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   11.10.2021
		*/
		//-----------------------------------------------------------------------------
		void Clear()
		{
			Name.clear();
			Vertices.clear();
			VertexIndices.clear();
			VertexNormals.clear();
		}
	};

} // Symplektis::IOService