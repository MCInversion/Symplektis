/*! \file  Vector3_Tests.cpp
 *  \brief Vector3_Tests
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   8.5.2021
 * 
 */

#include "gtest/gtest.h"

#include "Symplekt_UtilityGeneral/ToleranceSettings.h"
#include "Symplekt_UtilityGeneral/NumericUtils.h"

#include "Symplekt_GeometryBase/Vector2.h"
#include "Symplekt_GeometryBase/Vector3.h"
#include "Symplekt_GeometryBase/Vector3Utils.h"
#include "Symplekt_GeometryBase/Matrix3.h"
#include "Symplekt_GeometryBase/Matrix4.h"
#include "Symplekt_GeometryBase/Quaternion.h"

#include <corecrt_math_defines.h>

namespace Symplektis::UnitTests
{
	using namespace GeometryBase;
	TEST(Vector3_TestSuite, Vector3_ConstructFromVector2_Vector3)
	{
		// Arrange
		const Vector2 vec2(1.0, -2.5);

		// Act
		Vector3 vec3(vec2);

		// Assert
		EXPECT_DOUBLE_EQ(vec3.X(), 1.0);
		EXPECT_DOUBLE_EQ(vec3.Y(), -2.5);
		EXPECT_DOUBLE_EQ(vec3.Z(), 0.0);
	}

	TEST(Vector3_TestSuite, ThreeVector3s_EqualityComparisonOperator_Vector3Equality)
	{
		// Arrange
		const Vector3 vec1(1.0, -2.5, 3.0);
		const Vector3 vec2(1.0, -2.5, 3.0);
		const Vector3 vec3(1.0, -2.5, 2.0);

		// Act & Assert
		EXPECT_TRUE(vec1 == vec2);
		EXPECT_FALSE(vec1 != vec2);
		EXPECT_TRUE(vec1 != vec3);
		EXPECT_FALSE(vec1 == vec3);
	}

	TEST(Vector3_TestSuite, ThreeVector3s_EqualityWithTolerance_Vector3Equality)
	{
		// Arrange
		const Vector3 vec1(1.0, -2.5, 3.0);
		const Vector3 vec2(1.0, -2.5, 3.00000002);
		const Vector3 vec3(1.0, -2.5, 3.001);

		// Act & Assert
		EXPECT_TRUE(vec1.EqualsWithTolerance(vec2));
		EXPECT_FALSE(vec1.EqualsWithTolerance(vec3));
	}

	TEST(Vector3_TestSuite, Vector3_StandardAssignmentOperator_Vector3Equality)
	{
		// Arrange
		const Vector3 vec1(1.0, -2.5, 3.0);
		Vector3 vec2;

		// Act
		vec2 = vec1;

		// Assert
		EXPECT_DOUBLE_EQ(vec2.X(), 1.0);
		EXPECT_DOUBLE_EQ(vec2.Y(), -2.5);
		EXPECT_DOUBLE_EQ(vec2.Z(), 3.0);
	}

	TEST(Vector3_TestSuite, Vector3_AdditionAssignmentOperator_Vector3)
	{
		// Arrange
		Vector3 vec1(1.0, -2.5, 3.0);
		const Vector3 vec2(1.5, 2.5, -1.0);

		// Act
		vec1 += vec2;

		// Assert
		EXPECT_DOUBLE_EQ(vec1.X(), 2.5);
		EXPECT_DOUBLE_EQ(vec1.Y(), 0.0);
		EXPECT_DOUBLE_EQ(vec1.Z(), 2.0);
	}

	TEST(Vector3_TestSuite, Vector3_SubtractionAssignmentOperator_Vector3)
	{
		// Arrange
		Vector3 vec1(1.0, -2.5, 3.0);
		const Vector3 vec2(1.5, 2.5, -1.0);

		// Act
		vec1 -= vec2;

		// Assert
		EXPECT_DOUBLE_EQ(vec1.X(), -0.5);
		EXPECT_DOUBLE_EQ(vec1.Y(), -5.0);
		EXPECT_DOUBLE_EQ(vec1.Z(), 4.0);
	}

