/*! \file  ReferencedMeshGeometry.cpp
 *  \brief Implementation of a referenced mesh geometry object.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   7.10.2021
 *
 */

#include "ReferencedMeshGeometry.h"

#include "Symplekt_UtilityGeneral/Assert.h"

namespace Symplektis::GeometryKernel
{
    //
    // ===================================== (Nested) Constructors ======================================
    //

    ReferencedMeshGeometry::ReferencedMeshGeometry()
    {
        m_PImpl = std::make_unique<ReferencedMeshGeometryPImpl>();
    }

    ReferencedMeshGeometry::ReferencedMeshGeometry(const BasePolygonalGeometryData& geometryData)
        : ReferencedMeshGeometry()
    {
        GetPImpl().SetData(geometryData);
    }

    ReferencedMeshGeometry::ReferencedMeshGeometry(const BasePolygonalGeometryData& geometryData, const GeometryKernel::Matrix4& transformationMatrix)
        : ReferencedMeshGeometry(geometryData)
    {
        GetPImpl().SetTransformation(transformationMatrix);
    }

    //
    // ===================================== Functionality ==============================================
    //

    void ReferencedMeshGeometry::BuildGeometry()
    {
        GetBuilder()->BuildGeometry();

    	// take over built data from m_Builder:
        m_MeshData = std::make_unique<ReferencedMeshGeometryData>(std::move(GetBuilder()->Data()));
    }

    //
	// ========================================  Setters  ===============================================
	//

    ReferencedMeshGeometry& ReferencedMeshGeometry::Set(const ReferencedMeshGeometry& other)
    {
        if (other.m_PImpl)
        {
            m_PImpl = std::make_unique<ReferencedMeshGeometryPImpl>(ReferencedMeshGeometryPImpl(*other.m_PImpl));
            if (other.m_MeshData)
            {
                m_MeshData = std::make_unique<ReferencedMeshGeometryData>(*other.m_MeshData);
            }
        }
        return *this;
    }

    //
    // ===================================== Internal getters ===========================================
    //

    ReferencedMeshGeometryBuilder* ReferencedMeshGeometry::GetBuilder()
    {
        if (m_Builder != nullptr)
        {
            return m_Builder.get();
        }
        m_Builder = std::make_unique<ReferencedMeshGeometryBuilder>(GetPImpl().BaseGeometryData);
        return m_Builder.get();
    }

    const ReferencedMeshGeometryBuilder* ReferencedMeshGeometry::GetBuilder() const
    {
        if (m_Builder != nullptr)
        {
            return m_Builder.get();
        }

        return GetBuilder();
    }

    //
    // ===================================== ------------------ ===========================================
    //

    ReferencedMeshGeometryPImpl& ReferencedMeshGeometry::GetPImpl()
    {
        MSG_CHECK(m_PImpl != nullptr, "ReferencedMeshGeometry::GetPImpl: m_PImpl == nullptr");
        return *m_PImpl;
    }

    const ReferencedMeshGeometryPImpl& ReferencedMeshGeometry::GetPImpl() const
    {
        MSG_CHECK(m_PImpl != nullptr, "ReferencedMeshGeometry::GetPImpl: m_PImpl == nullptr");
        return *m_PImpl;
    }

    ReferencedMeshGeometryPImpl::ReferencedMeshGeometryPImpl(const ReferencedMeshGeometryPImpl& other)
    {
        TransformationMatrix = other.TransformationMatrix;
        BaseGeometryData.Vertices = other.BaseGeometryData.Vertices;
        BaseGeometryData.PolyVertexIndices = other.BaseGeometryData.PolyVertexIndices;
    }

} // Symplektis::GeometryKernel