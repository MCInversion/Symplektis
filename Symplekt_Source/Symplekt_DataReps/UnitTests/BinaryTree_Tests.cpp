/*! \file  BinaryTree_Tests.cpp
 *  \brief Tests for working with generic implementations of BinaryTree with dummy node data.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   29.10.2021
 *
 */

#include "gtest/gtest.h"

#include "../StringSearchBinaryTree.h"

#include <vector>
#include <string>
#include <filesystem>
#include <fstream>

namespace Symplektis::UnitTests
{
    using namespace DataReps;

    std::vector<std::string> testDataBasic = {
    	"D", "C", "A", "B", "F", "X", "Z", "I", "O", "L"//
    };

    std::vector<std::string> testDataLarge = {
    	"In","computer","science,","a","binary","search","tree","(BST),",
    	"also","called","an","ordered","or","sorted","binary","tree,","is","a",
    	"rooted","binary","tree","data","structure","whose","internal","nodes",
    	"each","store","a","key","greater","than","all","the","keys","in","the",
    	"node's","left","subtree","and","less","than","those","in","its","right",
    	"subtree.","A","binary","tree","is","a","type","of","data","structure",
    	"for","storing","data","such","as","numbers","in","an","organized","way.",
    	"Binary","search","trees","allow","binary","search","for","fast","lookup,",
    	"addition","and ","removal","of","data","items,","and","can","be","used",
    	"to","implement","dynamic","sets","and","lookup","tables.","The","order",
    	"of","nodes","in","a","BST","means","that","each","comparison","skips",
    	"about","half","of","the","remaining","tree,","so","the","whole","lookup",
    	"takes","time","proportional","to","the","binary","logarithm","of","the",
    	"number","of","items","stored","in","the","tree.","This","is","much",
    	"better","than","the","linear","time","required","to","find","items",
    	"by","key","in","an","(unsorted)","array,","but","slower","than","the",
    	"corresponding","operations","on","hash","tables.","Several","variants",
    	"of","the","binary","search","tree","have","been","studied."
	};

	static bool WriteTreeDebugPrintToFile(const StringSearchBinaryTree& tree)
	{
		try
		{
	        const auto currPath = std::filesystem::current_path(); // assumed "{SymplektisRepo_root}\\build\\Symplekt_DataReps\\UnitTests\\{Release | Debug}"
            const auto parentPath = currPath.parent_path().parent_path().parent_path().parent_path();
	        const auto fileFullPath = parentPath / "Symplekt_OutputData\\UnitTests" / (tree.GetTreeName() + "_print.txt").c_str();

	        const auto printStringFull = tree.DebugPrint();

	        std::ofstream fileOStream(fileFullPath.c_str());
	        if (!fileOStream.is_open())
	            return false;

	        fileOStream << printStringFull;
	        fileOStream.close();
		}
        catch (...)
        {
            return false;
        }

        return true;
	}

	static bool WritePlantUMLOutputToFile(const StringSearchBinaryTree& tree)
	{
        try
        {
            const auto currPath = std::filesystem::current_path(); // assumed "{SymplektisRepo_root}\\build\\Symplekt_DataReps\\UnitTests\\{Release | Debug}"
            const auto parentPath = currPath.parent_path().parent_path().parent_path().parent_path();
            const auto fileFullPath = parentPath / "Symplekt_OutputData\\UnitTests" / (tree.GetTreeName() + "_plantUML.txt").c_str();

            const auto printStringFull = tree.PlantUMLPrint();

            std::ofstream fileOStream(fileFullPath.c_str());
            if (!fileOStream.is_open())
                return false;

            fileOStream << printStringFull;
            fileOStream.close();
        }
        catch (...)
        {
            return false;
        }

        return true;
	}

