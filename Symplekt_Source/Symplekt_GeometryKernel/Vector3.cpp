/*! \file Vector3.cpp
*   \brief Implmentation of the 3D Vector class
*
\verbatim
-------------------------------------------------------------------------------
created  : 5.5.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/
#include "Vector3.h"

#include "Symplekt_UtilityGeneral/NumericUtils.h"
#include "Symplekt_UtilityGeneral/ToleranceSettings.h"
#include "Vector2.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Quaternion.h"

namespace Symplektis::GeometryKernel
{
	Vector3::Vector3(const Vector2& vec)
	{
		Set(vec.X(), vec.Y(), 0.0);
	}

	bool Vector3::operator==(const Vector3& vec) const
	{
		if (m_Coords[X_COORD_3D] != vec.m_Coords[X_COORD_3D])
			return false;

		if (m_Coords[Y_COORD_3D] != vec.m_Coords[Y_COORD_3D])
			return false;

		return (m_Coords[Z_COORD_3D] == vec.m_Coords[Z_COORD_3D]);
	}

	bool Vector3::EqualsWithTolerance(const Vector3& vec) const
	{
		const double epsilon = Symplektis::Util::GetCoordinateTolerance();

		if (!Symplektis::Util::EqualsWithTolerance(m_Coords[X_COORD_3D], vec.m_Coords[X_COORD_3D], epsilon))
			return false;

		if (!Symplektis::Util::EqualsWithTolerance(m_Coords[Y_COORD_3D], vec.m_Coords[Y_COORD_3D], epsilon))
			return false;

		return (Symplektis::Util::EqualsWithTolerance(m_Coords[Z_COORD_3D], vec.m_Coords[Z_COORD_3D], epsilon));
	}

	bool Vector3::operator!=(const Vector3& vec) const
	{
		if (*this == vec)
			return false;
		else
			return true;
	}

	Vector3 Vector3::operator+(const Vector3& vec) const
	{
		Vector3 result(*this);
		result += vec;
		return result;
	}

	Vector3 Vector3::operator-(const Vector3& vec) const
	{
		Vector3 result(*this);
		result -= vec;
		return result;
	}

	Vector3& Vector3::operator*=(const Vector3& vec)
	{
		double x = m_Coords[Y_COORD_3D] * vec.m_Coords[Z_COORD_3D] - m_Coords[Z_COORD_3D] * vec.m_Coords[Y_COORD_3D];
		double y = m_Coords[Z_COORD_3D] * vec.m_Coords[X_COORD_3D] - m_Coords[X_COORD_3D] * vec.m_Coords[Z_COORD_3D];
		double z = m_Coords[X_COORD_3D] * vec.m_Coords[Y_COORD_3D] - m_Coords[Y_COORD_3D] * vec.m_Coords[X_COORD_3D];
		m_Coords[X_COORD_3D] = x;
		m_Coords[Y_COORD_3D] = y;
		m_Coords[Z_COORD_3D] = z;
		return *this;
	}

	Vector3& Vector3::operator*=(const Vector2& vec)
	{
		double x = m_Coords[Y_COORD_3D] * 0.0     - m_Coords[Z_COORD_3D] * vec.Y();
		double y = m_Coords[Z_COORD_3D] * vec.X() - m_Coords[X_COORD_3D] * 0.0;
		double z = m_Coords[X_COORD_3D] * vec.Y() - m_Coords[Y_COORD_3D] * vec.X();
		m_Coords[X_COORD_3D] = x;
		m_Coords[Y_COORD_3D] = y;
		m_Coords[Z_COORD_3D] = z;
		return *this;
	}

	Vector3& Vector3::operator*=(const Matrix3& mat)
	{
		const double x = mat.Elem(MAT3_11) * m_Coords[X_COORD_3D] + mat.Elem(MAT3_12) * m_Coords[Y_COORD_3D] + mat.Elem(MAT3_13) * m_Coords[Z_COORD_3D];
		const double y = mat.Elem(MAT3_21) * m_Coords[X_COORD_3D] + mat.Elem(MAT3_22) * m_Coords[Y_COORD_3D] + mat.Elem(MAT3_23) * m_Coords[Z_COORD_3D];
		const double z = mat.Elem(MAT3_31) * m_Coords[X_COORD_3D] + mat.Elem(MAT3_32) * m_Coords[Y_COORD_3D] + mat.Elem(MAT3_33) * m_Coords[Z_COORD_3D];
		return Set(x, y, z);
	}

	Vector3& Vector3::operator*=(const Matrix4& mat)
	{
		const double w = 1.0 / (mat.Elem(MAT4_41) * m_Coords[X_COORD_3D] + mat.Elem(MAT4_42) * m_Coords[Y_COORD_3D] + mat.Elem(MAT4_43) * m_Coords[Z_COORD_3D] + mat.Elem(MAT4_44));

		const double x = (mat.Elem(MAT4_11) * m_Coords[X_COORD_3D] + mat.Elem(MAT4_12) * m_Coords[Y_COORD_3D] + mat.Elem(MAT4_13) * m_Coords[Z_COORD_3D]) * w;
		const double y = (mat.Elem(MAT4_21) * m_Coords[X_COORD_3D] + mat.Elem(MAT4_22) * m_Coords[Y_COORD_3D] + mat.Elem(MAT4_23) * m_Coords[Z_COORD_3D]) * w;
		const double z = (mat.Elem(MAT4_31) * m_Coords[X_COORD_3D] + mat.Elem(MAT4_32) * m_Coords[Y_COORD_3D] + mat.Elem(MAT4_33) * m_Coords[Z_COORD_3D]) * w;
		return Set(x, y, z);
	}

	Vector3 Vector3::operator*(const Vector3& vec) const
	{
		Vector3 result(*this);
		result *= vec;
		return result;
	}

	Vector3 Vector3::operator*(const double& scalar) const
	{
		return Vector3(
			m_Coords[0] * scalar,
			m_Coords[1] * scalar,
			m_Coords[2] * scalar);
	}

	Vector3& Vector3::operator*=(const double& scalar)
	{
		m_Coords[0] *= scalar;
		m_Coords[1] *= scalar;
		m_Coords[2] *= scalar;

		return *this;
	}

	Vector3 Vector3::operator/(const double& scalar) const
	{
		return Vector3(
			m_Coords[0] / scalar,
			m_Coords[1] / scalar,
			m_Coords[2] / scalar);
	}

	Vector3& Vector3::operator/=(const double& scalar)
	{
		m_Coords[0] /= scalar;
		m_Coords[1] /= scalar;
		m_Coords[2] /= scalar;

		return *this;
	}

	bool Vector3::IsNormalized() const
	{
		// (?) instead of GetLengthSquared() use faster GetInvLength()
		return (GetLengthSquared() == 1.0);
	}

	bool Vector3::IsNormalizedWithTolerance() const
	{
		// (?) instead of GetLengthSquared() use faster GetInvLength()
		return Util::EqualsWithTolerance(GetLengthSquared(), 1.0, Util::GetProductTolerance());
	}

	double Vector3::GetLength() const
	{
		double dx2 = m_Coords[X_COORD_3D] * m_Coords[X_COORD_3D];
		double dy2 = m_Coords[Y_COORD_3D] * m_Coords[Y_COORD_3D];
		double dz2 = m_Coords[Z_COORD_3D] * m_Coords[Z_COORD_3D];
		return sqrt(dx2 + dy2 + dz2);
	}

	double Vector3::GetLengthSquared() const
	{
		return (
			m_Coords[X_COORD_3D] * m_Coords[X_COORD_3D] +
			m_Coords[Y_COORD_3D] * m_Coords[Y_COORD_3D] +
			m_Coords[Z_COORD_3D] * m_Coords[Z_COORD_3D]);
	}

	double Vector3::GetInvLength() const
	{
		double lengthSq = (
			m_Coords[X_COORD_3D] * m_Coords[X_COORD_3D] +
			m_Coords[Y_COORD_3D] * m_Coords[Y_COORD_3D] +
			m_Coords[Z_COORD_3D] * m_Coords[Z_COORD_3D]);
		return Util::FastInverseSqrt(lengthSq);
	}

	Vector3& Vector3::Normalize()
	{
		if (IsZero())
		{
			MSG_CHECK(false, "Vector3::Normalize: Attempting to normalize a zero-length vector!\n");
			return *this;
		}

		double oldLength = GetLength();

		m_Coords[X_COORD_3D] /= oldLength;
		m_Coords[Y_COORD_3D] /= oldLength;
		m_Coords[Z_COORD_3D] /= oldLength;

		return *this;
	}

	Vector3& Vector3::FastNormalize()
	{
		double oldInvLength = GetInvLength();

		m_Coords[X_COORD_3D] *= oldInvLength;
		m_Coords[Y_COORD_3D] *= oldInvLength;
		m_Coords[Z_COORD_3D] *= oldInvLength;

		return *this;
	}

	Vector3& Vector3::CrossProduct(const Vector3& vec)
	{
		*this *= vec;
		return *this;
	}

	Vector3& Vector3::DirectProduct(const Vector3& vec)
	{
		m_Coords[X_COORD_3D] *= vec.m_Coords[X_COORD_3D];
		m_Coords[Y_COORD_3D] *= vec.m_Coords[Y_COORD_3D];
		m_Coords[Z_COORD_3D] *= vec.m_Coords[Z_COORD_3D];
		return *this;
	}

	Vector3 Vector3::Project(const Vector3& vec) const
	{
		Vector3 result;
		if (IsZero())
		{
			MSG_CHECK(false, "Vector3::Project: Attempting to project onto a zero-length vector!\n");
			return result;
		}

		result = (*this) * (vec.DotProduct(*this) / DotProduct(*this));
		return result;
	}

	Vector3& Vector3::ApplyQuaternion(const Quaternion& quaternion)
	{
		// compute quat * vector
		const double ix =  quaternion.W() * m_Coords[X_COORD_3D] + quaternion.Y() * m_Coords[Z_COORD_3D] - quaternion.Z() * m_Coords[Y_COORD_3D];
		const double iy =  quaternion.W() * m_Coords[Y_COORD_3D] + quaternion.Z() * m_Coords[X_COORD_3D] - quaternion.X() * m_Coords[Z_COORD_3D];
		const double iz =  quaternion.W() * m_Coords[Z_COORD_3D] + quaternion.X() * m_Coords[Y_COORD_3D] - quaternion.Y() * m_Coords[X_COORD_3D];
		const double iw = -quaternion.X() * m_Coords[X_COORD_3D] - quaternion.Y() * m_Coords[Y_COORD_3D] - quaternion.Z() * m_Coords[Z_COORD_3D];

		// compute result * inverse quat
		return Set(
			ix * quaternion.W() + iw * (-quaternion.X()) + iy * (-quaternion.Z()) - iz * (-quaternion.Y()),
			iy * quaternion.W() + iw * (-quaternion.Y()) + iz * (-quaternion.X()) - ix * (-quaternion.Z()),
			iz * quaternion.W() + iw * (-quaternion.Z()) + ix * (-quaternion.Y()) - iy * (-quaternion.X())
		);
	}

	Vector3& Vector3::Min(const Vector3& vec)
	{
		/* TODO: is this faster for AABBTree ?
		m_Coords[X_COORD_3D] = (vec.m_Coords[X_COORD_3D] < m_Coords[X_COORD_3D] ? vec.m_Coords[X_COORD_3D] : m_Coords[X_COORD_3D]);
		m_Coords[Y_COORD_3D] = (vec.m_Coords[Y_COORD_3D] < m_Coords[Y_COORD_3D] ? vec.m_Coords[Y_COORD_3D] : m_Coords[Y_COORD_3D]);
		m_Coords[Z_COORD_3D] = (vec.m_Coords[Z_COORD_3D] < m_Coords[Z_COORD_3D] ? vec.m_Coords[Z_COORD_3D] : m_Coords[Z_COORD_3D]);
		*/
		if (vec.m_Coords[X_COORD_3D] < m_Coords[X_COORD_3D])
			m_Coords[X_COORD_3D] = vec.m_Coords[X_COORD_3D];

		if (vec.m_Coords[Y_COORD_3D] < m_Coords[Y_COORD_3D])
			m_Coords[Y_COORD_3D] = vec.m_Coords[Y_COORD_3D];

		if (vec.m_Coords[Z_COORD_3D] < m_Coords[Z_COORD_3D])
			m_Coords[Z_COORD_3D] = vec.m_Coords[Z_COORD_3D];

		return *this;
	}

	Vector3& Vector3::Max(const Vector3& vec)
	{
		/* // TODO: is this faster for AABBTree ?
		m_Coords[X_COORD_3D] = (vec.m_Coords[X_COORD_3D] > m_Coords[X_COORD_3D] ? vec.m_Coords[X_COORD_3D] : m_Coords[X_COORD_3D]);
		m_Coords[Y_COORD_3D] = (vec.m_Coords[Y_COORD_3D] > m_Coords[Y_COORD_3D] ? vec.m_Coords[Y_COORD_3D] : m_Coords[Y_COORD_3D]);
		m_Coords[Z_COORD_3D] = (vec.m_Coords[Z_COORD_3D] > m_Coords[Z_COORD_3D] ? vec.m_Coords[Z_COORD_3D] : m_Coords[Z_COORD_3D]);
		*/
		if (vec.m_Coords[X_COORD_3D] > m_Coords[X_COORD_3D])
			m_Coords[X_COORD_3D] = vec.m_Coords[X_COORD_3D];

		if (vec.m_Coords[Y_COORD_3D] > m_Coords[Y_COORD_3D])
			m_Coords[Y_COORD_3D] = vec.m_Coords[Y_COORD_3D];

		if (vec.m_Coords[Z_COORD_3D] > m_Coords[Z_COORD_3D])
			m_Coords[Z_COORD_3D] = vec.m_Coords[Z_COORD_3D];

		return *this;
	}

	Vector3& Vector3::ApplyAxisAngle(const Vector3& axis, const double& angle)
	{
		if (!axis.IsNormalizedWithTolerance())
		{
			MSG_CHECK(false, "Quaternion::SetFromAxisAngle: rotation axis is not normalized!\n");
			return *this;
		}

		Quaternion quat{axis, angle};
		return ApplyQuaternion(quat);
	}

	Vector3& Vector3::LinearInterpolate(const Vector3& vec, const double& param)
	{
		m_Coords[X_COORD_3D] += (vec.m_Coords[X_COORD_3D] - m_Coords[X_COORD_3D]) * param;
		m_Coords[Y_COORD_3D] += (vec.m_Coords[Y_COORD_3D] - m_Coords[Y_COORD_3D]) * param;
		m_Coords[Z_COORD_3D] += (vec.m_Coords[Z_COORD_3D] - m_Coords[Z_COORD_3D]) * param;
		return *this;
	}

} // Symplektis::GeometryKernel