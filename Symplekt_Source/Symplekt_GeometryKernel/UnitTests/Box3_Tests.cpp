/*! \file  Box3_Tests.cpp
 *  \brief Box3_Tests
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   27.6.2021
 *
 */
#include "gtest/gtest.h"

#include "Symplekt_GeometryKernel/Box3.h"
#include "Symplekt_GeometryKernel/Box3Utils.h"
#include "Symplekt_GeometryKernel/RectilinearGridBox3.h"
#include "Symplekt_GeometryKernel/Vector3.h"

namespace Symplektis::UnitTests
{
	using namespace GeometryKernel;

	TEST(Box3_TestSuite, Box3_ConstructFromPoints_Box3)
	{
		// Arrange
		const double phi = (1.0 + sqrt(5.0)) / 2.0;
		const std::vector<Vector3> points{
			{-1.0 / phi, 1.0, 0.0},    {1.0 / phi, 1.0, 0.0},   {-1.0 / phi, -1.0,  0.0},    {1.0 / phi, -1.0, 0.0},
			{0.0, -1.0 / phi, 1.0},    {0.0, 1.0 / phi, 1.0},    {0.0, -1.0 / phi, -1.0},    {0.0, 1.0 / phi, -1.0},
			{1.0, 0.0, -1.0 / phi},    {1.0, 0.0, 1.0 / phi},    {-1.0, 0.0, -1.0 / phi},    {-1.0, 0.0, 1.0 / phi}
		};

		// Act
		const Box3 box(points);

		// Assert
		EXPECT_DOUBLE_EQ(box.Min().X(), -1.0);
		EXPECT_DOUBLE_EQ(box.Min().Y(), -1.0);
		EXPECT_DOUBLE_EQ(box.Min().Z(), -1.0);

		EXPECT_DOUBLE_EQ(box.Max().X(), 1.0);
		EXPECT_DOUBLE_EQ(box.Max().Y(), 1.0);
		EXPECT_DOUBLE_EQ(box.Max().Z(), 1.0);
	}

	TEST(Box3_TestSuite, Box3_IntersectsBox_Box3Intersection)
	{
		// Arrange
		const Box3 boxBase{
			{-1.0, -1.0, -1.0},
			{1.0, 1.0, 1.0}
		};
		const Box3 box1{
			{0.5, 0.5, 0.5},
			{1.5, 1.5, 1.5}
		};
		const Box3 box2{
			{1.0, 1.0, 1.0},
			{3.0, 3.0, 3.0}
		};
		const Box3 box3{
			{1.000001151, 1.000000844, 1.000000011855},
			{3.0, 3.0, 3.0}
		};
		const Box3 box4{
			{-3.0, -3.0, -3.0},
			{-1.000001151, -1.000000844, -1.000000011855}
		};
		const Box3 box5{
			{-3.0, -3.0, -3.0},
			{-1.0, -1.0, -1.0}
		};

		// Act & Assert
		EXPECT_TRUE(boxBase.IntersectsBox(box1));
		EXPECT_TRUE(boxBase.IntersectsBox(box2));
		EXPECT_FALSE(boxBase.IntersectsBox(box3));
		EXPECT_FALSE(boxBase.IntersectsBox(box4));
		EXPECT_TRUE(boxBase.IntersectsBox(box5)); 
	}

	TEST(Box3_TestSuite, Box3_StandardAssignmentOperator_Box3)
	{
		// Arrange
		const Box3 box1{
			{0.5, 0.5, 0.5},
			{1.5, 1.5, 1.5}
		};
		Box3 box2;

		// Act
		box2 = box1;

		// Assert
		EXPECT_DOUBLE_EQ(box2.Min().X(), 0.5);
		EXPECT_DOUBLE_EQ(box2.Min().Y(), 0.5);
		EXPECT_DOUBLE_EQ(box2.Min().Z(), 0.5);

		EXPECT_DOUBLE_EQ(box2.Max().X(), 1.5);
		EXPECT_DOUBLE_EQ(box2.Max().Y(), 1.5);
		EXPECT_DOUBLE_EQ(box2.Max().Z(), 1.5);
	}

