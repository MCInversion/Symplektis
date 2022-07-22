/*! \file Matrix4.h
*   \brief Declaration of the 4x4 matrix class
*
\verbatim
-------------------------------------------------------------------------------
created  : 27.5.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/
#pragma once

#include "VectorUtils.h"
#include <tuple>

#pragma warning(disable : C26812_PREFER_ENUM_CLASS_WARNING)

namespace Symplektis::GeometryKernel
{
	// forward declarations
	class Vector3;
	class Quaternion;

	//=============================================================================
	/// \class Matrix4
	/// \brief A class acting as a 4x4 matrix
	///
	/// \ingroup GEOMETRY_BASE
	//
	// \author M. Cavarga (MCInversion)
	// \date 27.5.2021
	//=============================================================================
	class Matrix4
	{
	public:
		/// @{
		/// \name Constructors
		//-----------------------------------------------------------------------------
		/*!  \brief Default constructor.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*
		*   Creates an identity matrix.
		*/
		//-----------------------------------------------------------------------------
		Matrix4() = default;

		//-----------------------------------------------------------------------------
		/*! \brief Copy constructor.
		*   \param[in] mat matrix to be copied.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix4(const Matrix4& mat)
		{
			Set(mat);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Construct from coordinates.
		*   \param[in] component 1,1
		*   \param[in] component 1,2
		*   \param[in] component 1,3
		*   \param[in] component 1,4
		*   \param[in] component 2,1
		*   \param[in] component 2,2
		*   \param[in] component 2,3
		*	\param[in] component 2,4
		*   \param[in] component 3,1
		*   \param[in] component 3,2
		*   \param[in] component 3,3
		*   \param[in] component 3,4
		* 	\param[in] component 4,1
		*   \param[in] component 4,2
		*   \param[in] component 4,3
		*   \param[in] component 4,4
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix4(
			const double& m11, const double& m12, const double& m13, const double& m14,
			const double& m21, const double& m22, const double& m23, const double& m24,
			const double& m31, const double& m32, const double& m33, const double& m34,
			const double& m41, const double& m42, const double& m43, const double& m44)
		{
			Set(
				m11, m12, m13, m14,
				m21, m22, m23, m24,
				m31, m32, m33, m34,
				m41, m42, m43, m44
			);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Initialize from translation, scale and orientation
		*   \param[in] translation     Translation 3D vector
		*   \param[in] scale           Scale 3D vector
		*   \param[in] orientation     Quaternion corresponding to 3D rotation
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.6.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix4(const Vector3& translation, const Vector3& scale, const Quaternion& orientation)
		{
			Compose(translation, scale, orientation);
		}


		/// @{
		/// \name Operators
		//-----------------------------------------------------------------------------
		/*! \brief Comparison of 4x4 matrices without tolerance.
		*   \param[in] mat Compared 4x4 matrix.
		*   \return True when matrices are equal, otherwise false.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*
		*   Be careful, this method works without tolerance!
		*/
		//-----------------------------------------------------------------------------
		bool operator==(const Matrix4& mat) const;

		//-----------------------------------------------------------------------------
		/*! \brief Comparison of 4x4 matrices with tolerance.
		*   \param[in] mat Compared 4x4 matrix.
		*   \return True when matrices are equal up to Symplektis::Util::GetCoordinateTolerance(), otherwise false.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] bool EqualsWithTolerance(const Matrix4& mat) const;

		//-----------------------------------------------------------------------------
		/*! \brief Comparison of 4x4 matrices with tolerance.
		*   \param[in] mat Compared 4x4 matrix.
		*   \return True when matrices are not equal, otherwise false.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*
		*   Be careful, this method works without tolerance!
		*/
		//-----------------------------------------------------------------------------
		bool operator!=(const Matrix4& mat) const;

		//-----------------------------------------------------------------------------
		/*! \brief Standard assignment operator.
		*   \param[in] mat Matrix4(Mb) to be copied.
		*   \return Reference to a matrix.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*
		*   Formula: Ma = Mb \n
		*   Ma is this matrix.
		*/
		//-----------------------------------------------------------------------------
		Matrix4& operator=(const Matrix4& mat)
		{
			if (this == &mat)
				return *this;

			return Set(mat);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Addition assignment operator.
		*   \param[in] mat Mb Matrix4.
		*   \return Reference to this matrix.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*
		*   Formula: Ma = Ma + Mb \n
		*   Ma is this matrix.
		*/
		//-----------------------------------------------------------------------------
		Matrix4& operator+=(const Matrix4& mat)
		{
			m_Coords[MAT4_11] += mat.m_Coords[MAT4_11];
			m_Coords[MAT4_12] += mat.m_Coords[MAT4_12];
			m_Coords[MAT4_13] += mat.m_Coords[MAT4_13];
			m_Coords[MAT4_14] += mat.m_Coords[MAT4_14];

			m_Coords[MAT4_21] += mat.m_Coords[MAT4_21];
			m_Coords[MAT4_22] += mat.m_Coords[MAT4_22];
			m_Coords[MAT4_23] += mat.m_Coords[MAT4_23];
			m_Coords[MAT4_24] += mat.m_Coords[MAT4_24];

			m_Coords[MAT4_31] += mat.m_Coords[MAT4_31];
			m_Coords[MAT4_32] += mat.m_Coords[MAT4_32];
			m_Coords[MAT4_33] += mat.m_Coords[MAT4_33];
			m_Coords[MAT4_34] += mat.m_Coords[MAT4_34];

			m_Coords[MAT4_41] += mat.m_Coords[MAT4_41];
			m_Coords[MAT4_42] += mat.m_Coords[MAT4_42];
			m_Coords[MAT4_43] += mat.m_Coords[MAT4_43];
			m_Coords[MAT4_44] += mat.m_Coords[MAT4_44];

			return *this;
		}


		//-----------------------------------------------------------------------------
		/*! \brief Subtraction assignment operator.
		*   \param[in] mat Mb Matrix4.
		*   \return Reference to this matrix.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*
		*   Formula: Ma = Ma - Mb \n
		*   Ma is this matrix.
		*/
		//-----------------------------------------------------------------------------
		Matrix4& operator-=(const Matrix4& mat)
		{
			m_Coords[MAT4_11] -= mat.m_Coords[MAT4_11];	
			m_Coords[MAT4_12] -= mat.m_Coords[MAT4_12]; 
			m_Coords[MAT4_13] -= mat.m_Coords[MAT4_13];
			m_Coords[MAT4_14] -= mat.m_Coords[MAT4_14];

			m_Coords[MAT4_21] -= mat.m_Coords[MAT4_21];
			m_Coords[MAT4_22] -= mat.m_Coords[MAT4_22];
			m_Coords[MAT4_23] -= mat.m_Coords[MAT4_23];
			m_Coords[MAT4_24] -= mat.m_Coords[MAT4_24];

			m_Coords[MAT4_31] -= mat.m_Coords[MAT4_31];
			m_Coords[MAT4_32] -= mat.m_Coords[MAT4_32];
			m_Coords[MAT4_33] -= mat.m_Coords[MAT4_33];
			m_Coords[MAT4_34] -= mat.m_Coords[MAT4_34];

			m_Coords[MAT4_41] -= mat.m_Coords[MAT4_41];
			m_Coords[MAT4_42] -= mat.m_Coords[MAT4_42];
			m_Coords[MAT4_43] -= mat.m_Coords[MAT4_43];
			m_Coords[MAT4_44] -= mat.m_Coords[MAT4_44];

			return *this;
		}


		//-----------------------------------------------------------------------------
		/*! \brief Addition operator.
		*   \param[in] mat Matrix(Mb).
		*   \return new Matrix(Mc).
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*
		*   Formula: Mc = Ma + Mb \n
		*   Ma is this Matrix.
		*/
		//-----------------------------------------------------------------------------
		Matrix4 operator+(const Matrix4& mat) const;

		//-----------------------------------------------------------------------------
		/*! \brief Subtraction operator.
		*   \param[in] mat Matrix(Mb).
		*   \return new Matrix(Mc).
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*
		*   Formula: Mc = Ma - Mb \n
		*   Va is this Vector
		*/
		//-----------------------------------------------------------------------------
		Matrix4 operator-(const Matrix4& mat) const;

		//-----------------------------------------------------------------------------
		/*! \brief Matrix product
		*   \param[in] mat Matrix(Mb).
		*   \return Reference to matrix product of two matrices.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*
		*   Formula: Ma = Ma . Mb \n
		*   Ma is this Matrix
		*/
		//-----------------------------------------------------------------------------
		Matrix4& operator*=(const Matrix4& mat);

		//-----------------------------------------------------------------------------
		/*! \brief multiplication of Matrix4 by a scalar
		*   \param[in] scalar.
		*   \return Reference to a matrix multiplied by a scalar.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*
		*   Formula: Ma = scalar * Ma \n
		*   Ma is this Matrix
		*/
		//-----------------------------------------------------------------------------
		Matrix4& Multiply(const double& scalar);

		//-----------------------------------------------------------------------------
		/*! \brief multiplication of Matrix4 by a scalar
		*   \param[in] scalar.
		*   \return Reference to a matrix multiplied by a scalar.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*
		*   Formula: Ma = scalar * Ma \n
		*   Ma is this Matrix
		*/
		//-----------------------------------------------------------------------------
		Matrix4& operator*=(const double& scalar);

		//-----------------------------------------------------------------------------
		/*! \brief Matrix multiplication
		*   \param[in] mat Matrix(Mb).
		*   \return Reference to matrix product of two matrices.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*
		*   Formula: Ma = Ma . Mb \n
		*   Ma is this Matrix
		*/
		//-----------------------------------------------------------------------------
		Matrix4& Multiply(const Matrix4& mat);

		//-----------------------------------------------------------------------------
		/*! \brief Matrix pre-multiplication
		*   \param[in] mat Matrix(Mb).
		*   \return Reference to matrix product of two matrices.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*
		*   Formula: Ma = Mb . Ma \n
		*   Ma is this Matrix
		*/
		//-----------------------------------------------------------------------------
		Matrix4& Premultiply(const Matrix4& mat);

		//-----------------------------------------------------------------------------
		/*! \brief Matrix multiplication
		*   \param[in] mat Matrix(Mb).
		*   \return new matrix - product of two matrices.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*
		*   Formula: Mc = Ma . Mb \n
		*   Ma is this Matrix
		*/
		//-----------------------------------------------------------------------------
		Matrix4 operator*(const Matrix4& mat) const;

		//-----------------------------------------------------------------------------
		/*! \brief multiplication of Matrix4 by a scalar
		*   \param[in] scalar.
		*   \return Reference to a matrix multiplied by a scalar.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*
		*   Formula: Ma = scalar * Ma \n
		*   Ma is this Matrix
		*/
		//-----------------------------------------------------------------------------
		Matrix4& operator*(const double& scalar);

		//-----------------------------------------------------------------------------
		/*! \brief multiplication of Matrix4 by a scalar
		*   \param[in] scalar.
		*   \return Mc new matrix - Ma multiplied by a scalar.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*
		*   Formula: Mc = scalar * Ma \n
		*   Ma is this Matrix
		*/
		//-----------------------------------------------------------------------------
		Matrix4 operator*(const double& scalar) const;

		//-----------------------------------------------------------------------------
		/*! \brief Initialize from coordinates.
		*   \param[in] component 1,1
		*   \param[in] component 1,2
		*   \param[in] component 1,3
		*   \param[in] component 1,4
		*   \param[in] component 2,1
		*   \param[in] component 2,2
		*   \param[in] component 2,3
		*	\param[in] component 2,4
		*   \param[in] component 3,1
		*   \param[in] component 3,2
		*   \param[in] component 3,3
		*   \param[in] component 3,4
		* 	\param[in] component 4,1
		*   \param[in] component 4,2
		*   \param[in] component 4,3
		*   \param[in] component 4,4
		*   \return reference to this matrix.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix4& Set(
			const double& m11, const double& m12, const double& m13, const double& m14,
			const double& m21, const double& m22, const double& m23, const double& m24,
			const double& m31, const double& m32, const double& m33, const double& m34,
			const double& m41, const double& m42, const double& m43, const double& m44)
		{
			m_Coords[MAT4_11] = m11; m_Coords[MAT4_12] = m12; m_Coords[MAT4_13] = m13; m_Coords[MAT4_14] = m14;
			m_Coords[MAT4_21] = m21; m_Coords[MAT4_22] = m22; m_Coords[MAT4_23] = m23; m_Coords[MAT4_24] = m24;
			m_Coords[MAT4_31] = m31; m_Coords[MAT4_32] = m32; m_Coords[MAT4_33] = m33; m_Coords[MAT4_34] = m34;
			m_Coords[MAT4_41] = m41; m_Coords[MAT4_42] = m42; m_Coords[MAT4_43] = m43; m_Coords[MAT4_44] = m44;
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*!\brief Sets this matrix to an identity matrix
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix4& SetToIdentity();

		//-----------------------------------------------------------------------------
		/*! \brief Set this matrix to scale matrix (3 scale components to main diagonal)
		*   \param[in] sx.
		*	\param[in] sy.
		*   \param[in] sz.
		*   \return Reference to this matrix set to scale.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix4& SetToScale(const double& sx, const double& sy, const double& sz);

		//-----------------------------------------------------------------------------
		/*! \brief Set this matrix to scale matrix (3 scale components to main diagonal)
		*   \param[in] scaleVector
		*   \return Reference to this matrix set to scale.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix4& SetToScale(const Vector3& scaleVect);

		//-----------------------------------------------------------------------------
		/*! \brief Set this matrix to a rotation matrix (affecting the 3x3 sub-matrix)
		*   \param[in] ax        rotation axis x-coordinate. (ax, ay, az) Must be normalized!
		*   \param[in] ay        rotation axis y-coordinate. (ax, ay, az) Must be normalized!
		*   \param[in] az        rotation axis z-coordinate. (ax, ay, az) Must be normalized!
		*   \param[in] angle     rotation angle
		*   \return Reference to this matrix set to a rotation matrix.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix4& SetToRotationAboutAxis(const double& ax, const double& ay, const double& az, const double& angle);

		//-----------------------------------------------------------------------------
		/*! \brief Set this matrix to a rotation matrix (affecting the 3x3 sub-matrix)
		*   \param[in] axis      rotation axis. Must be normalized!
		*   \param[in] angle     rotation angle
		*   \return Reference to this matrix set to a rotation matrix.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix4& SetToRotationAboutAxis(const Vector3& axis, const double& angle);

		//-----------------------------------------------------------------------------
		/*!\brief Initialize from Matrix4.
		*   \param[in] mat Matrix.
		*   \return reference to this matrix.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix4& Set(const Matrix4& mat)
		{
			return Set(
				mat.m_Coords[MAT4_11], mat.m_Coords[MAT4_12], mat.m_Coords[MAT4_13], mat.m_Coords[MAT4_14],
				mat.m_Coords[MAT4_21], mat.m_Coords[MAT4_22], mat.m_Coords[MAT4_23], mat.m_Coords[MAT4_24],
				mat.m_Coords[MAT4_31], mat.m_Coords[MAT4_32], mat.m_Coords[MAT4_33], mat.m_Coords[MAT4_34],
				mat.m_Coords[MAT4_41], mat.m_Coords[MAT4_42], mat.m_Coords[MAT4_43], mat.m_Coords[MAT4_44]
			);
		}

		//-----------------------------------------------------------------------------
		/*!\brief Get index of an element
		*   \param[in] index        of an element
		*   \return copy of an element given by index
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   31.5.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] double Elem(const e4x4_MatrixCoordID& index) const
		{
			return m_Coords[index];
		}

		//-----------------------------------------------------------------------------
		/*!\brief IsIdentity
		*   \return true if this matrix is an identity matrix
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] bool IsIdentity() const;

		//-----------------------------------------------------------------------------
		/*!\brief Transposes this matrix
		*   \return Reference to this matrix (transposed)
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix4& Transpose();

		//-----------------------------------------------------------------------------
		/*!\brief Transposes this matrix
		*   \return new matrix (transposed)
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] Matrix4 Transpose() const;

		//-----------------------------------------------------------------------------
		/*!\brief Computes the determinant of this 4x4 matrix
		*   \return determinant
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] double Determinant() const;

		//-----------------------------------------------------------------------------
		/*!\brief Computes the inverse of this 4x4 matrix (if it exists)
		*   \return Reference to this matrix (inverted)
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix4& Inverse();

		//-----------------------------------------------------------------------------
		/*!\brief Computes the inverse of this 4x4 matrix (if it exists)
		*   \return inverted matrix
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.5.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] Matrix4 Inverse() const;

		//-----------------------------------------------------------------------------
		/*! \brief Set this matrix to a general transformation matrix from translation,\n
		*          rotation, and scale input.
		*   \param[in] translation     Translation 3D vector
		*   \param[in] scale           Scale 3D vector
		*   \param[in] orientation     Quaternion corresponding to 3D rotation
		*   \return Reference to this matrix set to a TRS matrix
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   31.5.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix4& Compose(const Vector3& translation, const Vector3& scale, const Quaternion& orientation);

		//-----------------------------------------------------------------------------
		/*!\brief Decomposes this transformation matrix into an ordered triple (translationVector, scaleVector, orientationQuaternion).
		*   \return triple (translationVector, scaleVector, orientationQuaternion)
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   31.5.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] std::tuple<Vector3, Vector3, Quaternion> Decompose() const;

		//-----------------------------------------------------------------------------
		/*!\brief Decomposes this transformation matrix into translationVector, scaleVector, orientationQuaternion.
		*   \param[in] translation       translation vector
		*   \param[in] scale             scale vector
		*   \param[in] orientation       orientation (3D rotation) quaternion
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   31.5.2021
		*/
		//-----------------------------------------------------------------------------
		void Decompose(Vector3& translation, Vector3& scale, Quaternion& orientation) const;

	private:

		double m_Coords[GEOMETRY_DIMENSION_4x4] = {
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
		};
	};
} // Symplektis::GeometryKernel