	TEST(Vector3_TestSuite, Vector3_ScalarAdditionAssignmentOperator_Vector3)
	{
		// Arrange
		Vector3 vec1(1.0, -2.5, 3.0);
		const double val = 2.5;

		// Act
		vec1 += val;

		// Assert
		EXPECT_DOUBLE_EQ(vec1.X(), 3.5);
		EXPECT_DOUBLE_EQ(vec1.Y(), 0.0);
		EXPECT_DOUBLE_EQ(vec1.Z(), 5.5);
	}

	TEST(Vector3_TestSuite, Vector3_ScalarSubtractionAssignmentOperator_Vector3)
	{
		// Arrange
		Vector3 vec1(1.0, -2.5, 3.0);
		const double val = 2.5;

		// Act
		vec1 -= val;

		// Assert
		EXPECT_DOUBLE_EQ(vec1.X(), -1.5);
		EXPECT_DOUBLE_EQ(vec1.Y(), -5.0);
		EXPECT_DOUBLE_EQ(vec1.Z(), 0.5);
	}

	TEST(Vector3_TestSuite, Vector3_AdditionOperator_Vector3)
	{
		// Arrange
		const Vector3 vec1(1.0, -2.5, 3.0);
		const Vector3 vec2(1.5, 2.5, -1.0);

		// Act
		const Vector3 vec3 = vec1 + vec2;

		// Assert
		EXPECT_DOUBLE_EQ(vec3.X(), 2.5);
		EXPECT_DOUBLE_EQ(vec3.Y(), 0.0);
		EXPECT_DOUBLE_EQ(vec3.Z(), 2.0);
	}

	TEST(Vector3_TestSuite, Vector3_SubtractionOperator_Vector3)
	{
		// Arrange
		const Vector3 vec1(1.0, -2.5, 3.0);
		const Vector3 vec2(1.5, 2.5, -1.0);

		// Act
		const Vector3 vec3 = vec1 - vec2;

		// Assert
		EXPECT_DOUBLE_EQ(vec3.X(), -0.5);
		EXPECT_DOUBLE_EQ(vec3.Y(), -5.0);
		EXPECT_DOUBLE_EQ(vec3.Z(), 4.0);
	}

	TEST(Vector3_TestSuite, Vector3_Vector3CrossProductAssignmentOperator_Vector3)
	{
		// Arrange
		Vector3 vec1(1.0, -2.5, 3.0);
		const Vector3 vec2(1.5, 2.5, -1.0);
		Vector3 vec3 = vec1;

		// Act
		vec1 *= vec2;
		vec3.CrossProduct(vec2);

		// Assert
		EXPECT_DOUBLE_EQ(vec1.X(), -5.0);
		EXPECT_DOUBLE_EQ(vec1.Y(), 5.5);
		EXPECT_DOUBLE_EQ(vec1.Z(), 6.25);

		EXPECT_DOUBLE_EQ(vec3.X(), -5.0);
		EXPECT_DOUBLE_EQ(vec3.Y(), 5.5);
		EXPECT_DOUBLE_EQ(vec3.Z(), 6.25);
	}

	TEST(Vector3_TestSuite, Vector3_Vector3WithVector2CrossProductAssignmentOperator_Vector3)
	{
		// Arrange
		Vector3 vec1(1.0, -2.5, 3.0);
		const Vector2 vec2(1.5, 2.5);

		// Act
		vec1 *= vec2;

		// Assert
		EXPECT_DOUBLE_EQ(vec1.X(), -7.5);
		EXPECT_DOUBLE_EQ(vec1.Y(), 4.5);
		EXPECT_DOUBLE_EQ(vec1.Z(), 6.25);
	}

	TEST(Vector3_TestSuite, Vector3_Vector3CrossProductOperator_Vector3)
	{
		// Arrange
		const Vector3 vec1(1.0, -2.5, 3.0);
		const Vector3 vec2(1.5, 2.5, -1.0);

		// Act
		const Vector3 vec3 = vec1 * vec2;
		const Vector3 vec4 = CrossProduct(vec1, vec2);

		// Assert
		EXPECT_DOUBLE_EQ(vec3.X(), -5.0);
		EXPECT_DOUBLE_EQ(vec3.Y(), 5.5);
		EXPECT_DOUBLE_EQ(vec3.Z(), 6.25);

		EXPECT_DOUBLE_EQ(vec4.X(), -5.0);
		EXPECT_DOUBLE_EQ(vec4.Y(), 5.5);
		EXPECT_DOUBLE_EQ(vec4.Z(), 6.25);
	}

