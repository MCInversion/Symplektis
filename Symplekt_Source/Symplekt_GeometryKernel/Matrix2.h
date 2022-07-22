/*! \file Matrix2.h
*   \brief Declaration of the 2x2 matrix class
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

#include <cmath>

#pragma warning(disable : C26812_PREFER_ENUM_CLASS_WARNING)

namespace Symplektis::GeometryKernel
{
	// forward declarations
	class Vector2;

	//=============================================================================
	/// \class Matrix2
	/// \brief A class acting as a 2x2 matrix
	///
	/// \ingroup GEOMETRY_BASE
	//
	// \author M. Cavarga (MCInversion)
	// \date1.6.2021
	//=============================================================================
	class Matrix2
	{
	public:
		/// @{
		/// \name Constructors
		//-----------------------------------------------------------------------------
		/*!  \brief Default constructor.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date  1.6.2021
		*
		*   Creates an identity matrix.
		*/
		//-----------------------------------------------------------------------------
		Matrix2() = default;

		//-----------------------------------------------------------------------------
		/*! \brief Copy constructor.
		*   \param[in] mat matrix to be copied.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date  1.6.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix2(const Matrix2& mat)
		{
			Set(mat);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Construct from coordinates.
		*   \param[in] component 1,1
		*   \param[in] component 1,2
		*   \param[in] component 2,1
		*   \param[in] component 2,2
		*
		*   \author M. Cavarga (MCInversion)
		*   \date  1.6.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix2(
			const double& m11, const double& m12,
			const double& m21, const double& m22)
		{
			Set(
				m11, m12,
				m21, m22
			);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Construct as a rotation matrix from rotation angle
		*   \param[in] angle     rotation angle
		*
		*   \author M. Cavarga (MCInversion)
		*   \date  26.6.2021
		*/
		//-----------------------------------------------------------------------------
		explicit Matrix2(const double& angle)
		{
			Set(
				cos(angle), -sin(angle),
				sin(angle), cos(angle)
			);
		}


		/// @{
		/// \name Operators
		//-----------------------------------------------------------------------------
		/*! \brief Comparison of 2x2 matrices without tolerance.
		*   \param[in] mat Compared 2x2 matrix.
		*   \return True when matrices are equal, otherwise false.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date  1.6.2021
		*
		*   Be careful, this method works without tolerance!
		*/
		//-----------------------------------------------------------------------------
		bool operator==(const Matrix2& mat) const;

		//-----------------------------------------------------------------------------
		/*! \brief Comparison of 2x2 matrices with tolerance.
		*   \param[in] mat Compared 2x2 matrix.
		*   \return True when matrices are equal up to Symplektis::Util::GetCoordinateTolerance(), otherwise false.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date  1.6.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] bool EqualsWithTolerance(const Matrix2& mat) const;

		//-----------------------------------------------------------------------------
		/*! \brief Comparison of 2x2 matrices without tolerance.
		*   \param[in] mat Compared 2x2 matrix.
		*   \return True when matrices are not equal, otherwise false.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date  1.6.2021
		*
		*   Be careful, this method works without tolerance!
		*/
		//-----------------------------------------------------------------------------
		bool operator!=(const Matrix2& mat) const;

		//-----------------------------------------------------------------------------
		/*! \brief Standard assignment operator.
		*   \param[in] mat Matrix2(Mb) to be copied.
		*   \return Reference to a matrix.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date  1.6.2021
		*
		*   Formula: Ma = Mb \n
		*   Ma is this matrix.
		*/
		//-----------------------------------------------------------------------------
		Matrix2& operator=(const Matrix2& mat)
		{
			if (this == &mat)
				return *this;

			return Set(mat);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Addition assignment operator.
		*   \param[in] mat Mb Matrix2.
		*   \return Reference to this matrix.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date  1.6.2021
		*
		*   Formula: Ma = Ma + Mb \n
		*   Ma is this matrix.
		*/
		//-----------------------------------------------------------------------------
		Matrix2& operator+=(const Matrix2& mat)
		{
			m_Coords[MAT2_11] += mat.m_Coords[MAT2_11];	m_Coords[MAT2_12] += mat.m_Coords[MAT2_12];
			m_Coords[MAT2_21] += mat.m_Coords[MAT2_21];	m_Coords[MAT2_22] += mat.m_Coords[MAT2_22];
			return *this;
		}


		//-----------------------------------------------------------------------------
		/*! \brief Subtraction assignment operator.
		*   \param[in] mat Mb Matrix2.
		*   \return Reference to this matrix.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date  1.6.2021
		*
		*   Formula: Ma = Ma - Mb \n
		*   Ma is this matrix.
		*/
		//-----------------------------------------------------------------------------
		Matrix2& operator-=(const Matrix2& mat)
		{
			m_Coords[MAT2_11] -= mat.m_Coords[MAT2_11];	m_Coords[MAT2_12] -= mat.m_Coords[MAT2_12];
			m_Coords[MAT2_21] -= mat.m_Coords[MAT2_21];	m_Coords[MAT2_22] -= mat.m_Coords[MAT2_22];
			return *this;
		}


		//-----------------------------------------------------------------------------
		/*! \brief Addition operator.
		*   \param[in] mat Matrix(Mb).
		*   \return new Matrix(Mc).
		*
		*   \author M. Cavarga (MCInversion)
		*   \date  1.6.2021
		*
		*   Formula: Mc = Ma + Mb \n
		*   Ma is this Matrix.
		*/
		//-----------------------------------------------------------------------------
		Matrix2 operator+(const Matrix2& mat) const;

		//-----------------------------------------------------------------------------
		/*! \brief Subtraction operator.
		*   \param[in] mat Matrix(Mb).
		*   \return new Matrix(Mc).
		*
		*   \author M. Cavarga (MCInversion)
		*   \date  1.6.2021
		*
		*   Formula: Mc = Ma - Mb \n
		*   Va is this Vector
		*/
		//-----------------------------------------------------------------------------
		Matrix2 operator-(const Matrix2& mat) const;

		//-----------------------------------------------------------------------------
		/*! \brief Matrix product
		*   \param[in] mat Matrix(Mb).
		*   \return Reference to matrix product of two matrices.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date  1.6.2021
		*
		*   Formula: Ma = Ma . Mb \n
		*   Ma is this Matrix
		*/
		//-----------------------------------------------------------------------------
		Matrix2& operator*=(const Matrix2& mat);

		//-----------------------------------------------------------------------------
		/*! \brief Matrix vector product
		*   \param[in] vec Vector2 (v).
		*   \return Reference to matrix product of two matrices.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date  1.6.2021
		*
		*   Formula: Ma . v \n
		*   Ma is this Matrix
		*/
		//-----------------------------------------------------------------------------
		Matrix2& operator*=(Vector2& vec);

		//-----------------------------------------------------------------------------
		/*! \brief multiplication of Matrix2 by a scalar
		*   \param[in] scalar.
		*   \return Reference to a matrix multiplied by a scalar.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   1.6.2021
		*
		*   Formula: Ma = scalar * Ma \n
		*   Ma is this Matrix
		*/
		//-----------------------------------------------------------------------------
		Matrix2& Multiply(const double& scalar);

		//-----------------------------------------------------------------------------
		/*! \brief multiplication of Matrix2 by a scalar
		*   \param[in] scalar.
		*   \return Reference to a matrix multiplied by a scalar.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   1.6.2021
		*
		*   Formula: Ma = scalar * Ma \n
		*   Ma is this Matrix
		*/
		//-----------------------------------------------------------------------------
		Matrix2& operator*=(const double& scalar);

		//-----------------------------------------------------------------------------
		/*! \brief Matrix multiplication
		*   \param[in] mat Matrix(Mb).
		*   \return Reference to matrix product of two matrices.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   1.6.2021
		*
		*   Formula: Ma = Ma . Mb \n
		*   Ma is this Matrix
		*/
		//-----------------------------------------------------------------------------
		Matrix2& Multiply(const Matrix2& mat);

		//-----------------------------------------------------------------------------
		/*! \brief Matrix pre-multiplication
		*   \param[in] mat Matrix(Mb).
		*   \return Reference to matrix product of two matrices.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   1.6.2021
		*
		*   Formula: Ma = Mb . Ma \n
		*   Ma is this Matrix
		*/
		//-----------------------------------------------------------------------------
		Matrix2& Premultiply(const Matrix2& mat);

		//-----------------------------------------------------------------------------
		/*! \brief Matrix multiplication
		*   \param[in] mat Matrix(Mb).
		*   \return new matrix - product of two matrices.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   1.6.2021
		*
		*   Formula: Mc = Ma . Mb \n
		*   Ma is this Matrix
		*/
		//-----------------------------------------------------------------------------
		Matrix2 operator*(const Matrix2& mat) const;

		//-----------------------------------------------------------------------------
		/*! \brief multiplication of Matrix2 by a scalar
		*   \param[in] scalar.
		*   \return Reference to a matrix multiplied by a scalar.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   1.6.2021
		*
		*   Formula: Ma = scalar * Ma \n
		*   Ma is this Matrix
		*/
		//-----------------------------------------------------------------------------
		Matrix2& operator*(const double& scalar);

		//-----------------------------------------------------------------------------
		/*! \brief multiplication of Matrix2 by a scalar
		*   \param[in] scalar.
		*   \return Mc new matrix - Ma multiplied by a scalar.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   1.6.2021
		*
		*   Formula: Mc = scalar * Ma \n
		*   Ma is this Matrix
		*/
		//-----------------------------------------------------------------------------
		Matrix2 operator*(const double& scalar) const;

		//-----------------------------------------------------------------------------
		/*! \brief Initialize from coordinates.
		*   \param[in] component 1,1
		*   \param[in] component 1,2
		*   \param[in] component 2,1
		*   \param[in] component 2,2
		*   reference to this matrix
		*
		*   \author M. Cavarga (MCInversion)
		*   \date  1.6.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix2& Set(
			const double& m11, const double& m12,
			const double& m21, const double& m22)
		{
			m_Coords[MAT2_11] = m11; m_Coords[MAT2_12] = m12;
			m_Coords[MAT2_21] = m21; m_Coords[MAT2_22] = m22;
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*!\brief Sets this matrix to an identity matrix
		*   \return reference to this matrix
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   1.6.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix2& SetToIdentity();

		//-----------------------------------------------------------------------------
		/*!\brief Initialize from Matrix2.
		*   \param[in] mat Matrix.
		*   \return reference to this matrix
		*
		*   \author M. Cavarga (MCInversion)
		*   \date  1.6.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix2& Set(const Matrix2& mat)
		{
			return Set(
				mat.m_Coords[MAT2_11], mat.m_Coords[MAT2_12],
				mat.m_Coords[MAT2_21], mat.m_Coords[MAT2_22]
			);
		}

		//-----------------------------------------------------------------------------
		/*!\brief Get index of an element
		*   \param[in] index        of an element
		*   \return copy of an element given by index
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   1.6.2021
		*/
		//-----------------------------------------------------------------------------
		double Elem(const e2x2_MatrixCoordID& index) const
		{
			return m_Coords[index];
		}

		//-----------------------------------------------------------------------------
		/*!\brief IsIdentity
		*   \return true if this matrix is an identity matrix
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   1.6.2021
		*/
		//-----------------------------------------------------------------------------
		bool IsIdentity() const;

		//-----------------------------------------------------------------------------
		/*!\brief Transposes this matrix
		*   \return Reference to this matrix (transposed)
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   1.6.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix2& Transpose();

		//-----------------------------------------------------------------------------
		/*!\brief Transposes this matrix
		*   \return new matrix (transposed)
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   1.6.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix2 Transpose() const;

		//-----------------------------------------------------------------------------
		/*!\brief Computes the determinant of this 2x2 matrix
		*   \return determinant
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   1.6.2021
		*/
		//-----------------------------------------------------------------------------
		double Determinant() const;

		//-----------------------------------------------------------------------------
		/*!\brief Computes the inverse of this 2x2 matrix (if it exists)
		*   \return Reference to this matrix (inverted)
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   1.6.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix2& Inverse();

		//-----------------------------------------------------------------------------
		/*!\brief Computes the inverse of this 2x2 matrix (if it exists)
		*   \return inverted matrix
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   1.6.2021
		*/
		//-----------------------------------------------------------------------------
		Matrix2 Inverse() const;

	private:

		double m_Coords[GEOMETRY_DIMENSION_2x2] = {
			1.0, 0.0,
			0.0, 1.0
		};
	};

} // Symplektis::GeometryKernel