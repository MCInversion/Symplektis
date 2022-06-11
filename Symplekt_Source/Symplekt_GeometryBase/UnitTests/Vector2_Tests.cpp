/*! \file  Vector2_Tests.cpp
 *  \brief Vector2_Tests
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   26.6.2021
 *
 */

#include "gtest/gtest.h"

#include "../../Symplekt_UtilityGeneral/NumericUtils.h"

#include "../Vector2.h"
#include "../Vector2Utils.h"
#include "../Matrix2.h"

#include <corecrt_math_defines.h>

namespace Symplektis::UnitTests
{
	using namespace GeometryBase;
	TEST(Vector2_TestSuite, ThreeVector2s_EqualityComparisonOperator_Vector2Equality)
	{
		// Arrange
		const Vector2 vec1(1.0, -2.5);
		const Vector2 vec2(1.0, -2.5);
		const Vector2 vec3(1.0, -2.500001245);

		// Act & Assert
		EXPECT_TRUE(vec1 == vec2);
		EXPECT_FALSE(vec1 != vec2);
		EXPECT_TRUE(vec1 != vec3);
		EXPECT_FALSE(vec1 == vec3);
	}

	TEST(Vector2_TestSuite, ThreeVector2s_EqualityWithTolerance_Vector2Equality)
	{
		// Arrange
		const Vector2 vec1(1.0, -2.5);
		const Vector2 vec2(1.0, -2.500000002);
		const Vector2 vec3(1.0, -2.501);

		// Act & Assert
		EXPECT_TRUE(vec1.EqualsWithTolerance(vec2));
		EXPECT_FALSE(vec1.EqualsWithTolerance(vec3));
	}

	TEST(Vector2_TestSuite, Vector2_StandardAssignmentOperator_Vector2Equality)
	{
		// Arrange
		const Vector2 vec1(1.0, -2.5);
		Vector2 vec2;

		// Act
		vec2 = vec1;

		// Assert
		EXPECT_DOUBLE_EQ(vec2.X(), 1.0);
		EXPECT_DOUBLE_EQ(vec2.Y(), -2.5);
	}

	TEST(Vector2_TestSuite, Vector2_AdditionAssignmentOperator_Vector2)
	{
		// Arrange
		Vector2 vec1(1.0, -2.5);
		const Vector2 vec2(1.5, 2.5);

		// Act
		vec1 += vec2;

		// Assert
		EXPECT_DOUBLE_EQ(vec1.X(), 2.5);
		EXPECT_DOUBLE_EQ(vec1.Y(), 0.0);
	}

	TEST(Vector2_TestSuite, Vector2_SubtractionAssignmentOperator_Vector2)
	{
		// Arrange
		Vector2 vec1(1.0, -2.5);
		const Vector2 vec2(1.5, 2.5);

		// Act
		vec1 -= vec2;

		// Assert
		EXPECT_DOUBLE_EQ(vec1.X(), -0.5);
		EXPECT_DOUBLE_EQ(vec1.Y(), -5.0);
	}

	TEST(Vector2_TestSuite, Vector2_ScalarAdditionAssignmentOperator_Vector2)
	{
		// Arrange
		Vector2 vec1(1.0, -2.5);
		const double val = 2.5;

		// Act
		vec1 += val;

		// Assert
		EXPECT_DOUBLE_EQ(vec1.X(), 3.5);
		EXPECT_DOUBLE_EQ(vec1.Y(), 0.0);
	}

	TEST(Vector2_TestSuite, Vector2_ScalarSubtractionAssignmentOperator_Vector2)
	{
		// Arrange
		Vector2 vec1(1.0, -2.5);
		const double val = 2.5;

		// Act
		vec1 -= val;

		// Assert
		EXPECT_DOUBLE_EQ(vec1.X(), -1.5);
		EXPECT_DOUBLE_EQ(vec1.Y(), -5.0);
	}

	TEST(Vector2_TestSuite, Vector2_AdditionOperator_Vector2)
	{
		// Arrange
		const Vector2 vec1(1.0, -2.5);
		const Vector2 vec2(1.5, 2.5);

		// Act
		const Vector2 vec3 = vec1 + vec2;

		// Assert
		EXPECT_DOUBLE_EQ(vec3.X(), 2.5);
		EXPECT_DOUBLE_EQ(vec3.Y(), 0.0);
	}

	TEST(Vector2_TestSuite, Vector2_SubtractionOperator_Vector2)
	{
		// Arrange
		const Vector2 vec1(1.0, -2.5);
		const Vector2 vec2(1.5, 2.5);

		// Act
		const Vector2 vec3 = vec1 - vec2;

		// Assert
		EXPECT_DOUBLE_EQ(vec3.X(), -0.5);
		EXPECT_DOUBLE_EQ(vec3.Y(), -5.0);
	}