	TEST(Vector3_TestSuite, Vector3_ScalarMultiplicationAssignmentOperator_Vector3)
	{
		// Arrange
		Vector3 vec(1.0, -2.5, 3.0);
		const double val = 2.5;

		// Act
		vec *= val;

		// Assert
		EXPECT_DOUBLE_EQ(vec.X(), 2.5);
		EXPECT_DOUBLE_EQ(vec.Y(), -6.25);
		EXPECT_DOUBLE_EQ(vec.Z(), 7.5);
	}

	TEST(Vector3_TestSuite, Vector3_ScalarMultiplicationOperator_Vector3)
	{
		// Arrange
		const Vector3 vec(1.0, -2.5, 3.0);
		const double val = 2.5;

		// Act
		const Vector3 vec1 = vec * val;

		// Assert
		EXPECT_DOUBLE_EQ(vec1.X(), 2.5);
		EXPECT_DOUBLE_EQ(vec1.Y(), -6.25);
		EXPECT_DOUBLE_EQ(vec1.Z(), 7.5);
	}

	TEST(Vector3_TestSuite, Vector3_ExternalScalarMultiplicationOperator_Vector3)
	{
		// Arrange
		const Vector3 vec(1.0, -2.5, 3.0);
		const double val = 2.5;

		// Act
		const Vector3 vec1 = val * vec;

		// Assert
		EXPECT_DOUBLE_EQ(vec1.X(), 2.5);
		EXPECT_DOUBLE_EQ(vec1.Y(), -6.25);
		EXPECT_DOUBLE_EQ(vec1.Z(), 7.5);
	}

	TEST(Vector3_TestSuite, Vector3_ScalarDivisionAssignmentOperator_Vector3)
	{
		// Arrange
		Vector3 vec(1.0, -2.5, 3.0);
		const double val = 2.5;

		// Act
		vec /= val;

		// Assert
		EXPECT_DOUBLE_EQ(vec.X(), 0.4);
		EXPECT_DOUBLE_EQ(vec.Y(), -1.0);
		EXPECT_DOUBLE_EQ(vec.Z(), 1.2);
	}

	TEST(Vector3_TestSuite, Vector3_ScalarDivisionOperator_Vector3)
	{
		// Arrange
		const Vector3 vec(1.0, -2.5, 3.0);
		const double val = 2.5;

		// Act
		const Vector3 vec1 = vec / val;

		// Assert
		EXPECT_DOUBLE_EQ(vec1.X(), 0.4);
		EXPECT_DOUBLE_EQ(vec1.Y(), -1.0);
		EXPECT_DOUBLE_EQ(vec1.Z(), 1.2);
	}

	TEST(Vector3_TestSuite, Vector3_Vector3Matrix3ProductAssignmentOperator_Vector3)
	{
		// Arrange
		Vector3 vec(1.0, -2.5, 3.0);
		const Matrix3 mat{
			 1.5, 2.5,  0.1,
			-1.0, 3.0, -0.7,
			 0.0, 2.0,  5.0
		};

		// Act
		vec *= mat;

		// Assert
		EXPECT_DOUBLE_EQ(vec.X(), -4.45);
		EXPECT_DOUBLE_EQ(vec.Y(), -10.6);
		EXPECT_DOUBLE_EQ(vec.Z(), 10.0);
	}

	TEST(Vector3_TestSuite, Vector3_Vector3Matrix4ProductAssignmentOperator_Vector3)
	{
		// Arrange
		Vector3 vec(1.0, -2.5, 3.0);
		const Matrix4 mat{
			 1.5, 2.5,  0.1, 0.0,
			-1.0, 3.0, -0.7, 0.0,
			 0.0, 2.0,  5.0, 0.0,
			 1.0, 2.0,  3.0, 1.0
		};

		// Act
		vec *= mat;

		// Assert
		EXPECT_DOUBLE_EQ(vec.X(), -4.45 / 6.0);
		EXPECT_DOUBLE_EQ(vec.Y(), -10.6 / 6.0);
		EXPECT_DOUBLE_EQ(vec.Z(), 10.0 / 6.0);
	}

