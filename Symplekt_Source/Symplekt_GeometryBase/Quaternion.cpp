/*! \file Quaternion.cpp
*   \brief Implmentation of the Quaternion class
*
\verbatim
-------------------------------------------------------------------------------
created  : 6.5.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/
#include "Quaternion.h"
#include "Symplekt_UtilityGeneral/ToleranceSettings.h"
#include "Symplekt_UtilityGeneral/NumericUtils.h"

#include "Vector3.h"
#include "Matrix3.h"

namespace Symplektis::GeometryBase
{
	bool Quaternion::operator==(const Quaternion& quat) const
	{
		if (m_Coords[X_COORD_4D] != quat.m_Coords[X_COORD_4D])
			return false;

		if (m_Coords[Y_COORD_4D] != quat.m_Coords[Y_COORD_4D])
			return false;

		if (m_Coords[Z_COORD_4D] != quat.m_Coords[Z_COORD_4D])
			return false;

		return (m_Coords[W_COORD_4D] == quat.m_Coords[W_COORD_4D]);
	}

	bool Quaternion::EqualsWithTolerance(const Quaternion& quat) const
	{
		const double epsilon = Symplektis::Util::GetCoordinateTolerance();

		if (std::fabs(m_Coords[X_COORD_4D] - quat.m_Coords[X_COORD_4D]) > epsilon)
			return false;

		if (std::fabs(m_Coords[Y_COORD_4D] - quat.m_Coords[Y_COORD_4D]) > epsilon)
			return false;

		if (std::fabs(m_Coords[Z_COORD_4D] - quat.m_Coords[Z_COORD_4D]) > epsilon)
			return false;

		return (std::fabs(m_Coords[W_COORD_4D] - quat.m_Coords[W_COORD_4D]) < epsilon);
	}

	bool Quaternion::operator!=(const Quaternion& quat) const
	{
		if (*this == quat)
			return false;
		else
			return true;
	}

	Quaternion& Quaternion::operator*=(const Quaternion& quat)
	{
		const double& qax = m_Coords[X_COORD_4D],      qay = m_Coords[Y_COORD_4D],      qaz = m_Coords[Z_COORD_4D],      qaw = m_Coords[W_COORD_4D];
		const double& qbx = quat.m_Coords[X_COORD_4D], qby = quat.m_Coords[Y_COORD_4D], qbz = quat.m_Coords[Z_COORD_4D], qbw = quat.m_Coords[W_COORD_4D];

		m_Coords[X_COORD_4D] = qax * qbw + qaw * qbx + qay * qbz - qaz * qby;
		m_Coords[Y_COORD_4D] = qay * qbw + qaw * qby + qaz * qbx - qax * qbz;
		m_Coords[Z_COORD_4D] = qaz * qbw + qaw * qbz + qax * qby - qay * qbx;
		m_Coords[W_COORD_4D] = qaw * qbw - qax * qbx - qay * qby - qaz * qbz;

		return *this;
	}

	Quaternion& Quaternion::operator*=(const double& scalar)
	{
		m_Coords[X_COORD_4D] *= scalar;
		m_Coords[Y_COORD_4D] *= scalar;
		m_Coords[Z_COORD_4D] *= scalar;
		m_Coords[W_COORD_4D] *= scalar;
		return *this;
	}

	Quaternion& Quaternion::SetFromAxisAngle(const Vector3& axis, double angle)
	{
		if (!axis.IsNormalizedWithTolerance())
		{
			MSG_CHECK(false, "Symplektis::GeometryReps::Quaternion::SetFromAxisAngle: rotation axis is not normalized!\n");
			return *this;
		}

		double halfAngle = angle / 2.0;
		double sinHalfAngle = sin(halfAngle);

		m_Coords[X_COORD_4D] = axis.X() * sinHalfAngle;
		m_Coords[Y_COORD_4D] = axis.Y() * sinHalfAngle;
		m_Coords[Z_COORD_4D] = axis.Z() * sinHalfAngle;
		m_Coords[W_COORD_4D] = cos(halfAngle);

		return *this;
	}

	Quaternion& Quaternion::SetFromRotationMatrix(const Matrix3& matrix)
	{
		const double m11 = matrix.Elem(MAT3_11), m12 = matrix.Elem(MAT3_12), m13 = matrix.Elem(MAT3_13),
				     m21 = matrix.Elem(MAT3_21), m22 = matrix.Elem(MAT3_22), m23 = matrix.Elem(MAT3_23),
				     m31 = matrix.Elem(MAT3_31), m32 = matrix.Elem(MAT3_32), m33 = matrix.Elem(MAT3_33);

		//
		// column vector orthonormality test
		//
		const double dot12 = m11 * m12 + m21 * m22 + m31 * m32;
		const double dot11 = m11 * m11 + m21 * m21 + m31 * m31;

		const double dot23 = m12 * m13 + m22 * m23 + m32 * m33;
		const double dot22 = m12 * m12 + m22 * m22 + m32 * m32;

		const double dot31 = m13 * m11 + m23 * m21 + m33 * m31;
		const double dot33 = m13 * m13 + m23 * m23 + m33 * m33;

		const double epsilon = Symplektis::Util::GetProductTolerance();

		if (!Symplektis::Util::EqualsWithTolerance(dot12, 0.0, epsilon) || !Symplektis::Util::EqualsWithTolerance(dot11, 1.0, epsilon) ||
			!Symplektis::Util::EqualsWithTolerance(dot23, 0.0, epsilon) || !Symplektis::Util::EqualsWithTolerance(dot22, 1.0, epsilon) ||
			!Symplektis::Util::EqualsWithTolerance(dot31, 0.0, epsilon) || !Symplektis::Util::EqualsWithTolerance(dot33, 1.0, epsilon))
		{
			MSG_CHECK(false, "Quaternion::SetFromRotationMatrix: input matrix is not orthonormal!");
			return *this;
		}

		/// --------------------

		const double trace = m11 + m22 + m33;
		double s = 1.0;

		if (trace > 0.0)
		{
			s = 0.5 / sqrt(trace + 1.0);

			m_Coords[W_COORD_4D] = 0.25 / s;
			m_Coords[X_COORD_4D] = (m32 - m23) * s;
			m_Coords[Y_COORD_4D] = (m13 - m31) * s;
			m_Coords[Z_COORD_4D] = (m21 - m12) * s;
		}
		else if (m11 > m22 && m11 > m33)
		{
			s = 2.0 * sqrt(1.0 + m11 - m22 - m33);

			m_Coords[W_COORD_4D] = (m32 - m23) / s;
			m_Coords[X_COORD_4D] = 0.25 * s;
			m_Coords[Y_COORD_4D] = (m12 + m21) / s;
			m_Coords[Z_COORD_4D] = (m13 + m31) / s;
		}
		else if (m22 > m33)
		{
			s = 2.0 * sqrt(1.0 + m22 - m11 - m33);

			m_Coords[W_COORD_4D] = (m13 - m31) / s;
			m_Coords[X_COORD_4D] = (m12 + m21) / s;
			m_Coords[Y_COORD_4D] = 0.25 * s;
			m_Coords[Z_COORD_4D] = (m23 + m32) / s;
		}
		else
		{
			s = 2.0 * sqrt(1.0 + m33 - m11 - m22);

			m_Coords[W_COORD_4D] = (m21 - m12) / s;
			m_Coords[X_COORD_4D] = (m13 + m31) / s;
			m_Coords[Y_COORD_4D] = (m23 + m32) / s;
			m_Coords[Z_COORD_4D] = 0.25 * s;
		}

		return *this;
	}

	double Quaternion::GetLength() const
	{
		return sqrt(m_Coords[X_COORD_4D] * m_Coords[X_COORD_4D] +
					m_Coords[Y_COORD_4D] * m_Coords[Y_COORD_4D] + 
					m_Coords[Z_COORD_4D] * m_Coords[Z_COORD_4D] + 
					m_Coords[W_COORD_4D] * m_Coords[W_COORD_4D]);
	}

	double Quaternion::GetLengthSquared() const
	{
		return (m_Coords[X_COORD_4D] * m_Coords[X_COORD_4D] +
				m_Coords[Y_COORD_4D] * m_Coords[Y_COORD_4D] +
				m_Coords[Z_COORD_4D] * m_Coords[Z_COORD_4D] +
				m_Coords[W_COORD_4D] * m_Coords[W_COORD_4D]);
	}

	Quaternion& Quaternion::Normalize()
	{
		if (IsZero())
		{
			MSG_CHECK(false, "Symplektis::GeometryReps::Quaternion::SetFromAxisAngle: attempting to normalize a zero quaternion!\n");
			return *this;
		}

		double oldLength = GetLength();

		m_Coords[X_COORD_4D] /= oldLength;
		m_Coords[Y_COORD_4D] /= oldLength;
		m_Coords[Z_COORD_4D] /= oldLength;
		m_Coords[W_COORD_4D] /= oldLength;

		return *this;
	}
	
	double Quaternion::AngleTo(const Quaternion& quat) const
	{
		return 2.0 * acos(std::fabs(Symplektis::Util::Clamp(DotProduct(quat), -1.0, 1.0)));
	}

} // Symplektis::GeometryBase