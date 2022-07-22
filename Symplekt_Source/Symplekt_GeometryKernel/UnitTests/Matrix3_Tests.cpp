/*! \file  Matrix3_Tests.cpp
 *  \brief Matrix3_Tests
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   15.6.2021
 *
 */

#include "gtest/gtest.h"

#include "Symplekt_GeometryKernel/Matrix3.h"
#include "Symplekt_GeometryKernel/Matrix3Utils.h"
#include "Symplekt_GeometryKernel/Matrix4.h"

namespace Symplektis::UnitTests
{
	using namespace GeometryKernel;
	
	TEST(Matrix3_TestSuite, Matrix3_ConstructFromMatrix4_Matrix3)
	{
		// Arrange
		const Matrix4 M4{
			 1.5, 2.5,  0.1, 0.0,
			-1.0, 3.0, -0.7, 0.0,
			 0.0, 2.0,  5.0, 0.0,
			 1.0, 2.0,  3.0, 1.0
		};

		// Act
		const Matrix3 mat(M4);

		// Assert
		EXPECT_DOUBLE_EQ(mat.Elem(MAT3_11), 1.5);
		EXPECT_DOUBLE_EQ(mat.Elem(MAT3_12), 2.5);
		EXPECT_DOUBLE_EQ(mat.Elem(MAT3_13), 0.1);
		
		EXPECT_DOUBLE_EQ(mat.Elem(MAT3_21), -1.0);
		EXPECT_DOUBLE_EQ(mat.Elem(MAT3_22), 3.0);
		EXPECT_DOUBLE_EQ(mat.Elem(MAT3_23), -0.7);
		
		EXPECT_DOUBLE_EQ(mat.Elem(MAT3_31), 0.0);
		EXPECT_DOUBLE_EQ(mat.Elem(MAT3_32), 2.0);
		EXPECT_DOUBLE_EQ(mat.Elem(MAT3_33), 5.0);
	}

	TEST(Matrix3_TestSuite, ThreeMatrix3s_EqualityComparisonOperator_Matrix3Equality)
	{
		// Arrange
		const Matrix3 mat1{
			-1.0, 3.0, 2.0,
			-2.0, 4.0, 2.0,
			1.0, -1.0, 0.0
		};

		const Matrix3 mat2{
			-1.0, 3.0, 2.0,
			-2.0, 4.0, 2.0,
			1.0, -1.0, 0.0
		};

		const Matrix3 mat3{
			-1.0, -2.0, -1.0,
			-2.0, 3.0, 1.0,
			3.0, -1.0, 3.0
		};

		// Act & Assert
		EXPECT_TRUE(mat1 == mat2);
		EXPECT_FALSE(mat1 != mat2);
		EXPECT_TRUE(mat1 != mat3);
		EXPECT_FALSE(mat1 == mat3);
	}

	TEST(Matrix3_TestSuite, ThreeMatrix3s_EqualityWithTolerance_Matrix3Equality)
	{
		// Arrange
		const Matrix3 mat1{
			-1.0, 3.0, 2.0,
			-2.0, 4.0, 2.0,
			1.0, -1.0, 0.0
		};

		const Matrix3 mat2{
			-1.0, 3.0, 2.0,
			-2.0, 4.0, 2.0,
			1.0, -1.0, 0.000000012345
		};

		const Matrix3 mat3{
			-1.0, 3.0, 2.0,
			-2.0, 4.0, 2.0,
			1.0, -1.0, 0.001
		};

		// Act & Assert
		EXPECT_TRUE(mat1.EqualsWithTolerance(mat2));
		EXPECT_FALSE(mat1.EqualsWithTolerance(mat3));
	}