	TEST(Vector3_TestSuite, Vector3_Vector3IsZero_Vector3IsZero)
	{
		// Arrange
		const Vector3 vec{ 0.0, 0.0, 0.0 };
		const Vector3 vec1{ 0.0, 0.0, 1.75656e-17 };
		const Vector3 vec2{ 0.0, -1.75656e-17, 1.75656e-17 };

		// Act & Assert
		EXPECT_TRUE(vec.IsZero());
		EXPECT_FALSE(vec1.IsZero());
		EXPECT_FALSE(vec2.IsZero());
	}

	TEST(Vector3_TestSuite, Vector3_Vector3IsNormalized_Vector3IsNormalized)
	{
		// Arrange
		const Vector3 vec1{ 1.0, 0.0, 0.0 };
		const Vector3 vec2{ 3.0, 0.0, 0.0 };
		const Vector3 vec3{ cos(M_PI_4), sin(M_PI_4), 0.0 };

		// Act & Assert
		EXPECT_TRUE(vec1.IsNormalized());
		EXPECT_FALSE(vec2.IsNormalized());
		EXPECT_FALSE(vec3.IsNormalized()); // passes only for IsNormalizedWithTolerance
	}

	TEST(Vector3_TestSuite, Vector3_Vector3IsNormalizedWithTolerance_Vector3IsNormalizedWithTolerance)
	{
		// Arrange
		const Vector3 vec1{ cos(M_PI_4), sin(M_PI_4), 0.0 };
		const Vector3 vec2{ 1.0, 1.0, 0.0 };

		// Act & Assert
		EXPECT_TRUE(vec1.IsNormalizedWithTolerance());
		EXPECT_FALSE(vec2.IsNormalizedWithTolerance());
	}

	TEST(Vector3_TestSuite, Vector3_Vector3GetLengthSquared_LengthSquared)
	{
		// Arrange
		const Vector3 vec{ 1.0, 2.0, 3.0 };

		// Act
		const double lengthSq = vec.GetLengthSquared();

		// Assert
		EXPECT_DOUBLE_EQ(lengthSq, 14.0);
	}

	TEST(Vector3_TestSuite, Vector3_Vector3GetLength_Length)
	{
		// Arrange
		const Vector3 vec{ 2.0, 3.0, 6.0 };

		// Act
		const double length = vec.GetLength();

		// Assert
		EXPECT_DOUBLE_EQ(length, 7.0);
	}

	TEST(Vector3_TestSuite, Vector3_Vector3GetInvLength_InvLength)
	{
		// Arrange
		const Vector3 vec{ 2.0, 3.0, 6.0 };

		// Act
		const double invLength = vec.GetInvLength();

		// Assert
		const double epsilon = Symplektis::Util::GetCoordinateTolerance();
		EXPECT_TRUE(Symplektis::Util::EqualsWithTolerance(invLength, 1.0 / 7.0, epsilon));
	}

	TEST(Vector3_TestSuite, Vector3_Vector3Normalize_NormalizedVector3)
	{
		// Arrange
		Vector3 vec1{ 2.0, 3.0, 6.0 };

		// Act
		vec1.Normalize();

		// Assert
		EXPECT_TRUE(vec1.IsNormalizedWithTolerance());
	}

	TEST(Vector3_TestSuite, Vector3_Vector3FastNormalize_FastNormalizedVector3)
	{
		// Arrange
		Vector3 vec1{ 2.0, 3.0, 6.0 };

		// Act
		vec1.FastNormalize();

		// Assert
		EXPECT_TRUE(vec1.IsNormalizedWithTolerance());
	}

	TEST(Vector3_TestSuite, Vector3_Vector3DotProduct_DotProduct)
	{
		// Arrange
		const Vector3 vec1{ 2.0, 3.0, 6.0 };
		const Vector3 vec2{ 1.0, 2.0, -1.5 };

		// Act
		const double dot = vec1.DotProduct(vec2);

		// Assert
		EXPECT_DOUBLE_EQ(dot, -1.0);
	}

