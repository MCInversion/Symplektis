/*! \file  BufferMeshGeometry.h
 *  \brief Instance of a buffer mesh geometry object.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   7.10.2021
 *
 */

#pragma once

#include "Symplekt_GeometryBase/Matrix4.h"

#include "BufferGeometryBuilder.h"

#include <memory>

namespace Symplektis::GeometryReps
{
    //=============================================================================
    /// \class BufferMeshGeometryPImpl
    /// \brief PImpl class for BufferMeshGeometry (internal implementation).\n
    ///        see: https://en.cppreference.com/w/cpp/language/pimpl for "PImpl idiom".
    ///
    /// \ingroup GEOMETRY_REPS
    ///
    /// \author M. Cavarga (MCInversion)
    /// \date   7.10.2021
    //=============================================================================
    class BufferMeshGeometryPImpl
    {
    public:
    	/// \brief default constructor
        BufferMeshGeometryPImpl() = default;

        /// \brief set base geometry data
        void SetData(const BasePolygonalGeometryData& data)
        {
            BaseGeometryData = data;
        };

        /// \brief set transformation matrix
        void SetTransformation(const GeometryBase::Matrix4& matrix)
        {
            TransformationMatrix = matrix;
        };

        BasePolygonalGeometryData  BaseGeometryData;
        GeometryBase::Matrix4      TransformationMatrix;
    };
	
    //=============================================================================
    /// \class BufferMeshGeometry
    /// \brief Mesh geometry instance with base data stored in an internal implementation \n
    ///        producing result data composed of vertices, vertex indices, triangulation\n
    ///        indices, and vertex normals.
    ///
    /// \ingroup GEOMETRY_REPS
    ///
    /// \author M. Cavarga (MCInversion)
    /// \date   7.10.2021
    //=============================================================================
    class BufferMeshGeometry
    {
    public:
        /// @{
        /// \name Default special members

        /// \brief destructor
        ~BufferMeshGeometry() = default;

        /// \brief move constructor
        BufferMeshGeometry(BufferMeshGeometry&& other) = default;

        /// \brief move-assign operator
        BufferMeshGeometry& operator=(BufferMeshGeometry&& other) = default;
    	
        /// @{
        /// \name Constructors

        //-----------------------------------------------------------------------------
        /*! \brief Default constructor. Creates an empty instance of m_PImpl.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   7.10.2021
        */
        //-----------------------------------------------------------------------------
        BufferMeshGeometry();

        //-----------------------------------------------------------------------------
        /*! \brief Constructor. Writes geometryData to m_PImpl.
         *  \param[in] geometryData         BasePolygonalGeometryData
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   7.10.2021
        */
        //-----------------------------------------------------------------------------
        explicit BufferMeshGeometry(const BasePolygonalGeometryData& geometryData);

        //-----------------------------------------------------------------------------
        /*! \brief Constructor. Writes geometryData and transformationMatrix to m_PImpl.
         *  \param[in] geometryData             BasePolygonalGeometryData
         *  \param[in] transformationMatrix     geometry transformation 4x4 matrix
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   7.10.2021
        */
        //-----------------------------------------------------------------------------
        BufferMeshGeometry(const BasePolygonalGeometryData& geometryData, const GeometryBase::Matrix4& transformationMatrix);

        //-----------------------------------------------------------------------------
        /*! \brief Copy constructor
         *  \param[in] other     Other BufferMeshGeometry instance
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   7.10.2021
        */
        //-----------------------------------------------------------------------------
        BufferMeshGeometry(const BufferMeshGeometry& other)
        {
            Set(other);
        }

        /// @{
        /// \name Operators

        //-----------------------------------------------------------------------------
        /*! \brief Copy-assignment operator
         *  \param[in] other        Other buffer mesh geometry instance.
         *  \return reference to this BufferMeshGeometry instance
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   10.10.2021
        */
        //-----------------------------------------------------------------------------
        BufferMeshGeometry& operator=(const BufferMeshGeometry& other)
        {
            if (this == &other)
                return *this;

            Set(other);
            return *this;
        }

        /// @{
        /// \name Setters

        //-----------------------------------------------------------------------------
        /*! \brief Setter form another instance of BufferMeshGeometry
         *  \param[in] other        Other buffer mesh geometry instance.
         *  \return reference to this BufferMeshGeometry instance
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   10.10.2021
        */
        //-----------------------------------------------------------------------------
        BufferMeshGeometry& Set(const BufferMeshGeometry& other);
    	
        /// @{
        /// \name Functionality

        //-----------------------------------------------------------------------------
        /*! \brief Invokes an instance of m_Builder and builds m_MeshData
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   7.10.2021
        */
        //-----------------------------------------------------------------------------
        void BuildGeometry();

        /// @{
        /// \name Getters

        //-----------------------------------------------------------------------------
        /*! \brief Const mesh geometry data getter
         *  \return const reference to buffer mesh geometry data
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   7.10.2021
         *
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] const BufferMeshGeometryData& GetMeshData() const
        {
            return *m_MeshData;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Mesh geometry data getter
         *  \return buffer mesh geometry data
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   7.10.2021
         *
         */
         //-----------------------------------------------------------------------------
        BufferMeshGeometryData& GetMeshData()
        {
            return *m_MeshData;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Const transformation matrix getter
         *  \return const reference to geometry's transformation matrix
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   7.10.2021
         *
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] const GeometryBase::Matrix4& GetTransformationMatrix() const
        {
            return GetPImpl().TransformationMatrix;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Transformation matrix getter
         *  \return geometry's transformation matrix
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   7.10.2021
         *
         */
         //-----------------------------------------------------------------------------
        GeometryBase::Matrix4& GetTransformationMatrix()
        {
            return GetPImpl().TransformationMatrix;
        }

    private:

        //
        // =============== Internal getters ==================================================
        //

        //-----------------------------------------------------------------------------
        /*! \brief Gets an instance of BufferMeshGeometryPImpl
         *  \return reference to a BufferMeshGeometryPImpl
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   7.10.2021
         *
         */
         //-----------------------------------------------------------------------------
        BufferMeshGeometryPImpl& GetPImpl();

        //-----------------------------------------------------------------------------
        /*! \brief Gets a const instance of BufferMeshGeometryPImpl
         *  \return const reference to a BufferMeshGeometryPImpl
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   7.10.2021
         *
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] const BufferMeshGeometryPImpl&  GetPImpl() const;

        //-----------------------------------------------------------------------------
        /*! \brief Gets an instance of BufferMeshGeometryBuilder
         *  \return pointer to a BufferMeshGeometryBuilder
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   7.10.2021
         *
         */
         //-----------------------------------------------------------------------------
        BufferMeshGeometryBuilder* GetBuilder();

        //-----------------------------------------------------------------------------
        /*! \brief Gets a const instance of BufferMeshGeometryBuilder
         *  \return const pointer to a BufferMeshGeometryBuilder
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   7.10.2021
         *
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] const BufferMeshGeometryBuilder* GetBuilder() const;

        //
        // =============== Data ========================================================
        //

        std::unique_ptr<BufferMeshGeometryPImpl>       m_PImpl;    //!> internal implementation
        std::unique_ptr<BufferMeshGeometryData>        m_MeshData; //!> Mesh geometry data container
        std::unique_ptr<BufferMeshGeometryBuilder>     m_Builder;  //!> Geometry data builder
    };

} // Symplektis::GeometryReps