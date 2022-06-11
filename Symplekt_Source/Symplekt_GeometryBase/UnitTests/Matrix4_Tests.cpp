/*! \file  Matrix4_Tests.cpp
 *  \brief Matrix4_Tests
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   15.6.2021
 *
 */

#include "gtest/gtest.h"

#include "../../Symplekt_UtilityGeneral/NumericUtils.h"

#include "../Matrix4.h"
#include "../Matrix4Utils.h"
#include "../Vector3.h"
#include "../Quaternion.h"

#include <corecrt_math_defines.h>

namespace Symplektis::UnitTests
{
	using namespace GeometryBase;
	TEST(Matrix4_TestSuite, Matrix4_EqualityComparisonOperator_Matrix4Equality)
	{
		// Arrange
		const Matrix4 mat1{
			-1.0, 3.0, 2.0, 0.0,
			-2.0, 4.0, 2.0, 0.0,
			1.0, -1.0, 0.0, 0.0,
			1.0,  1.0, 0.0, 0.0,
		};

		const Matrix4 mat2{
			-1.0, 3.0, 2.0, 0.0,
			-2.0, 4.0, 2.0, 0.0,
			1.0, -1.0, 0.0, 0.0,
			1.0,  1.0, 0.0, 0.0,
		};

		const Matrix4 mat3{
			-1.0, 3.0, 2.0, 0.0,
			-2.0, 4.000045, 2.0, 0.0,
			1.0, -1.0, 0.0, 0.0,
			1.0,  1.0, 0.0, 0.0,
		};

		// Act & Assert
		EXPECT_TRUE(mat1 == mat2);
		EXPECT_FALSE(mat1 != mat2);
		EXPECT_TRUE(mat1 != mat3);
		EXPECT_FALSE(mat1 == mat3);
	}

	TEST(Matrix4_TestSuite, Matrix4_EqualityWithToleranceOperator_Matrix4Equality)
	{
		// Arrange
		const Matrix4 mat1{
			-1.0, 3.0, 2.0, 0.0,
			-2.0, 4.0, 2.0, 0.0,
			1.0, -1.0, 0.0, 0.0,
			1.0,  1.0, 0.0, 1.0
		};

		const Matrix4 mat2{
			-1.0, 3.0, 2.0, 0.0,
			-2.0, 4.0, 2.0, 0.0,
			1.0, -1.0, 0.0, 0.0,
			1.0,  1.0, 0.0, 1.0000007878
		};

		const Matrix4 mat3{
			-1.0, 3.0, 2.0, 0.0,
			-2.0, 4.000045, 2.0, 0.0,
			1.0, -1.0, 0.0, 0.0,
			1.0,  1.0, 0.0, 1.0
		};

		// Act & Assert
		EXPECT_TRUE(mat1.EqualsWithTolerance(mat2));
		EXPECT_FALSE(mat1.EqualsWithTolerance(mat3));
	}

