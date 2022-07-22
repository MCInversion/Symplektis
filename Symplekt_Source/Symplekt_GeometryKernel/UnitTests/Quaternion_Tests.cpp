/*! \file  Quaternion_Tests.cpp
 *  \brief Quaternion_Tests
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   19.6.2021
 *
 */

#include "gtest/gtest.h"

#include "Symplekt_UtilityGeneral/ToleranceSettings.h"
#include "Symplekt_UtilityGeneral/NumericUtils.h"

#include "Symplekt_GeometryKernel/Vector3.h"
#include "Symplekt_GeometryKernel/Matrix3.h"
#include "Symplekt_GeometryKernel/Quaternion.h"
#include "Symplekt_GeometryKernel/QuaternionUtils.h"

#include <corecrt_math_defines.h>

namespace Symplektis::UnitTests
{
	using namespace GeometryKernel;

	TEST(Quaternion_TestSuite, Quaternion_ConstructFromAxisAndAngle_Quaternion)
	{
		// Arrange
		const Vector3 axis{ 1.0, 0.0, 0.0 };
		const double angle = M_PI_4;

		// Act
		const Quaternion quat(axis, angle);

		// Assert
		EXPECT_DOUBLE_EQ(quat.X(), 0.38268343236508978);
		EXPECT_DOUBLE_EQ(quat.Y(), 0.0);
		EXPECT_DOUBLE_EQ(quat.Z(), 0.0);
		EXPECT_DOUBLE_EQ(quat.W(), 0.92387953251128674);
	}

	TEST(Quaternion_TestSuite, Quatenion_ConstructFromRotationMatrix_Quaternion)
	{
		// Arrange
		const Matrix3 mat{
			1.0,       0.0,        0.0,
			0.0, M_SQRT1_2, -M_SQRT1_2,
			0.0, M_SQRT1_2,  M_SQRT1_2
		};

		// Act
		const Quaternion quat(mat);

		// Assert
		EXPECT_DOUBLE_EQ(quat.X(), 0.38268343236508978);
		EXPECT_DOUBLE_EQ(quat.Y(), 0.0);
		EXPECT_DOUBLE_EQ(quat.Z(), 0.0);
		EXPECT_DOUBLE_EQ(quat.W(), 0.92387953251128674);		
	}

	TEST(Quaternion_TestSuite, Quaternion_QuaternionEqualityComparisonOperator_QuaternionsEqual)
	{
		// Arrange
		const Quaternion quat1{ 0.5, 0.5, 0.5, 1.0 };
		const Quaternion quat2{ 0.5, 0.5, 0.5, 1.0 };
		const Quaternion quat3{ 0.5, 0.5, 0.50000456457, 1.0 };

		// Act & Assert
		EXPECT_TRUE(quat1 == quat2);
		EXPECT_FALSE(quat1 != quat2);
		EXPECT_FALSE(quat2 == quat3);
		EXPECT_TRUE(quat2 != quat3);
	}

	TEST(Quaternion_TestSuite, Quaternion_QuaternionEqualityWithToleranceOperator_QuaternionsEqual)
	{
		// Arrange
		const Quaternion quat1{ 0.5, 0.5, 0.5, 1.0 };
		const Quaternion quat2{ 0.5, 0.5, 0.5000001124, 1.0 };
		const Quaternion quat3{ 0.5, 0.5, 0.5004545444, 1.0 };

		// Act & Assert
		EXPECT_TRUE(quat1.EqualsWithTolerance(quat2));
		EXPECT_FALSE(quat2.EqualsWithTolerance(quat3));
	}

	TEST(Quaternion_TestSuite, Quaternion_QuaternionCopyAssignmentOperator_Quaternion)
	{
		// Arrange
		const Quaternion quat1{ 0.5, 0.5, 0.5, 1.0 };

		// Act
		const Quaternion quat2 = quat1;

		// Assert
		EXPECT_DOUBLE_EQ(quat2.X(), 0.5);
		EXPECT_DOUBLE_EQ(quat2.Y(), 0.5);
		EXPECT_DOUBLE_EQ(quat2.Z(), 0.5);
		EXPECT_DOUBLE_EQ(quat2.W(), 1.0);
	}

