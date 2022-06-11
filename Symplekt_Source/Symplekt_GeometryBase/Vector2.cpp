/*! \file Vector2.cpp
*   \brief Implmentation of the 2D vector class
*
\verbatim
-------------------------------------------------------------------------------
created  : 6.5.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/
#include "Vector2.h"

#include "../Symplekt_UtilityGeneral/NumericUtils.h"
#include "../Symplekt_UtilityGeneral/ToleranceSettings.h"
#include "Vector3.h"
#include "Matrix2.h"

namespace Symplektis::GeometryBase
{
	bool Vector2::operator==(const Vector2& vec) const
	{
		if (m_Coords[X_COORD_2D] != vec.m_Coords[X_COORD_2D])
			return false;

		return (m_Coords[Y_COORD_2D] == vec.m_Coords[Y_COORD_2D]);
	}

	bool Vector2::EqualsWithTolerance(const Vector2& vec) const
	{
		const double epsilon = Symplektis::Util::GetCoordinateTolerance();
		if (std::fabs(m_Coords[X_COORD_2D] - vec.m_Coords[X_COORD_2D]) > epsilon)
			return false;

		return (std::fabs(m_Coords[Y_COORD_2D] - vec.m_Coords[Y_COORD_2D]) < epsilon);
	}

	bool Vector2::operator!=(const Vector2& vec) const
	{
		if (*this == vec)
			return false;
		else
			return true;
	}

	Vector2 Vector2::operator+(const Vector2& vec) const
	{
		Vector2 result(*this);
		result += vec;
		return result;
	}

	Vector2 Vector2::operator-(const Vector2& vec) const
	{
		Vector2 result(*this);
		result -= vec;
		return result;
	}

	Vector3 Vector2::operator*(const Vector2& vec) const
	{
		Vector3 result(m_Coords[X_COORD_2D], m_Coords[Y_COORD_2D], 0.0);
		result *= vec;
		return result;
	}

	Vector2 Vector2::operator*(const double& scalar) const
	{
		return Vector2(
			m_Coords[0] * scalar,
			m_Coords[1] * scalar);
	}

	Vector2& Vector2::operator*=(const double& scalar)
	{
		m_Coords[0] *= scalar;
		m_Coords[1] *= scalar;

		return *this;
	}

	Vector2 Vector2::operator/(const double& scalar) const
	{
		return Vector2(
			m_Coords[0] / scalar,
			m_Coords[1] / scalar);
	}

	Vector2& Vector2::operator/=(const double& scalar)
	{
		m_Coords[0] /= scalar;
		m_Coords[1] /= scalar;

		return *this;
	}

	Vector2& Vector2::operator*=(const Matrix2& matrix)
	{
		return Set(
			matrix.Elem(MAT2_11) * m_Coords[X_COORD_2D] + matrix.Elem(MAT2_12) * m_Coords[Y_COORD_2D],
			matrix.Elem(MAT2_21) * m_Coords[X_COORD_2D] + matrix.Elem(MAT2_22) * m_Coords[Y_COORD_2D]
		);
	}

	Vector2 Vector2::operator*(const Matrix2& matrix) const
	{
		Vector2 result(*this);
		result *= matrix;
		return result;
	}

	Vector2& Vector2::Set(const Vector3& vec)
	{
		return Set(vec.X(), vec.Y());
	}

	bool Vector2::IsNormalized() const
	{
		return (GetLengthSquared() == 1.0);
	}

	bool Vector2::IsNormalizedWithTolerance() const
	{
		return Symplektis::Util::EqualsWithTolerance(GetLengthSquared(), 1.0, Symplektis::Util::GetProductTolerance());
	}

	double Vector2::GetLength() const
	{
		double dx2 = m_Coords[X_COORD_2D] * m_Coords[X_COORD_2D];
		double dy2 = m_Coords[Y_COORD_2D] * m_Coords[Y_COORD_2D];
		return sqrt(dx2 + dy2);
	}

	double Vector2::GetLengthSquared() const
	{
		return (
			m_Coords[X_COORD_2D] * m_Coords[X_COORD_2D] +
			m_Coords[Y_COORD_2D] * m_Coords[Y_COORD_2D]);
	}

	Vector2& Vector2::Normalize()
	{
		if (IsZero())
		{
			MSG_CHECK(false, "Vector2::Normalize: Attempting to normalize a zero-length vector!\n");
			return *this;
		}

		double oldLength = GetLength();

		m_Coords[X_COORD_2D] /= oldLength;
		m_Coords[Y_COORD_2D] /= oldLength;

		return *this;
	}

	double Vector2::CrossProduct(const Vector2& vec) const
	{
		return m_Coords[X_COORD_2D] * vec.m_Coords[Y_COORD_2D] - m_Coords[Y_COORD_2D] * vec.m_Coords[X_COORD_2D];
	}

	Vector2& Vector2::DirectProduct(const Vector2& vec)
	{
		m_Coords[X_COORD_2D] *= vec.m_Coords[X_COORD_2D];
		m_Coords[Y_COORD_2D] *= vec.m_Coords[Y_COORD_2D];
		return *this;
	}

	Vector2 Vector2::DirectProduct(const Vector2& vec) const
	{
		Vector2 result(*this);
		result.m_Coords[X_COORD_2D] *= vec.m_Coords[X_COORD_2D];
		result.m_Coords[Y_COORD_2D] *= vec.m_Coords[Y_COORD_2D];
		return result;
	}

	Vector2 Vector2::Project(const Vector2& vec) const
	{
		Vector2 result;
		if (IsZero())
		{
			MSG_CHECK(false, "Vector2::Project: Attempting to project onto a zero-length vector!\n");
			return result;
		}

		result = (*this) * (vec.DotProduct(*this) / DotProduct(*this));
		return result;
	}

	Vector2& Vector2::ApplyAngle(const double& angle)
	{
		const double c = cos(angle);
		const double s = sin(angle);
		return Set(
			c * m_Coords[X_COORD_2D] - s * m_Coords[Y_COORD_2D],
			s * m_Coords[X_COORD_2D] + c * m_Coords[Y_COORD_2D]
		);
	}

	Vector2& Vector2::Min(const Vector2& vec)
	{
		/* TODO: is this faster for AABBTree ?
		m_Coords[X_COORD_2D] = (vec.m_Coords[X_COORD_2D] < m_Coords[X_COORD_2D] ? vec.m_Coords[X_COORD_2D] : m_Coords[X_COORD_2D]);
		m_Coords[Y_COORD_2D] = (vec.m_Coords[Y_COORD_2D] < m_Coords[Y_COORD_2D] ? vec.m_Coords[Y_COORD_2D] : m_Coords[Y_COORD_2D]);
		*/
		if (vec.m_Coords[X_COORD_2D] < m_Coords[X_COORD_2D])
			m_Coords[X_COORD_2D] = vec.m_Coords[X_COORD_2D];

		if (vec.m_Coords[Y_COORD_2D] < m_Coords[Y_COORD_2D])
			m_Coords[Y_COORD_2D] = vec.m_Coords[Y_COORD_2D];

		return *this;
	}

	Vector2& Vector2::Max(const Vector2& vec)
	{
		/* // TODO: is this faster for AABBTree ?
		m_Coords[X_COORD_2D] = (vec.m_Coords[X_COORD_2D] > m_Coords[X_COORD_2D] ? vec.m_Coords[X_COORD_2D] : m_Coords[X_COORD_2D]);
		m_Coords[Y_COORD_2D] = (vec.m_Coords[Y_COORD_2D] > m_Coords[Y_COORD_2D] ? vec.m_Coords[Y_COORD_2D] : m_Coords[Y_COORD_2D]);
		*/
		if (vec.m_Coords[X_COORD_2D] > m_Coords[X_COORD_2D])
			m_Coords[X_COORD_2D] = vec.m_Coords[X_COORD_2D];

		if (vec.m_Coords[Y_COORD_2D] > m_Coords[Y_COORD_2D])
			m_Coords[Y_COORD_2D] = vec.m_Coords[Y_COORD_2D];

		return *this;
	}

	Vector2& Vector2::LinearInterpolate(const Vector2& vec, const double& param)
	{
		m_Coords[X_COORD_2D] += (vec.m_Coords[X_COORD_2D] - m_Coords[X_COORD_2D]) * param;
		m_Coords[Y_COORD_2D] += (vec.m_Coords[Y_COORD_2D] - m_Coords[Y_COORD_2D]) * param;
		return *this;
	}

} // Symplektis::GeometryBase