	TEST(Vector2_TestSuite, Vector2_Vector2CrossProductBetween2DVectors_ZValueOfCrossProduct)
	{
		// Arrange
		const Vector2 vec1(1.0, -2.5);
		const Vector2 vec2(1.5, 2.5);

		// Act
		const double result = vec1.CrossProduct(vec2);

		// Assert
		EXPECT_DOUBLE_EQ(result, 6.25);
	}

	TEST(Vector2_TestSuite, Vector2_ScalarMultiplicationAssignmentOperator_Vector2)
	{
		// Arrange
		Vector2 vec(1.0, -2.5);
		const double val = 2.5;

		// Act
		vec *= val;

		// Assert
		EXPECT_DOUBLE_EQ(vec.X(), 2.5);
		EXPECT_DOUBLE_EQ(vec.Y(), -6.25);
	}

	TEST(Vector2_TestSuite, Vector2_ScalarMultiplicationOperator_Vector2)
	{
		// Arrange
		const Vector2 vec(1.0, -2.5);
		const double val = 2.5;

		// Act
		const Vector2 vec1 = vec * val;

		// Assert
		EXPECT_DOUBLE_EQ(vec1.X(), 2.5);
		EXPECT_DOUBLE_EQ(vec1.Y(), -6.25);
	}

	TEST(Vector2_TestSuite, Vector2_ExternalScalarMultiplicationOperator_Vector2)
	{
		// Arrange
		const Vector2 vec(1.0, -2.5);
		const double val = 2.5;

		// Act
		const Vector2 vec1 = val * vec;

		// Assert
		EXPECT_DOUBLE_EQ(vec1.X(), 2.5);
		EXPECT_DOUBLE_EQ(vec1.Y(), -6.25);
	}

	TEST(Vector2_TestSuite, Vector2_ScalarDivisionAssignmentOperator_Vector2)
	{
		// Arrange
		Vector2 vec(1.0, -2.5);
		const double val = 2.5;

		// Act
		vec /= val;

		// Assert
		EXPECT_DOUBLE_EQ(vec.X(), 0.4);
		EXPECT_DOUBLE_EQ(vec.Y(), -1.0);
	}

	TEST(Vector2_TestSuite, Vector2_ScalarDivisionOperator_Vector2)
	{
		// Arrange
		const Vector2 vec(1.0, -2.5);
		const double val = 2.5;

		// Act
		const Vector2 vec1 = vec / val;

		// Assert
		EXPECT_DOUBLE_EQ(vec1.X(), 0.4);
		EXPECT_DOUBLE_EQ(vec1.Y(), -1.0);
	}

	TEST(Vector2_TestSuite, Vector2_Vector2Matrix3ProductAssignmentOperator_Vector2)
	{
		// Arrange
		Vector2 vec(1.0, -2.5);
		const Matrix2 mat{
			 1.5, 2.5,
			-1.0, 3.0
		};

		// Act
		vec *= mat;

		// Assert
		EXPECT_DOUBLE_EQ(vec.X(), -4.75);
		EXPECT_DOUBLE_EQ(vec.Y(), -8.5);
	}

	TEST(Vector2_TestSuite, Vector2_Vector2IsZero_Vector2IsZero)
	{
		// Arrange
		const Vector2 vec{ 0.0, 0.0 };
		const Vector2 vec1{ 0.0, 1.75656e-17 };
		const Vector2 vec2{ -1.75656e-17, 1.75656e-17 };

		// Act & Assert
		EXPECT_TRUE(vec.IsZero());
		EXPECT_FALSE(vec1.IsZero());
		EXPECT_FALSE(vec2.IsZero());
	}

	TEST(Vector2_TestSuite, Vector2_Vector2IsNormalized_Vector2IsNormalized)
	{
		// Arrange
		const Vector2 vec1{ 1.0, 0.0 };
		const Vector2 vec2{ 3.0, 0.0 };
		const Vector2 vec3{ cos(M_PI_4), sin(M_PI_4) };

		// Act & Assert
		EXPECT_TRUE(vec1.IsNormalized());
		EXPECT_FALSE(vec2.IsNormalized());
		EXPECT_FALSE(vec3.IsNormalized()); // passes only for IsNormalizedWithTolerance
	}

	TEST(Vector2_TestSuite, Vector2_Vector2IsNormalizedWithTolerance_Vector2IsNormalizedWithTolerance)
	{
		// Arrange
		const Vector2 vec1{ cos(M_PI_4), sin(M_PI_4) };
		const Vector2 vec2{ 1.0, 1.0 };

		// Act & Assert
		EXPECT_TRUE(vec1.IsNormalizedWithTolerance());
		EXPECT_FALSE(vec2.IsNormalizedWithTolerance());
	}

	TEST(Vector2_TestSuite, Vector2_Vector2GetLengthSquared_LengthSquared)
	{
		// Arrange
		const Vector2 vec{ 1.0, 2.0 };

		// Act
		const double lengthSq = vec.GetLengthSquared();

		// Assert
		EXPECT_DOUBLE_EQ(lengthSq, 5.0);
	}

