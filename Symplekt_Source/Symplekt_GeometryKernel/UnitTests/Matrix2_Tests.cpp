/*! \file  Matrix2_Tests.cpp
 *  \brief Matrix2_Tests
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   26.6.2021
 *
 */

#include "gtest/gtest.h"

#include "Symplekt_GeometryKernel/Matrix2.h"
#include "Symplekt_GeometryKernel/Matrix2Utils.h"
#include "Symplekt_GeometryKernel/Vector2.h"

#include <corecrt_math_defines.h>

namespace Symplektis::UnitTests
{
	using namespace GeometryKernel;
	TEST(Matrix2_TestSuite, Matrix2_Matrix2ConstructRotationFromAngle_RotationMatrix2)
	{
		// Arrange
		const double angle = M_PI_4;
		Vector2 testVector{ M_SQRT1_2, M_SQRT1_2 };

		// Act
		const Matrix2 mat{ angle };
		testVector *= mat;

		// Assert
		EXPECT_DOUBLE_EQ(mat.Elem(MAT2_11), M_SQRT1_2);
		EXPECT_DOUBLE_EQ(mat.Elem(MAT2_12), -M_SQRT1_2);
		EXPECT_DOUBLE_EQ(mat.Elem(MAT2_21), M_SQRT1_2);
		EXPECT_DOUBLE_EQ(mat.Elem(MAT2_22), M_SQRT1_2);

		EXPECT_DOUBLE_EQ(testVector.X(), 0.0);
		EXPECT_DOUBLE_EQ(testVector.Y(), 1.0);
	}
	TEST(Matrix2_TestSuite, ThreeMatrix2s_EqualityComparisonOperator_Matrix2Equality)
	{
		// Arrange
		const Matrix2 mat1{
			-1.0, 3.0,
			-2.0, 4.0
		};

		const Matrix2 mat2{
			-1.0, 3.0,
			-2.0, 4.0
		};

		const Matrix2 mat3{
			-1.0, -2.0,
			-2.0, 3.0
		};

		// Act & Assert
		EXPECT_TRUE(mat1 == mat2);
		EXPECT_FALSE(mat1 != mat2);
		EXPECT_TRUE(mat1 != mat3);
		EXPECT_FALSE(mat1 == mat3);
	}

	TEST(Matrix2_TestSuite, ThreeMatrix2s_EqualityWithTolerance_Matrix2Equality)
	{
		// Arrange
		const Matrix2 mat1{
			-1.0, 3.0,
			-2.0, 4.0
		};

		const Matrix2 mat2{
			-1.0, 3.0,
			-2.0, 4.000000012345
		};

		const Matrix2 mat3{
			-1.0, 3.0,
			-2.0, 4.001
		};

		// Act & Assert
		EXPECT_TRUE(mat1.EqualsWithTolerance(mat2));
		EXPECT_FALSE(mat1.EqualsWithTolerance(mat3));
	}