	TEST(Quaternion_TestSuite, Quaternion_QuaternionMultiplicationAssignmentOperator_Quaternion)
	{
		// Arrange
		Quaternion quat1{ 0.5, 0.5, 0.5, 1.0 };
		const Quaternion quat2{ 0.5, 0.5, 0.5, 0.5 };

		// Act
		quat1 *= quat2;

		// Assert
		EXPECT_DOUBLE_EQ(quat1.X(), 0.75);
		EXPECT_DOUBLE_EQ(quat1.Y(), 0.625);
		EXPECT_DOUBLE_EQ(quat1.Z(), 0.875);
		EXPECT_DOUBLE_EQ(quat1.W(), -0.375);
	}

	TEST(Quaternion_TestSuite, Quaternion_ExternalQuaternionMultiplicationOperator_Quaternion)
	{
		// Arrange
		const Quaternion quat1{ 0.5, 0.5, 0.5, 1.0 };
		const Quaternion quat2{ 0.5, 0.5, 0.5, 0.5 };

		// Act
		const Quaternion quat3 = quat1 * quat2;

		// Assert
		EXPECT_DOUBLE_EQ(quat3.X(), 0.75);
		EXPECT_DOUBLE_EQ(quat3.Y(), 0.625);
		EXPECT_DOUBLE_EQ(quat3.Z(), 0.875);
		EXPECT_DOUBLE_EQ(quat3.W(), -0.375);
	}

	TEST(Quaternion_TestSuite, Quaternion_QuaternionScalarMultiplicationAssignmnentOperator_Quaternion)
	{
		// Arrange
		Quaternion quat{ 0.5, 0.5, 0.5, 1.0 };
		const double value = 2.25;

		// Act
		quat *= value;

		// Assert
		EXPECT_DOUBLE_EQ(quat.X(), 1.125);
		EXPECT_DOUBLE_EQ(quat.Y(), 1.125);
		EXPECT_DOUBLE_EQ(quat.Z(), 1.125);
		EXPECT_DOUBLE_EQ(quat.W(), 2.25);
	}

	TEST(Quaternion_TestSuite, Quaternion_ExternalQuaternionScalarMultiplicationOperator_Quaternion)
	{
		// Arrange
		const Quaternion quat1{ 0.5, 0.5, 0.5, 1.0 };
		const double value = 2.25;

		// Act
		const Quaternion quat2 = value * quat1;

		// Assert
		EXPECT_DOUBLE_EQ(quat2.X(), 1.125);
		EXPECT_DOUBLE_EQ(quat2.Y(), 1.125);
		EXPECT_DOUBLE_EQ(quat2.Z(), 1.125);
		EXPECT_DOUBLE_EQ(quat2.W(), 2.25);
	}

	TEST(Quaternion_TestSuite, Quaternion_QuaternionVector3MultiplicationAssignmentOperator_RotatedVector3)
	{
		// Arrange
		const Vector3 axis{ 1.0, 0.0, 0.0 };
		const double angle = M_PI_4;
		const Quaternion quat(axis, angle);
		Vector3 testZVect{ 0.0, 0.0, 1.0 };

		// Act
		testZVect *= quat;

		// Assert
		EXPECT_DOUBLE_EQ(testZVect.X(), 0.0);
		EXPECT_DOUBLE_EQ(testZVect.Y(), -M_SQRT1_2);
		EXPECT_DOUBLE_EQ(testZVect.Z(), M_SQRT1_2);
	}

	TEST(Quaternion_TestSuite, Quaternion_IsZero_QuaternionIsZero)
	{
		// Arrange
		const Quaternion quat1{ 0.0, 0.0, 0.0, 0.0 };
		const Quaternion quat2{ 0.0, 0.0, 0.0, 1e-5 };
		const Quaternion quat3; // default

		// Act & Assert
		EXPECT_TRUE(quat1.IsZero());
		EXPECT_FALSE(quat2.IsZero());
		EXPECT_FALSE(quat3.IsZero());
	}

