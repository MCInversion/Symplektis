/*! \file Matrix3.cpp
*   \brief Implmentation of the 3x3 matrix class
*
\verbatim
-------------------------------------------------------------------------------
created  : 6.5.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/

#include "Matrix3.h"

#include "../Symplekt_UtilityGeneral/NumericUtils.h"
#include "../Symplekt_UtilityGeneral/ToleranceSettings.h"
#include "Vector3.h"
#include "Matrix4.h"

namespace Symplektis::GeometryBase
{
    Matrix3::Matrix3(const Matrix4& mat)
    {
        Set(
            mat.Elem(MAT4_11), mat.Elem(MAT4_12), mat.Elem(MAT4_13),
            mat.Elem(MAT4_21), mat.Elem(MAT4_22), mat.Elem(MAT4_23),
            mat.Elem(MAT4_31), mat.Elem(MAT4_32), mat.Elem(MAT4_33)
        );
    }

    bool Matrix3::operator==(const Matrix3& mat) const
    {
        if (m_Coords[MAT3_11] != mat.m_Coords[MAT3_11])
            return false;
        if (m_Coords[MAT3_12] != mat.m_Coords[MAT3_12])
            return false;
        if (m_Coords[MAT3_13] != mat.m_Coords[MAT3_13])
            return false;
        if (m_Coords[MAT3_21] != mat.m_Coords[MAT3_21])
            return false;
        if (m_Coords[MAT3_22] != mat.m_Coords[MAT3_22])
            return false;
        if (m_Coords[MAT3_23] != mat.m_Coords[MAT3_23])
            return false;
        if (m_Coords[MAT3_31] != mat.m_Coords[MAT3_31])
            return false;
        if (m_Coords[MAT3_32] != mat.m_Coords[MAT3_32])
            return false;

        return (m_Coords[MAT3_33] == mat.m_Coords[MAT3_33]);
    }

    bool Matrix3::EqualsWithTolerance(const Matrix3& mat) const
    {
        const double epsilon = Symplektis::Util::GetCoordinateTolerance();

        if (!Symplektis::Util::EqualsWithTolerance(m_Coords[MAT3_11], mat.m_Coords[MAT3_11], epsilon))
            return false;
        if (!Symplektis::Util::EqualsWithTolerance(m_Coords[MAT3_12], mat.m_Coords[MAT3_12], epsilon))
            return false;
        if (!Symplektis::Util::EqualsWithTolerance(m_Coords[MAT3_13], mat.m_Coords[MAT3_13], epsilon))
            return false;
        if (!Symplektis::Util::EqualsWithTolerance(m_Coords[MAT3_21], mat.m_Coords[MAT3_21], epsilon))
            return false;
        if (!Symplektis::Util::EqualsWithTolerance(m_Coords[MAT3_22], mat.m_Coords[MAT3_22], epsilon))
            return false;
        if (!Symplektis::Util::EqualsWithTolerance(m_Coords[MAT3_23], mat.m_Coords[MAT3_23], epsilon))
            return false;
        if (!Symplektis::Util::EqualsWithTolerance(m_Coords[MAT3_31], mat.m_Coords[MAT3_31], epsilon))
            return false;
        if (!Symplektis::Util::EqualsWithTolerance(m_Coords[MAT3_32], mat.m_Coords[MAT3_32], epsilon))
            return false;

        return (Symplektis::Util::EqualsWithTolerance(m_Coords[MAT3_33], mat.m_Coords[MAT3_33], epsilon));
    }

    bool Matrix3::operator!=(const Matrix3& mat) const
    {
        if (m_Coords[MAT3_11] != mat.m_Coords[MAT3_11])
            return true;
        if (m_Coords[MAT3_12] != mat.m_Coords[MAT3_12])
            return true;
        if (m_Coords[MAT3_13] != mat.m_Coords[MAT3_13])
            return true;
        if (m_Coords[MAT3_21] != mat.m_Coords[MAT3_21])
            return true;
        if (m_Coords[MAT3_22] != mat.m_Coords[MAT3_22])
            return true;
        if (m_Coords[MAT3_23] != mat.m_Coords[MAT3_23])
            return true;
        if (m_Coords[MAT3_31] != mat.m_Coords[MAT3_31])
            return true;
        if (m_Coords[MAT3_32] != mat.m_Coords[MAT3_32])
            return true;

        return (m_Coords[MAT3_33] != mat.m_Coords[MAT3_33]);
    }

    Matrix3 Matrix3::operator+(const Matrix3& mat) const
    {
        Matrix3 result(*this);
        result += mat;
        return result;
    }

    Matrix3 Matrix3::operator-(const Matrix3& mat) const
    {
        Matrix3 result(*this);
        result -= mat;
        return result;
    }

    Matrix3& Matrix3::Multiply(const Matrix3& mat)
    {
        double result[GEOMETRY_DIMENSION_3x3] = {
            m_Coords[MAT3_11] * mat.m_Coords[MAT3_11] + m_Coords[MAT3_12] * mat.m_Coords[MAT3_21] + m_Coords[MAT3_13] * mat.m_Coords[MAT3_31],
            m_Coords[MAT3_11] * mat.m_Coords[MAT3_12] + m_Coords[MAT3_12] * mat.m_Coords[MAT3_22] + m_Coords[MAT3_13] * mat.m_Coords[MAT3_32],
            m_Coords[MAT3_11] * mat.m_Coords[MAT3_13] + m_Coords[MAT3_12] * mat.m_Coords[MAT3_23] + m_Coords[MAT3_13] * mat.m_Coords[MAT3_33],

            m_Coords[MAT3_21] * mat.m_Coords[MAT3_11] + m_Coords[MAT3_22] * mat.m_Coords[MAT3_21] + m_Coords[MAT3_23] * mat.m_Coords[MAT3_31],
            m_Coords[MAT3_21] * mat.m_Coords[MAT3_12] + m_Coords[MAT3_22] * mat.m_Coords[MAT3_22] + m_Coords[MAT3_23] * mat.m_Coords[MAT3_32],
            m_Coords[MAT3_21] * mat.m_Coords[MAT3_13] + m_Coords[MAT3_22] * mat.m_Coords[MAT3_23] + m_Coords[MAT3_23] * mat.m_Coords[MAT3_33],

            m_Coords[MAT3_31] * mat.m_Coords[MAT3_11] + m_Coords[MAT3_32] * mat.m_Coords[MAT3_21] + m_Coords[MAT3_33] * mat.m_Coords[MAT3_31],
            m_Coords[MAT3_31] * mat.m_Coords[MAT3_12] + m_Coords[MAT3_32] * mat.m_Coords[MAT3_22] + m_Coords[MAT3_33] * mat.m_Coords[MAT3_32],
            m_Coords[MAT3_31] * mat.m_Coords[MAT3_13] + m_Coords[MAT3_32] * mat.m_Coords[MAT3_23] + m_Coords[MAT3_33] * mat.m_Coords[MAT3_33]
        };
        memcpy(m_Coords, result, GEOMETRY_DIMENSION_3x3 * sizeof(double));

        return *this;
    }

    Matrix3& Matrix3::Premultiply(const Matrix3& mat)
    {
        double result[GEOMETRY_DIMENSION_3x3] = {
            mat.m_Coords[MAT3_11] * m_Coords[MAT3_11] + mat.m_Coords[MAT3_12] * m_Coords[MAT3_21] + mat.m_Coords[MAT3_13] * m_Coords[MAT3_31],
            mat.m_Coords[MAT3_11] * m_Coords[MAT3_12] + mat.m_Coords[MAT3_12] * m_Coords[MAT3_22] + mat.m_Coords[MAT3_13] * m_Coords[MAT3_32],
            mat.m_Coords[MAT3_11] * m_Coords[MAT3_13] + mat.m_Coords[MAT3_12] * m_Coords[MAT3_23] + mat.m_Coords[MAT3_13] * m_Coords[MAT3_33],

            mat.m_Coords[MAT3_21] * m_Coords[MAT3_11] + mat.m_Coords[MAT3_22] * m_Coords[MAT3_21] + mat.m_Coords[MAT3_23] * m_Coords[MAT3_31],
            mat.m_Coords[MAT3_21] * m_Coords[MAT3_12] + mat.m_Coords[MAT3_22] * m_Coords[MAT3_22] + mat.m_Coords[MAT3_23] * m_Coords[MAT3_32],
            mat.m_Coords[MAT3_21] * m_Coords[MAT3_13] + mat.m_Coords[MAT3_22] * m_Coords[MAT3_23] + mat.m_Coords[MAT3_23] * m_Coords[MAT3_33],

            mat.m_Coords[MAT3_31] * m_Coords[MAT3_11] + mat.m_Coords[MAT3_32] * m_Coords[MAT3_21] + mat.m_Coords[MAT3_33] * m_Coords[MAT3_31],
            mat.m_Coords[MAT3_31] * m_Coords[MAT3_12] + mat.m_Coords[MAT3_32] * m_Coords[MAT3_22] + mat.m_Coords[MAT3_33] * m_Coords[MAT3_32],
            mat.m_Coords[MAT3_31] * m_Coords[MAT3_13] + mat.m_Coords[MAT3_32] * m_Coords[MAT3_23] + mat.m_Coords[MAT3_33] * m_Coords[MAT3_33]
        };
        memcpy(m_Coords, result, GEOMETRY_DIMENSION_3x3 * sizeof(double));

        return *this;
    }

    Matrix3 Matrix3::operator*(const Matrix3& mat) const
    {
        Matrix3 result(*this);
        result *= mat;
        return result;
    }

    Matrix3& Matrix3::Multiply(const double& scalar)
    {
        m_Coords[MAT3_11] *= scalar;	m_Coords[MAT3_12] *= scalar;    m_Coords[MAT3_13] *= scalar;
        m_Coords[MAT3_21] *= scalar;	m_Coords[MAT3_22] *= scalar;	m_Coords[MAT3_23] *= scalar;
        m_Coords[MAT3_31] *= scalar;	m_Coords[MAT3_32] *= scalar;	m_Coords[MAT3_33] *= scalar;
        return *this;
    }

    Matrix3 Matrix3::operator*(const double& scalar) const
    {
        Matrix3 result(*this);
        result.Multiply(scalar);
        return result;
    }

    Matrix3& Matrix3::SetToIdentity()
    {
        return Set(
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0
        );
    }

    bool Matrix3::IsIdentity() const
    {
        if (m_Coords[MAT3_11] != 1.0)
            return false;
        if (m_Coords[MAT3_12] != 0.0)
            return false;
        if (m_Coords[MAT3_13] != 0.0)
            return false;
        if (m_Coords[MAT3_21] != 0.0)
            return false;
        if (m_Coords[MAT3_22] != 1.0)
            return false;
        if (m_Coords[MAT3_23] != 0.0)
            return false;
        if (m_Coords[MAT3_31] != 0.0)
            return false;
        if (m_Coords[MAT3_32] != 0.0)
            return false;

        return (m_Coords[MAT3_33] == 1.0);
    }

    Matrix3& Matrix3::Transpose()
    {
        double result[GEOMETRY_DIMENSION_3x3] = {
            m_Coords[MAT3_11], m_Coords[MAT3_21], m_Coords[MAT3_31],
            m_Coords[MAT3_12], m_Coords[MAT3_22], m_Coords[MAT3_32],
            m_Coords[MAT3_13], m_Coords[MAT3_23], m_Coords[MAT3_33]
        };
        memcpy(m_Coords, result, GEOMETRY_DIMENSION_3x3 * sizeof(double));
        return *this;
    }

    double Matrix3::Determinant() const
    {
        return (m_Coords[MAT3_11] * m_Coords[MAT3_22] * m_Coords[MAT3_33] - m_Coords[MAT3_13] * m_Coords[MAT3_22] * m_Coords[MAT3_31] +
                m_Coords[MAT3_12] * m_Coords[MAT3_23] * m_Coords[MAT3_31] - m_Coords[MAT3_12] * m_Coords[MAT3_21] * m_Coords[MAT3_33] +
                m_Coords[MAT3_13] * m_Coords[MAT3_21] * m_Coords[MAT3_32] - m_Coords[MAT3_11] * m_Coords[MAT3_23] * m_Coords[MAT3_32]);
    }

    Matrix3& Matrix3::Inverse()
    {
        const double det = Determinant();
        const double epsilon = Symplektis::Util::GetProductTolerance();
        if (std::fabs(det) < epsilon)
        {
            MSG_CHECK(false, "Matrix3::Inverse: det == 0! Attempting to invert a singular 3x3 matrix!");
            return *this;
        }

        double result[GEOMETRY_DIMENSION_3x3] = {
            m_Coords[MAT3_22] * m_Coords[MAT3_33] - m_Coords[MAT3_32] * m_Coords[MAT3_23],
            m_Coords[MAT3_13] * m_Coords[MAT3_32] - m_Coords[MAT3_12] * m_Coords[MAT3_33],
            m_Coords[MAT3_12] * m_Coords[MAT3_23] - m_Coords[MAT3_13] * m_Coords[MAT3_22],

            m_Coords[MAT3_23] * m_Coords[MAT3_31] - m_Coords[MAT3_21] * m_Coords[MAT3_33],
            m_Coords[MAT3_11] * m_Coords[MAT3_33] - m_Coords[MAT3_13] * m_Coords[MAT3_31],
            m_Coords[MAT3_21] * m_Coords[MAT3_13] - m_Coords[MAT3_11] * m_Coords[MAT3_23],

            m_Coords[MAT3_21] * m_Coords[MAT3_32] - m_Coords[MAT3_31] * m_Coords[MAT3_22],
            m_Coords[MAT3_31] * m_Coords[MAT3_12] - m_Coords[MAT3_11] * m_Coords[MAT3_32],
            m_Coords[MAT3_11] * m_Coords[MAT3_22] - m_Coords[MAT3_21] * m_Coords[MAT3_12]
        };
        memcpy(m_Coords, result, GEOMETRY_DIMENSION_3x3 * sizeof(double));

        *this *= (1.0 / det);

        return *this;
    }
 
    Matrix3& Matrix3::operator*=(const Matrix3& mat)
    {
        return Multiply(mat);
    }

    Matrix3& Matrix3::operator*=(const double& scalar)
    {
        return Multiply(scalar);
    }


} // Symplektis::GeometryBase