	TEST(Box3_TestSuite, Box3_EqualityComparisonOperator_Box3Equality)
	{
		// Arrange
		const Box3 box1{
			{0.5, 0.5, 0.5},
			{1.5, 1.5, 1.5}
		};
		const Box3 box2{
			{0.5, 0.5, 0.5},
			{1.5, 1.5, 1.5}
		};
		const Box3 box3{
			{0.5, 0.5, 0.5},
			{1.51, 1.5, 1.2}
		};

		// Act & Assert
		EXPECT_TRUE(box1 == box2);
		EXPECT_FALSE(box1 != box2);
		EXPECT_TRUE(box1 != box3);
		EXPECT_FALSE(box1 == box3);
	}

	TEST(Box3_TestSuite, Box3_EqualityWithToleranceOperator_Box3Equality)
	{
		// Arrange
		const Box3 box1{
			{0.5, 0.5, 0.5},
			{1.5, 1.5, 1.5}
		};
		const Box3 box2{
			{0.5, 0.5, 0.5},
			{1.5, 1.50000000454554, 1.5}
		};
		const Box3 box3{
			{0.5, 0.5, 0.5},
			{1.5, 1.50137878, 1.5}
		};

		// Act & Assert
		EXPECT_TRUE(box1.EqualsWithTolerance(box2));
		EXPECT_FALSE(box1.EqualsWithTolerance(box3));
	}

	TEST(Box3_TestSuite, Box3_ClearAndIsEmpty_Box3IsEmpty)
	{
		// Arrange
		Box3 box1{
			{0.5, 0.5, 0.5},
			{1.5, 1.5, 1.5}
		};
		const Box3 box2;
		const Box3 box3{
			{1.5, 1.5, 1.5},
			{1.5, 1.5, 1.5}
		};
		const Box3 box4{
			{0.5, 0.5, 0.5},
			{1.5, 1.5, 1.5}
		};

		// Act
		box1.Clear();

		// Act & Assert
		EXPECT_TRUE(box1.IsEmpty());
		EXPECT_TRUE(box2.IsEmpty());
		EXPECT_TRUE(box3.IsEmpty());
		EXPECT_FALSE(box4.IsEmpty());
	}

	TEST(Box3_TestSuite, Box3_GetAndSetMinOrMaxById_Box3)
	{
		// Arrange
		const Box3 box1{
			{0.5, 0.5, 0.5},
			{1.5, 1.5, 1.5}
		};
		Box3 box2{
			{-0.5, -0.5, -0.5},
			{1.5, 1.5, 1.5}
		};
		const Vector3 newMin{ -1.0, -1.0, -1.0 };
		const Vector3 newMax{ 1.0, 1.0, 1.0 };

		// Act
		box2.SetMinOrMaxById(0, newMin);
		box2.SetMinOrMaxById(1, newMax);
		const Vector3& box1Min = box1.GetMinOrMaxById(0);
		const Vector3& box1Max = box1.GetMinOrMaxById(1);

		// Assert
		EXPECT_DOUBLE_EQ(box2.Min().X(), -1.0);
		EXPECT_DOUBLE_EQ(box2.Min().Y(), -1.0);
		EXPECT_DOUBLE_EQ(box2.Min().Z(), -1.0);

		EXPECT_DOUBLE_EQ(box2.Max().X(), 1.0);
		EXPECT_DOUBLE_EQ(box2.Max().Y(), 1.0);
		EXPECT_DOUBLE_EQ(box2.Max().Z(), 1.0);

		EXPECT_DOUBLE_EQ(box1Min.X(), 0.5);
		EXPECT_DOUBLE_EQ(box1Min.Y(), 0.5);
		EXPECT_DOUBLE_EQ(box1Min.Z(), 0.5);

		EXPECT_DOUBLE_EQ(box1Max.X(), 1.5);
		EXPECT_DOUBLE_EQ(box1Max.Y(), 1.5);
		EXPECT_DOUBLE_EQ(box1Max.Z(), 1.5);
	}

	TEST(Box3_TestSuite, Box3_GetCenter_Box3Center)
	{
		// Arrange
		const Box3 box{
			{-0.5, -0.5, -0.5},
			{1.5, 1.5, 1.5}
		};

		// Act
		const Vector3 boxCenter = box.GetCenter();

		// Assert
		EXPECT_DOUBLE_EQ(boxCenter.X(), 0.5);
		EXPECT_DOUBLE_EQ(boxCenter.Y(), 0.5);
		EXPECT_DOUBLE_EQ(boxCenter.Z(), 0.5);
	}

