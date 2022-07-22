/*! \file Matrix3.h
*   \brief Declaration of the 3x3 matrix class
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

namespace Symplektis::GeometryKernel
{
	// forward declarations
	class Vector3;
	class Matrix4;

	//=============================================================================
	/// \class Matrix3
	/// \brief A class acting as a 3x3 matrix
	///
	/// \ingroup GEOMETRY_BASE
	//
	// \author M. Cavarga (MCInversion)
	// \date 9.5.2021
	//=============================================================================
	class Matrix3
	{
	public:
		/// @{
		/// \name Constructors
		//-----------------------------------------------------------------------------
		/*!  \brief Default constructor.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.5.2021
		*
		*   Creates an identity matrix.
		*/
		//-----------------------------------------------------------------------------
		Matrix3() = default;

		//-----------------------------------------------------------------------------
		/*! \brief Copy constructor.
		*   \param[in] mat matrix to be copied.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.5.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix3(const Matrix3& mat)
		{
			Set(mat);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Constructor. Initialize from 4x4 Matrix
		*   \param[in] mat  matrix4 to be copied.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   1.6.2021
		*/
		//-----------------------------------------------------------------------------
		explicit Matrix3(const Matrix4& mat);

		//-----------------------------------------------------------------------------
		/*! \brief Construct from coordinates.
		*   \param[in] component 1,1
		*   \param[in] component 1,2
		*   \param[in] component 1,3
		*   \param[in] component 2,1
		*   \param[in] component 2,2
		*   \param[in] component 2,3
		*   \param[in] component 3,1
		*   \param[in] component 3,2
		*   \param[in] component 3,3
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.5.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix3(
			const double& m11, const double& m12, const double& m13,
			const double& m21, const double& m22, const double& m23,
			const double& m31, const double& m32, const double& m33)
		{
			Set(
				m11, m12, m13,
				m21, m22, m23,
				m31, m32, m33
			);
		}


		/// @{
		/// \name Operators
		//-----------------------------------------------------------------------------
		/*! \brief Comparison of 3x3 matrices without tolerance.
		*   \param[in] mat Compared 3x3 matrix.
		*   \return True when matrices are equal, otherwise false.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.5.2021
		*
		*   Be careful, this method works without tolerance!
		*/
		//-----------------------------------------------------------------------------
		bool operator==(const Matrix3& mat) const;

		//-----------------------------------------------------------------------------
		/*! \brief Comparison of 3x3 matrices with tolerance.
		*   \param[in] mat Compared 3x3 matrix.
		*   \return True when matrices are equal up to Symplektis::Util::GetCoordinateTolerance(), otherwise false.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.5.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] bool EqualsWithTolerance(const Matrix3& mat) const;

		//-----------------------------------------------------------------------------
		/*! \brief Comparison of 3x3 matrices with tolerance.
		*   \param[in] mat Compared 3x3 matrix.
		*   \return True when matrices are not equal, otherwise false.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.5.2021
		*
		*   Be careful, this method works without tolerance!
		*/
		//-----------------------------------------------------------------------------
		bool operator!=(const Matrix3& mat) const;

		//-----------------------------------------------------------------------------
		/*! \brief Standard assignment operator.
		*   \param[in] mat Matrix3(Mb) to be copied.
		*   \return Reference to a matrix.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.5.2021
		*
		*   Formula: Ma = Mb \n
		*   Ma is this matrix.
		*/
		//-----------------------------------------------------------------------------
		Matrix3& operator=(const Matrix3& mat)
		{
			if (this == &mat)
				return *this;

			return Set(mat);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Addition assignment operator.
		*   \param[in] mat Mb Matrix3.
		*   \return Reference to this matrix.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.5.2021
		*
		*   Formula: Ma = Ma + Mb \n
		*   Ma is this matrix.
		*/
		//-----------------------------------------------------------------------------
		Matrix3& operator+=(const Matrix3& mat)
		{
			m_Coords[MAT3_11] += mat.m_Coords[MAT3_11];	m_Coords[MAT3_12] += mat.m_Coords[MAT3_12]; m_Coords[MAT3_13] += mat.m_Coords[MAT3_13];
			m_Coords[MAT3_21] += mat.m_Coords[MAT3_21];	m_Coords[MAT3_22] += mat.m_Coords[MAT3_22];	m_Coords[MAT3_23] += mat.m_Coords[MAT3_23];
			m_Coords[MAT3_31] += mat.m_Coords[MAT3_31];	m_Coords[MAT3_32] += mat.m_Coords[MAT3_32];	m_Coords[MAT3_33] += mat.m_Coords[MAT3_33];
			return *this;
		}


		//-----------------------------------------------------------------------------
		/*! \brief Subtraction assignment operator.
		*   \param[in] mat Mb Matrix3.
		*   \return Reference to this matrix.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.5.2021
		*
		*   Formula: Ma = Ma - Mb \n
		*   Ma is this matrix.
		*/
		//-----------------------------------------------------------------------------
		Matrix3& operator-=(const Matrix3& mat)
		{
			m_Coords[MAT3_11] -= mat.m_Coords[MAT3_11];	m_Coords[MAT3_12] -= mat.m_Coords[MAT3_12]; m_Coords[MAT3_13] -= mat.m_Coords[MAT3_13];
			m_Coords[MAT3_21] -= mat.m_Coords[MAT3_21];	m_Coords[MAT3_22] -= mat.m_Coords[MAT3_22];	m_Coords[MAT3_23] -= mat.m_Coords[MAT3_23];
			m_Coords[MAT3_31] -= mat.m_Coords[MAT3_31];	m_Coords[MAT3_32] -= mat.m_Coords[MAT3_32];	m_Coords[MAT3_33] -= mat.m_Coords[MAT3_33];
			return *this;
		}


		//-----------------------------------------------------------------------------
		/*! \brief Addition operator.
		*   \param[in] mat Matrix(Mb).
		*   \return new Matrix(Mc).
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.5.2021
		*
		*   Formula: Mc = Ma + Mb \n
		*   Ma is this Matrix.
		*/
		//-----------------------------------------------------------------------------
		Matrix3 operator+(const Matrix3& mat) const;

		//-----------------------------------------------------------------------------
		/*! \brief Subtraction operator.
		*   \param[in] mat Matrix(Mb).
		*   \return new Matrix(Mc).
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.5.2021
		*
		*   Formula: Mc = Ma - Mb \n
		*   Va is this Vector
		*/
		//-----------------------------------------------------------------------------
		Matrix3 operator-(const Matrix3& mat) const;

		//-----------------------------------------------------------------------------
		/*! \brief Matrix product
		*   \param[in] mat Matrix(Mb).
		*   \return Reference to matrix product of two matrices.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.5.2021
		*
		*   Formula: Ma = Ma . Mb \n
		*   Ma is this Matrix
		*/
		//-----------------------------------------------------------------------------
		Matrix3& operator*=(const Matrix3& mat);

		//-----------------------------------------------------------------------------
		/*! \brief multiplication of Matrix3 by a scalar
		*   \param[in] scalar.
		*   \return Reference to a matrix multiplied by a scalar.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.5.2021
		*
		*   Formula: Ma = scalar * Ma \n
		*   Ma is this Matrix
		*/
		//-----------------------------------------------------------------------------
		Matrix3& Multiply(const double& scalar);

		//-----------------------------------------------------------------------------
		/*! \brief multiplication of Matrix3 by a scalar
		*   \param[in] scalar.
		*   \return Reference to a matrix multiplied by a scalar.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.5.2021
		*
		*   Formula: Ma = scalar * Ma \n
		*   Ma is this Matrix
		*/
		//-----------------------------------------------------------------------------
		Matrix3& operator*=(const double& scalar);

		//-----------------------------------------------------------------------------
		/*! \brief Matrix multiplication
		*   \param[in] mat Matrix(Mb).
		*   \return Reference to matrix product of two matrices.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.5.2021
		*
		*   Formula: Ma = Ma . Mb \n
		*   Ma is this Matrix
		*/
		//-----------------------------------------------------------------------------
		Matrix3& Multiply(const Matrix3& mat);

		//-----------------------------------------------------------------------------
		/*! \brief Matrix pre-multiplication
		*   \param[in] mat Matrix(Mb).
		*   \return Reference to matrix product of two matrices.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.5.2021
		*
		*   Formula: Ma = Mb . Ma \n
		*   Ma is this Matrix
		*/
		//-----------------------------------------------------------------------------
		Matrix3& Premultiply(const Matrix3& mat);

		//-----------------------------------------------------------------------------
		/*! \brief Matrix multiplication
		*   \param[in] mat Matrix(Mb).
		*   \return new matrix - product of two matrices.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.5.2021
		*
		*   Formula: Mc = Ma . Mb \n
		*   Ma is this Matrix
		*/
		//-----------------------------------------------------------------------------
		Matrix3 operator*(const Matrix3& mat) const;

		//-----------------------------------------------------------------------------
		/*! \brief multiplication of Matrix3 by a scalar
		*   \param[in] scalar      Scalar value
		*   \return Mc new matrix - Ma multiplied by a scalar.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.5.2021
		*
		*   Formula: Mc = scalar * Ma \n
		*   Ma is this Matrix
		*/
		//-----------------------------------------------------------------------------
		Matrix3 operator*(const double& scalar) const;

		//-----------------------------------------------------------------------------
		/*! \brief Initialize from coordinates.
		*   \param[in] component 1,1
		*   \param[in] component 1,2
		*   \param[in] component 1,3
		*   \param[in] component 2,1
		*   \param[in] component 2,2
		*   \param[in] component 2,3
		*   \param[in] component 3,1
		*   \param[in] component 3,2
		*   \param[in] component 3,3
		*   reference to this matrix
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.5.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix3& Set(
			const double& m11, const double& m12, const double& m13,
			const double& m21, const double& m22, const double& m23,
			const double& m31, const double& m32, const double& m33)
		{
			m_Coords[MAT3_11] = m11; m_Coords[MAT3_12] = m12; m_Coords[MAT3_13] = m13;
			m_Coords[MAT3_21] = m21; m_Coords[MAT3_22] = m22; m_Coords[MAT3_23] = m23;
			m_Coords[MAT3_31] = m31; m_Coords[MAT3_32] = m32; m_Coords[MAT3_33] = m33;
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*!\brief Sets this matrix to an identity matrix
		*   \return reference to this matrix
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.5.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix3& SetToIdentity();

		//-----------------------------------------------------------------------------
		/*!\brief Initialize from Matrix3.
		*   \param[in] mat Matrix.
		*   \return reference to this matrix
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   9.5.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix3& Set(const Matrix3& mat)
		{
			return Set(
				mat.m_Coords[MAT3_11], mat.m_Coords[MAT3_12], mat.m_Coords[MAT3_13],
				mat.m_Coords[MAT3_21], mat.m_Coords[MAT3_22], mat.m_Coords[MAT3_23],
				mat.m_Coords[MAT3_31], mat.m_Coords[MAT3_32], mat.m_Coords[MAT3_33]
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
		[[nodiscard]] double Elem(const e3x3_MatrixCoordID& index) const
		{
			return m_Coords[index];
		}

		//-----------------------------------------------------------------------------
		/*!\brief IsIdentity
		*   \return true if this matrix is an identity matrix
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.5.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] bool IsIdentity() const;

		//-----------------------------------------------------------------------------
		/*!\brief Transposes this matrix
		*   \return Reference to this matrix (transposed)
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.5.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix3& Transpose();

		//-----------------------------------------------------------------------------
		/*!\brief Computes the determinant of this 3x3 matrix
		*   \return determinant
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.5.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] double Determinant() const;

		//-----------------------------------------------------------------------------
		/*!\brief Computes the inverse of this 3x3 matrix (if it exists)
		*   \return Reference to this matrix (inverted)
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   26.5.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix3& Inverse();

	private:

		double m_Coords[GEOMETRY_DIMENSION_3x3] = {
			1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 0.0, 1.0
		};
	};
} // Symplektis::GeometryKernel