/*! \file Matrix4.cpp
*   \brief Implmentation of the 4x4 matrix class
*
\verbatim
-------------------------------------------------------------------------------
created  : 6.5.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/

#include "Matrix4.h"

#include "Symplekt_UtilityGeneral/ToleranceSettings.h"
#include "Symplekt_UtilityGeneral/NumericUtils.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix3.h"

namespace Symplektis::GeometryBase
{
    bool Matrix4::operator==(const Matrix4& mat) const
    {
        if (m_Coords[MAT4_11] != mat.m_Coords[MAT4_11])
            return false;
        if (m_Coords[MAT4_12] != mat.m_Coords[MAT4_12])
            return false;
        if (m_Coords[MAT4_13] != mat.m_Coords[MAT4_13])
            return false;
        if (m_Coords[MAT4_14] != mat.m_Coords[MAT4_14])
            return false;

        if (m_Coords[MAT4_21] != mat.m_Coords[MAT4_21])
            return false;
        if (m_Coords[MAT4_22] != mat.m_Coords[MAT4_22])
            return false;
        if (m_Coords[MAT4_23] != mat.m_Coords[MAT4_23])
            return false;
        if (m_Coords[MAT4_24] != mat.m_Coords[MAT4_24])
            return false;

        if (m_Coords[MAT4_31] != mat.m_Coords[MAT4_31])
            return false;
        if (m_Coords[MAT4_32] != mat.m_Coords[MAT4_32])
            return false;
        if (m_Coords[MAT4_33] != mat.m_Coords[MAT4_33])
            return false;
        if (m_Coords[MAT4_34] != mat.m_Coords[MAT4_34])
            return false;

        if (m_Coords[MAT4_41] != mat.m_Coords[MAT4_41])
            return false;
        if (m_Coords[MAT4_42] != mat.m_Coords[MAT4_42])
            return false;
        if (m_Coords[MAT4_43] != mat.m_Coords[MAT4_43])
            return false;

        return (m_Coords[MAT4_44] == mat.m_Coords[MAT4_44]);
    }

    bool Matrix4::EqualsWithTolerance(const Matrix4& mat) const
    {
        const double epsilon = Symplektis::Util::GetCoordinateTolerance();

        if (!Symplektis::Util::EqualsWithTolerance(m_Coords[MAT4_11], mat.m_Coords[MAT4_11], epsilon))
            return false;
        if (!Symplektis::Util::EqualsWithTolerance(m_Coords[MAT4_12], mat.m_Coords[MAT4_12], epsilon))
            return false;
        if (!Symplektis::Util::EqualsWithTolerance(m_Coords[MAT4_13], mat.m_Coords[MAT4_13], epsilon))
            return false;
        if (!Symplektis::Util::EqualsWithTolerance(m_Coords[MAT4_14], mat.m_Coords[MAT4_14], epsilon))
            return false;

        if (!Symplektis::Util::EqualsWithTolerance(m_Coords[MAT4_21], mat.m_Coords[MAT4_21], epsilon))
            return false;
        if (!Symplektis::Util::EqualsWithTolerance(m_Coords[MAT4_22], mat.m_Coords[MAT4_22], epsilon))
            return false;
        if (!Symplektis::Util::EqualsWithTolerance(m_Coords[MAT4_23], mat.m_Coords[MAT4_23], epsilon))
            return false;
        if (!Symplektis::Util::EqualsWithTolerance(m_Coords[MAT4_24], mat.m_Coords[MAT4_24], epsilon))
            return false;

        if (!Symplektis::Util::EqualsWithTolerance(m_Coords[MAT4_31], mat.m_Coords[MAT4_31], epsilon))
            return false;
        if (!Symplektis::Util::EqualsWithTolerance(m_Coords[MAT4_32], mat.m_Coords[MAT4_32], epsilon))
            return false;
        if (!Symplektis::Util::EqualsWithTolerance(m_Coords[MAT4_33], mat.m_Coords[MAT4_33], epsilon))
            return false;
        if (!Symplektis::Util::EqualsWithTolerance(m_Coords[MAT4_34], mat.m_Coords[MAT4_34], epsilon))
            return false;

        if (!Symplektis::Util::EqualsWithTolerance(m_Coords[MAT4_41], mat.m_Coords[MAT4_41], epsilon))
            return false;
        if (!Symplektis::Util::EqualsWithTolerance(m_Coords[MAT4_42], mat.m_Coords[MAT4_42], epsilon))
            return false;
        if (!Symplektis::Util::EqualsWithTolerance(m_Coords[MAT4_43], mat.m_Coords[MAT4_43], epsilon))
            return false;

        return (Symplektis::Util::EqualsWithTolerance(m_Coords[MAT4_44], mat.m_Coords[MAT4_44], epsilon));
    }

    bool Matrix4::operator!=(const Matrix4& mat) const
    {
        if (m_Coords[MAT4_11] != mat.m_Coords[MAT4_11])
            return true;
        if (m_Coords[MAT4_12] != mat.m_Coords[MAT4_12])
            return true;
        if (m_Coords[MAT4_13] != mat.m_Coords[MAT4_13])
            return true;
        if (m_Coords[MAT4_14] != mat.m_Coords[MAT4_14])
            return true;

        if (m_Coords[MAT4_21] != mat.m_Coords[MAT4_21])
            return true;
        if (m_Coords[MAT4_22] != mat.m_Coords[MAT4_22])
            return true;
        if (m_Coords[MAT4_23] != mat.m_Coords[MAT4_23])
            return true;
        if (m_Coords[MAT4_24] != mat.m_Coords[MAT4_24])
            return true;

        if (m_Coords[MAT4_31] != mat.m_Coords[MAT4_31])
            return true;
        if (m_Coords[MAT4_32] != mat.m_Coords[MAT4_32])
            return true;
        if (m_Coords[MAT4_33] != mat.m_Coords[MAT4_33])
            return true;
        if (m_Coords[MAT4_34] != mat.m_Coords[MAT4_34])
            return true;

        if (m_Coords[MAT4_41] != mat.m_Coords[MAT4_41])
            return true;
        if (m_Coords[MAT4_42] != mat.m_Coords[MAT4_42])
            return true;
        if (m_Coords[MAT4_43] != mat.m_Coords[MAT4_43])
            return true;

        return (m_Coords[MAT4_44] != mat.m_Coords[MAT4_44]);
    }

    Matrix4 Matrix4::operator+(const Matrix4& mat) const
    {
        Matrix4 result(*this);
        result += mat;
        return result;
    }

    Matrix4 Matrix4::operator-(const Matrix4& mat) const
    {
        Matrix4 result(*this);
        result -= mat;
        return result;
    }


    Matrix4& Matrix4::Multiply(const Matrix4& mat)
    {
        double result[GEOMETRY_DIMENSION_4x4] = {
            m_Coords[MAT4_11] * mat.m_Coords[MAT4_11] + m_Coords[MAT4_12] * mat.m_Coords[MAT4_21] + m_Coords[MAT4_13] * mat.m_Coords[MAT4_31] + m_Coords[MAT4_14] * mat.m_Coords[MAT4_41],
            m_Coords[MAT4_11] * mat.m_Coords[MAT4_12] + m_Coords[MAT4_12] * mat.m_Coords[MAT4_22] + m_Coords[MAT4_13] * mat.m_Coords[MAT4_32] + m_Coords[MAT4_14] * mat.m_Coords[MAT4_42],
            m_Coords[MAT4_11] * mat.m_Coords[MAT4_13] + m_Coords[MAT4_12] * mat.m_Coords[MAT4_23] + m_Coords[MAT4_13] * mat.m_Coords[MAT4_33] + m_Coords[MAT4_14] * mat.m_Coords[MAT4_43],
            m_Coords[MAT4_11] * mat.m_Coords[MAT4_14] + m_Coords[MAT4_12] * mat.m_Coords[MAT4_24] + m_Coords[MAT4_13] * mat.m_Coords[MAT4_34] + m_Coords[MAT4_14] * mat.m_Coords[MAT4_44],

            m_Coords[MAT4_21] * mat.m_Coords[MAT4_11] + m_Coords[MAT4_22] * mat.m_Coords[MAT4_21] + m_Coords[MAT4_23] * mat.m_Coords[MAT4_31] + m_Coords[MAT4_24] * mat.m_Coords[MAT4_41],
            m_Coords[MAT4_21] * mat.m_Coords[MAT4_12] + m_Coords[MAT4_22] * mat.m_Coords[MAT4_22] + m_Coords[MAT4_23] * mat.m_Coords[MAT4_32] + m_Coords[MAT4_24] * mat.m_Coords[MAT4_42],
            m_Coords[MAT4_21] * mat.m_Coords[MAT4_13] + m_Coords[MAT4_22] * mat.m_Coords[MAT4_23] + m_Coords[MAT4_23] * mat.m_Coords[MAT4_33] + m_Coords[MAT4_24] * mat.m_Coords[MAT4_43],
            m_Coords[MAT4_21] * mat.m_Coords[MAT4_14] + m_Coords[MAT4_22] * mat.m_Coords[MAT4_24] + m_Coords[MAT4_23] * mat.m_Coords[MAT4_34] + m_Coords[MAT4_24] * mat.m_Coords[MAT4_44],

            m_Coords[MAT4_31] * mat.m_Coords[MAT4_11] + m_Coords[MAT4_32] * mat.m_Coords[MAT4_21] + m_Coords[MAT4_33] * mat.m_Coords[MAT4_31] + m_Coords[MAT4_34] * mat.m_Coords[MAT4_41],
            m_Coords[MAT4_31] * mat.m_Coords[MAT4_12] + m_Coords[MAT4_32] * mat.m_Coords[MAT4_22] + m_Coords[MAT4_33] * mat.m_Coords[MAT4_32] + m_Coords[MAT4_34] * mat.m_Coords[MAT4_42],
            m_Coords[MAT4_31] * mat.m_Coords[MAT4_13] + m_Coords[MAT4_32] * mat.m_Coords[MAT4_23] + m_Coords[MAT4_33] * mat.m_Coords[MAT4_33] + m_Coords[MAT4_34] * mat.m_Coords[MAT4_43],
            m_Coords[MAT4_31] * mat.m_Coords[MAT4_14] + m_Coords[MAT4_32] * mat.m_Coords[MAT4_24] + m_Coords[MAT4_33] * mat.m_Coords[MAT4_34] + m_Coords[MAT4_34] * mat.m_Coords[MAT4_44],

            m_Coords[MAT4_41] * mat.m_Coords[MAT4_11] + m_Coords[MAT4_42] * mat.m_Coords[MAT4_21] + m_Coords[MAT4_43] * mat.m_Coords[MAT4_31] + m_Coords[MAT4_44] * mat.m_Coords[MAT4_41],
            m_Coords[MAT4_41] * mat.m_Coords[MAT4_12] + m_Coords[MAT4_42] * mat.m_Coords[MAT4_22] + m_Coords[MAT4_43] * mat.m_Coords[MAT4_32] + m_Coords[MAT4_44] * mat.m_Coords[MAT4_42],
            m_Coords[MAT4_41] * mat.m_Coords[MAT4_13] + m_Coords[MAT4_42] * mat.m_Coords[MAT4_23] + m_Coords[MAT4_43] * mat.m_Coords[MAT4_33] + m_Coords[MAT4_44] * mat.m_Coords[MAT4_43],
            m_Coords[MAT4_41] * mat.m_Coords[MAT4_14] + m_Coords[MAT4_42] * mat.m_Coords[MAT4_24] + m_Coords[MAT4_43] * mat.m_Coords[MAT4_34] + m_Coords[MAT4_44] * mat.m_Coords[MAT4_44]
        };
        memcpy(m_Coords, result, GEOMETRY_DIMENSION_4x4 * sizeof(double));

        return *this;
    }

    Matrix4& Matrix4::Premultiply(const Matrix4& mat)
    {
        double result[GEOMETRY_DIMENSION_4x4] = {
            mat.m_Coords[MAT4_11] * m_Coords[MAT4_11] + mat.m_Coords[MAT4_12] * m_Coords[MAT4_21] + mat.m_Coords[MAT4_13] * m_Coords[MAT4_31] + mat.m_Coords[MAT4_14] * m_Coords[MAT4_41],
            mat.m_Coords[MAT4_11] * m_Coords[MAT4_12] + mat.m_Coords[MAT4_12] * m_Coords[MAT4_22] + mat.m_Coords[MAT4_13] * m_Coords[MAT4_32] + mat.m_Coords[MAT4_14] * m_Coords[MAT4_42],
            mat.m_Coords[MAT4_11] * m_Coords[MAT4_13] + mat.m_Coords[MAT4_12] * m_Coords[MAT4_23] + mat.m_Coords[MAT4_13] * m_Coords[MAT4_33] + mat.m_Coords[MAT4_14] * m_Coords[MAT4_43],
            mat.m_Coords[MAT4_11] * m_Coords[MAT4_14] + mat.m_Coords[MAT4_12] * m_Coords[MAT4_24] + mat.m_Coords[MAT4_13] * m_Coords[MAT4_34] + mat.m_Coords[MAT4_14] * m_Coords[MAT4_44],

            mat.m_Coords[MAT4_21] * m_Coords[MAT4_11] + mat.m_Coords[MAT4_22] * m_Coords[MAT4_21] + mat.m_Coords[MAT4_23] * m_Coords[MAT4_31] + mat.m_Coords[MAT4_24] * m_Coords[MAT4_41],
            mat.m_Coords[MAT4_21] * m_Coords[MAT4_12] + mat.m_Coords[MAT4_22] * m_Coords[MAT4_22] + mat.m_Coords[MAT4_23] * m_Coords[MAT4_32] + mat.m_Coords[MAT4_24] * m_Coords[MAT4_42],
            mat.m_Coords[MAT4_21] * m_Coords[MAT4_13] + mat.m_Coords[MAT4_22] * m_Coords[MAT4_23] + mat.m_Coords[MAT4_23] * m_Coords[MAT4_33] + mat.m_Coords[MAT4_24] * m_Coords[MAT4_43],
            mat.m_Coords[MAT4_21] * m_Coords[MAT4_14] + mat.m_Coords[MAT4_22] * m_Coords[MAT4_24] + mat.m_Coords[MAT4_23] * m_Coords[MAT4_34] + mat.m_Coords[MAT4_24] * m_Coords[MAT4_44],

            mat.m_Coords[MAT4_31] * m_Coords[MAT4_11] + mat.m_Coords[MAT4_32] * m_Coords[MAT4_21] + mat.m_Coords[MAT4_33] * m_Coords[MAT4_31] + mat.m_Coords[MAT4_34] * m_Coords[MAT4_41],
            mat.m_Coords[MAT4_31] * m_Coords[MAT4_12] + mat.m_Coords[MAT4_32] * m_Coords[MAT4_22] + mat.m_Coords[MAT4_33] * m_Coords[MAT4_32] + mat.m_Coords[MAT4_34] * m_Coords[MAT4_42],
            mat.m_Coords[MAT4_31] * m_Coords[MAT4_13] + mat.m_Coords[MAT4_32] * m_Coords[MAT4_23] + mat.m_Coords[MAT4_33] * m_Coords[MAT4_33] + mat.m_Coords[MAT4_34] * m_Coords[MAT4_43],
            mat.m_Coords[MAT4_31] * m_Coords[MAT4_14] + mat.m_Coords[MAT4_32] * m_Coords[MAT4_24] + mat.m_Coords[MAT4_33] * m_Coords[MAT4_34] + mat.m_Coords[MAT4_34] * m_Coords[MAT4_44],

            mat.m_Coords[MAT4_41] * m_Coords[MAT4_11] + mat.m_Coords[MAT4_42] * m_Coords[MAT4_21] + mat.m_Coords[MAT4_43] * m_Coords[MAT4_31] + mat.m_Coords[MAT4_44] * m_Coords[MAT4_41],
            mat.m_Coords[MAT4_41] * m_Coords[MAT4_12] + mat.m_Coords[MAT4_42] * m_Coords[MAT4_22] + mat.m_Coords[MAT4_43] * m_Coords[MAT4_32] + mat.m_Coords[MAT4_44] * m_Coords[MAT4_42],
            mat.m_Coords[MAT4_41] * m_Coords[MAT4_13] + mat.m_Coords[MAT4_42] * m_Coords[MAT4_23] + mat.m_Coords[MAT4_43] * m_Coords[MAT4_33] + mat.m_Coords[MAT4_44] * m_Coords[MAT4_43],
            mat.m_Coords[MAT4_41] * m_Coords[MAT4_14] + mat.m_Coords[MAT4_42] * m_Coords[MAT4_24] + mat.m_Coords[MAT4_43] * m_Coords[MAT4_34] + mat.m_Coords[MAT4_44] * m_Coords[MAT4_44]
        };
        memcpy(m_Coords, result, GEOMETRY_DIMENSION_4x4 * sizeof(double));

        return *this;
    }

    Matrix4& Matrix4::operator*=(const Matrix4& mat)
    {
        Multiply(mat);
        return *this;
    }

    Matrix4 Matrix4::operator*(const Matrix4& mat) const
    {
        Matrix4 result(*this);
        result *= mat;
        return result;
    }


    Matrix4& Matrix4::Multiply(const double& scalar)
    {
        m_Coords[MAT4_11] *= scalar; m_Coords[MAT4_12] *= scalar; m_Coords[MAT4_13] *= scalar; m_Coords[MAT4_14] *= scalar;
        m_Coords[MAT4_21] *= scalar; m_Coords[MAT4_22] *= scalar; m_Coords[MAT4_23] *= scalar; m_Coords[MAT4_24] *= scalar;
        m_Coords[MAT4_31] *= scalar; m_Coords[MAT4_32] *= scalar; m_Coords[MAT4_33] *= scalar; m_Coords[MAT4_34] *= scalar;
        m_Coords[MAT4_41] *= scalar; m_Coords[MAT4_42] *= scalar; m_Coords[MAT4_43] *= scalar; m_Coords[MAT4_44] *= scalar;
        return *this;
    }

    Matrix4& Matrix4::operator*(const double& scalar)
    {
        Multiply(scalar);
        return *this;
    }

    Matrix4& Matrix4::operator*=(const double& scalar)
    {
        Multiply(scalar);
        return *this;
    }

    Matrix4 Matrix4::operator*(const double& scalar) const
    {
        Matrix4 result(*this);
        result *= scalar;
        return result;
    }

    Matrix4& Matrix4::SetToIdentity()
    {
        return Set(
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
        );
    }

    Matrix4& Matrix4::SetToScale(const double& sx, const double& sy, const double& sz)
    {
        return Set(
            sx,  0.0, 0.0, 0.0,
            0.0, sy,  0.0, 0.0,
            0.0, 0.0, sz,  0.0,
            0.0, 0.0, 0.0, 1.0
        );
    }

    Matrix4& Matrix4::SetToScale(const Vector3& scaleVect)
    {
        return Set(
            scaleVect.X(), 0.0,           0.0,           0.0,
            0.0,           scaleVect.Y(), 0.0,           0.0,
            0.0,           0.0,           scaleVect.Z(), 0.0,
            0.0,           0.0,           0.0,           1.0
        );
    }

    Matrix4& Matrix4::SetToRotationAboutAxis(const double& ax, const double& ay, const double& az, const double& angle)
    {
        const double axisNormSq = ax * ax + ay * ay + az * az;
        if (!Symplektis::Util::EqualsWithTolerance(axisNormSq, 1.0, Symplektis::Util::GetProductTolerance()))
        {
            MSG_CHECK(false, "Matrix4::SetToRotationAboutAxis: Attempting to use a non-normalized rotation axis!\n");
            return *this;
        }
        const double c = cos(angle), s = sin(angle);
        const double t = 1 - c;
        const double tx = t * ax, ty = t * ay;

        return Set(
            tx * ax + c,        tx * ay - s * az,   tx * az + s * ay,  0.0,
            tx * ay + s * az,   ty * ay + c,        ty * az - s * ax,  0.0,
            tx * az - s * ay,   ty * az + s * ax,   t * az * az + c,   0.0,
            0.0,                0.0,                0.0,               1.0
        );
    }

    Matrix4& Matrix4::SetToRotationAboutAxis(const Vector3& axis, const double& angle)
    {
        if (!axis.IsNormalizedWithTolerance())
        {
            MSG_CHECK(false, "Matrix4::SetToRotationAboutAxis: Attempting to use a non-normalized rotation axis!\n");
            return *this;
        }
        const double c = cos(angle), s = sin(angle);
        const double t = 1 - c;
        const double ax = axis.X(), ay = axis.Y(), az = axis.Z();
        const double tx = t * ax, ty = t * ay;

        return Set(
            tx * ax + c,       tx * ay - s * az,   tx * az + s * ay,  0.0,
            tx * ay + s * az,  ty * ay + c,        ty * az - s * ax,  0.0,
            tx * az - s * ay,  ty * az + s * ax,   t * az * az + c,   0.0,
            0.0,               0.0,                0.0,               1.0
        );
    }

    bool Matrix4::IsIdentity() const
    {
        if (m_Coords[MAT4_11] != 1.0)
            return false;
        if (m_Coords[MAT4_12] != 0.0)
            return false;
        if (m_Coords[MAT4_13] != 0.0)
            return false;
        if (m_Coords[MAT4_14] != 0.0)
            return false;

        if (m_Coords[MAT4_21] != 0.0)
            return false;
        if (m_Coords[MAT4_22] != 1.0)
            return false;
        if (m_Coords[MAT4_23] != 0.0)
            return false;
        if (m_Coords[MAT4_24] != 0.0)
            return false;

        if (m_Coords[MAT4_31] != 0.0)
            return false;
        if (m_Coords[MAT4_32] != 0.0)
            return false;
        if (m_Coords[MAT4_33] != 1.0)
            return false;
        if (m_Coords[MAT4_34] != 0.0)
            return false;

        if (m_Coords[MAT4_41] != 0.0)
            return false;
        if (m_Coords[MAT4_42] != 0.0)
            return false;
        if (m_Coords[MAT4_43] != 0.0)
            return false;

        return (m_Coords[MAT4_44] == 1.0);
    }

    Matrix4& Matrix4::Transpose()
    {
        double result[GEOMETRY_DIMENSION_4x4] = {
            m_Coords[MAT4_11], m_Coords[MAT4_21], m_Coords[MAT4_31], m_Coords[MAT4_41],
            m_Coords[MAT4_12], m_Coords[MAT4_22], m_Coords[MAT4_32], m_Coords[MAT4_42],
            m_Coords[MAT4_13], m_Coords[MAT4_23], m_Coords[MAT4_33], m_Coords[MAT4_43],
            m_Coords[MAT4_14], m_Coords[MAT4_24], m_Coords[MAT4_34], m_Coords[MAT4_44]
        };
        memcpy(m_Coords, result, GEOMETRY_DIMENSION_4x4 * sizeof(double));
        return *this;
    }

    Matrix4 Matrix4::Transpose() const
    {
        Matrix4 result(*this);
        return result.Transpose();
    }

    double Matrix4::Determinant() const
    {
        return (
            m_Coords[MAT4_14] * m_Coords[MAT4_23] * m_Coords[MAT4_32] * m_Coords[MAT4_41] - m_Coords[MAT4_13] * m_Coords[MAT4_24] * m_Coords[MAT4_32] * m_Coords[MAT4_41] - m_Coords[MAT4_14] * m_Coords[MAT4_22] * m_Coords[MAT4_33] * m_Coords[MAT4_41] + m_Coords[MAT4_12] * m_Coords[MAT4_24] * m_Coords[MAT4_33] * m_Coords[MAT4_41] +
            m_Coords[MAT4_13] * m_Coords[MAT4_22] * m_Coords[MAT4_34] * m_Coords[MAT4_41] - m_Coords[MAT4_12] * m_Coords[MAT4_23] * m_Coords[MAT4_34] * m_Coords[MAT4_41] - m_Coords[MAT4_14] * m_Coords[MAT4_23] * m_Coords[MAT4_31] * m_Coords[MAT4_42] + m_Coords[MAT4_13] * m_Coords[MAT4_24] * m_Coords[MAT4_31] * m_Coords[MAT4_42] +
            m_Coords[MAT4_14] * m_Coords[MAT4_21] * m_Coords[MAT4_33] * m_Coords[MAT4_42] - m_Coords[MAT4_11] * m_Coords[MAT4_24] * m_Coords[MAT4_33] * m_Coords[MAT4_42] - m_Coords[MAT4_13] * m_Coords[MAT4_21] * m_Coords[MAT4_34] * m_Coords[MAT4_42] + m_Coords[MAT4_11] * m_Coords[MAT4_23] * m_Coords[MAT4_34] * m_Coords[MAT4_42] +
            m_Coords[MAT4_14] * m_Coords[MAT4_22] * m_Coords[MAT4_31] * m_Coords[MAT4_43] - m_Coords[MAT4_12] * m_Coords[MAT4_24] * m_Coords[MAT4_31] * m_Coords[MAT4_43] - m_Coords[MAT4_14] * m_Coords[MAT4_21] * m_Coords[MAT4_32] * m_Coords[MAT4_43] + m_Coords[MAT4_11] * m_Coords[MAT4_24] * m_Coords[MAT4_32] * m_Coords[MAT4_43] +
            m_Coords[MAT4_12] * m_Coords[MAT4_21] * m_Coords[MAT4_34] * m_Coords[MAT4_43] - m_Coords[MAT4_11] * m_Coords[MAT4_22] * m_Coords[MAT4_34] * m_Coords[MAT4_43] - m_Coords[MAT4_13] * m_Coords[MAT4_22] * m_Coords[MAT4_31] * m_Coords[MAT4_44] + m_Coords[MAT4_12] * m_Coords[MAT4_23] * m_Coords[MAT4_31] * m_Coords[MAT4_44] +
            m_Coords[MAT4_13] * m_Coords[MAT4_21] * m_Coords[MAT4_32] * m_Coords[MAT4_44] - m_Coords[MAT4_11] * m_Coords[MAT4_23] * m_Coords[MAT4_32] * m_Coords[MAT4_44] - m_Coords[MAT4_12] * m_Coords[MAT4_21] * m_Coords[MAT4_33] * m_Coords[MAT4_44] + m_Coords[MAT4_11] * m_Coords[MAT4_22] * m_Coords[MAT4_33] * m_Coords[MAT4_44]
        );
    }

    Matrix4& Matrix4::Inverse()
    {
        const double det = Determinant();
        const double epsilon = Symplektis::Util::GetProductTolerance();
        if (std::fabs(det) < epsilon)
        {
            MSG_CHECK(false, "Matrix4::Inverse: det == 0! Attempting to invert a singular 4x4 matrix!");
            return *this;
        }

        double result[GEOMETRY_DIMENSION_4x4] = {
            m_Coords[MAT4_23] * m_Coords[MAT4_34] * m_Coords[MAT4_42] - m_Coords[MAT4_24] * m_Coords[MAT4_33] * m_Coords[MAT4_42] + m_Coords[MAT4_24] * m_Coords[MAT4_32] * m_Coords[MAT4_43] - m_Coords[MAT4_22] * m_Coords[MAT4_34] * m_Coords[MAT4_43] - m_Coords[MAT4_23] * m_Coords[MAT4_32] * m_Coords[MAT4_44] + m_Coords[MAT4_22] * m_Coords[MAT4_33] * m_Coords[MAT4_44],
            m_Coords[MAT4_14] * m_Coords[MAT4_33] * m_Coords[MAT4_42] - m_Coords[MAT4_13] * m_Coords[MAT4_34] * m_Coords[MAT4_42] - m_Coords[MAT4_14] * m_Coords[MAT4_32] * m_Coords[MAT4_43] + m_Coords[MAT4_12] * m_Coords[MAT4_34] * m_Coords[MAT4_43] + m_Coords[MAT4_13] * m_Coords[MAT4_32] * m_Coords[MAT4_44] - m_Coords[MAT4_12] * m_Coords[MAT4_33] * m_Coords[MAT4_44],
            m_Coords[MAT4_13] * m_Coords[MAT4_24] * m_Coords[MAT4_42] - m_Coords[MAT4_14] * m_Coords[MAT4_23] * m_Coords[MAT4_42] + m_Coords[MAT4_14] * m_Coords[MAT4_22] * m_Coords[MAT4_43] - m_Coords[MAT4_12] * m_Coords[MAT4_24] * m_Coords[MAT4_43] - m_Coords[MAT4_13] * m_Coords[MAT4_22] * m_Coords[MAT4_44] + m_Coords[MAT4_12] * m_Coords[MAT4_23] * m_Coords[MAT4_44],
            m_Coords[MAT4_14] * m_Coords[MAT4_23] * m_Coords[MAT4_32] - m_Coords[MAT4_13] * m_Coords[MAT4_24] * m_Coords[MAT4_32] - m_Coords[MAT4_14] * m_Coords[MAT4_22] * m_Coords[MAT4_33] + m_Coords[MAT4_12] * m_Coords[MAT4_24] * m_Coords[MAT4_33] + m_Coords[MAT4_13] * m_Coords[MAT4_22] * m_Coords[MAT4_34] - m_Coords[MAT4_12] * m_Coords[MAT4_23] * m_Coords[MAT4_34],

            m_Coords[MAT4_24] * m_Coords[MAT4_33] * m_Coords[MAT4_41] - m_Coords[MAT4_23] * m_Coords[MAT4_34] * m_Coords[MAT4_41] - m_Coords[MAT4_24] * m_Coords[MAT4_31] * m_Coords[MAT4_43] + m_Coords[MAT4_21] * m_Coords[MAT4_34] * m_Coords[MAT4_43] + m_Coords[MAT4_23] * m_Coords[MAT4_31] * m_Coords[MAT4_44] - m_Coords[MAT4_21] * m_Coords[MAT4_33] * m_Coords[MAT4_44],
            m_Coords[MAT4_13] * m_Coords[MAT4_34] * m_Coords[MAT4_41] - m_Coords[MAT4_14] * m_Coords[MAT4_33] * m_Coords[MAT4_41] + m_Coords[MAT4_14] * m_Coords[MAT4_31] * m_Coords[MAT4_43] - m_Coords[MAT4_11] * m_Coords[MAT4_34] * m_Coords[MAT4_43] - m_Coords[MAT4_13] * m_Coords[MAT4_31] * m_Coords[MAT4_44] + m_Coords[MAT4_11] * m_Coords[MAT4_33] * m_Coords[MAT4_44],
            m_Coords[MAT4_14] * m_Coords[MAT4_23] * m_Coords[MAT4_41] - m_Coords[MAT4_13] * m_Coords[MAT4_24] * m_Coords[MAT4_41] - m_Coords[MAT4_14] * m_Coords[MAT4_21] * m_Coords[MAT4_43] + m_Coords[MAT4_11] * m_Coords[MAT4_24] * m_Coords[MAT4_43] + m_Coords[MAT4_13] * m_Coords[MAT4_21] * m_Coords[MAT4_44] - m_Coords[MAT4_11] * m_Coords[MAT4_23] * m_Coords[MAT4_44],
            m_Coords[MAT4_13] * m_Coords[MAT4_24] * m_Coords[MAT4_31] - m_Coords[MAT4_14] * m_Coords[MAT4_23] * m_Coords[MAT4_31] + m_Coords[MAT4_14] * m_Coords[MAT4_21] * m_Coords[MAT4_33] - m_Coords[MAT4_11] * m_Coords[MAT4_24] * m_Coords[MAT4_33] - m_Coords[MAT4_13] * m_Coords[MAT4_21] * m_Coords[MAT4_34] + m_Coords[MAT4_11] * m_Coords[MAT4_23] * m_Coords[MAT4_34],

            m_Coords[MAT4_22] * m_Coords[MAT4_34] * m_Coords[MAT4_41] - m_Coords[MAT4_24] * m_Coords[MAT4_32] * m_Coords[MAT4_41] + m_Coords[MAT4_24] * m_Coords[MAT4_31] * m_Coords[MAT4_42] - m_Coords[MAT4_21] * m_Coords[MAT4_34] * m_Coords[MAT4_42] - m_Coords[MAT4_22] * m_Coords[MAT4_31] * m_Coords[MAT4_44] + m_Coords[MAT4_21] * m_Coords[MAT4_32] * m_Coords[MAT4_44],
            m_Coords[MAT4_14] * m_Coords[MAT4_32] * m_Coords[MAT4_41] - m_Coords[MAT4_12] * m_Coords[MAT4_34] * m_Coords[MAT4_41] - m_Coords[MAT4_14] * m_Coords[MAT4_31] * m_Coords[MAT4_42] + m_Coords[MAT4_11] * m_Coords[MAT4_34] * m_Coords[MAT4_42] + m_Coords[MAT4_12] * m_Coords[MAT4_31] * m_Coords[MAT4_44] - m_Coords[MAT4_11] * m_Coords[MAT4_32] * m_Coords[MAT4_44],
            m_Coords[MAT4_12] * m_Coords[MAT4_24] * m_Coords[MAT4_41] - m_Coords[MAT4_14] * m_Coords[MAT4_22] * m_Coords[MAT4_41] + m_Coords[MAT4_14] * m_Coords[MAT4_21] * m_Coords[MAT4_42] - m_Coords[MAT4_11] * m_Coords[MAT4_24] * m_Coords[MAT4_42] - m_Coords[MAT4_12] * m_Coords[MAT4_21] * m_Coords[MAT4_44] + m_Coords[MAT4_11] * m_Coords[MAT4_22] * m_Coords[MAT4_44],
            m_Coords[MAT4_14] * m_Coords[MAT4_22] * m_Coords[MAT4_31] - m_Coords[MAT4_12] * m_Coords[MAT4_24] * m_Coords[MAT4_31] - m_Coords[MAT4_14] * m_Coords[MAT4_21] * m_Coords[MAT4_32] + m_Coords[MAT4_11] * m_Coords[MAT4_24] * m_Coords[MAT4_32] + m_Coords[MAT4_12] * m_Coords[MAT4_21] * m_Coords[MAT4_34] - m_Coords[MAT4_11] * m_Coords[MAT4_22] * m_Coords[MAT4_34],

            m_Coords[MAT4_23] * m_Coords[MAT4_32] * m_Coords[MAT4_41] - m_Coords[MAT4_22] * m_Coords[MAT4_33] * m_Coords[MAT4_41] - m_Coords[MAT4_23] * m_Coords[MAT4_31] * m_Coords[MAT4_42] + m_Coords[MAT4_21] * m_Coords[MAT4_33] * m_Coords[MAT4_42] + m_Coords[MAT4_22] * m_Coords[MAT4_31] * m_Coords[MAT4_43] - m_Coords[MAT4_21] * m_Coords[MAT4_32] * m_Coords[MAT4_43],
            m_Coords[MAT4_12] * m_Coords[MAT4_33] * m_Coords[MAT4_41] - m_Coords[MAT4_13] * m_Coords[MAT4_32] * m_Coords[MAT4_41] + m_Coords[MAT4_13] * m_Coords[MAT4_31] * m_Coords[MAT4_42] - m_Coords[MAT4_11] * m_Coords[MAT4_33] * m_Coords[MAT4_42] - m_Coords[MAT4_12] * m_Coords[MAT4_31] * m_Coords[MAT4_43] + m_Coords[MAT4_11] * m_Coords[MAT4_32] * m_Coords[MAT4_43],
            m_Coords[MAT4_13] * m_Coords[MAT4_22] * m_Coords[MAT4_41] - m_Coords[MAT4_12] * m_Coords[MAT4_23] * m_Coords[MAT4_41] - m_Coords[MAT4_13] * m_Coords[MAT4_21] * m_Coords[MAT4_42] + m_Coords[MAT4_11] * m_Coords[MAT4_23] * m_Coords[MAT4_42] + m_Coords[MAT4_12] * m_Coords[MAT4_21] * m_Coords[MAT4_43] - m_Coords[MAT4_11] * m_Coords[MAT4_22] * m_Coords[MAT4_43],
            m_Coords[MAT4_12] * m_Coords[MAT4_23] * m_Coords[MAT4_31] - m_Coords[MAT4_13] * m_Coords[MAT4_22] * m_Coords[MAT4_31] + m_Coords[MAT4_13] * m_Coords[MAT4_21] * m_Coords[MAT4_32] - m_Coords[MAT4_11] * m_Coords[MAT4_23] * m_Coords[MAT4_32] - m_Coords[MAT4_12] * m_Coords[MAT4_21] * m_Coords[MAT4_33] + m_Coords[MAT4_11] * m_Coords[MAT4_22] * m_Coords[MAT4_33]
        };
        memcpy(m_Coords, result, GEOMETRY_DIMENSION_4x4 * sizeof(double));

        *this *= (1.0 / det);

        return *this;
    }

    Matrix4 Matrix4::Inverse() const
    {
        Matrix4 result(*this);
        return result.Inverse();
    }

    Matrix4& Matrix4::Compose(const Vector3& translation, const Vector3& scale, const Quaternion& orientation)
    {
        const double& x = orientation.X(), y = orientation.Y(), z = orientation.Z(), w = orientation.W();
        const double x2 = x + x, y2 = y + y, z2 = z + z;
        const double xx = x * x2, xy = x * y2, xz = x * z2;
        const double yy = y * y2, yz = y * z2, zz = z * z2;
        const double wx = w * x2, wy = w * y2, wz = w * z2;

        m_Coords[MAT4_11] = (1 - (yy + zz)) * scale.X();
        m_Coords[MAT4_12] = (xy + wz) * scale.X();
        m_Coords[MAT4_13] = (xz - wy) * scale.X();
        m_Coords[MAT4_14] = 0.0;

        m_Coords[MAT4_21] = (xy - wz) * scale.Y();
        m_Coords[MAT4_22] = (1 - (xx + zz)) * scale.Y();
        m_Coords[MAT4_23] = (yz + wx) * scale.Y();
        m_Coords[MAT4_24] = 0.0;

        m_Coords[MAT4_31] = (xz + wy) * scale.Z();
        m_Coords[MAT4_32] = (yz - wx) * scale.Z();
        m_Coords[MAT4_33] = (1 - (xx + yy)) * scale.Z();
        m_Coords[MAT4_34] = 0.0;

        m_Coords[MAT4_41] = translation.X();
        m_Coords[MAT4_42] = translation.Y();
        m_Coords[MAT4_43] = translation.Z();
        m_Coords[MAT4_44] = 1.0;

        return *this;
    }

    void Matrix4::Decompose(Vector3& translation, Vector3& scale, Quaternion& orientation) const
    {
        Vector3 v{};

        double       sx = v.Set(m_Coords[MAT4_11], m_Coords[MAT4_12], m_Coords[MAT4_13]).GetLength();
        const double sy = v.Set(m_Coords[MAT4_21], m_Coords[MAT4_22], m_Coords[MAT4_23]).GetLength();
        const double sz = v.Set(m_Coords[MAT4_31], m_Coords[MAT4_32], m_Coords[MAT4_33]).GetLength();

        const double det = Determinant();

        // a negative determinant means changing orientation => negating one scale component
        if (det < 0.0)
        {
            sx *= -1.0;
        }

        translation.X() = m_Coords[MAT4_41];
        translation.Y() = m_Coords[MAT4_42];
        translation.Z() = m_Coords[MAT4_43];

        // scale the rotation part
        Matrix3 mRot{
            m_Coords[MAT4_11], m_Coords[MAT4_12], m_Coords[MAT4_13],
            m_Coords[MAT4_21], m_Coords[MAT4_22], m_Coords[MAT4_23],  
            m_Coords[MAT4_31], m_Coords[MAT4_32], m_Coords[MAT4_33]
        };

        mRot.Set(
            mRot.Elem(MAT3_11) / sx,
            mRot.Elem(MAT3_12) / sx,
            mRot.Elem(MAT3_13) / sx,

            mRot.Elem(MAT3_21) / sy,
            mRot.Elem(MAT3_22) / sy,
            mRot.Elem(MAT3_23) / sy,

            mRot.Elem(MAT3_31) / sz,
            mRot.Elem(MAT3_32) / sz,
            mRot.Elem(MAT3_33) / sz
        );

        orientation.SetFromRotationMatrix(mRot);

        scale.Set(sx, sy, sz);
    }

    std::tuple<Vector3, Vector3, Quaternion> Matrix4::Decompose() const
    {
        Vector3 translation, scale;
        Quaternion orientation;
        Decompose(translation, scale, orientation);

        return std::tuple<Vector3, Vector3, Quaternion>(translation, scale, orientation);
    }
} // Symplektis::GeometryBase