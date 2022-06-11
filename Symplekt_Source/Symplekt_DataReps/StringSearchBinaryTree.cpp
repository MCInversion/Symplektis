/*! \file  StringSearchBinaryTree.cpp
 *  \brief Implementation of a test class for binary tree architecture with switchable implementation.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   28.11.2021
 *
 */

#include "StringSearchBinaryTree.h"

namespace Symplektis::DataReps
{
    constexpr size_t size_type_size = sizeof(size_t);
	
	BinaryTreeErrorCode StringSearchBinaryTree::InternalBuildFromData()
	{
        while (!m_DataForConstruction.empty())
        {
			const auto dataIterator = m_DataForConstruction.begin();

        	//
        	// ================ init data node ==============================================
        	//

            const size_t stringDataSize = sizeof(*dataIterator);            
            const StringSearchNodeData newDataNodeData{ {stringDataSize + size_type_size}, *dataIterator };
            const auto nodeDatPtr = std::make_shared<StringSearchNodeData>(newDataNodeData);
            const auto newDataNode = std::make_shared<StringSearchNode>(StringSearchNode(nodeDatPtr));

        	//
            // =============== Insertion to an empty tree ===================================
        	//

        	if (IsEmpty())
            {                
                if (const auto treeErrorCode = InternalInsertNodeAsDataNode(newDataNode); // internally, new node gets set as current (if successful)
                    treeErrorCode != BinaryTreeErrorCode::OK)
                    return treeErrorCode;

                m_DataForConstruction.erase(dataIterator); // erase from data vector
                continue;
            }

        	//
            // =============== Insertion to an non-empty tree ===============================
            //

            const auto prevDataNode = std::dynamic_pointer_cast<StringSearchNode>(InternalGetCurrentNodeQueryDataNode());
            if (!prevDataNode)
                return BinaryTreeErrorCode::InternalError;


            if (newDataNodeData.IsPreferredOver(*prevDataNode->GetData()))
            {
                //
                // ============== Insertion to the left is preferred =============================
                //

                if (const auto treeErrorCode = InternalInsertLeftNodeAsDataNode(newDataNode); // internally, new left node gets set as current (if successful)
                    treeErrorCode != BinaryTreeErrorCode::OK)
                {
                    //
                    // ============== Left insertion failed =============================
                    // Possible reasons: ReinsertNode, NodeSaturated, LeftNodeExists, NodeNotPreLeaf, InternalError

                    if (treeErrorCode == BinaryTreeErrorCode::ReinsertNode)
                        continue;
                	
                	if (treeErrorCode == BinaryTreeErrorCode::NodeSaturated)
                	{
                		// If currentNode is saturated, left or right child node is set as current (based on value preference)
                        const auto leftDataNode = std::dynamic_pointer_cast<StringSearchNode>(InternalGetCurrentNodeLeftChildQueryDataNode());
                		if (!leftDataNode)
                            return BinaryTreeErrorCode::InternalError;

                		if (newDataNodeData.IsPreferredOver(*leftDataNode->GetData()))
                		{
                			// New node data has left preference over left child node data
                			
                            if (InternalSetCurrentNodeLeftChildAsCurrent() != BinaryTreeErrorCode::OK)
                                return BinaryTreeErrorCode::InternalError;

                			// left child is set as current, continue loop
                            continue;
                		}

                		// New node data does not have left preference over left child node data
                		// Right child node is the only option left, setting it as current node

                        if (InternalSetCurrentNodeRightChildAsCurrent() != BinaryTreeErrorCode::OK)
                            return BinaryTreeErrorCode::InternalError;

                        // right child is set as current, continue loop
                        continue;                		
                	}

                	if (treeErrorCode == BinaryTreeErrorCode::LeftNodeExists || treeErrorCode == BinaryTreeErrorCode::NodeNotPreLeaf)
                	{
                		// If left child node exists, left node is to be set as current
                        // Also if (in an AVL Tree construction) current node is not pre-leaf, we need to move further down to the left
                        if (InternalSetCurrentNodeLeftChildAsCurrent() != BinaryTreeErrorCode::OK)
                            return BinaryTreeErrorCode::InternalError;

                        // right child is set as current, continue loop
                        continue;
                	}

                	//
                	// ========= An unspecified internal error has occurred at this point, aborting construction ===========
                	//
                	
                    return treeErrorCode;
                }

            	//
            	// ========== Left Insertion Successful, Resetting Node Cursor to Root =================
            	//
            	
                if (const auto resetToRootErrorCode = InternalSetRootAsCurrent();
                    resetToRootErrorCode != BinaryTreeErrorCode::OK)
                    return resetToRootErrorCode;

                m_DataForConstruction.erase(dataIterator); // erase from data vector
                continue;
            }

            //
			// ============== Insertion to the right is preferred =============================
			//

            if (const auto treeErrorCode = InternalInsertRightNodeAsDataNode(newDataNode); // internally, new right node gets set as current (if successful)
                treeErrorCode != BinaryTreeErrorCode::OK)
            {
            	
                //
                // ============== Right insertion failed =============================
                // Possible reasons: ReinsertNode, NodeSaturated, RightNodeExists, NodeNotPreLeaf, InternalError

                if (treeErrorCode == BinaryTreeErrorCode::ReinsertNode)
                    continue;
            	
                if (treeErrorCode == BinaryTreeErrorCode::NodeSaturated)
                {
                    // If currentNode is saturated, left or right child node is set as current (based on value preference)
                    const auto rightDataNode = std::dynamic_pointer_cast<StringSearchNode>(InternalGetCurrentNodeRightChildQueryDataNode());
                    if (!rightDataNode)
                        return BinaryTreeErrorCode::InternalError;

                    if (newDataNodeData.IsPreferredOver(*rightDataNode->GetData()))
                    {
                        // New node data has left preference over right child node data

                        if (InternalSetCurrentNodeRightChildAsCurrent() != BinaryTreeErrorCode::OK)
                            return BinaryTreeErrorCode::InternalError;

                        // right child is set as current, continue loop
                        continue;
                    }

                    // New node data does not have left preference over right child node data
                    // Right child node is the only option left, setting it as current node

                    if (InternalSetCurrentNodeRightChildAsCurrent() != BinaryTreeErrorCode::OK)
                        return BinaryTreeErrorCode::InternalError;

                    // right child is set as current, continue loop
                    continue;
                }

                if (treeErrorCode == BinaryTreeErrorCode::RightNodeExists || treeErrorCode == BinaryTreeErrorCode::NodeNotPreLeaf)
                {
                    // If right child node exists, right node is to be set as current
                	// Also if (in an AVL Tree construction) current node is not pre-leaf, we need to move further down to the right
                    if (InternalSetCurrentNodeRightChildAsCurrent() != BinaryTreeErrorCode::OK)
                        return BinaryTreeErrorCode::InternalError;

                    // right child is set as current, continue loop
                    continue;
                }

                //
                // ========= An unspecified internal error has occurred at this point, aborting construction ===========
                //

                return treeErrorCode;            	
            }

            //
            // ========== Right Insertion Successful, Resetting Node Cursor to Root =================
            //

            if (const auto resetToRootErrorCode = InternalSetRootAsCurrent();
                resetToRootErrorCode != BinaryTreeErrorCode::OK)
                return resetToRootErrorCode;

            m_DataForConstruction.erase(dataIterator); // erase from data vector
        }

        InternalSetHeight();
        return BinaryTreeErrorCode::OK;
	}

	
    bool StringSearchNode::IntersectsData(const std::shared_ptr<NodeDataWrapper>& queryData) const
    {
        const auto stringData = std::static_pointer_cast<StringSearchNodeData>(queryData);

        if (stringData->DataString.empty() || m_Data->DataString.empty())
            return false;

        constexpr size_t startPos = 0;
        const auto match = m_Data->DataString.find(stringData->DataString, startPos);

        return match > 0;
    }

    //
    // ======================== Helper Functionality ======================================================
    //
	
    std::string StringSearchNode::DebugPrint() const
    {
        std::string result = "              m_Data->DataSize   :       " + std::to_string(m_Data->DataSize) + "\n";
                   result += "            m_Data->DataString   :       \"" + m_Data->DataString + "\"\n";
        return result;
    }
	
    std::string StringSearchNode::PlantUMLPrint() const
    {
        const std::string indent = "    ";        
        std::string result = indent + "-DataSize   = " + std::to_string(m_Data->DataSize) + "\n";
                   result += indent + "+DataString = \"" + m_Data->DataString + "\"\n";
		
        return result;
    }
} // Symplektis::DataReps