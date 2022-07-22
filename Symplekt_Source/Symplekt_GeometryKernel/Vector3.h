/*! \file Vector3.h
*   \brief Declaration of the 3D Vector class
*
\verbatim
-------------------------------------------------------------------------------
created  : 5.5.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/
#pragma once

#include "VectorUtils.h"

#pragma warning(disable : C26812_PREFER_ENUM_CLASS_WARNING)

namespace Symplektis::GeometryKernel
{
    // forward declarations
    class Vector2;
    class Matrix3;
    class Matrix4;
    class Quaternion;

	//=============================================================================
	/// \class Vector3
	/// \brief A class acting as a 3D vector
	///
	/// \ingroup GEOMETRY_BASE
	//
	// \author M. Cavarga (MCInversion)
	// \date 5.5.2021
	//=============================================================================
	class Vector3
	{
	public:

        /// @{
        /// \name Constructors

        //-----------------------------------------------------------------------------
        /*!  \brief Default constructor.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        *
        *   Create zero vector.
        */
        //-----------------------------------------------------------------------------
        Vector3() = default;

        //-----------------------------------------------------------------------------
        /*! \brief Copy constructor.
        *   \param[in] vec 2D vector to be copied to the 3D vector.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        *
        *   Copy only X_COORD_3D and Y_COORD_3D from vector, Z_COORD_3D is set to zero.
        */
        //-----------------------------------------------------------------------------
        explicit Vector3(const Vector2& vec);

        //-----------------------------------------------------------------------------
        /*! \brief Copy constructor.
        *   \param[in] vec vector to be copied.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        */
        //-----------------------------------------------------------------------------
        Vector3(const Vector3& vec)
        {
            Set(vec);
        }

        //-----------------------------------------------------------------------------
        /*! \brief Constructor.
        *   \param[in] x    X coordinate of vector.
        *   \param[in] y    Y coordinate of vector.
        *   \param[in] z    Z coordinate of vector.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        *
        *   Initialize vector from coordinates.
        */
        //-----------------------------------------------------------------------------
        Vector3(const double& x, const double& y, const double& z)
        {
            Set(x, y, z);
        }

        /// @{
        /// \name Operators

        //-----------------------------------------------------------------------------
        /*! \brief Comparison of vectors without tolerance.
        *   \param[in] vec Compared vector.
        *   \return True when points are equal, otherwise false.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        *
        *   Be careful, this method works without tolerance!
        */
        //-----------------------------------------------------------------------------
        bool operator==(const Vector3& vec) const;

        //-----------------------------------------------------------------------------
        /*! \brief Comparison of vectors with tolerance.
        *   \param[in] vec Compared vector.
        *   \return True when points are equal up to Symplektis::Util::GetCoordinateTolerance(), otherwise false.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        */
        //-----------------------------------------------------------------------------
        bool EqualsWithTolerance(const Vector3& vec) const;

        //-----------------------------------------------------------------------------
        /*! \brief Comparison of vectors without tolerance.
        *   \param[in] vec Compared vector.
        *   \return True when points are not equal, otherwise false.
        * 
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        *
        *   Be careful, this method works without tolerance!
        */
        //-----------------------------------------------------------------------------
        bool operator!=(const Vector3& vec) const;

        //-----------------------------------------------------------------------------
        /*! \brief Standard assignment operator.
        *   \param[in] vec Vector(Vb) to be copied.
        *   \return Reference to vector.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        *
        *   Formula: Va = Vb \n
        *   Va is this Vector.
        */
        //-----------------------------------------------------------------------------
        Vector3& operator=(const Vector3& vec)
        {
            if (this == &vec)
                return *this;

            Set(vec);
            return *this;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Addition assignment operator.
        *   \param[in] vec Vb Vector.
        *   \return Reference to vector.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        *
        *   Formula: Va = Va + Vb \n
        *   Va is this Vector.
        */
        //-----------------------------------------------------------------------------
        Vector3& operator+=(const Vector3& vec)
        {
            m_Coords[X_COORD_3D] += vec.m_Coords[X_COORD_3D];
            m_Coords[Y_COORD_3D] += vec.m_Coords[Y_COORD_3D];
            m_Coords[Z_COORD_3D] += vec.m_Coords[Z_COORD_3D];
            return *this;
        }


        //-----------------------------------------------------------------------------
        /*! \brief Subtraction assignment operator.
        *   \param[in] vec Vb Vector.
        *   \return Reference to vector.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        *
        *   Formula: Va = Va - Vb \n
        *   Va is this Vector.
        */
        //-----------------------------------------------------------------------------
        Vector3& operator-=(const Vector3& vec)
        {
            m_Coords[X_COORD_3D] -= vec.m_Coords[X_COORD_3D];
            m_Coords[Y_COORD_3D] -= vec.m_Coords[Y_COORD_3D];
            m_Coords[Z_COORD_3D] -= vec.m_Coords[Z_COORD_3D];
            return *this;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Scalar addition assignment operator.
        *   \param[in] scalar   Scalar to be added to all coordinates
        *   \return Reference to this vector.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   3.6.2021
        *
        *   Formula: Va = Va + (s, s, s) \n
        *   Va is this Vector.
        */
        //-----------------------------------------------------------------------------
        Vector3& operator+=(const double& scalar)
        {
            m_Coords[X_COORD_3D] += scalar;
            m_Coords[Y_COORD_3D] += scalar;
            m_Coords[Z_COORD_3D] += scalar;
            return *this;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Scalar subtraction assignment operator.
        *   \param[in] scalar   Scalar to be subtracted from all coordinates
        *   \return Reference to this vector.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   3.6.2021
        *
        *   Formula: Va = Va - (s, s, s) \n
        *   Va is this Vector.
        */
        //-----------------------------------------------------------------------------
        Vector3& operator-=(const double& scalar)
        {
            m_Coords[X_COORD_3D] -= scalar;
            m_Coords[Y_COORD_3D] -= scalar;
            m_Coords[Z_COORD_3D] -= scalar;
            return *this;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Addition operator.
        *   \param[in] vec Vector(Vb).
        *   \return new Vector(Vc).
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        *
        *   Formula: Vc = Va + Vb \n
        *   Va is this Vector.
        */
        //-----------------------------------------------------------------------------
        Vector3 operator+(const Vector3& vec) const;

        //-----------------------------------------------------------------------------
        /*! \brief Subtraction operator.
        *   \param[in] vec Vector(Vb).
        *   \return new Vector(Vc).
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        *
        *   Formula: Vc = Va - Vb \n
        *   Va is this Vector
        */
        //-----------------------------------------------------------------------------
        Vector3 operator-(const Vector3& vec) const;

        //-----------------------------------------------------------------------------
        /*! \brief Cross(vector) product operator.
        *   \param[in] vec Vector(Vb).
        *   \return Reference to the cross(vector) product of vectors.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        *
        *   Formula: Va = Va x Vb \n
        *   Va is this Vector
        */
        //-----------------------------------------------------------------------------
        Vector3& operator*=(const Vector3& vec);

        //-----------------------------------------------------------------------------
        /*! \brief Cross(vector) product operator.
        *   \param[in] vec Vector2(Vb).
        *   \return Reference to the cross(vector) product (this).
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        *
        *   Formula: Va = Va x Vb \n
        *   Va is this Vector
        */
        //-----------------------------------------------------------------------------
        Vector3& operator*=(const Vector2& vec);

        //-----------------------------------------------------------------------------
        /*! \brief Cross(vector) product operator.
        *   \param[in] vec Vector(Vb).
        *   \return new Vector(Vc).
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        *
        *   Formula: Vc = Va x Vb \n
        *   Va is this Vector
        */
        //-----------------------------------------------------------------------------
        Vector3 operator*(const Vector3& vec) const;

        //-----------------------------------------------------------------------------
        /// \brief   Multiply the vector by a scalar
        ///
        /// \param[in]  scalar  Scale factor
        ///
        /// \return  New vector
        ///
        /// \author  M. Cavarga (MCInversion)
        /// \date    5.5.2021
        /// 
        //-----------------------------------------------------------------------------
        Vector3 operator*(const double& scalar) const;

        //-----------------------------------------------------------------------------
        /// \brief   Multiply the vector by a scalar
        ///
        /// \param[in]  scalar  Scale factor
        ///
        /// \return  vector reference to this vector
        ///
        /// \author  M. Cavarga (MCInversion)
        /// \date    5.5.2021
        /// 
        //-----------------------------------------------------------------------------
        Vector3& operator*=(const double& scalar);

        //-----------------------------------------------------------------------------
        /// \brief   Divide the vector by a scalar
        ///
        /// \param[in]  scalar  1 / (Scale factor)
        ///
        /// \return  New vector
        ///
        /// \author  M. Cavarga (MCInversion)
        /// \date    5.5.2021
        /// 
        //-----------------------------------------------------------------------------
        Vector3 operator/(const double& scalar) const;

        //-----------------------------------------------------------------------------
        /// \brief   Divide the vector by a scalar
        ///
        /// \param[in]  scalar  1 / (Scale factor)
        ///
        /// \return  vector reference to this vector
        ///
        /// \author  M. Cavarga (MCInversion)
        /// \date    5.5.2021
        /// 
        //-----------------------------------------------------------------------------
        Vector3& operator/=(const double& scalar);

        //-----------------------------------------------------------------------------
        /*! \brief 2D matrix transformation.
        *   \param[in] matrix - 3D transformation matrix.
        *   \return ref to this vector
        *
        *   \author M. Cavarga (MCInversion)
        *   \date 6.5.2021
        *
        *   Formula: Vector(this) = Vector(this) * matrix
        */
        //-----------------------------------------------------------------------------
        Vector3& operator*=(const Matrix3& matrix);

        //-----------------------------------------------------------------------------
        /*! \brief 3D matrix transformation + translation in homogeneous coordinates.
        *   \param[in] 4D transformation matrix.
        *   \return reference to this vector
        *
        *   \author M. Cavarga (MCInversion)
        *   \date 6.5.2021
        *
        *  Formula: Vector(this) = Vector(this) * matrix
        */
        //-----------------------------------------------------------------------------
        Vector3& operator*=(const Matrix4& matrix);

        //-----------------------------------------------------------------------------
		/*! \brief Quaternion rotation multiplication assigmnent operator
		*   \param[in] quat - quaternion
		*   \return ref to this vector
		*
		*   \author M. Cavarga (MCInversion)
		*   \date 19.6.2021
		*
		*   Formula: Vector(this) = Vector(this) * quat
		*/
		//-----------------------------------------------------------------------------
        Vector3& operator*=(const Quaternion& quat)
        {
            return ApplyQuaternion(quat);
        }

        /// @}

        /// @{
        /// \name Get/Set Functions
        //-----------------------------------------------------------------------------
        /*! \brief Get the X coordinate constant reference.
        *   \return constant reference to double.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        */
        //-----------------------------------------------------------------------------
        const double& X() const
        {
            return m_Coords[X_COORD_3D];
        }

        //-----------------------------------------------------------------------------
        /*! \brief Get the Y coordinate constant reference.
        *   \return constant reference to double.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        */
        //-----------------------------------------------------------------------------
        const double& Y() const
        {
            return m_Coords[Y_COORD_3D];
        }

        //-----------------------------------------------------------------------------
        /*! \brief Get the Z coordinate constant reference.
        *   \return constant reference to double.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        */
        //-----------------------------------------------------------------------------
        const double& Z() const
        {
            return m_Coords[Z_COORD_3D];
        }

        //-----------------------------------------------------------------------------
        /*! \brief Get the X coordinate reference.
        *   \return reference to double.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        */
        //-----------------------------------------------------------------------------
        double& X()
        {
            return m_Coords[X_COORD_3D];
        }

        //-----------------------------------------------------------------------------
        /*! \brief Get the Y coordinate reference.
        *   \return reference to double.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        */
        //-----------------------------------------------------------------------------
        double& Y()
        {
            return m_Coords[Y_COORD_3D];
        }

        //-----------------------------------------------------------------------------
        /*! \brief Get the Z coordinate reference.
        *   \return reference to double.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        */
        //-----------------------------------------------------------------------------
        double& Z()
        {
            return m_Coords[Z_COORD_3D];
        }

        //-----------------------------------------------------------------------------
        /*! \brief Get a coordinate reference by eCoord3D_ID.
        *   \param[in] index      eCoord3D_ID index to extract from m_Coords
        *   \return reference to double.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   10.6.2021
        */
        //-----------------------------------------------------------------------------
        double& GetCoordById(const eCoord3D_ID& index)
        {
            return m_Coords[index];
        }

        //-----------------------------------------------------------------------------
        /*!\brief Initialize from vector 3D.
        *   \param[in] vec Vector.
        *   \return reference to this vector
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        */
        //-----------------------------------------------------------------------------
        Vector3& Set(const Vector3& vec)
        {
            return Set(vec.m_Coords[X_COORD_3D], vec.m_Coords[Y_COORD_3D], vec.m_Coords[Z_COORD_3D]);
        }

        //-----------------------------------------------------------------------------
        /*! \brief Initialize from x,y,z coordinates.
        *   \param[in] x coordinate.
        *   \param[in] y coordinate.
        *   \param[in] z coordinate.
        *   \return reference to this vector
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        */
        //-----------------------------------------------------------------------------
        Vector3& Set(const double& x, const double& y, const double& z)
        {
            m_Coords[X_COORD_3D] = x;
            m_Coords[Y_COORD_3D] = y;
            m_Coords[Z_COORD_3D] = z;
            return *this;
        }

        /// @{
        /// \name Member functions

        //-----------------------------------------------------------------------------
        /*! \brief Check the coords [0.0, 0.0, 0.0]
        *   \return Is zero? true/false
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        *
        *   Careful! This method does not return true if at least one coordinate is not a true double zero
        */
        //-----------------------------------------------------------------------------
        bool IsZero() const
        {
            return (((m_Coords[X_COORD_3D] == 0.)
                  && (m_Coords[Y_COORD_3D] == 0.)
                  && (m_Coords[Z_COORD_3D] == 0.))
                  ? true : false);
        }

        //-----------------------------------------------------------------------------
        /*! \brief Check if the length is exactly 1.0
        *   \return Is normalized? true/false
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   7.5.2021
        *
        */
        //-----------------------------------------------------------------------------
        bool IsNormalized() const;

        //-----------------------------------------------------------------------------
        /*! \brief Check if the length is 1.0 with Symplektis::Util::GetProductTolerance()
        *   \return Is normalized? true/false
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   7.5.2021
        *
        */
        //-----------------------------------------------------------------------------
        bool IsNormalizedWithTolerance() const;

        //-----------------------------------------------------------------------------
        /*! \brief  Get vector length.
        *   \return double length.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        *
        *   Formula: Result(double) = ||Va||
        *   Va is this vector
        */
        //-----------------------------------------------------------------------------
        double GetLength() const;

        //-----------------------------------------------------------------------------
        /*! \brief Get vector length without computationally expensive sqrt operation.
        *   \return double length squared.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        */
        //-----------------------------------------------------------------------------
        double GetLengthSquared() const;

        //-----------------------------------------------------------------------------
        /*! \brief Get inverse vector length via accelerated Symplektis::Util::FastInverseSqrt function
        *   \return double 1 / length.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   3.6.2021
        */
        //-----------------------------------------------------------------------------
        double GetInvLength() const;

        //-----------------------------------------------------------------------------
        /*! \brief Normalize vector.
        *   \return reference to this vector
        * 
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        */
        //-----------------------------------------------------------------------------
        Vector3& Normalize();

        //-----------------------------------------------------------------------------
        /*! \brief FastNormalize vector. WARNING: This method uses Symplektis::Util::FastInverseSqrt method whose   \n
        *          results hold up to product tolerance. WARNING: This method does not check whether this vector is \n
        *          zero. This vector needs to be non-zero in length prior to calling this method!
        *   \return reference to this vector
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        */
        //-----------------------------------------------------------------------------
        Vector3& FastNormalize();

        //-----------------------------------------------------------------------------
        /*! \brief Dot (scalar) product.
        *   \param[in] vec Vector(Vb).
        *   \return double.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        *
        *   Formula: S = Va . Vb = Va1 * Va2 + Vb1 * Vb2 + Va3 * Vb3\n
        *   Va is this Vector
        */
        //-----------------------------------------------------------------------------
        double DotProduct(const Vector3& vec) const
        {
            return m_Coords[X_COORD_3D] * vec.m_Coords[X_COORD_3D]
                 + m_Coords[Y_COORD_3D] * vec.m_Coords[Y_COORD_3D]
                 + m_Coords[Z_COORD_3D] * vec.m_Coords[Z_COORD_3D];
        }

        //-----------------------------------------------------------------------------
        /*! \brief Cross(vector) product operator.
        *   \param[in] vec Vector(Vb).
        *   \return reference to this vector
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        *
        *   Formula: Va = Va x Vb \n
        *   Va is this Vector
        */
        //-----------------------------------------------------------------------------
        Vector3& CrossProduct(const Vector3& vec);

        //-----------------------------------------------------------------------------
        /*! \brief direct (vector) product.
        *   \param[in] vec Vector3(Vb).
        *   \return Reference to the direct product (this).
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   6.5.2021
        *
        *   Formula: Va = (Va.X() * Vb.X(), Va.Y() * Vb.Y(), Va.Z() * Vb.Z()) \n
        *   Va is this Vector
        */
        //-----------------------------------------------------------------------------
        Vector3& DirectProduct(const Vector3& vec);

        //-----------------------------------------------------------------------------
        /*! \brief Projection operator.
        *   \param[in] vec Vector(Vb).
        *   \return (new) projected vector
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        *
        *   Formula: Vc = <Vb,Va>/<Va,Va> . Va \n
        *   Va is this Vector
        */
        //-----------------------------------------------------------------------------
        Vector3 Project(const Vector3& vec) const;

        //-----------------------------------------------------------------------------
        /*! \brief Compute reversed vector
        *   \return Negated vector (reference to this)
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        *
        */
        //-----------------------------------------------------------------------------
        Vector3& Negate()
        {
            m_Coords[X_COORD_3D] = -m_Coords[X_COORD_3D];
            m_Coords[Y_COORD_3D] = -m_Coords[Y_COORD_3D];
            m_Coords[Z_COORD_3D] = -m_Coords[Z_COORD_3D];

            return *this;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Apply axis angle - rotation about axis (unit) vector with angle
        *   \param[in] axis          vector - must be normalized!.
        *   \param[in] angle         rotation angle
        *   \return reference to this vector
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   5.5.2021
        *
        *   Formula: Vc = Rot(angle, axis). Va \n
        *   Va is this Vector
        */
        //-----------------------------------------------------------------------------
        Vector3& ApplyAxisAngle(const Vector3& axis, const double& angle);

        //-----------------------------------------------------------------------------
        /*! \brief Apply quaternion rotation
        *   \param[in] quaternion
        *   \return    Rotated Vector3 (reference to this)
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   1.6.2021
        *
        */
        //-----------------------------------------------------------------------------
        Vector3& ApplyQuaternion(const Quaternion& quaternion);

        //-----------------------------------------------------------------------------
        /*! \brief Resets those of this vector's coordinates which satisfy the condition\n
        *          of the other vector's coordinates being smaller
        *   \param[in] vec     other Vector3
        *   \return    minimized Vector3 (reference to this)
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   3.6.2021
        */
        //-----------------------------------------------------------------------------
        Vector3& Min(const Vector3& vec);

        //-----------------------------------------------------------------------------
        /*! \brief Resets those of this vector's coordinates which satisfy the condition\n
        *          of the other vector's coordinates being larger
        *   \param[in] vec     other Vector3
        *   \return    maximized Vector3 (reference to this)
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   3.6.2021
        */
        //-----------------------------------------------------------------------------
        Vector3& Max(const Vector3& vec);

        //-----------------------------------------------------------------------------
        /*! \brief Sets coordinate value by eCoordID index
        *   \param[in] value         value to be set
        *   \param[in] index         index eCoordID: X_COORD_3D, Y_COORD_3D, Z_COORD_3D
        *   \return pair (geometry error code (eError if axis is not normalized), reference to this vector)
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   3.6.2021
        */
        //-----------------------------------------------------------------------------
        void SetCoordById(const double& value, const eCoord3D_ID& index)
        {
            m_Coords[index] = value;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Sets this vector to a linear interpolation between this original vector, and vec.\n
        *          The interpolation parameter is not required to be within [0,1]!
        *   \param[in] vec     other Vector3
        *   \param[in] param   interpolation parameter, for convex hull choose param from [0,1]
        *   \return    interpolated Vector3 (reference to this)
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   11.6.2021
        */
        //-----------------------------------------------------------------------------
        Vector3& LinearInterpolate(const Vector3& vec, const double& param);

	private:

		double m_Coords[GEOMETRY_DIMENSION3]{};
	};

} // Symplektis::GeometryKernel

