/*! \file  MeshGeometryDataTypes.h
 *  \brief A gallery of data container types (mostly structs) for mesh geometry data.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   7.10.2021
 *
 */

#pragma once


#include "Symplekt_GeometryBase/HalfEdge.h"
#include "Symplekt_GeometryBase/Vertex.h"
#include "Symplekt_GeometryBase/VertexNormal.h"
#include "Symplekt_GeometryBase/Edge.h"
#include "Symplekt_GeometryBase/Face.h"
#include "Symplekt_GeometryBase/Vector3.h"

#include <string>
#include <vector>

namespace Symplektis::GeometryReps
{
    //=============================================================================
    /// \struct BasePolygonalGeometryData
    /// \brief A base data container for polygonal geometry data containing only vertices, polygon vertex indices, and vertex normals .
    ///
    /// \ingroup GEOMETRY_REPS
    ///
    /// \author M. Cavarga (MCInversion)
    /// \date   7.10.2021
    //=============================================================================
	struct BasePolygonalGeometryData
	{
		std::wstring                             Name;
		std::vector<GeometryBase::Vector3>       Vertices{};
		std::vector<std::vector<unsigned int>>   PolyVertexIndices{};
		std::vector<GeometryBase::Vector3>       VertexNormals{};

		/// \brief Returns the byte size of this geometry container.
		[[nodiscard]] size_t Size() const
		{
			size_t polySize = 0;
			for (const auto& poly : PolyVertexIndices)
				polySize += poly.size();
			
			return
				Vertices.size() * sizeof(GeometryBase::Vector3) +
				polySize * sizeof(unsigned int) +
				VertexNormals.size() * sizeof(GeometryBase::Vector3);
		}
	};

	//=============================================================================
	/// \struct BufferMeshGeometryData
	/// \brief A data container for geometry data containing raw vertex and vertex normal coordinates, vertex indices, and triangulation indices.
	///
	/// \ingroup GEOMETRY_REPS
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   30.9.2021
	//=============================================================================
	struct BufferMeshGeometryData
	{
		std::wstring                           Name;
		std::vector<double>                    VertexCoords{};
		std::vector<double>                    VertexNormalCoords{};
		std::vector<unsigned int>              VertexIndices{};
		std::vector<std::vector<unsigned int>> TriangulationIndices{};

		/// \brief Returns the byte size of this geometry container.
		[[nodiscard]] size_t Size() const
		{
			return
				VertexCoords.size() * sizeof(double) +
				VertexNormalCoords.size() * sizeof(double) +
				VertexIndices.size() * sizeof(unsigned int) +
				TriangulationIndices.size() * sizeof(unsigned int);
		}

		/// \brief Construct data with a name
		explicit BufferMeshGeometryData(std::wstring name)
			: Name(name)
		{ }
	};

	//=============================================================================
	/// \struct ReferencedMeshGeometryData
	/// \brief A data container for referenced geometry data. Requires special copy & copy-assignment\n
	///        implementations for iterator members of buffer items (mesh elements, e.g.: HalfEdge) \n
	///        pointing to previous instance items (e.g. copied HalfEdge->NextHalfEdge() still points\n
	///        to previous ReferencedMeshGeometryData.HalfEdges item).
	///
	/// \ingroup GEOMETRY_REPS
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   14.9.2021
	//=============================================================================
	struct ReferencedMeshGeometryData
	{
		std::wstring Name;
		
		//
		// =============== Data containers ========================================================
		//
		
		std::vector<GeometryBase::HalfEdge>         HalfEdges{};
		std::vector<GeometryBase::Vertex>            Vertices{};
		std::vector<GeometryBase::Edge>                 Edges{};
		std::vector<GeometryBase::Face>                 Faces{};
		std::vector<GeometryBase::Face>        BoundaryCycles{};
		std::vector<GeometryBase::VertexNormal> VertexNormals{};

		/// \brief Returns the byte size of this geometry container.
		[[nodiscard]] size_t Size() const
		{
			return
				HalfEdges.size() * sizeof(GeometryBase::HalfEdge) +
				Vertices.size() * sizeof(GeometryBase::Vertex) +
				Edges.size() * sizeof(GeometryBase::Edge) +
				(Faces.size() + BoundaryCycles.size()) * sizeof(GeometryBase::Face) +
				VertexNormals.size() * sizeof(GeometryBase::VertexNormal);
		}
	};

} // Symplektis::GeometryReps