	TEST(Vector2_TestSuite, Vector2_Vector2GetLength_Length)
	{
		// Arrange
		const Vector2 vec{ 3.0, 4.0 };

		// Act
		const double length = vec.GetLength();

		// Assert
		EXPECT_DOUBLE_EQ(length, 5.0);
	}

	TEST(Vector2_TestSuite, Vector2_Vector2Normalize_NormalizedVector2)
	{
		// Arrange
		Vector2 vec1{ 2.0, 3.0 };

		// Act
		vec1.Normalize();

		// Assert
		EXPECT_TRUE(vec1.IsNormalizedWithTolerance());
	}

	TEST(Vector2_TestSuite, Vector2_Vector2DotProduct_DotProduct)
	{
		// Arrange
		const Vector2 vec1{ 2.0, 3.0 };
		const Vector2 vec2{ 1.0, -2.0 };

		// Act
		const double dot = vec1.DotProduct(vec2);

		// Assert
		EXPECT_DOUBLE_EQ(dot, -4.0);
	}

	TEST(Vector2_TestSuite, Vector2_ExternalVector2DotProduct_DotProduct)
	{
		// Arrange
		const Vector2 vec1{ 2.0, 3.0 };
		const Vector2 vec2{ 1.0, -2.0 };

		// Act
		const double dot = DotProduct(vec1, vec2);

		// Assert
		EXPECT_DOUBLE_EQ(dot, -4.0);
	}

	TEST(Vector2_TestSuite, Vector2_Vector2DirectProduct_DirectProduct)
	{
		// Arrange
		Vector2 vec1{ 2.0, 6.0 };
		const Vector2 vec2{ 1.0, -1.5 };

		// Act
		vec1.DirectProduct(vec2);

		// Assert
		EXPECT_DOUBLE_EQ(vec1.X(), 2.0);
		EXPECT_DOUBLE_EQ(vec1.Y(), -9.0);
	}
	TEST(Vector2_TestSuite, Vector2_ProjectOntoVector2_Vector2Projection)
	{
		// Arrange
		const Vector2 vec1{ 2.0, 3.0 };
		const Vector2 vec2{ 1.0, 1.0 };

		// Act
		Vector2 vec3 = vec1.Project(vec2);

		// Assert
		EXPECT_DOUBLE_EQ(vec3.X(), 0.76923076923076927);
		EXPECT_DOUBLE_EQ(vec3.Y(), 1.1538461538461540);
	}

	TEST(Vector2_TestSuite, Vector2_ApplyAngle_RotatedVector2)
	{
		// Arrange
		Vector2 vec{ 2.0, 3.0 };
		const double angle = M_PI_4;

		// Act
		vec.ApplyAngle(angle);

		// Assert
		EXPECT_DOUBLE_EQ(vec.X(), -sqrt(2.0) / 2.0);
		EXPECT_DOUBLE_EQ(vec.Y(), 3.5355339059327373);
	}

	TEST(Vector2_TestSuite, Vector2_Vector2Min_Min)
	{
		// Arrange
		Vector2 vec1{ 2.0, 3.0 };
		const Vector2 vec2{ -1.0, 1.0 };

		// Act
		vec1.Min(vec2);

		// Assert
		EXPECT_DOUBLE_EQ(vec1.X(), -1.0);
		EXPECT_DOUBLE_EQ(vec1.Y(), 1.0);
	}

	TEST(Vector2_TestSuite, Vector2_Vector2Max_Max)
	{
		// Arrange
		Vector2 vec1{ 2.0, 3.0 };
		const Vector2 vec2{ -1.0, 1.0 };

		// Act
		vec1.Max(vec2);

		// Assert
		EXPECT_DOUBLE_EQ(vec1.X(), 2.0);
		EXPECT_DOUBLE_EQ(vec1.Y(), 3.0);
	}

	TEST(Vector2_TestSuite, Vector2_Vector2LinInterpolate_InterpolatedVector)
	{
		// Arrange
		Vector2 vec1{ 2.0, 3.0 };
		const Vector2 vec2{ -1.0, 1.0 };
		const double param = 0.75;

		// Act
		vec1.LinearInterpolate(vec2, param);

		// Assert
		EXPECT_DOUBLE_EQ(vec1.X(), -0.25);
		EXPECT_DOUBLE_EQ(vec1.Y(), 1.5);
	}

	TEST(Vector2_TestSuite, Vector2_ExternalVector2LinInterpolate_InterpolatedVector)
	{
		// Arrange
		const Vector2 vec1{ 2.0, 3.0 };
		const Vector2 vec2{ -1.0, 1.0 };
		const double param = 0.75;

		// Act
		const Vector2 vec3 = LinearInterpolate(vec1, vec2, param);

		// Assert
		EXPECT_DOUBLE_EQ(vec3.X(), -0.25);
		EXPECT_DOUBLE_EQ(vec3.Y(), 1.5);
	}

	
} // Symplektis::UnitTests