	TEST(Matrix4_TestSuite, Matrix4_StandardAssignmentOperator_Matrix4Equality)
	{
		// Arrange
		const Matrix4 mat1{
			-1.0, 3.0, 2.0, 0.0,
			-2.0, 4.0, 2.0, 0.0,
			1.0, -1.0, 0.0, 0.0,
			1.0,  1.0, 0.0, 1.0
		};
		Matrix4 mat2;

		// Act
		mat2 = mat1;

		// Assert
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_11), -1.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_12), 3.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_13), 2.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_14), 0.0);

		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_21), -2.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_22), 4.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_23), 2.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_24), 0.0);

		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_31), 1.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_32), -1.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_33), 0.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_34), 0.0);

		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_41), 1.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_42), 1.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_43), 0.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_44), 1.0);
	}
	
	TEST(Matrix4_TestSuite, Matrix4_AdditionAssignmentOperator_Matrix4)
	{
		// Arrange
		Matrix4 mat1{
			-1.0, 3.0, 2.0, 0.0,
			-2.0, 4.0, 2.0, 0.0,
			1.0, -1.0, 0.0, 0.0,
			1.0,  1.0, 0.0, 1.0
		};

		const Matrix4 mat2{
			1.0, 3.5, 1.0, 0.0,
			-7.0, 4.5, 2.0, 0.0,
			1.0, -2.0, 1.0, 0.0,
			1.0,  1.0, 0.0, 1.0
		};

		// Act
		mat1 += mat2;

		// Assert
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_11), 0.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_12), 6.5);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_13), 3.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_14), 0.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_21), -9.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_22), 8.5);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_23), 4.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_24), 0.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_31), 2.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_32), -3.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_33), 1.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_34), 0.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_41), 2.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_42), 2.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_43), 0.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_44), 2.0);
	}

	TEST(Matrix4_TestSuite, Matrix4_SubtractionAssignmentOperator_Matrix4)
	{
		// Arrange
		Matrix4 mat1{
			-1.0, 3.0, 2.0, 0.0,
			-2.0, 4.0, 2.0, 0.0,
			1.0, -1.0, 0.0, 0.0,
			1.0,  1.0, 0.0, 1.0
		};

		const Matrix4 mat2{
			1.0, 3.5, 1.0, 0.0,
			-7.0, 4.5, 2.0, 0.0,
			1.0, -2.0, 1.0, 0.0,
			1.0,  1.0, 0.0, 1.0
		};

		// Act
		mat1 -= mat2;

		// Assert
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_11), -2.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_12), -0.5);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_13), 1.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_14), 0.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_21), 5.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_22), -0.5);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_23), 0.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_24), 0.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_31), 0.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_32), 1.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_33), -1.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_34), 0.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_41), 0.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_42), 0.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_43), 0.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_44), 0.0);
	}

	TEST(Matrix4_TestSuite, Matrix4_AdditionOperator_Matrix4)
	{
		// Arrange
		const Matrix4 mat1{
			-1.0, 3.0, 2.0, 0.0,
			-2.0, 4.0, 2.0, 0.0,
			1.0, -1.0, 0.0, 0.0,
			1.0,  1.0, 0.0, 1.0
		};

		const Matrix4 mat2{
			1.0, 3.5, 1.0, 0.0,
			-7.0, 4.5, 2.0, 0.0,
			1.0, -2.0, 1.0, 0.0,
			1.0,  1.0, 0.0, 1.0
		};

		// Act
		Matrix4 mat3 = mat1 + mat2;

		// Assert
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_11), 0.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_12), 6.5);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_13), 3.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_14), 0.0);

		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_21), -9.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_22), 8.5);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_23), 4.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_24), 0.0);

		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_31), 2.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_32), -3.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_33), 1.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_34), 0.0);

		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_41), 2.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_42), 2.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_43), 0.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_44), 2.0);
	}

	TEST(Matrix4_TestSuite, Matrix4_SubtractionOperator_Matrix4)
	{
		// Arrange
		const Matrix4 mat1{
			-1.0, 3.0, 2.0, 0.0,
			-2.0, 4.0, 2.0, 0.0,
			1.0, -1.0, 0.0, 0.0,
			1.0,  1.0, 0.0, 1.0
		};

		const Matrix4 mat2{
			1.0, 3.5, 1.0, 0.0,
			-7.0, 4.5, 2.0, 0.0,
			1.0, -2.0, 1.0, 0.0,
			1.0,  1.0, 0.0, 1.0
		};

		// Act
		const Matrix4 mat3 = mat1 - mat2;

		// Assert
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_11), -2.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_12), -0.5);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_13), 1.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_14), 0.0);

		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_21), 5.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_22), -0.5);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_23), 0.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_24), 0.0);

		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_31), 0.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_32), 1.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_33), -1.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_34), 0.0);

		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_41), 0.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_42), 0.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_43), 0.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_44), 0.0);
	}

	TEST(Matrix4_TestSuite, Matrix4_Matrix4MultiplicationAssignmentOperator_Matrix4)
	{
		// Arrange
		Matrix4 mat1{
			-1.0, 3.0, 2.0, 0.0,
			-2.0, 4.0, 2.0, 0.0,
			1.0, -1.0, 0.0, 0.0,
			1.0,  1.0, 0.0, 1.0
		};

		const Matrix4 mat2{
			1.0, 3.5, 1.0, 0.0,
			-7.0, 4.5, 2.0, 0.0,
			1.0, -2.0, 1.0, 0.0,
			1.0,  1.0, 0.0, 1.0
		};
		Matrix4 mat3 = mat1;

		// Act
		mat1 *= mat2;
		mat3.Multiply(mat2);

		// Assert
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_11), -20.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_12), 6.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_13), 7.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_14), 0.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_21), -28.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_22), 7.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_23), 8.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_24), 0.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_31), 8.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_32), -1.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_33), -1.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_34), 0.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_41), -5.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_42), 9.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_43), 3.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_44), 1.0);

		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_11), -20.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_12), 6.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_13), 7.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_14), 0.0);

		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_21), -28.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_22), 7.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_23), 8.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_24), 0.0);

		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_31), 8.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_32), -1.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_33), -1.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_34), 0.0);

		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_41), -5.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_42), 9.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_43), 3.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_44), 1.0);
	}

	TEST(Matrix4_TestSuite, Matrix4_Matrix4Premultiply_Matrix4)
	{
		// Arrange
		Matrix4 mat1{
			-1.0, 3.0, 2.0, 0.0,
			-2.0, 4.0, 2.0, 0.0,
			1.0, -1.0, 0.0, 0.0,
			1.0,  1.0, 0.0, 1.0
		};

		const Matrix4 mat2{
			1.0, 3.5, 1.0, 0.0,
			-7.0, 4.5, 2.0, 0.0,
			1.0, -2.0, 1.0, 0.0,
			1.0,  1.0, 0.0, 1.0
		};

		// Act
		mat1.Premultiply(mat2);

		// Assert
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_11), -7.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_12), 16.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_13), 9.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_14), 0.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_21), 0.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_22), -5.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_23), -5.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_24), 0.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_31), 4.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_32), -6.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_33), -2.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_34), 0.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_41), -2.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_42), 8.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_43), 4.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_44), 1.0);
	}

	TEST(Matrix4_TestSuite, Matrix4_ScalarMultiplicationAssignmentOperator_Matrix4)
	{
		// Arrange
		Matrix4 mat1{
			1.0, 3.5, 1.0, 0.0,
			-7.0, 4.5, 2.0, 0.0,
			1.0, -2.0, 1.0, 0.0,
			1.0,  1.0, 0.0, 1.0
		};

		// Act
		mat1 *= 2.25;

		// Assert
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_11), 2.25);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_12), 7.875);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_13), 2.25);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_14), 0.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_21), -15.75);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_22), 10.125);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_23), 4.5);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_24), 0.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_31), 2.25);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_32), -4.5);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_33), 2.25);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_34), 0.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_41), 2.25);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_42), 2.25);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_43), 0.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_44), 2.25);
	}

	TEST(Matrix4_TestSuite, Matrix4_ScalarMultiplicationOperator_Matrix4)
	{
		// Arrange
		const Matrix4 mat1{
			1.0, 3.5, 1.0, 0.0,
			-7.0, 4.5, 2.0, 0.0,
			1.0, -2.0, 1.0, 0.0,
			1.0,  1.0, 0.0, 1.0
		};

		// Act
		const Matrix4 mat2 = mat1 * 2.25;
		const Matrix4 mat3 = 2.25 * mat1;

		// Assert
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_11), 2.25);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_12), 7.875);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_13), 2.25);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_14), 0.0);

		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_21), -15.75);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_22), 10.125);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_23), 4.5);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_24), 0.0);

		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_31), 2.25);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_32), -4.5);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_33), 2.25);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_34), 0.0);

		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_41), 2.25);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_42), 2.25);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_43), 0.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_44), 2.25);

		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_11), 2.25);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_12), 7.875);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_13), 2.25);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_14), 0.0);

		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_21), -15.75);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_22), 10.125);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_23), 4.5);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_24), 0.0);

		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_31), 2.25);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_32), -4.5);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_33), 2.25);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_34), 0.0);

		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_41), 2.25);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_42), 2.25);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_43), 0.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT4_44), 2.25);
	}

	TEST(Matrix4_TestSuite, Matrix4_IsIdentity_Matrix4IsIdentity)
	{
		// Arrange
		const Matrix4 matDefault;
		const Matrix4 mat{
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.000000084557, 0.0,
			0.0, 0.0, 0.0, 1.0
		};

		// Act & Assert
		EXPECT_TRUE(matDefault.IsIdentity());
		EXPECT_FALSE(mat.IsIdentity());
	}

	TEST(Matrix4_TestSuite, Matrix4_Matrix4Transpose_Matrix4Transposed)
	{
		// Arrange
		Matrix4 mat1{
			1.0, 3.5, 1.0, 0.0,
			-7.0, 4.5, 2.0, 0.0,
			1.0, -2.0, 1.0, 0.0,
			1.0,  1.0, 0.0, 1.0
		};

		// Act
		mat1.Transpose();

		// Assert
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_11), 1.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_12), -7.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_13), 1.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_14), 1.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_21), 3.5);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_22), 4.5);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_23), -2.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_24), 1.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_31), 1.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_32), 2.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_33), 1.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_34), 0.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_41), 0.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_42), 0.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_43), 0.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_44), 1.0);
	}

	TEST(Matrix4_TestSuite, Matrix4_Matrix4CopyTranspose_Matrix4Transposed)
	{
		// Arrange
		const Matrix4 mat1{
			1.0, 3.5, 1.0, 0.0,
			-7.0, 4.5, 2.0, 0.0,
			1.0, -2.0, 1.0, 0.0,
			1.0,  1.0, 0.0, 1.0
		};

		// Act
		const Matrix4 mat2 = Transpose(mat1);

		// Assert
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_11), 1.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_12), -7.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_13), 1.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_14), 1.0);

		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_21), 3.5);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_22), 4.5);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_23), -2.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_24), 1.0);

		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_31), 1.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_32), 2.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_33), 1.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_34), 0.0);

		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_41), 0.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_42), 0.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_43), 0.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_44), 1.0);
	}

	TEST(Matrix4_TestSuite, Matrix4_Determinant_Matrix4Determinant)
	{
		// Arrange
		const Matrix4 mat1{
			1.0, 3.5, 1.0, 0.0,
			-7.0, 4.5, 2.0, 0.0,
			1.0, -2.0, 1.0, 0.0,
			1.0,  1.0, 0.0, 1.0
		};
		const Matrix4 mat2{
			1.5, 10.75, 1.5, 0.0,
			1.0, 3.5, 1.0, 0.0,
			1.0, -2.0, 1.0, 0.0,
			1.0,  1.0, 0.0, 1.0
		};

		// Act
		const double det1 = mat1.Determinant();
		const double det2 = mat2.Determinant();

		// Assert
		EXPECT_DOUBLE_EQ(det1, 49.5);
		EXPECT_DOUBLE_EQ(det2, 0.0);
	}

	TEST(Matrix4_TestSuite, Matrix4_Inverse_Matrix4Inverted)
	{
		// Arrange
		Matrix4 mat1{
			5.0, 3.5, 10.0, 0.0,
			-7.0, 4.5, 2.0, 0.0,
			1.0, -2.0, 1.0, 0.0,
			1.0,  1.0, 0.0, 1.0
		};

		// Act
		mat1.Inverse();

		// Assert
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_11), 0.050295857988165681);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_12), -0.13905325443786981);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_13), -0.22485207100591714);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_14), 0.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_21), 0.053254437869822487);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_22), -0.029585798816568046);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_23), -0.47337278106508873);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_24), 0.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_31), 0.056213017751479286);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_32), 0.079881656804733719);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_33), 0.27810650887573962);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_34), 0.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_41), -0.10355029585798817);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_42), 0.16863905325443787);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_43), 0.69822485207100593);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT4_44), 1.0);
	}

	TEST(Matrix4_TestSuite, Matrix4_CopyInverse_Matrix4Inverted)
	{
		// Arrange
		const Matrix4 mat1{
			5.0, 3.5, 10.0, 0.0,
			-7.0, 4.5, 2.0, 0.0,
			1.0, -2.0, 1.0, 0.0,
			1.0,  1.0, 0.0, 1.0
		};

		// Act
		const Matrix4 mat2 = Inverse(mat1);

		// Assert
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_11), 0.050295857988165681);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_12), -0.13905325443786981);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_13), -0.22485207100591714);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_14), 0.0);

		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_21), 0.053254437869822487);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_22), -0.029585798816568046);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_23), -0.47337278106508873);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_24), 0.0);

		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_31), 0.056213017751479286);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_32), 0.079881656804733719);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_33), 0.27810650887573962);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_34), 0.0);

		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_41), -0.10355029585798817);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_42), 0.16863905325443787);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_43), 0.69822485207100593);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT4_44), 1.0);
	}

	TEST(Matrix4_TestSuite, Matrix4_ComposeFromTRS_Matrix4Composed)
	{
		// Arrange
		const Vector3 translation{ -1.0, 2.0, 5.0 }; // translation vector
		
		const Vector3 axis{ 1.0, 0.0, 0.0 };
		const double angle = M_PI / 3.0;
		const Quaternion quat(axis, angle); // quaternion corresponding to 60 deg rotation about x-axis

		const Vector3 scale{ 0.5, 0.5, 1.0 }; // scale vector

		// Act
		const Matrix4 transformMat{ translation, scale, quat };
		Vector3 testVector{ 1.0, 1.0, 1.0 };
		testVector *= transformMat;

		// Assert
		EXPECT_DOUBLE_EQ(transformMat.Elem(MAT4_11), 0.5);
		EXPECT_DOUBLE_EQ(transformMat.Elem(MAT4_12), 0.0);
		EXPECT_DOUBLE_EQ(transformMat.Elem(MAT4_13), 0.0);
		EXPECT_DOUBLE_EQ(transformMat.Elem(MAT4_14), 0.0);

		EXPECT_DOUBLE_EQ(transformMat.Elem(MAT4_21), 0.0);
		EXPECT_DOUBLE_EQ(transformMat.Elem(MAT4_22), 0.25);
		EXPECT_DOUBLE_EQ(transformMat.Elem(MAT4_23), 0.43301270189221930);
		EXPECT_DOUBLE_EQ(transformMat.Elem(MAT4_24), 0.0);

		EXPECT_DOUBLE_EQ(transformMat.Elem(MAT4_31), 0.0);
		EXPECT_DOUBLE_EQ(transformMat.Elem(MAT4_32), -0.86602540378443860);
		EXPECT_DOUBLE_EQ(transformMat.Elem(MAT4_33), 0.50000000000000011);
		EXPECT_DOUBLE_EQ(transformMat.Elem(MAT4_34), 0.0);

		EXPECT_DOUBLE_EQ(transformMat.Elem(MAT4_41), -1.0);
		EXPECT_DOUBLE_EQ(transformMat.Elem(MAT4_42), 2.0);
		EXPECT_DOUBLE_EQ(transformMat.Elem(MAT4_43), 5.0);
		EXPECT_DOUBLE_EQ(transformMat.Elem(MAT4_44), 1.0);

		EXPECT_DOUBLE_EQ(testVector.X(), 0.071428571428571425);
		EXPECT_DOUBLE_EQ(testVector.Y(), 0.097573243127459908);
		EXPECT_DOUBLE_EQ(testVector.Z(), -0.052289343397776925);
	}

	TEST(Matrix4_TestSuite, Matrix4_DecomposeToTRS_Matrix4Decomposed)
	{
		// Arrange
		const Matrix4 mat{
			 0.5,                  0.0,                 0.0, 0.0,
			 0.0,                 0.25, 0.43301270189221930, 0.0,
			 0.0, -0.86602540378443860, 0.50000000000000011, 0.0,
			-1.0,                  2.0,                 5.0, 1.0
		};

		// Act
		auto [translation, scale, orientation] = mat.Decompose();

		// Assert
		EXPECT_DOUBLE_EQ(translation.X(), -1.0);
		EXPECT_DOUBLE_EQ(translation.Y(), 2.0);
		EXPECT_DOUBLE_EQ(translation.Z(), 5.0);

		EXPECT_DOUBLE_EQ(scale.X(), 0.5);
		EXPECT_DOUBLE_EQ(scale.Y(), 0.5);
		EXPECT_DOUBLE_EQ(scale.Z(), 1.0);

		EXPECT_DOUBLE_EQ(orientation.X(), -0.5);
		EXPECT_DOUBLE_EQ(orientation.Y(), 0.0);
		EXPECT_DOUBLE_EQ(orientation.Z(), 0.0);
		EXPECT_DOUBLE_EQ(orientation.W(), 0.86602540378443849);
	}
	
} // Symplektis::UnitTests