	TEST(Box3_TestSuite, Box3_GetSize_Box3Size)
	{
		// Arrange
		const Box3 box{
			{-0.5, -0.5, -0.5},
			{1.5, 1.5, 1.5}
		};

		// Act
		const Vector3 boxSize = box.GetSize();

		// Assert
		EXPECT_DOUBLE_EQ(boxSize.X(), 2.0);
		EXPECT_DOUBLE_EQ(boxSize.Y(), 2.0);
		EXPECT_DOUBLE_EQ(boxSize.Z(), 2.0);
	}

	TEST(Box3_TestSuite, Box3_ExpandBox3ByOffset_Box3Expanded)
	{
		// Arrange
		Box3 box1{
			{-0.5, -0.5, -0.5},
			{1.5, 1.5, 1.5}
		};
		Box3 box2 = box1;
		constexpr double offset = 2.0;
		const Vector3 offsets{ 2.0, 1.0, 0.5 };

		// Act
		box1.ExpandByOffset(offset);
		box2.ExpandByOffsets(offsets);

		// Assert
		EXPECT_DOUBLE_EQ(box1.Min().X(), -2.5);
		EXPECT_DOUBLE_EQ(box1.Min().Y(), -2.5);
		EXPECT_DOUBLE_EQ(box1.Min().Z(), -2.5);

		EXPECT_DOUBLE_EQ(box1.Max().X(), 3.5);
		EXPECT_DOUBLE_EQ(box1.Max().Y(), 3.5);
		EXPECT_DOUBLE_EQ(box1.Max().Z(), 3.5);

		EXPECT_DOUBLE_EQ(box2.Min().X(), -2.5);
		EXPECT_DOUBLE_EQ(box2.Min().Y(), -1.5);
		EXPECT_DOUBLE_EQ(box2.Min().Z(), -1.0);

		EXPECT_DOUBLE_EQ(box2.Max().X(), 3.5);
		EXPECT_DOUBLE_EQ(box2.Max().Y(), 2.5);
		EXPECT_DOUBLE_EQ(box2.Max().Z(), 2.0);
	}

	TEST(Box3_TestSuite, Box3_ExpandBox3ByFactor_Box3Expanded)
	{
		// Arrange
		Box3 box{
			{-0.5, -0.5, -0.5},
			{1.5, 1.5, 1.5}
		};
		constexpr double factor = 1.5;

		// Act
		box.ExpandByFactor(factor);

		// Assert
		EXPECT_DOUBLE_EQ(box.Min().X(), -1.0);
		EXPECT_DOUBLE_EQ(box.Min().Y(), -1.0);
		EXPECT_DOUBLE_EQ(box.Min().Z(), -1.0);

		EXPECT_DOUBLE_EQ(box.Max().X(), 2.0);
		EXPECT_DOUBLE_EQ(box.Max().Y(), 2.0);
		EXPECT_DOUBLE_EQ(box.Max().Z(), 2.0);
	}

	TEST(Box3_TestSuite, Box3_IsPointInside_Vector3Inside)
	{
		// Arrange
		const Box3 box{
			{-0.5, -0.5, -0.5},
			{1.5, 1.5, 1.5}
		};
		const std::vector<Vector3> points{
			{-0.50001, 1.0, 0.0},    {-0.49999, 1.0, 0.0},   {-1.0, -1.0,  0.0},    {1.0, -1.0, 0.0},
			{0.0, -1.0, 1.0},        {-0.5, 1.0, 1.0},        {0.0, -1.0, -1.0},    {0.0, 1.0, -1.0},
			{1.0, 0.0, -1.0},        {1.0, 0.0, 1.0},        {-1.0, 0.0, -1.0},    {-1.0, 0.0, 1.0}
		};
		const std::vector inclusionValues{
			false, true, false, false,
			false, true, false, false,
			false, true, false, false
		};

		// Act & Assert
		for (unsigned int i = 0; i < points.size(); i++)
		{
			EXPECT_TRUE(box.IsPointInside(points[i]) == inclusionValues[i]);
			EXPECT_TRUE(IsPointInsideBox(points[i], box) == inclusionValues[i]);
		}
	}

