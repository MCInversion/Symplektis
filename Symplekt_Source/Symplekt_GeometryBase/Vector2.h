/*! \file Vector3.h
*   \brief Declaration of the 2D Vector class
*
\verbatim
-------------------------------------------------------------------------------
created  : 6.5.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/
#pragma once

#include "VectorUtils.h"

#pragma warning(disable : C26812_PREFER_ENUM_CLASS_WARNING)

namespace Symplektis::GeometryBase
{
    // forward declarations
    class Vector3;
    class Matrix2;
    class Matrix3;

    //=============================================================================
    /// \class Vector2
    /// \brief A class acting as a 2D vector
    ///
    /// \ingroup GEOMETRY_BASE
    //
    // \author M. Cavarga (MCInversion)
    // \date 6.5.2021
    //=============================================================================
    class Vector2
    {
    public:

        /// @{
        /// \name Constructors
        //-----------------------------------------------------------------------------
        /*!  \brief Default constructor.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   6.5.2021
        *
        *   Create a zero vector.
        */
        //-----------------------------------------------------------------------------
        Vector2() = default;

        //-----------------------------------------------------------------------------
        /*! \brief Copy constructor.
        *   \param[in] vec vector to be copied.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   6.5.2021
        */
        //-----------------------------------------------------------------------------
        Vector2(const Vector2& vec)
        {
            Set(vec);
        }

        //-----------------------------------------------------------------------------
        /*! \brief Constructor.
        *   \param[in] x    X coordinate of vector.
        *   \param[in] y    Y coordinate of vector.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   6.5.2021
        *
        *   Initialize vector from coordinates.
        */
        //-----------------------------------------------------------------------------
        Vector2(const double& x, const double& y)
        {
            Set(x, y);
        }

        /// @{
        /// \name Operators
        //-----------------------------------------------------------------------------
        /*! \brief Comparison of vectors without tolerance.
        *   \param[in] vec Compared vector.
        *   \return True when points are equal, otherwise false.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   6.5.2021
        *
        *   Be careful, this method works without tolerance!
        */
        //-----------------------------------------------------------------------------
        bool operator==(const Vector2& vec) const;

        //-----------------------------------------------------------------------------
        /*! \brief Comparison of vectors with tolerance.
        *   \param[in] vec Compared vector.
        *   \return True when points are equal up to Symplektis::Util::GetCoordinateTolerance(), otherwise false.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   6.5.2021
        */
        //-----------------------------------------------------------------------------
        bool EqualsWithTolerance(const Vector2& vec) const;

        //-----------------------------------------------------------------------------
        /*! \brief Comparison of vectors without tolerance.
        *   \param[in] vec Compared vector.
        *   \return True when points are not equal, otherwise false.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   6.5.2021
        *
        *   Be careful, this method works without tolerance!
        */
        //-----------------------------------------------------------------------------
        bool operator!=(const Vector2& vec) const;

        //-----------------------------------------------------------------------------
        /*! \brief Standard assignment operator.
        *   \param[in] vec Vector(Vb) to be copied.
        *   \return Reference to vector.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   6.5.2021
        *
        *   Formula: Va = Vb \n
        *   Va is this Vector.
        */
        //-----------------------------------------------------------------------------
        Vector2& operator=(const Vector2& vec)
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
        *   \date   6.5.2021
        *
        *   Formula: Va = Va + Vb \n
        *   Va is this Vector.
        */
        //-----------------------------------------------------------------------------
        Vector2& operator+=(const Vector2& vec)
        {
            m_Coords[X_COORD_2D] += vec.m_Coords[X_COORD_2D];
            m_Coords[Y_COORD_2D] += vec.m_Coords[Y_COORD_2D];
            return *this;
        }


        //-----------------------------------------------------------------------------
        /*! \brief Subtraction assignment operator.
        *   \param[in] vec Vb Vector.
        *   \return Reference to vector.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   6.5.2021
        *
        *   Formula: Va = Va - Vb \n
        *   Va is this Vector.
        */
        //-----------------------------------------------------------------------------
        Vector2& operator-=(const Vector2& vec)
        {
            m_Coords[X_COORD_2D] -= vec.m_Coords[X_COORD_2D];
            m_Coords[Y_COORD_2D] -= vec.m_Coords[Y_COORD_2D];
            return *this;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Addition operator.
        *   \param[in] vec Vector(Vb).
        *   \return new Vector(Vc).
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   6.5.2021
        *
        *   Formula: Vc = Va + Vb \n
        *   Va is this Vector.
        */
        //-----------------------------------------------------------------------------
        Vector2 operator+(const Vector2& vec) const;

        //-----------------------------------------------------------------------------
        /*! \brief Subtraction operator.
        *   \param[in] vec Vector(Vb).
        *   \return new Vector(Vc).
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   6.5.2021
        *
        *   Formula: Vc = Va - Vb \n
        *   Va is this Vector
        */
        //-----------------------------------------------------------------------------
        Vector2 operator-(const Vector2& vec) const;

        //-----------------------------------------------------------------------------
		/*! \brief Scalar addition assignment operator.
		*   \param[in] scalar   Scalar to be added to all coordinates
		*   \return Reference to this vector.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   3.6.2021
		*
		*   Formula: Va = Va + (s, s) \n
		*   Va is this Vector.
		*/
		//-----------------------------------------------------------------------------
        Vector2& operator+=(const double& scalar)
        {
            m_Coords[X_COORD_2D] += scalar;
            m_Coords[Y_COORD_2D] += scalar;
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
		*   Formula: Va = Va + (s, s) \n
		*   Va is this Vector.
		*/
		//-----------------------------------------------------------------------------
        Vector2& operator-=(const double& scalar)
        {
            m_Coords[X_COORD_2D] -= scalar;
            m_Coords[Y_COORD_2D] -= scalar;
            return *this;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Cross(vector) product operator.
        *   \param[in] vec Vector(Vb).
        *   \return new Vector3(Vc).
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   6.5.2021
        *
        *   Formula: Vc = Va x Vb \n
        *   Va is this Vector
        */
        //-----------------------------------------------------------------------------
        Vector3 operator*(const Vector2& vec) const;

        //-----------------------------------------------------------------------------
        /// \brief   Multiply the vector by a scalar
        ///
        /// \param[in]  scalar  Scale factor
        ///
        /// \return  New vector
        ///
        /// \author  M. Cavarga (MCInversion)
        /// \date    6.5.2021
        /// 
        //-----------------------------------------------------------------------------
        Vector2 operator*(const double& scalar) const;

        //-----------------------------------------------------------------------------
        /// \brief   Multiply the vector by a scalar
        ///
        /// \param[in]  scalar  Scale factor
        ///
        /// \return  vector reference to this vector
        ///
        /// \author  M. Cavarga (MCInversion)
        /// \date    6.5.2021
        /// 
        //-----------------------------------------------------------------------------
        Vector2& operator*=(const double& scalar);

        //-----------------------------------------------------------------------------
        /// \brief   Divide the vector by a scalar
        ///
        /// \param[in]  scalar  1 / (Scale factor)
        ///
        /// \return  New vector
        ///
        /// \author  M. Cavarga (MCInversion)
        /// \date    6.5.2021
        /// 
        //-----------------------------------------------------------------------------
        Vector2 operator/(const double& scalar) const;

        //-----------------------------------------------------------------------------
        /// \brief   Divide the vector by a scalar
        ///
        /// \param[in]  scalar  1 / (Scale factor)
        ///
        /// \return  vector reference to this vector
        ///
        /// \author  M. Cavarga (MCInversion)
        /// \date    6.5.2021
        /// 
        //-----------------------------------------------------------------------------
        Vector2& operator/=(const double& scalar);

        //-----------------------------------------------------------------------------
        /*! \brief 2D matrix transformation.
        *   \param[in] matrix - 2D transformation matrix.
        *   \return ref to this vector
        *
        *   \author M. Cavarga (MCInversion)
        *   \date 6.5.2021
        *
        *   Formula: Vector(this) = Vector(this) * matrix
        */
        //-----------------------------------------------------------------------------
        Vector2& operator*=(const Matrix2& matrix);

        //-----------------------------------------------------------------------------
        /*! \brief 2D matrix transformation.
        *   \param[in] matrix - 2D transformation matrix.
        *   \return new vector
        *
        *   \author M. Cavarga (MCInversion)
        *   \date 6.5.2021
        *
        *   Formula: Result = Vector(this) * matrix
        */
        //-----------------------------------------------------------------------------
        Vector2 operator*(const Matrix2& matrix) const;

        //-----------------------------------------------------------------------------
        /*! \brief 2D matrix transformation + translation in homogeneous coordinates.
        *   \param[in] 3D transformation matrix.
        *   \return new vector
        *
        *   \author M. Cavarga (MCInversion)
        *   \date 6.5.2021
        *
        *  Formula: Result = Vector(this) * matrix
        */
        //-----------------------------------------------------------------------------
        //Vector2 operator*(const Matrix3& matrix) const;

        /// @}

        /// @{
        /// \name Get/Set Functions
        //-----------------------------------------------------------------------------
        /*! \brief Get the X coordinate constant reference.
        *   \return constant reference to double.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   6.5.2021
        */
        //-----------------------------------------------------------------------------
        const double& X() const
        {
            return m_Coords[X_COORD_2D];
        }

        //-----------------------------------------------------------------------------
        /*! \brief Get the Y coordinate constant reference.
        *   \return constant reference to double.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   6.5.2021
        */
        //-----------------------------------------------------------------------------
        const double& Y() const
        {
            return m_Coords[Y_COORD_2D];
        }

        //-----------------------------------------------------------------------------
        /*! \brief Get the X coordinate reference.
        *   \return reference to double.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   6.5.2021
        */
        //-----------------------------------------------------------------------------
        double& X()
        {
            return m_Coords[X_COORD_2D];
        }

        //-----------------------------------------------------------------------------
        /*! \brief Get the Y coordinate reference.
        *   \return reference to double.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   6.5.2021
        */
        //-----------------------------------------------------------------------------
        double& Y()
        {
            return m_Coords[Y_COORD_2D];
        }

        //-----------------------------------------------------------------------------
        /*!\brief Initialize from Vector3.
        *   \param[in] vec Vector.
        *   \return reference to this vector
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   6.5.2021
        */
        //-----------------------------------------------------------------------------
        Vector2& Set(const Vector3& vec);

        //-----------------------------------------------------------------------------
        /*!\brief Initialize from Vector2.
        *   \param[in] vec Vector.
        *   \return reference to this vector
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   6.5.2021
        */
        //-----------------------------------------------------------------------------
        Vector2& Set(const Vector2& vec)
        {
            return Set(vec.m_Coords[X_COORD_2D], vec.m_Coords[Y_COORD_2D]);
        }

        //-----------------------------------------------------------------------------
        /*! \brief Initialize from x,y coordinates.
        *   \param[in] x coordinate.
        *   \param[in] y coordinate.
        *   \return reference to this vector
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   6.5.2021
        */
        //-----------------------------------------------------------------------------
        Vector2& Set(const double& x, const double& y)
        {
            m_Coords[X_COORD_2D] = x;
            m_Coords[Y_COORD_2D] = y;
            return *this;
        }

        /// @{
        /// \name Member functions

        //-----------------------------------------------------------------------------
        /*! \brief Check the coords [0.0, 0.0]
        *   \return Is zero? true/false
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   6.5.2021
        *
        *   If the coords are zero, the return value is true.
        *   If the coords aren't zero, the return value is false.
        */
        //-----------------------------------------------------------------------------
        bool IsZero() const
        {
            return (m_Coords[X_COORD_2D] == 0.)
                && (m_Coords[Y_COORD_2D] == 0.)
                ? true : false;
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
        *   \date   6.5.2021
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
        *   \date   6.5.2021
        */
        //-----------------------------------------------------------------------------
        double GetLengthSquared() const;

        //-----------------------------------------------------------------------------
        /*! \brief Normalize vector.
        *   \return reference to this vector
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   6.5.2021
        *
        */
        //-----------------------------------------------------------------------------
        Vector2& Normalize();

        //-----------------------------------------------------------------------------
        /*! \brief Dot (scalar) product.
        *   \param[in] vec Vector(Vb).
        *   \return double dot product.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   6.5.2021
        *
        *   Formula: S = Va . Vb = Va1 * Va2 + Vb1 * Vb2 + Va3 * Vb3\n
        *   Va is this Vector
        */
        //-----------------------------------------------------------------------------
        double DotProduct(const Vector2& vec) const
        {
            return m_Coords[X_COORD_2D] * vec.m_Coords[X_COORD_2D]
                 + m_Coords[Y_COORD_2D] * vec.m_Coords[Y_COORD_2D];
        }

        //-----------------------------------------------------------------------------
        /*! \brief Cross(vector) product operator.
        *   \param[in] vec Vector2(Vb).
        *   \return  double value o cross product Z-coord
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   6.5.2021
        *
        *   Formula: Vc.Z() = (Va x Vb).Z() \n
        *   Va is this Vector
        */
        //-----------------------------------------------------------------------------
        double CrossProduct(const Vector2& vec) const;

        //-----------------------------------------------------------------------------
        /*! \brief direct (vector) product.
        *   \param[in] vec Vector2(Vb).
        *   \return Reference to the direct product (this).
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   6.5.2021
        *
        *   Formula: Va = (Va.X() * Vb.X(), Va.Y() * Vb.Y()) \n
        *   Va is this Vector
        */
        //-----------------------------------------------------------------------------
        Vector2& DirectProduct(const Vector2& vec);

        //-----------------------------------------------------------------------------
        /*! \brief direct (vector) product.
        *   \param[in] vec Vector2(Vb).
        *   \return new direct product vector.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   6.5.2021
        *
        *   Formula: Va = (Va.X() * Vb.X(), Va.Y() * Vb.Y()) \n
        *   Va is this Vector
        */
        //-----------------------------------------------------------------------------
        Vector2 DirectProduct(const Vector2& vec) const;

        //-----------------------------------------------------------------------------
        /*! \brief Projection operator.
        *   \param[in] vec Vector(Vb).
        *   \return (new) projected vector
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   1.6.2021
        *
        *   Formula: Vc = <Vb,Va>/<Va,Va> . Va \n
        *   Va is this Vector
        */
        //-----------------------------------------------------------------------------
        Vector2 Project(const Vector2& vec) const;

        //-----------------------------------------------------------------------------
        /*! \brief Compute reversed vector
        *   \return Negated vector
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   6.5.2021
        *
        */
        //-----------------------------------------------------------------------------
        Vector2& Negate()
        {
            m_Coords[X_COORD_2D] = -m_Coords[X_COORD_2D];
            m_Coords[Y_COORD_2D] = -m_Coords[Y_COORD_2D];

            return *this;
        }

        //-----------------------------------------------------------------------------
        /*! \brief 2D rotation operator
        *   \param[in] angle      rotation angle
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   1.6.2021
        *
        *   Formula: Vc = Rot(angle, Z_axis). Va \n
        *   Va is this Vector
        */
        //-----------------------------------------------------------------------------
        Vector2& ApplyAngle(const double& angle);

        //-----------------------------------------------------------------------------
		/*! \brief Resets those of this vector's coordinates which satisfy the condition\n
		*          of the other vector's coordinates being smaller
		*   \param[in] vec     other Vector2
		*   \return    minimized Vector2 (reference to this)
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   3.6.2021
		*/
		//-----------------------------------------------------------------------------
        Vector2& Min(const Vector2& vec);

        //-----------------------------------------------------------------------------
        /*! \brief Resets those of this vector's coordinates which satisfy the condition\n
        *          of the other vector's coordinates being larger
        *   \param[in] vec     other Vector2
        *   \return    maximized Vector2 (reference to this)
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   3.6.2021
        */
        //-----------------------------------------------------------------------------
        Vector2& Max(const Vector2& vec);

        //-----------------------------------------------------------------------------
        /*! \brief Sets this vector to a linear interpolation between this original vector, and vec.\n
        *          The interpolation parameter is not required to be within [0,1]!
        *   \param[in] vec     other Vector2
        *   \param[in] param   interpolation parameter, for convex hull choose param from [0,1]
        *   \return    interpolated Vector2 (reference to this)
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   11.6.2021
        */
        //-----------------------------------------------------------------------------
        Vector2& LinearInterpolate(const Vector2& vec, const double& param);

    private:

        double m_Coords[GEOMETRY_DIMENSION2]{};
    };
} // Symplektis::GeometryBase