    TEST(BinaryTree_TestSuite, CreateRecursiveBinaryTreeInstance)
    {
        // Arrange, Act
        StringSearchBinaryTree recursiveStrTreeInstance{ testDataBasic,
        	BinaryTreeImplementationType::Recursive, "MyRecursiveStrTreeInstance"};
        recursiveStrTreeInstance.BuildFromData();
        const auto breadthFirstTreeData = recursiveStrTreeInstance.GetTreeDataFromBreadthFirstTraversal();
        const auto depthFirstTreeData = recursiveStrTreeInstance.GetTreeDataFromDepthFirstTraversal();

    	// Assert
        EXPECT_EQ(recursiveStrTreeInstance.IsValid(), true);
        //EXPECT_EQ(recursiveStrTreeInstance.IsBalanced(), false);
        EXPECT_EQ(recursiveStrTreeInstance.IsEmpty(), false);
        EXPECT_EQ(recursiveStrTreeInstance.IsSelfBalancing(), false);
        EXPECT_EQ(WriteTreeDebugPrintToFile(recursiveStrTreeInstance), true);
        EXPECT_EQ(WritePlantUMLOutputToFile(recursiveStrTreeInstance), true);

        // breadth-first traversal verification
        auto strSearchData = std::static_pointer_cast<StringSearchNodeData>(breadthFirstTreeData[0]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[0]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(breadthFirstTreeData[1]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[1]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(breadthFirstTreeData[2]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[4]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(breadthFirstTreeData[3]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[2]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(breadthFirstTreeData[4]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[5]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(breadthFirstTreeData[5]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[3]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(breadthFirstTreeData[6]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[7]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(breadthFirstTreeData[7]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[6]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(breadthFirstTreeData[8]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[8]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(breadthFirstTreeData[9]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[9]);

        // depth-first traversal verification
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(depthFirstTreeData[0]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[0]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(depthFirstTreeData[1]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[1]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(depthFirstTreeData[2]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[2]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(depthFirstTreeData[3]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[3]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(depthFirstTreeData[4]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[4]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(depthFirstTreeData[5]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[5]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(depthFirstTreeData[6]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[7]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(depthFirstTreeData[7]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[8]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(depthFirstTreeData[8]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[9]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(depthFirstTreeData[9]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[6]);
    }

    TEST(BinaryTree_TestSuite, CreateIterativeBinaryTreeInstance)
    {
        // Arrange, Act
        StringSearchBinaryTree iterativeStrTreeInstance{ testDataBasic,
        	BinaryTreeImplementationType::Iterative, "MyIterativeStrTreeInstance" };
        iterativeStrTreeInstance.BuildFromData();
        const auto breadthFirstTreeData = iterativeStrTreeInstance.GetTreeDataFromBreadthFirstTraversal();
        const auto depthFirstTreeData = iterativeStrTreeInstance.GetTreeDataFromDepthFirstTraversal();

        // Assert
        EXPECT_EQ(iterativeStrTreeInstance.IsValid(), true);
        EXPECT_EQ(iterativeStrTreeInstance.IsBalanced(), false);
        EXPECT_EQ(iterativeStrTreeInstance.IsEmpty(), false);
        EXPECT_EQ(iterativeStrTreeInstance.IsSelfBalancing(), false);
        EXPECT_EQ(WriteTreeDebugPrintToFile(iterativeStrTreeInstance), true);
        EXPECT_EQ(WritePlantUMLOutputToFile(iterativeStrTreeInstance), true);

        // breadth-first traversal verification
        auto strSearchData = std::static_pointer_cast<StringSearchNodeData>(breadthFirstTreeData[0]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[0]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(breadthFirstTreeData[1]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[1]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(breadthFirstTreeData[2]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[4]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(breadthFirstTreeData[3]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[2]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(breadthFirstTreeData[4]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[5]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(breadthFirstTreeData[5]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[3]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(breadthFirstTreeData[6]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[7]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(breadthFirstTreeData[7]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[6]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(breadthFirstTreeData[8]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[8]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(breadthFirstTreeData[9]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[9]);

        // depth-first traversal verification
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(depthFirstTreeData[0]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[0]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(depthFirstTreeData[1]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[1]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(depthFirstTreeData[2]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[2]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(depthFirstTreeData[3]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[3]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(depthFirstTreeData[4]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[4]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(depthFirstTreeData[5]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[5]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(depthFirstTreeData[6]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[7]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(depthFirstTreeData[7]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[8]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(depthFirstTreeData[8]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[9]);
        strSearchData = std::static_pointer_cast<StringSearchNodeData>(depthFirstTreeData[9]);
        EXPECT_EQ(strSearchData->DataString, testDataBasic[6]);
    }

    TEST(BinaryTree_TestSuite, CreateLargerRecursiveBinaryTreeInstance)
    {
        // Arrange, Act
        StringSearchBinaryTree recursiveStrTreeInstance{ testDataLarge,
            BinaryTreeImplementationType::Recursive, "LargerMyRecursiveStrTreeInstance" };
        recursiveStrTreeInstance.BuildFromData();

        // Assert
        EXPECT_EQ(recursiveStrTreeInstance.IsValid(), true);
        //EXPECT_EQ(recursiveStrTreeInstance.IsBalanced(), false);
        EXPECT_EQ(recursiveStrTreeInstance.IsEmpty(), false);
        EXPECT_EQ(recursiveStrTreeInstance.IsSelfBalancing(), false);
        EXPECT_EQ(WriteTreeDebugPrintToFile(recursiveStrTreeInstance), true);
    }

    TEST(BinaryTree_TestSuite, CreateLargerIterativeBinaryTreeInstance)
    {
        // Arrange, Act
        StringSearchBinaryTree iterativeStrTreeInstance{ testDataLarge,
            BinaryTreeImplementationType::Iterative, "LargerIterativeStrTreeInstance" };
        iterativeStrTreeInstance.BuildFromData();

        // Assert
        EXPECT_EQ(iterativeStrTreeInstance.IsValid(), true);
        EXPECT_EQ(iterativeStrTreeInstance.IsBalanced(), false);
        EXPECT_EQ(iterativeStrTreeInstance.IsEmpty(), false);
        EXPECT_EQ(iterativeStrTreeInstance.IsSelfBalancing(), false);
        EXPECT_EQ(WriteTreeDebugPrintToFile(iterativeStrTreeInstance), true);
    }

    /* // WIP: Recursive version
    TEST(BinaryTree_TestSuite, CreateRecursiveAVLTreeInstance)
    {
        // Arrange, Act
        const bool isSelfBalancing = true;
        StringSearchBinaryTree recursiveStrTreeInstance{ testDataBasic,
            BinaryTreeImplementationType::Recursive, "MyRecursiveStrAVLTreeInstance", isSelfBalancing };
        recursiveStrTreeInstance.BuildFromData();

        // Assert
        EXPECT_EQ(recursiveStrTreeInstance.IsValid(), true);
        EXPECT_EQ(WriteTreeDebugPrintToFile(recursiveStrTreeInstance), true);
        EXPECT_EQ(WritePlantUMLOutputToFile(recursiveStrTreeInstance), true);
    }

    TEST(BinaryTree_TestSuite, CreateIterativeAVLTreeInstance)
    {
        // Arrange, Act
        const bool isSelfBalancing = true;
        StringSearchBinaryTree iterativeStrTreeInstance{ testDataBasic,
            BinaryTreeImplementationType::Iterative, "MyIterativeStrAVLTreeInstance", isSelfBalancing };
        iterativeStrTreeInstance.BuildFromData();

        // Assert
        EXPECT_EQ(iterativeStrTreeInstance.IsValid(), true);
        EXPECT_EQ(WriteTreeDebugPrintToFile(iterativeStrTreeInstance), true);
        EXPECT_EQ(WritePlantUMLOutputToFile(iterativeStrTreeInstance), true);
    }*/

} // Symplektis::UnitTests