	TEST(Box3_TestSuite, Box3_SetVectorToBoxSize_Vector3BoxSize)
	{
		// Arrange
		const Box3 box{
			{-0.5, -0.5, -0.5},
			{1.5, 1.5, 1.5}
		};
		Vector3 testVect;

		// Act
		SetVectorToBoxSize(testVect, box);

		// Assert
		EXPECT_DOUBLE_EQ(testVect.X(), 2.0);
		EXPECT_DOUBLE_EQ(testVect.Y(), 2.0);
		EXPECT_DOUBLE_EQ(testVect.Z(), 2.0);
	}

	TEST(Box3_TestSuite, Box3_SetVectorToBoxHalfSize_Vector3BoxHalfSize)
	{
		// Arrange
		const Box3 box{
			{-0.5, -0.5, -0.5},
			{1.5, 1.5, 1.5}
		};
		Vector3 testVect;

		// Act
		SetVectorToBoxHalfSize(testVect, box);

		// Assert
		EXPECT_DOUBLE_EQ(testVect.X(), 1.0);
		EXPECT_DOUBLE_EQ(testVect.Y(), 1.0);
		EXPECT_DOUBLE_EQ(testVect.Z(), 1.0);
	}

	TEST(Box3_TestSuite, Box3_SetVectorToBoxCenter_Vector3BoxCenter)
	{
		// Arrange
		const Box3 box{
			{-0.5, -0.5, -0.5},
			{1.5, 1.5, 1.5}
		};
		Vector3 testVect;

		// Act
		SetVectorToBoxCenter(testVect, box);

		// Assert
		EXPECT_DOUBLE_EQ(testVect.X(), 0.5);
		EXPECT_DOUBLE_EQ(testVect.Y(), 0.5);
		EXPECT_DOUBLE_EQ(testVect.Z(), 0.5);
	}

	TEST(RectilinearGridBox3_TestSuite, RectilinearGridBox3_ConstructFromMinMaxAndCellSize_RectilinearGridBox3)
	{
		// Arrange
		constexpr double cellSize = 1.25;

		// Act
		const auto testBox = RectilinearGridBox3{
			cellSize,
			{-10.3, -21.5, 6.25},
			{5.123, 11.35, 17.25}
		};

		// Assert
		const auto& actualMinVector = testBox.Min();
		EXPECT_DOUBLE_EQ(actualMinVector.X(), -11.25);
		EXPECT_DOUBLE_EQ(actualMinVector.Y(), -22.5);
		EXPECT_DOUBLE_EQ(actualMinVector.Z(), 6.25);
		const auto& actualMaxVector = testBox.Max();
		EXPECT_DOUBLE_EQ(actualMaxVector.X(), 6.25);
		EXPECT_DOUBLE_EQ(actualMaxVector.Y(), 12.5);
		EXPECT_DOUBLE_EQ(actualMaxVector.Z(), 17.5);
	}

	TEST(RectilinearGridBox3_TestSuite, RectilinearGridBox3_ConstructFromBox3AndCellSize_RectilinearGridBox3)
	{
		// Arrange
		constexpr double cellSize = 1.25;
		const auto testBox3 = Box3{
			{-10.3, -21.5, 6.25},
			{5.123, 11.35, 17.25}
		};

		// Act
		const auto testBox = RectilinearGridBox3{ cellSize, testBox3 };

		// Assert
		const auto& actualMinVector = testBox.Min();
		EXPECT_DOUBLE_EQ(actualMinVector.X(), -11.25);
		EXPECT_DOUBLE_EQ(actualMinVector.Y(), -22.5);
		EXPECT_DOUBLE_EQ(actualMinVector.Z(), 6.25);
		const auto& actualMaxVector = testBox.Max();
		EXPECT_DOUBLE_EQ(actualMaxVector.X(), 6.25);
		EXPECT_DOUBLE_EQ(actualMaxVector.Y(), 12.5);
		EXPECT_DOUBLE_EQ(actualMaxVector.Z(), 17.5);
	}
	
} // Symplektis::UnitTests