	TEST(Vector3_TestSuite, Vector3_ExternalVector3DotProduct_DotProduct)
	{
		// Arrange
		const Vector3 vec1{ 2.0, 3.0, 6.0 };
		const Vector3 vec2{ 1.0, 2.0, -1.5 };

		// Act
		const double dot = DotProduct(vec1, vec2);

		// Assert
		EXPECT_DOUBLE_EQ(dot, -1.0);
	}

	TEST(Vector3_TestSuite, Vector3_Vector3DirectProduct_DirectProduct)
	{
		// Arrange
		Vector3 vec1{ 2.0, 3.0, 6.0 };
		const Vector3 vec2{ 1.0, 2.0, -1.5 };

		// Act
		vec1.DirectProduct(vec2);

		// Assert
		EXPECT_DOUBLE_EQ(vec1.X(), 2.0);
		EXPECT_DOUBLE_EQ(vec1.Y(), 6.0);
		EXPECT_DOUBLE_EQ(vec1.Z(), -9.0);
	}
	TEST(Vector3_TestSuite, Vector3_ProjectOntoVector3_Vector3Projection)
	{
		// Arrange
		const Vector3 vec1{ 2.0, 3.0, 6.0 };
		const Vector3 vec2{ 1.0, 1.0, 1.0 };

		// Act
		Vector3 vec3 = vec1.Project(vec2);

		// Assert
		EXPECT_DOUBLE_EQ(vec3.X(), 0.44897959183673469);
		EXPECT_DOUBLE_EQ(vec3.Y(), 0.67346938775510201);
		EXPECT_DOUBLE_EQ(vec3.Z(), 1.3469387755102040);
	}

	TEST(Vector3_TestSuite, Vector3_ApplyQuaternion_RotatedVector3)
	{
		// Arrange
		Vector3 vec{ 2.0, 3.0, 6.0 };
		const Vector3 zAxis(0.0, 0.0, 1.0);
		const Quaternion quat(zAxis, M_PI_4);

		// Act
		vec.ApplyQuaternion(quat);

		// Assert
		EXPECT_DOUBLE_EQ(vec.X(), -sqrt(2.0) / 2.0);
		EXPECT_DOUBLE_EQ(vec.Y(), 3.5355339059327373);
		EXPECT_DOUBLE_EQ(vec.Z(), 6.0);
	}

	TEST(Vector3_TestSuite, Vector3_Vector3Min_Min)
	{
		// Arrange
		Vector3 vec1{ 2.0, 3.0, 6.0 };
		const Vector3 vec2{ -1.0, 1.0, 3.0 };

		// Act
		vec1.Min(vec2);

		// Assert
		EXPECT_DOUBLE_EQ(vec1.X(), -1.0);
		EXPECT_DOUBLE_EQ(vec1.Y(), 1.0);
		EXPECT_DOUBLE_EQ(vec1.Z(), 3.0);
	}

	TEST(Vector3_TestSuite, Vector3_Vector3Max_Max)
	{
		// Arrange
		Vector3 vec1{ 2.0, 3.0, 6.0 };
		const Vector3 vec2{ -1.0, 1.0, 3.0 };

		// Act
		vec1.Max(vec2);

		// Assert
		EXPECT_DOUBLE_EQ(vec1.X(), 2.0);
		EXPECT_DOUBLE_EQ(vec1.Y(), 3.0);
		EXPECT_DOUBLE_EQ(vec1.Z(), 6.0);
	}

	TEST(Vector3_TestSuite, Vector3_Vector3SetCoordsByIDs_CoordsSetByIDs)
	{
		// Arrange
		Vector3 vec{ 2.0, 3.0, 6.0 };

		// Act
		vec.SetCoordById(-7.35, X_COORD_3D);
		vec.SetCoordById(1.17, Y_COORD_3D);
		vec.SetCoordById(3.27, Z_COORD_3D);

		// Assert
		EXPECT_DOUBLE_EQ(vec.X(), -7.35);
		EXPECT_DOUBLE_EQ(vec.Y(), 1.17);
		EXPECT_DOUBLE_EQ(vec.Z(), 3.27);
	}