	TEST(Matrix3_TestSuite, ThreeMatrix3s_StandardAssignmentOperator_Matrix3Equality)
	{
		// Arrange
		const Matrix3 mat1{
			-1.0, 3.0, 2.0,
			-2.0, 4.0, 2.0,
			1.0, -1.0, 0.0
		};
		Matrix3 mat2;

		// Act
		mat2 = mat1;

		// Assert
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_11), -1.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_12), 3.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_13), 2.0);

		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_21), -2.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_22), 4.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_23), 2.0);

		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_31), 1.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_32), -1.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_33), 0.0);
	}

	TEST(Matrix3_TestSuite, Matrix3_AdditionAssignmentOperator_Matrix3)
	{
		// Arrange
		Matrix3 mat1{
			-1.0, 3.0, 2.0,
			-2.0, 4.0, 2.0,
			1.0, -1.0, 0.0
		};

		const Matrix3 mat2{
			-1.0, -2.0, -1.0,
			-2.0, 3.0, 1.0,
			3.0, -1.0, 3.0
		};

		// Act
		mat1 += mat2;

		// Assert
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_11), -2.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_12), 1.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_13), 1.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_21), -4.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_22), 7.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_23), 3.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_31), 4.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_32), -2.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_33), 3.0);
	}

	TEST(Matrix3_TestSuite, Matrix3_SubtractionAssignmentOperator_Matrix3)
	{
		// Arrange
		Matrix3 mat1{
			-1.0, 3.0, 2.0,
			-2.0, 4.0, 2.0,
			1.0, -1.0, 0.0
		};

		const Matrix3 mat2{
			-1.0, -2.0, -1.0,
			-2.0, 3.0, 1.0,
			3.0, -1.0, 3.0
		};

		// Act
		mat1 -= mat2;

		// Assert
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_11), 0.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_12), 5.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_13), 3.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_21), 0.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_22), 1.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_23), 1.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_31), -2.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_32), 0.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_33), -3.0);
	}

	TEST(Matrix3_TestSuite, Matrix3_AdditionOperator_Matrix3)
	{
		// Arrange
		const Matrix3 mat1{
			-1.0, 3.0, 2.0,
			-2.0, 4.0, 2.0,
			1.0, -1.0, 0.0
		};

		const Matrix3 mat2{
			-1.0, -2.0, -1.0,
			-2.0, 3.0, 1.0,
			3.0, -1.0, 3.0
		};

		// Act
		const Matrix3 mat3 = mat1 + mat2;

		// Assert
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_11), -2.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_12), 1.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_13), 1.0);

		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_21), -4.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_22), 7.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_23), 3.0);

		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_31), 4.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_32), -2.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_33), 3.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_11), -1.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_12), 3.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_13), 2.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_21), -2.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_22), 4.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_23), 2.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_31), 1.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_32), -1.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_33), 0.0);
	}

	TEST(Matrix3_TestSuite, Matrix3_SubtractionOperator_Matrix3)
	{
		// Arrange
		const Matrix3 mat1{
			-1.0, 3.0, 2.0,
			-2.0, 4.0, 2.0,
			1.0, -1.0, 0.0
		};

		const Matrix3 mat2{
			-1.0, -2.0, -1.0,
			-2.0, 3.0, 1.0,
			3.0, -1.0, 3.0
		};

		// Act
		const Matrix3 mat3 = mat1 - mat2;

		// Assert
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_11), 0.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_12), 5.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_13), 3.0);

		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_21), 0.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_22), 1.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_23), 1.0);

		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_31), -2.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_32), 0.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_33), -3.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_11), -1.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_12), 3.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_13), 2.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_21), -2.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_22), 4.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_23), 2.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_31), 1.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_32), -1.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_33), 0.0);
	}

	TEST(Matrix3_TestSuite, Matrix3_Matrix3MultiplicationAssignmentOperator_Matrix3)
	{
		// Arrange
		Matrix3 mat1{
			-1.0, 3.0, 2.0,
			-2.0, 4.0, 2.0,
			1.0, -1.0, 0.0
		};

		const Matrix3 mat2{
			-1.0, -2.0, -1.0,
			-2.0, 3.0, 1.0,
			3.0, -1.0, 3.0
		};
		Matrix3 mat3 = mat1;

		// Act
		mat1 *= mat2;
		mat3.Multiply(mat2);

		// Assert
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_11), 1.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_12), 9.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_13), 10.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_21), 0.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_22), 14.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_23), 12.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_31), 1.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_32), -5.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_33), -2.0);

		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_11), 1.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_12), 9.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_13), 10.0);

		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_21), 0.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_22), 14.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_23), 12.0);

		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_31), 1.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_32), -5.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_33), -2.0);
	}

	TEST(Matrix3_TestSuite, Matrix3_Matrix3Premultiply_Matrix3)
	{
		// Arrange
		Matrix3 mat1{
			-1.0, -2.0, -1.0,
			-2.0, 3.0, 1.0,
			3.0, -1.0, 3.0
		};

		const Matrix3 mat2{
			-1.0, 3.0, 2.0,
			-2.0, 4.0, 2.0,
			1.0, -1.0, 0.0
		};

		// Act
		mat1.Premultiply(mat2);

		// Assert
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_11), 1.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_12), 9.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_13), 10.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_21), 0.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_22), 14.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_23), 12.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_31), 1.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_32), -5.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_33), -2.0);
	}

	TEST(Matrix3_TestSuite, Matrix3_Matrix3MultiplicationOperator_Matrix3)
	{
		// Arrange
		const Matrix3 mat1{
			-1.0, 3.0, 2.0,
			-2.0, 4.0, 2.0,
			1.0, -1.0, 0.0
		};

		const Matrix3 mat2{
			-1.0, -2.0, -1.0,
			-2.0, 3.0, 1.0,
			3.0, -1.0, 3.0
		};

		// Act
		const Matrix3 mat3 = mat1 * mat2;

		// Assert
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_11), 1.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_12), 9.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_13), 10.0);

		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_21), 0.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_22), 14.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_23), 12.0);

		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_31), 1.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_32), -5.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_33), -2.0);
	}

	TEST(Matrix3_TestSuite, Matrix3_ScalarMultiplicationAssignmentOperator_Matrix3)
	{
		// Arrange
		Matrix3 mat1{
			-1.0, 3.0, 2.0,
			-2.0, 4.0, 2.0,
			1.0, -1.0, 0.0
		};

		// Act
		mat1 *= 2.25;

		// Assert
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_11), -2.25);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_12), 6.75);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_13), 4.5);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_21), -4.5);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_22), 9.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_23), 4.5);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_31), 2.25);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_32), -2.25);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_33), 0.0);
	}

	TEST(Matrix3_TestSuite, Matrix3_ScalarMultiplicationOperator_Matrix3)
	{
		// Arrange
		const Matrix3 mat1{
			-1.0, 3.0, 2.0,
			-2.0, 4.0, 2.0,
			1.0, -1.0, 0.0
		};

		// Act
		const Matrix3 mat2 = mat1 * 2.25;
		const Matrix3 mat3 = 2.25 * mat1;

		// Assert
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_11), -2.25);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_12), 6.75);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_13), 4.5);

		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_21), -4.5);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_22), 9.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_23), 4.5);

		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_31), 2.25);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_32), -2.25);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_33), 0.0);

		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_11), -2.25);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_12), 6.75);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_13), 4.5);

		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_21), -4.5);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_22), 9.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_23), 4.5);

		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_31), 2.25);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_32), -2.25);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT3_33), 0.0);
	}

	TEST(Matrix3_TestSuite, Matrix3_IsIdentity_Matrix3IsIdentity)
	{
		// Arrange
		const Matrix3 matDefault;
		const Matrix3 mat{
			1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 0.0, 1.000000084557
		};

		// Act & Assert
		EXPECT_TRUE(matDefault.IsIdentity());
		EXPECT_FALSE(mat.IsIdentity());
	}

	TEST(Matrix3_TestSuite, Matrix3_Transpose_Matrix3Transposed)
	{
		// Arrange
		Matrix3 mat1{
			-1.0, 3.0, 2.0,
			-2.0, 4.0, 2.0,
			1.0, -1.0, 0.0
		};

		// Act
		mat1.Transpose();

		// Assert
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_11), -1.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_12), -2.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_13), 1.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_21), 3.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_22), 4.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_23), -1.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_31), 2.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_32), 2.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_33), 0.0);
	}

	TEST(Matrix3_TestSuite, Matrix3_CopyTranspose_Matrix3Transposed)
	{
		// Arrange
		const Matrix3 mat1{
			-1.0, 3.0, 2.0,
			-2.0, 4.0, 2.0,
			1.0, -1.0, 0.0
		};

		// Act
		const Matrix3 mat2 = Transpose(mat1);

		// Assert
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_11), -1.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_12), -2.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_13), 1.0);

		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_21), 3.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_22), 4.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_23), -1.0);

		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_31), 2.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_32), 2.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_33), 0.0);
	}

	TEST(Matrix3_TestSuite, Matrix3_Determinant_Matrix3Determinant)
	{
		// Arrange
		const Matrix3 mat1{
			-1.0, 3.0, 2.0,
			-2.0, 4.0, 2.0,
			1.0, -1.0, 0.0
		};
		const Matrix3 mat2{
			-1.0, 3.0, 2.0,
			-2.0, -4.0, 2.0,
			1.0, -1.0, 0.0
		};

		// Act
		const double det1 = mat1.Determinant();
		const double det2 = mat2.Determinant();

		// Assert
		EXPECT_DOUBLE_EQ(det1, 0.0);
		EXPECT_DOUBLE_EQ(det2, 16.0);
	}

	TEST(Matrix3_TestSuite, Matrix3_Inverse_Matrix3Inverted)
	{
		// Arrange
		Matrix3 mat1{
			-1.0, 3.0, 2.0,
			-2.0, -4.0, 2.0,
			1.0, -1.0, 0.0
		};

		// Act
		mat1.Inverse();

		// Assert
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_11), 0.125);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_12), -0.125);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_13), 0.875);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_21), 0.125);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_22), -0.125);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_23), -0.125);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_31), 0.375);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_32), 0.125);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT3_33), 0.625);
	}

	TEST(Matrix3_TestSuite, Matrix3_CopyInverse_Matrix3Inverted)
	{
		// Arrange
		const Matrix3 mat1{
			-1.0, 3.0, 2.0,
			-2.0, -4.0, 2.0,
			1.0, -1.0, 0.0
		};

		// Act
		const Matrix3 mat2 = Inverse(mat1);

		// Assert
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_11), 0.125);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_12), -0.125);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_13), 0.875);

		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_21), 0.125);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_22), -0.125);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_23), -0.125);

		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_31), 0.375);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_32), 0.125);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT3_33), 0.625);
	}
	
} // Symplektis::UnitTests