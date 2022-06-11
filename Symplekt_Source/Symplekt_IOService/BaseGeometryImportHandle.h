/*! \file  BaseGeometryImportHandle.h
 *  \brief Conversion utilities from GeometryIOData to BasePolygonalGeometryData
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   17.10.2021
 *
 */

#pragma once

#include "GeometryIOData.h"

#include "../Symplekt_GeometryReps/MeshGeometryDataTypes.h"

namespace Symplektis::IOService
{
	
    //-----------------------------------------------------------------------------
    /*! \brief Builds ReferencedMeshGeometryData from imported GeometryIOData using ReferencedMeshGeometry implementation.
     *  \param[in] importedData          imported GeometryIOData.
     *  \return result ReferencedMeshGeometryData
     *
     *   \author M. Cavarga (MCInversion)
     *   \date   17.10.2021
     *
     */
     //-----------------------------------------------------------------------------
	GeometryReps::ReferencedMeshGeometryData ConvertIODataToReferencedMeshGeometryData(const GeometryIOData& importedData);

    //-----------------------------------------------------------------------------
    /*! \brief Builds BufferMeshGeometryData from imported GeometryIOData using BufferMeshGeometry implementation.
     *  \param[in] importedData          imported GeometryIOData.
     *  \return result BufferMeshGeometryData
     *
     *   \author M. Cavarga (MCInversion)
     *   \date   17.10.2021
     *
     */
     //-----------------------------------------------------------------------------
	GeometryReps::BufferMeshGeometryData ConvertIODataToBufferMeshGeometryData(const GeometryIOData& importedData);

} // Symplektis::IOService