	TEST(Matrix2_TestSuite, ThreeMatrix2s_StandardAssignmentOperator_Matrix2Equality)
	{
		// Arrange
		const Matrix2 mat1{
			-1.0, 3.0,
			-2.0, 4.0
		};
		Matrix2 mat2;

		// Act
		mat2 = mat1;

		// Assert
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT2_11), -1.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT2_12), 3.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT2_21), -2.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT2_22), 4.0);
	}

	TEST(Matrix2_TestSuite, Matrix2_AdditionAssignmentOperator_Matrix2)
	{
		// Arrange
		Matrix2 mat1{
			-1.0, 3.0,
			-2.0, 4.0
		};

		const Matrix2 mat2{
			-1.0, -2.0,
			-2.0, 3.0
		};

		// Act
		mat1 += mat2;

		// Assert
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_11), -2.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_12), 1.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_21), -4.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_22), 7.0);
	}

	TEST(Matrix2_TestSuite, Matrix2_SubtractionAssignmentOperator_Matrix2)
	{
		// Arrange
		Matrix2 mat1{
			-1.0, 3.0,
			-2.0, 4.0
		};

		const Matrix2 mat2{
			-1.0, -2.0,
			-2.0, 3.0
		};

		// Act
		mat1 -= mat2;

		// Assert
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_11), 0.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_12), 5.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_21), 0.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_22), 1.0);
	}

	TEST(Matrix2_TestSuite, Matrix2_AdditionOperator_Matrix2)
	{
		// Arrange
		const Matrix2 mat1{
			-1.0, 3.0,
			-2.0, 4.0
		};

		const Matrix2 mat2{
			-1.0, -2.0,
			-2.0, 3.0
		};

		// Act
		const Matrix2 mat3 = mat1 + mat2;

		// Assert
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT2_11), -2.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT2_12), 1.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT2_21), -4.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT2_22), 7.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_11), -1.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_12), 3.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_21), -2.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_22), 4.0);
	}

	TEST(Matrix2_TestSuite, Matrix2_SubtractionOperator_Matrix2)
	{
		// Arrange
		const Matrix2 mat1{
			-1.0, 3.0,
			-2.0, 4.0
		};

		const Matrix2 mat2{
			-1.0, -2.0,
			-2.0, 3.0
		};

		// Act
		const Matrix2 mat3 = mat1 - mat2;

		// Assert
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT2_11), 0.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT2_12), 5.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT2_21), 0.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT2_22), 1.0);

		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_11), -1.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_12), 3.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_21), -2.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_22), 4.0);
	}

	TEST(Matrix2_TestSuite, Matrix2_Matrix2MultiplicationAssignmentOperator_Matrix2)
	{
		// Arrange
		Matrix2 mat1{
			-1.0, 3.0,
			-2.0, 4.0
		};

		const Matrix2 mat2{
			-1.0, -2.0,
			-2.0, 3.0
		};
		Matrix2 mat3 = mat1;

		// Act
		mat1 *= mat2;
		mat3.Multiply(mat2);

		// Assert
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_11), -5.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_12), 11.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_21), -6.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_22), 16.0);

		EXPECT_DOUBLE_EQ(mat3.Elem(MAT2_11), -5.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT2_12), 11.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT2_21), -6.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT2_22), 16.0);
	}

	TEST(Matrix2_TestSuite, Matrix2_Matrix2Premultiply_Matrix2)
	{
		// Arrange
		Matrix2 mat1{
			-1.0, -2.0,
			-2.0, 3.0
		};

		const Matrix2 mat2{
			-1.0, 3.0,
			-2.0, 4.0,
		};

		// Act
		mat1.Premultiply(mat2);

		// Assert
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_11), -5.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_12), 11.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_21), -6.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_22), 16.0);
	}

	TEST(Matrix2_TestSuite, Matrix2_Matrix2MultiplicationOperator_Matrix2)
	{
		// Arrange
		const Matrix2 mat1{
			-1.0, 3.0,
			-2.0, 4.0
		};

		const Matrix2 mat2{
			-1.0, -2.0,
			-2.0, 3.0
		};

		// Act
		const Matrix2 mat3 = mat1 * mat2;

		// Assert
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT2_11), -5.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT2_12), 11.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT2_21), -6.0);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT2_22), 16.0);
	}

	TEST(Matrix2_TestSuite, Matrix2_ScalarMultiplicationAssignmentOperator_Matrix2)
	{
		// Arrange
		Matrix2 mat1{
			-1.0, 3.0,
			-2.0, 4.0
		};

		// Act
		mat1 *= 2.25;

		// Assert
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_11), -2.25);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_12), 6.75);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_21), -4.5);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_22), 9.0);
	}

	TEST(Matrix2_TestSuite, Matrix2_ScalarMultiplicationOperator_Matrix2)
	{
		// Arrange
		const Matrix2 mat1{
			-1.0, 3.0,
			-2.0, 4.0
		};

		// Act
		const Matrix2 mat2 = mat1 * 2.25;
		const Matrix2 mat3 = 2.25 * mat1;

		// Assert
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT2_11), -2.25);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT2_12), 6.75);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT2_21), -4.5);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT2_22), 9.0);

		EXPECT_DOUBLE_EQ(mat3.Elem(MAT2_11), -2.25);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT2_12), 6.75);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT2_21), -4.5);
		EXPECT_DOUBLE_EQ(mat3.Elem(MAT2_22), 9.0);
	}

	TEST(Matrix2_TestSuite, Matrix2_IsIdentity_Matrix2IsIdentity)
	{
		// Arrange
		const Matrix2 matDefault;
		const Matrix2 mat{
			1.0, 0.0,
			0.0, 1.000000084557
		};

		// Act & Assert
		EXPECT_TRUE(matDefault.IsIdentity());
		EXPECT_FALSE(mat.IsIdentity());
	}

	TEST(Matrix2_TestSuite, Matrix2_Transpose_Matrix2Transposed)
	{
		// Arrange
		Matrix2 mat1{
			-1.0, 3.0,
			-2.0, 4.0
		};

		// Act
		mat1.Transpose();

		// Assert
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_11), -1.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_12), -2.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_21), 3.0);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_22), 4.0);
	}

	TEST(Matrix2_TestSuite, Matrix2_CopyTranspose_Matrix2Transposed)
	{
		// Arrange
		const Matrix2 mat1{
			-1.0, 3.0,
			-2.0, 4.0
		};

		// Act
		const Matrix2 mat2 = Transpose(mat1);

		// Assert
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT2_11), -1.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT2_12), -2.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT2_21), 3.0);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT2_22), 4.0);
	}

	TEST(Matrix2_TestSuite, Matrix2_Determinant_Matrix2Determinant)
	{
		// Arrange
		const Matrix2 mat1{
			-1.0, 3.0,
			-2.0, 6.0
		};
		const Matrix2 mat2{
			-1.0, 3.0,
			-2.0, -4.0
		};

		// Act
		const double det1 = mat1.Determinant();
		const double det2 = mat2.Determinant();

		// Assert
		EXPECT_DOUBLE_EQ(det1, 0.0);
		EXPECT_DOUBLE_EQ(det2, 10.0);
	}

	TEST(Matrix2_TestSuite, Matrix2_Inverse_Matrix2Inverted)
	{
		// Arrange
		Matrix2 mat1{
			-1.0, 3.0,
			-2.0, -4.0
		};

		// Act
		mat1.Inverse();

		// Assert
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_11), -0.4);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_12), -0.3);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_21), 0.2);
		EXPECT_DOUBLE_EQ(mat1.Elem(MAT2_22), -0.1);
	}

	TEST(Matrix2_TestSuite, Matrix2_CopyInverse_Matrix2Inverted)
	{
		// Arrange
		const Matrix2 mat1{
			-1.0, 3.0,
			-2.0, -4.0
		};

		// Act
		const Matrix2 mat2 = Inverse(mat1);

		// Assert
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT2_11), -0.4);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT2_12), -0.3);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT2_21), 0.2);
		EXPECT_DOUBLE_EQ(mat2.Elem(MAT2_22), -0.1);
	}

} // Symplektis::UnitTests