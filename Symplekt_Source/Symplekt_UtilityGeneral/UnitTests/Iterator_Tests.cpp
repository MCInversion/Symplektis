/*! \file  Iterator_Tests.cpp
 *  \brief Tests for working with iterator utilities.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   28.11.2021
 *
 */

#include "gtest/gtest.h"

#include "Symplekt_UtilityGeneral/IteratorHelperUtils.h"

namespace Symplektis::UnitTests
{
	using namespace Util;

	/// \brief Doubly linked list node for testing
	struct DoublyLinkedListNode
	{		
		std::vector<DoublyLinkedListNode>::iterator Previous;
		std::vector<DoublyLinkedListNode>::iterator Next;
		unsigned int Data{ 0 };
	};

	/// \brief test data values
	std::vector<unsigned int> testData = {
		6, 3, 1, 2, 12
	};

	static void FillTestDataContainer(std::vector<DoublyLinkedListNode>& testObjVect)
	{
		testObjVect.clear();
		testObjVect.reserve(testData.size());
		for (const auto& item : testData)
		{
			const auto dummyEndIter = testObjVect.end();
			testObjVect.emplace_back(DoublyLinkedListNode{ dummyEndIter, dummyEndIter, item });
		}

		for (size_t id = 0; auto& testObjItem : testObjVect)
		{
			if (id == 0)
			{
				testObjItem.Next = testObjVect.begin() + 1;
				testObjItem.Previous = testObjVect.end() - 1;
				id++;
				continue;
			}

			if (id < testObjVect.size() - 1)
			{
				testObjItem.Next = testObjVect.begin() + id + 1;
				testObjItem.Previous = testObjVect.begin() + id - 1;
				id++;
				continue;
			}

			testObjItem.Next = testObjVect.begin();
			testObjItem.Previous = testObjVect.begin() + id - 1;
		}
	}

	/// \brief Binary tree node for testing
	struct BinaryTreeTestNode
	{
		std::vector<BinaryTreeTestNode>::iterator Left;
		std::vector<BinaryTreeTestNode>::iterator Right;
		unsigned int Data{ 0 };
	};

	static void FillBinaryTreeLinearContainer(std::vector<BinaryTreeTestNode>& testObjVect)
	{
		testObjVect.clear();
		testObjVect.reserve(testData.size());
		for (const auto& item : testData)
		{
			const auto dummyEndIter = testObjVect.end();
			testObjVect.emplace_back(BinaryTreeTestNode{ dummyEndIter, dummyEndIter, item });
		}

		testObjVect[0].Left = testObjVect.begin() + 1;
		testObjVect[0].Right = testObjVect.begin() + 4;

		testObjVect[1].Left = testObjVect.begin() + 3;
		testObjVect[1].Right = testObjVect.begin() + 2;
	}

	TEST(Iterator_TestSuite, TransferIteratorFromVectorToVector)
	{
		// Arrange
		std::vector<DoublyLinkedListNode> dblLinkedList{};
		FillTestDataContainer(dblLinkedList);
		std::vector<DoublyLinkedListNode> dblLinkedListCopy = dblLinkedList;

		// Act
		for (auto& item : dblLinkedListCopy)
		{
			TransferIteratorToContainer(item.Previous, dblLinkedList, dblLinkedListCopy);
			TransferIteratorToContainer(item.Next, dblLinkedList, dblLinkedListCopy);
		}

		// Assert
		EXPECT_EQ(dblLinkedListCopy[0].Next->Data, testData[1]);
		EXPECT_EQ(dblLinkedListCopy[0].Previous->Data, testData[4]);

		EXPECT_EQ(dblLinkedListCopy[1].Next->Data, testData[2]);
		EXPECT_EQ(dblLinkedListCopy[1].Previous->Data, testData[0]);

		EXPECT_EQ(dblLinkedListCopy[2].Next->Data, testData[3]);
		EXPECT_EQ(dblLinkedListCopy[2].Previous->Data, testData[1]);

		EXPECT_EQ(dblLinkedListCopy[3].Next->Data, testData[4]);
		EXPECT_EQ(dblLinkedListCopy[3].Previous->Data, testData[2]);

		EXPECT_EQ(dblLinkedListCopy[4].Next->Data, testData[0]);
		EXPECT_EQ(dblLinkedListCopy[4].Previous->Data, testData[3]);
	}

	TEST(Iterator_TestSuite, TransferIteratorFromVectorWithBackInsertedElement)
	{
		// Arrange
		std::vector<DoublyLinkedListNode> dblLinkedList{};
		FillTestDataContainer(dblLinkedList);
		const DoublyLinkedListNode newNode{ dblLinkedList.begin(), dblLinkedList.end() - 2, 17 };
		dblLinkedList.reserve(dblLinkedList.size() + 1);
		dblLinkedList.insert(dblLinkedList.end(), newNode);

		for (unsigned int i = 0; i < dblLinkedList.size(); i++)
		{
			dblLinkedList[i].Previous = (i == 0 ? dblLinkedList.end() - 1 : dblLinkedList.begin() + i - 1);
			dblLinkedList[i].Next = (i == dblLinkedList.size() - 1 ? dblLinkedList.begin() : dblLinkedList.begin() + i + 1);
		}

		// Act
		
	}

	/*TEST(Iterator_TestSuite, IteratorsOfBinaryTreeNodes)
	{
		// Arrange
		std::vector<BinaryTreeTestNode> bTreeContainer{};
		FillBinaryTreeLinearContainer(bTreeContainer);
		const BinaryTreeTestNode newNode{ bTreeContainer.end(), bTreeContainer.end(), 7};
		bTreeContainer.reserve(bTreeContainer.size() + 1);
		bTreeContainer.insert(bTreeContainer.end(), newNode);

		bTreeContainer[4].Left = bTreeContainer.begin() + 5;

		for (unsigned int i = 0; i < bTreeContainer.size(); i++)
		{
			TransferIteratorToContainer(bTreeContainer[i].Left, bTreeContainer, bTreeContainer);
			TransferIteratorToContainer(bTreeContainer[i].Right, bTreeContainer, bTreeContainer);
		}
	}*/
}