	TEST(Quaternion_TestSuite, Quaternion_GetLengthAndGetLengthSquared_QuaternionLengthAndLengthSquared)
	{
		// Arrange
		const Quaternion quat{ 0.5, 0.5, 0.5, 1.0 };

		// Act
		const double lengthSq = quat.GetLengthSquared();
		const double length = quat.GetLength();

		// Assert
		EXPECT_DOUBLE_EQ(lengthSq, 1.75);
		EXPECT_DOUBLE_EQ(length, sqrt(1.75));
	}

	TEST(Quaternion_TestSuite, Quaternion_Normalize_QuaternionNormalized)
	{
		// Arrange
		Quaternion quat{ 0.5, 0.5, 0.5, 1.0 };

		// Act
		quat.Normalize();

		// Assert
		const double expectLen = sqrt(1.75);
		EXPECT_DOUBLE_EQ(quat.X(), 0.5 / expectLen);
		EXPECT_DOUBLE_EQ(quat.Y(), 0.5 / expectLen);
		EXPECT_DOUBLE_EQ(quat.Z(), 0.5 / expectLen);
		EXPECT_DOUBLE_EQ(quat.W(), 1.0 / expectLen);
	}

	TEST(Quaternion_TestSuite, Quaternion_Conjugate_ConjugateQuaternion)
	{
		// Arrange
		Quaternion quat{ 0.5, 0.5, 0.5, 1.0 };

		// Act
		quat.Conjugate();

		// Assert
		EXPECT_DOUBLE_EQ(quat.X(), -0.5);
		EXPECT_DOUBLE_EQ(quat.Y(), -0.5);
		EXPECT_DOUBLE_EQ(quat.Z(), -0.5);
		EXPECT_DOUBLE_EQ(quat.W(), 1.0);
	}
	
	TEST(Quaternion_TestSuite, Quaternion_AngleToAnotherQuaternion_AngleBetweenQuaternions)
	{
		// Arrange
		const Quaternion quat1{ 0.38268343236508978, 0.0, 0.0,0.92387953251128674 };

		const Vector3 axis{ 1.0, 0.0, 0.0 };
		const double angle = M_PI / 3.0;
		const Quaternion quat2(axis, angle);

		// Act
		const double angleTo = quat1.AngleTo(quat2);

		// Assert
		const double expectedAngle = angle - M_PI_4;
		const double epsilon = Util::GetCoordinateTolerance();
		EXPECT_TRUE(Util::EqualsWithTolerance(angleTo, expectedAngle, epsilon));
	}

	TEST(Quaternion_TestSuite, Quaternion_ComputeLookAtQuaternionGeneralLookDirection_LookAtQuaternion)
	{
		// Arrange
		const Vector3 lookDirection{ 1.0, -0.5, 1.3 };
		const Vector3 upVector{ 0.0, 0.0, 1.0 };

		// Act
		const Quaternion lookAtQuat = ComputeLookAtQuaternion(lookDirection, upVector);

		// Assert
		EXPECT_DOUBLE_EQ(lookAtQuat.X(), -0.095830565091809441);
		EXPECT_DOUBLE_EQ(lookAtQuat.Y(), -0.40594478805112311);
		EXPECT_DOUBLE_EQ(lookAtQuat.Z(), -0.20881309176923399);
		EXPECT_DOUBLE_EQ(lookAtQuat.W(), 0.88454645132637710);
	}

	TEST(Quaternion_TestSuite, Quaternion_ComputeLookAtQuaternionLookDirCollinearWithUpVect_LookAtQuaternion)
	{
		// Arrange
		const Vector3 lookDirNegZ{ 0.0, 0.0, -2.0 };
		const Vector3 upVector{ 0.0, 0.0, 1.0 };

		// Act
		const Quaternion lookAtQuatNegZ = ComputeLookAtQuaternion(lookDirNegZ, upVector);

		// Assert
		EXPECT_DOUBLE_EQ(lookAtQuatNegZ.X(), -M_SQRT1_2);
		EXPECT_DOUBLE_EQ(lookAtQuatNegZ.Y(), 0.0);
		EXPECT_DOUBLE_EQ(lookAtQuatNegZ.Z(), M_SQRT1_2);
		EXPECT_DOUBLE_EQ(lookAtQuatNegZ.W(), 0.0);
	}

} // Symplektis::UnitTests