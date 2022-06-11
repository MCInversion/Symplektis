/*! \file Matrix2.cpp
*   \brief Implmentation of the 2x2 matrix class
*
\verbatim
-------------------------------------------------------------------------------
created  : 6.5.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/

#include "Matrix2.h"

#include "../Symplekt_UtilityGeneral/NumericUtils.h"
#include "../Symplekt_UtilityGeneral/ToleranceSettings.h"

#include "Vector2.h"

namespace Symplektis::GeometryBase
{
	bool Matrix2::operator==(const Matrix2& mat) const
	{
		if (m_Coords[MAT2_11] != mat.m_Coords[MAT2_11])
			return false;
		if (m_Coords[MAT2_12] != mat.m_Coords[MAT2_12])
			return false;
		if (m_Coords[MAT2_21] != mat.m_Coords[MAT2_21])
			return false;

		return (m_Coords[MAT2_22] == mat.m_Coords[MAT2_22]);
	}

	bool Matrix2::EqualsWithTolerance(const Matrix2& mat) const
	{
		const double epsilon = Symplektis::Util::GetCoordinateTolerance();

		if (!Symplektis::Util::EqualsWithTolerance(m_Coords[MAT2_11], mat.m_Coords[MAT2_11], epsilon))
			return false;
		if (!Symplektis::Util::EqualsWithTolerance(m_Coords[MAT2_12], mat.m_Coords[MAT2_12], epsilon))
			return false;
		if (!Symplektis::Util::EqualsWithTolerance(m_Coords[MAT2_21], mat.m_Coords[MAT2_21], epsilon))
			return false;

		return (Symplektis::Util::EqualsWithTolerance(m_Coords[MAT2_22], mat.m_Coords[MAT2_22], epsilon));
	}

	bool Matrix2::operator!=(const Matrix2& mat) const
	{
		if (m_Coords[MAT2_11] != mat.m_Coords[MAT2_11])
			return true;
		if (m_Coords[MAT2_12] != mat.m_Coords[MAT2_12])
			return true;
		if (m_Coords[MAT2_21] != mat.m_Coords[MAT2_21])
			return true;

		return (m_Coords[MAT2_22] != mat.m_Coords[MAT2_22]);
	}

	Matrix2 Matrix2::operator+(const Matrix2& mat) const
	{
		Matrix2 result(*this);
		result += mat;
		return result;
	}

	Matrix2 Matrix2::operator-(const Matrix2& mat) const
	{
        Matrix2 result(*this);
        result -= mat;
        return result;
	}

	Matrix2& Matrix2::operator*=(const Matrix2& mat)
	{
		return Multiply(mat);
	}

	Matrix2& Matrix2::operator*=(Vector2& vec)
	{
		const double x = m_Coords[MAT2_11] * vec.X() + m_Coords[MAT2_12] * vec.Y();
		const double y = m_Coords[MAT2_21] * vec.X() + m_Coords[MAT2_22] * vec.Y();
		vec.Set(x, y);
		return *this;
	}

	Matrix2& Matrix2::Multiply(const double& scalar)
	{
		m_Coords[MAT2_11] *= scalar; m_Coords[MAT2_12] *= scalar;
		m_Coords[MAT2_21] *= scalar; m_Coords[MAT2_22] *= scalar;
		return *this;
	}

	Matrix2& Matrix2::operator*=(const double& scalar)
	{
		return Multiply(scalar);
	}

	Matrix2& Matrix2::Multiply(const Matrix2& mat)
	{
		double result[GEOMETRY_DIMENSION_2x2] = {
			m_Coords[MAT2_11] * mat.m_Coords[MAT2_11] + m_Coords[MAT2_12] * mat.m_Coords[MAT2_21],
			m_Coords[MAT2_11] * mat.m_Coords[MAT2_12] + m_Coords[MAT2_12] * mat.m_Coords[MAT2_22],
			m_Coords[MAT2_21] * mat.m_Coords[MAT2_11] + m_Coords[MAT2_22] * mat.m_Coords[MAT2_21],
			m_Coords[MAT2_21] * mat.m_Coords[MAT2_12] + m_Coords[MAT2_22] * mat.m_Coords[MAT2_22]
		};
		memcpy(m_Coords, result, GEOMETRY_DIMENSION_2x2 * sizeof(double));

		return *this;
	}

	Matrix2& Matrix2::Premultiply(const Matrix2& mat)
	{
		double result[GEOMETRY_DIMENSION_2x2] = {
			mat.m_Coords[MAT2_11] * m_Coords[MAT2_11] + mat.m_Coords[MAT2_12] * m_Coords[MAT2_21],
			mat.m_Coords[MAT2_11] * m_Coords[MAT2_12] + mat.m_Coords[MAT2_12] * m_Coords[MAT2_22],
			mat.m_Coords[MAT2_21] * m_Coords[MAT2_11] + mat.m_Coords[MAT2_22] * m_Coords[MAT2_21],
			mat.m_Coords[MAT2_21] * m_Coords[MAT2_12] + mat.m_Coords[MAT2_22] * m_Coords[MAT2_22]
		};
		memcpy(m_Coords, result, GEOMETRY_DIMENSION_2x2 * sizeof(double));

		return *this;
	}

	Matrix2 Matrix2::operator*(const Matrix2& mat) const
	{
		Matrix2 result(*this);
		result *= mat;
		return result;
	}

	Matrix2& Matrix2::operator*(const double& scalar)
	{
		return Multiply(scalar);
	}

	Matrix2 Matrix2::operator*(const double& scalar) const
	{
		Matrix2 result(*this);
		result *= scalar;
		return result;
	}

	Matrix2& Matrix2::SetToIdentity()
	{
		return Set(
			1.0, 0.0,
			0.0, 1.0
		);
	}

	bool Matrix2::IsIdentity() const
	{
		if (m_Coords[MAT2_11] != 1.0)
			return false;
		if (m_Coords[MAT2_12] != 0.0)
			return false;
		if (m_Coords[MAT2_21] != 0.0)
			return false;

		return (m_Coords[MAT2_22] == 1.0);
	}

	Matrix2& Matrix2::Transpose()
	{
		double result[GEOMETRY_DIMENSION_2x2] = {
			m_Coords[MAT2_11], m_Coords[MAT2_21],
			m_Coords[MAT2_12], m_Coords[MAT2_22]
		};
		memcpy(m_Coords, result, GEOMETRY_DIMENSION_2x2 * sizeof(double));
		return *this;
	}

	Matrix2 Matrix2::Transpose() const
	{
		Matrix2 result(*this);
		result.Transpose();
		return result;
	}

	double Matrix2::Determinant() const
	{
		return (m_Coords[MAT2_11] * m_Coords[MAT2_22] - m_Coords[MAT2_12] * m_Coords[MAT2_21]);
	}

	Matrix2& Matrix2::Inverse()
	{
		const double det = Determinant();
		const double epsilon = Symplektis::Util::GetProductTolerance();
		if (std::fabs(det) < epsilon)
		{
			MSG_CHECK(false, "Matrix2::Inverse: det == 0! Attempting to invert a singular 2x2 matrix!");
			return *this;
		}

		double result[GEOMETRY_DIMENSION_2x2] = {
			 m_Coords[MAT2_22],
			-m_Coords[MAT2_12],
			-m_Coords[MAT2_21],
			 m_Coords[MAT2_11]
		};
		memcpy(m_Coords, result, GEOMETRY_DIMENSION_2x2 * sizeof(double));

		*this *= (1.0 / det);

		return *this;
	}

	Matrix2 Matrix2::Inverse() const
	{
		Matrix2 result(*this);
		result.Inverse();
		return result;
	}

} // Symplektis::GeometryBase