	TEST(Vector3_TestSuite, Vector3_Vector3GetCoordsByIDs_CoordsReceivedByIDs)
	{
		// Arrange
		Vector3 vec{ 2.0, 3.0, 6.0 };

		// Act & Assert
		EXPECT_DOUBLE_EQ(vec.GetCoordById(X_COORD_3D), 2.0);
		EXPECT_DOUBLE_EQ(vec.GetCoordById(Y_COORD_3D), 3.0);
		EXPECT_DOUBLE_EQ(vec.GetCoordById(Z_COORD_3D), 6.0);
	}

	TEST(Vector3_TestSuite, Vector3_Vector3LinInterpolate_InterpolatedVector)
	{
		// Arrange
		Vector3 vec1{ 2.0, 3.0, 6.0 };
		const Vector3 vec2{ -1.0, 1.0, 3.0 };
		const double param = 0.75;

		// Act
		vec1.LinearInterpolate(vec2, param);

		// Assert
		EXPECT_DOUBLE_EQ(vec1.X(), -0.25);
		EXPECT_DOUBLE_EQ(vec1.Y(), 1.5);
		EXPECT_DOUBLE_EQ(vec1.Z(), 3.75);
	}

	TEST(Vector3_TestSuite, Vector3_ExternalVector3LinInterpolate_InterpolatedVector)
	{
		// Arrange
		const Vector3 vec1{ 2.0, 3.0, 6.0 };
		const Vector3 vec2{ -1.0, 1.0, 3.0 };
		const double param = 0.75;

		// Act
		const Vector3 vec3 = LinearInterpolate(vec1, vec2, param);

		// Assert
		EXPECT_DOUBLE_EQ(vec3.X(), -0.25);
		EXPECT_DOUBLE_EQ(vec3.Y(), 1.5);
		EXPECT_DOUBLE_EQ(vec3.Z(), 3.75);
	}

	TEST(Vector3_TestSuite, Vector3_ComputePerpendicularUnitVectorVectorInAwayFromX_PerpendicularUnitVectorYZPlane)
	{
		// Arrange
		const Vector3 vecAwayFromX{ 1.0, 2.0, 2.0 };

		// Act
		const Vector3 resultYXPlane = ComputePerpendicularUnitVector(vecAwayFromX);

		// Assert
		EXPECT_DOUBLE_EQ(resultYXPlane.X(), 0.0);
		EXPECT_DOUBLE_EQ(resultYXPlane.Y(), -M_SQRT1_2);
		EXPECT_DOUBLE_EQ(resultYXPlane.Z(), M_SQRT1_2);
	}

	TEST(Vector3_TestSuite, Vector3_ComputePerpendicularUnitVectorVectorInXYPlaneCloseToX_PerpendicularUnitVectorNegXYPlane)
	{
		// Arrange
		const Vector3 vecXYPlaneCloseToX{ 2.0, 1.0, 0.0 };

		// Act
		const Vector3 resultXYPlane = ComputePerpendicularUnitVector(vecXYPlaneCloseToX);

		// Assert
		const double INV_SQRT5 = 1.0 / sqrt(5.0);
        EXPECT_DOUBLE_EQ(resultXYPlane.X(), -INV_SQRT5);
        EXPECT_DOUBLE_EQ(resultXYPlane.Y(), 2.0 * INV_SQRT5);
        EXPECT_DOUBLE_EQ(resultXYPlane.Z(), 0.0);
	}

	TEST(Vector3_TestSuite, Vector3_ComputePerpendicularUnitVectorNegZVector_PerpendicularUnitVectorNegXYPlane)
	{
		// Arrange
		const Vector3 vecNegZ{ 0.0, 0.0, -2.0 };

		// Act
		const Vector3 resultXYPlane = ComputePerpendicularUnitVector(vecNegZ);

		// Assert
		EXPECT_DOUBLE_EQ(resultXYPlane.X(), -1.0);
		EXPECT_DOUBLE_EQ(resultXYPlane.Y(), 0.0);
		EXPECT_DOUBLE_EQ(resultXYPlane.Z(), 0.0);
	}

} // Symplektis::UnitTests
