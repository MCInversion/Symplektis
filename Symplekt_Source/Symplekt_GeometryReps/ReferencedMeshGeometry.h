/*! \file  ReferencedMeshGeometry.h
 *  \brief Instance of a referenced mesh geometry object.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   7.10.2021
 *
 */

#pragma once

#include "../Symplekt_GeometryBase/Matrix4.h"

#include "ReferencedGeometryBuilder.h"

#include <memory>

namespace Symplektis::GeometryReps
{
    //=============================================================================
    /// \class ReferencedMeshGeometryPImpl
    /// \brief PImpl class for ReferencedMeshGeometry (internal implementation).\n
    ///        see: https://en.cppreference.com/w/cpp/language/pimpl for "PImpl idiom".
    ///
    /// \ingroup GEOMETRY_REPS
    ///
    /// \author M. Cavarga (MCInversion)
    /// \date   7.10.2021
    //=============================================================================
    class ReferencedMeshGeometryPImpl
    {
    public:
        /// \brief default constructor
        ReferencedMeshGeometryPImpl() = default;

        /// \brief destructor
        ~ReferencedMeshGeometryPImpl() = default;

        /// \brief copy constructor
        ReferencedMeshGeometryPImpl(const ReferencedMeshGeometryPImpl& other);

        /// \brief move constructor
        ReferencedMeshGeometryPImpl(ReferencedMeshGeometryPImpl&& other) noexcept = default;

        /// \brief copy-assign operator
        ReferencedMeshGeometryPImpl& operator=(const ReferencedMeshGeometryPImpl& other) = default;

        /// \brief move-assign operator
        ReferencedMeshGeometryPImpl& operator=(ReferencedMeshGeometryPImpl&& other) = default;

        /// \brief set base geometry data
        void SetData(const BasePolygonalGeometryData& data)
        {
            BaseGeometryData = data;
        }

        /// \brief set transformation matrix
        void SetTransformation(const GeometryBase::Matrix4& matrix)
        {
            TransformationMatrix = matrix;
        }

        BasePolygonalGeometryData  BaseGeometryData;
        GeometryBase::Matrix4      TransformationMatrix;
    };

    //=============================================================================
    /// \class ReferencedMeshGeometry
    /// \brief Mesh geometry instance with base data stored in an internal implementation \n
    ///        producing result data composed of vertices, vertex indices, triangulation\n
    ///        indices, and vertex normals.
    ///
    /// \ingroup GEOMETRY_REPS
    ///
    /// \author M. Cavarga (MCInversion)
    /// \date   7.10.2021
    //=============================================================================
    class ReferencedMeshGeometry
    {
    public:
        /// @{
        /// \name Default special members

    	/// \brief destructor
        ~ReferencedMeshGeometry() = default;

    	/// \brief move constructor
        ReferencedMeshGeometry(ReferencedMeshGeometry&& other) = default;

    	/// \brief move-assign operator
        ReferencedMeshGeometry& operator=(ReferencedMeshGeometry&& other) = default;
    	
        /// @{
        /// \name Constructors

        //-----------------------------------------------------------------------------
        /*! \brief Default constructor. Creates an empty instance of m_PImpl.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   7.10.2021
        */
        //-----------------------------------------------------------------------------
        ReferencedMeshGeometry();

        //-----------------------------------------------------------------------------
        /*! \brief Constructor. Writes geometryData to m_PImpl.
         *  \param[in] geometryData         BasePolygonalGeometryData
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   7.10.2021
        */
        //-----------------------------------------------------------------------------
        explicit ReferencedMeshGeometry(const BasePolygonalGeometryData& geometryData);

        //-----------------------------------------------------------------------------
        /*! \brief Constructor. Writes geometryData and transformationMatrix to m_PImpl.
         *  \param[in] geometryData             BasePolygonalGeometryData
         *  \param[in] transformationMatrix     geometry transformation 4x4 matrix
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   7.10.2021
        */
        //-----------------------------------------------------------------------------
        ReferencedMeshGeometry(const BasePolygonalGeometryData& geometryData, const GeometryBase::Matrix4& transformationMatrix);

        //-----------------------------------------------------------------------------
        /*! \brief Copy constructor
         *  \param[in] other        Other referenced mesh geometry instance.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   8.10.2021
        */
        //-----------------------------------------------------------------------------
        ReferencedMeshGeometry(const ReferencedMeshGeometry& other)
        {
            Set(other);
        }

        /// @{
        /// \name Operators

        //-----------------------------------------------------------------------------
        /*! \brief Copy-assignment operator
         *  \param[in] other        Other referenced mesh geometry instance.
         *  \return reference to this ReferencedMeshGeometry instance
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   10.10.2021
        */
        //-----------------------------------------------------------------------------
        ReferencedMeshGeometry& operator=(const ReferencedMeshGeometry& other)
        {
            if (this == &other)
                return *this;

            Set(other);
            return *this;
        }

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
		/// \name Setters

        //-----------------------------------------------------------------------------
        /*! \brief Setter form another instance of ReferencedMeshGeometry
         *  \param[in] other        Other referenced mesh geometry instance.
         *  \return reference to this ReferencedMeshGeometry instance
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   10.10.2021
        */
        //-----------------------------------------------------------------------------
        ReferencedMeshGeometry& Set(const ReferencedMeshGeometry& other);
    	
        /// @{
        /// \name Getters

        //-----------------------------------------------------------------------------
        /*! \brief Const mesh geometry data getter
         *  \return const reference to referenced mesh geometry data
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   7.10.2021
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] const ReferencedMeshGeometryData& GetMeshData() const
        {
            return *m_MeshData;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Mesh geometry data getter
         *  \return referenced mesh geometry data
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   7.10.2021
         */
         //-----------------------------------------------------------------------------
        ReferencedMeshGeometryData& GetMeshData()
        {
            return *m_MeshData;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Const transformation matrix getter
         *  \return const reference to geometry's transformation matrix
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   7.10.2021
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
        /*! \brief Gets an instance of ReferencedMeshGeometryPImpl
         *  \return reference to a ReferencedMeshGeometryPImpl
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   7.10.2021
         */
         //-----------------------------------------------------------------------------
        ReferencedMeshGeometryPImpl& GetPImpl();

        //-----------------------------------------------------------------------------
        /*! \brief Gets a const instance of ReferencedMeshGeometryPImpl
         *  \return const reference to a ReferencedMeshGeometryPImpl
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   7.10.2021
         *
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] const ReferencedMeshGeometryPImpl& GetPImpl() const;

        //-----------------------------------------------------------------------------
        /*! \brief Gets an instance of ReferencedMeshGeometryBuilder
         *  \return pointer to a ReferencedMeshGeometryBuilder
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   7.10.2021
         */
         //-----------------------------------------------------------------------------
        ReferencedMeshGeometryBuilder* GetBuilder();

        //-----------------------------------------------------------------------------
        /*! \brief Gets a const instance of ReferencedMeshGeometryBuilder
         *  \return const pointer to a ReferencedMeshGeometryBuilder
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   7.10.2021
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] const ReferencedMeshGeometryBuilder* GetBuilder() const;

        //
        // =============== Data ========================================================
        //

        std::unique_ptr<ReferencedMeshGeometryPImpl>       m_PImpl;    //!> internal implementation
        std::unique_ptr<ReferencedMeshGeometryData>        m_MeshData; //!> Mesh geometry data container
        std::unique_ptr<ReferencedMeshGeometryBuilder>     m_Builder;  //!> Geometry data builder
    };

} // Symplektis::GeometryReps