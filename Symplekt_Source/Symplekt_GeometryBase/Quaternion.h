/*! \file Quaternion.h
*   \brief Declaration of the Quaternion class
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

namespace Symplektis::GeometryBase
{
	// forward declarations
	class Vector3;
	class Matrix3;

	class Quaternion
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
		*   Create zero quaternion.
		*/
		//-----------------------------------------------------------------------------
        Quaternion() = default;

		//-----------------------------------------------------------------------------
		/*! \brief Copy constructor.
		*   \param[in] quat  quaternion to be copied.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   6.5.2021
		*/
		//-----------------------------------------------------------------------------
		Quaternion(const Quaternion& quat)
		{
			Set(quat);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Constructor.
		*   \param[in] x    X coordinate of vector.
		*   \param[in] y    Y coordinate of vector.
		*   \param[in] z    Z coordinate of vector.
		* 	\param[in] w    W coordinate of vector.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   6.5.2021
		*
		*   Initialize quaternion from coordinates.
		*/
		//-----------------------------------------------------------------------------
		Quaternion(const double& x, const double& y, const double& z, const double& w)
		{
			Set(x, y, z, w);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Constructor.
		*   \param[in] axis    Rotation axis (must be normalized)
		*   \param[in] angle   Rotation angle
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   1.6.2021
		*
		*   Initialize quaternion from axis and angle.
		*/
		//-----------------------------------------------------------------------------
		explicit Quaternion(const Vector3& axis, const double& angle)
		{
			SetFromAxisAngle(axis, angle);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Constructor.
		*   \param[in] mat    Rotation matrix (must be orthonormal)
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   1.6.2021
		*
		*   Initialize quaternion from rotation matrix
		*/
		//-----------------------------------------------------------------------------
		explicit Quaternion(const Matrix3& mat)
		{
			SetFromRotationMatrix(mat);
		}

		/// @{
		/// \name Operators
		//-----------------------------------------------------------------------------
		/*! \brief Comparison of quaternions without tolerance.
		*   \param[in] quat Compared quaternion
		*   \return True when coordinate are equal, otherwise false.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   6.5.2021
		*
		*   Be careful, this method works without tolerance!
		*/
		//-----------------------------------------------------------------------------
		bool operator==(const Quaternion& quat) const;

		//-----------------------------------------------------------------------------
		/*! \brief Comparison of quaternions with tolerance.
		*   \param[in] quat Compared quaternion.
		*   \return True when coordinates are equal up to Symplektis::Util::GetCoordinateTolerance(), otherwise false.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   6.5.2021
		*/
		//-----------------------------------------------------------------------------
		bool EqualsWithTolerance(const Quaternion& quat) const;

		//-----------------------------------------------------------------------------
		/*! \brief Comparison of quaternions without tolerance.
		*   \param[in] quat Compared quaternion.
		*   \return True when coordinates are not equal, otherwise false.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   6.5.2021
		*
		*   Be careful, this method works without tolerance!
		*/
		//-----------------------------------------------------------------------------
		bool operator!=(const Quaternion& quat) const;

		//-----------------------------------------------------------------------------
		/*! \brief Standard assignment operator.
		*   \param[in] quat - Quaternion to be copied.
		*   \return Reference to this quaternion.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   6.5.2021
		*
		*   Formula: Qa = Qb \n
		*   Qa is this Quaternion.
		*/
		//-----------------------------------------------------------------------------
		Quaternion& operator=(const Quaternion& quat)
		{
			if (this == &quat)
				return *this;

			return Set(quat);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Quaternion product operator.\n
		*   see http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/code/index.htm
		*   \param[in] quat Quaternion(Qb).
		*   \return Reference to the quaternion product (this).
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   6.5.2021
		*
		*   Formula: Qa = Qa * Qb \n
		*   Qa is this Quaternion
		*/
		//-----------------------------------------------------------------------------
		Quaternion& operator*=(const Quaternion& quat);

		//-----------------------------------------------------------------------------
		/// \brief   Multiply the quaternion by a scalar
		///
		/// \param[in]  scalar  Scale factor
		///
		/// \return  quaternion reference to this quaternion
		///
		/// \author  M. Cavarga (MCInversion)
		/// \date    11.6.2021
		/// 
		//-----------------------------------------------------------------------------
		Quaternion& operator*=(const double& scalar);

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
			return m_Coords[X_COORD_4D];
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
			return m_Coords[Y_COORD_4D];
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get the Z coordinate constant reference.
		*   \return constant reference to double.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   6.5.2021
		*/
		//-----------------------------------------------------------------------------
		const double& Z() const
		{
			return m_Coords[Z_COORD_4D];
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get the W coordinate constant reference.
		*   \return constant reference to double.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   6.5.2021
		*/
		//-----------------------------------------------------------------------------
		const double& W() const
		{
			return m_Coords[W_COORD_4D];
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get the X coordinate constant reference.
		*   \return reference to double.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   6.5.2021
		*/
		//-----------------------------------------------------------------------------
		double& X()
		{
			return m_Coords[X_COORD_4D];
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get the Y coordinate constant reference.
		*   \return reference to double.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   6.5.2021
		*/
		//-----------------------------------------------------------------------------
		double& Y()
		{
			return m_Coords[Y_COORD_4D];
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get the Z coordinate constant reference.
		*   \return reference to double.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   6.5.2021
		*/
		//-----------------------------------------------------------------------------
		double& Z()
		{
			return m_Coords[Z_COORD_4D];
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get the W coordinate constant reference.
		*   \return reference to double.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   6.5.2021
		*/
		//-----------------------------------------------------------------------------
		double& W()
		{
			return m_Coords[W_COORD_4D];
		}

		//-----------------------------------------------------------------------------
		/*!\brief Initialize from Quaternion.
		*   \param[in] quat Quaternion
		*   \return reference to this quaternion
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   6.5.2021
		*/
		//-----------------------------------------------------------------------------
		Quaternion& Set(const Quaternion& quat)
		{
			return Set(
				quat.m_Coords[X_COORD_4D], quat.m_Coords[Y_COORD_4D], 
				quat.m_Coords[Z_COORD_4D], quat.m_Coords[W_COORD_4D]);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Initialize from x,y,z,w coordinates.
		*   \param[in] x coordinate.
		*   \param[in] y coordinate.
		*   \param[in] z coordinate.
		*   \param[in] w coordinate.
		*   \return reference to this quaternion
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   6.5.2021
		*/
		//-----------------------------------------------------------------------------
		Quaternion& Set(const double& x, const double& y, const double& z, const double& w)
		{
			m_Coords[X_COORD_4D] = x;
			m_Coords[Y_COORD_4D] = y;
			m_Coords[Z_COORD_4D] = z;
			m_Coords[W_COORD_4D] = w;
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Initialize from axis (unit) vector and angle.
		*   \param[in] axis (normalized).
		*   \param[in] angle.
		*   \return pair reference to this quaternion
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   6.5.2021
		*/
		//-----------------------------------------------------------------------------
		Quaternion& SetFromAxisAngle(const Vector3& axis, double angle);

		//-----------------------------------------------------------------------------
		/*! \brief Initialize from 3x3 rotation matrix\n
		*	see http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm
		*   \param[in] matrix    rotation matrix (unscaled) with non-zero determinant
		*   \return reference to this quaternion
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   31.5.2021
		*/
		//-----------------------------------------------------------------------------
		Quaternion& SetFromRotationMatrix(const Matrix3& matrix);

		//-----------------------------------------------------------------------------
		/*! \brief Check the coords [0.0, 0.0, 0.0, 0.0]
		*   \return Is zero? true/false
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   6.5.2021
		*
		*   If the coords are zero, the return value is true.
		*/
		//-----------------------------------------------------------------------------
		bool IsZero() const
		{
			return (m_Coords[X_COORD_4D] == 0.0)
				&& (m_Coords[Y_COORD_4D] == 0.0)
				&& (m_Coords[Z_COORD_4D] == 0.0)
				&& (m_Coords[W_COORD_4D] == 0.0)
				? true : false;
		}

		//-----------------------------------------------------------------------------
		/*! \brief  Get quaternion length.
		*   \return double length.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   6.5.2021
		*
		*   Formula: Result(double) = ||Qa||
		*   Qa is this quaternion
		*/
		//-----------------------------------------------------------------------------
		double GetLength() const;

		//-----------------------------------------------------------------------------
		/*! \brief Get quaternion length without computationally expensive sqrt operation.
		*   \return double length squared.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   6.5.2021
		*/
		//-----------------------------------------------------------------------------
		double GetLengthSquared() const;

		//-----------------------------------------------------------------------------
		/*! \brief Normalize quaternion (if IsZero() == true).
		*   \return reference to this quaternion.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   6.5.2021
		*
		*/
		//-----------------------------------------------------------------------------
		Quaternion& Normalize();

		//-----------------------------------------------------------------------------
		/*! \brief Dot (scalar) product.
		*   \param[in] quat Quaternion(Qb).
		*   \return double.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   6.5.2021
		*
		*   Formula: S = Qa . Qb = Qa1 * Qa2 + Qb1 * Qb2 + Qa3 * Qb3 + Qa4 * Qb4\n
		*   Qa is this Quaternion
		*/
		//-----------------------------------------------------------------------------
		double DotProduct(const Quaternion& quat) const
		{
			return m_Coords[X_COORD_4D] * quat.m_Coords[X_COORD_4D]
				 + m_Coords[Y_COORD_4D] * quat.m_Coords[Y_COORD_4D]
				 + m_Coords[Z_COORD_4D] * quat.m_Coords[Z_COORD_4D]
				 + m_Coords[W_COORD_4D] * quat.m_Coords[W_COORD_4D];
		}

		//-----------------------------------------------------------------------------
		/*! \brief Compute conjugated quaternion (all coords except W are negated)
		*   \return Conjugated quaternion (this)
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   6.5.2021
		*
		*/
		//-----------------------------------------------------------------------------
		Quaternion& Conjugate()
		{
			m_Coords[X_COORD_4D] = -m_Coords[X_COORD_4D];
			m_Coords[Y_COORD_4D] = -m_Coords[Y_COORD_4D];
			m_Coords[Z_COORD_4D] = -m_Coords[Z_COORD_4D];

			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Computes rotation angle between orientations represented by this quaternion and quat
		*   \param[in] quat Quaternion(Qb).
		*   \return double.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   6.5.2021
		*
		*   
		*   Qa is this Quaternion
		*/
		//-----------------------------------------------------------------------------
		double AngleTo(const Quaternion& quat) const;

	private:
		///\brief    All coords being zero except the last W coordinate being 1.0 means \n
		//           that this quaternion's orientation coincides with rotation about Z-axis by 0 radians.
		double m_Coords[GEOMETRY_DIMENSION4] = {0.0, 0.0, 0.0, 1.0};
	};

} // Symplektis::GeometryBase