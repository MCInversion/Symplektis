/*! \file  BaseGeometryImportHandle.cpp
 *  \brief Implementation of conversion utilities from GeometryIOData to BasePolygonalGeometryData
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   17.10.2021
 *
 */

#include "BaseGeometryImportHandle.h"

#include "../Symplekt_GeometryReps/BufferMeshGeometry.h"
#include "../Symplekt_GeometryReps/ReferencedMeshGeometry.h"

namespace Symplektis::IOService
{
	using namespace GeometryReps;

	//-----------------------------------------------------------------------------
	/*! \brief Copies buffers from imported GeometryIOData to BasePolygonalGeometryData object used for geometry construction.
	 *  \param[in] importedData          imported GeometryIOData.
	 *  \return result BasePolygonalGeometryData
	 *
	 *   \author M. Cavarga (MCInversion)
	 *   \date   17.10.2021
	 *
	 */
	 //-----------------------------------------------------------------------------
	static BasePolygonalGeometryData ConvertIODataToBasePolygonalGeometryData(const GeometryIOData& importedData)
	{
		return BasePolygonalGeometryData{
			importedData.Name,
			importedData.Vertices,
			importedData.VertexIndices,
			importedData.VertexNormals
		};
	}

	//
	// =============================================================
	//
	
	ReferencedMeshGeometryData ConvertIODataToReferencedMeshGeometryData(const GeometryIOData& importedData)
	{
		const auto baseGeometryData = ConvertIODataToBasePolygonalGeometryData(importedData);

		ReferencedMeshGeometry refGeom{ baseGeometryData };
		refGeom.BuildGeometry();
		
		return refGeom.GetMeshData();
	}
	
	BufferMeshGeometryData ConvertIODataToBufferMeshGeometryData(const GeometryIOData& importedData)
	{
		const auto baseGeometryData = ConvertIODataToBasePolygonalGeometryData(importedData);

		BufferMeshGeometry buffGeom{ baseGeometryData };
		buffGeom.BuildGeometry();

		return buffGeom.GetMeshData();
	}
} // Symplektis::IOService