/*! \file  BufferMeshGeometry.cpp
 *  \brief Implementation of a referenced mesh geometry object.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   7.10.2021
 *
 */

#include "BufferMeshGeometry.h"

#include "Symplekt_UtilityGeneral/Assert.h"

namespace Symplektis::GeometryReps
{
    //
    // ===================================== (Nested) Constructors ======================================
    //
	
    BufferMeshGeometry::BufferMeshGeometry()
    {
        m_PImpl = std::make_unique<BufferMeshGeometryPImpl>();
    }

    BufferMeshGeometry::BufferMeshGeometry(const BasePolygonalGeometryData& geometryData)
        : BufferMeshGeometry()
    {
        GetPImpl().SetData(geometryData);
    }

    BufferMeshGeometry::BufferMeshGeometry(const BasePolygonalGeometryData& geometryData, const GeometryBase::Matrix4& transformationMatrix)
	    : BufferMeshGeometry(geometryData)
    {
        GetPImpl().SetTransformation(transformationMatrix);
    }

    //
    // ===================================== Functionality ==============================================
    //

    void BufferMeshGeometry::BuildGeometry()
    {
        GetBuilder()->BuildGeometry();

        // take over built data from m_Builder:
        m_MeshData = std::make_unique<BufferMeshGeometryData>(std::move(GetBuilder()->Data()));
    }

    //
    // ========================================  Setters  ===============================================
    //

    BufferMeshGeometry& BufferMeshGeometry::Set(const BufferMeshGeometry& other)
    {
        if (other.m_PImpl)
        {
            m_PImpl = std::make_unique<BufferMeshGeometryPImpl>(BufferMeshGeometryPImpl(*other.m_PImpl));
            if (other.m_MeshData)
            {
                m_MeshData = std::make_unique<BufferMeshGeometryData>(*other.m_MeshData);
            }
        }
        return *this;
    }
	
    //
    // ===================================== Internal getters ===========================================
    //

    BufferMeshGeometryBuilder* BufferMeshGeometry::GetBuilder()
    {
        if (m_Builder != nullptr)
        {
            return m_Builder.get();
        }
        m_Builder = std::make_unique<BufferMeshGeometryBuilder>(GetPImpl().BaseGeometryData);
        return m_Builder.get();
    }

    const BufferMeshGeometryBuilder* BufferMeshGeometry::GetBuilder() const
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

    BufferMeshGeometryPImpl& BufferMeshGeometry::GetPImpl()
    {
        MSG_CHECK(m_PImpl != nullptr, "BufferMeshGeometry::GetPImpl: m_PImpl == nullptr");
        return *m_PImpl;
    }

    const BufferMeshGeometryPImpl& BufferMeshGeometry::GetPImpl() const
    {
        MSG_CHECK(m_PImpl != nullptr, "BufferMeshGeometry::GetPImpl: m_PImpl == nullptr");
        return *m_PImpl;
    }

	
} // Symplektis::GeometryReps