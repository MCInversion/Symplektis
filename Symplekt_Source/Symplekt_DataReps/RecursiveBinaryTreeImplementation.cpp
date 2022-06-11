/*! \file  RecursiveBinaryTreeImplementation.cpp
 *  \brief Implementation of a recursive implementation of a generic BinaryTree object.\n
 *         Allocates nodes recursively storing them in heap memory.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   29.10.2021
 *
 */

#include "RecursiveBinaryTreeImplementation.h"

#include <stack>
#include <queue>
#include <map>

namespace Symplektis::DataReps
{

    BinaryTreeErrorCode RecursiveBinaryTreeImplementation::InsertNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& newDataNode)
    {
        if (!newDataNode)
            return BinaryTreeErrorCode::InsertingNullNode;

        const auto newNode = std::make_shared<RecursiveBinaryTreeNode>(RecursiveBinaryTreeNode(m_TreeUUID));
        newNode->SetQueryDataNode(newDataNode);
    	
        if (!m_RootNode && !m_CurrentNode)
        {
            m_RootNode = newNode;
            m_CurrentNode = m_RootNode;
            m_NodeCount++; // update node count
            return BinaryTreeErrorCode::OK;
        }

        if (!m_CurrentNode)
            m_CurrentNode = m_RootNode;

        if (  m_CurrentNode->IsLeaf() ||    // if current node is a leaf prefer insertion to the left.
            (!m_CurrentNode->IsLeaf() &&
              m_CurrentNode->HasRightChild())) // left insertion also allowed when non leaf current node has no left child
        {
            const auto nodeErrorCode = m_CurrentNode->SetLeftChild(newNode);
            const auto treeErrorCode = InterpretNodeErrorCodeAsTreeErrorCode(nodeErrorCode);

            if (treeErrorCode != BinaryTreeErrorCode::OK)
                return treeErrorCode;

            m_CurrentNode = m_CurrentNode->LeftChildPtr();
            m_NodeCount++; // update node count
            return treeErrorCode;
        }

        if (!m_CurrentNode->HasLeftChild())
        {
            const auto nodeErrorCode = m_CurrentNode->SetRightChild(newNode);
            const auto treeErrorCode = InterpretNodeErrorCodeAsTreeErrorCode(nodeErrorCode);

            if (treeErrorCode != BinaryTreeErrorCode::OK)
                return treeErrorCode;

            m_CurrentNode = m_CurrentNode->RightChildPtr();
            m_NodeCount++;  // update node count
            return treeErrorCode;
        }

        // no insertion options left
        return BinaryTreeErrorCode::NodeSaturated;
    }

    BinaryTreeErrorCode RecursiveBinaryTreeImplementation::InsertLeftNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& newLeftDataNode)
    {
        if (!newLeftDataNode)
            return BinaryTreeErrorCode::InsertingNullNode;

        const auto newLeftNode = std::make_shared<RecursiveBinaryTreeNode>(RecursiveBinaryTreeNode(m_TreeUUID));
        newLeftNode->SetQueryDataNode(newLeftDataNode);
    	
        if (!m_RootNode && !m_CurrentNode)
        {
            m_RootNode = newLeftNode;
            m_CurrentNode = m_RootNode;
            return BinaryTreeErrorCode::OK;
        }

        if (!m_CurrentNode)
            m_CurrentNode = m_RootNode;

    	if (m_CurrentNode->HasLeftChild())
    	{
    		if (m_IsSelfBalancing && m_CurrentNode->ComputeAVLBalanceFactor() != 0) // right rotate insertion site for AVL tree implementation
    		{
                if (const auto rightRotateErr = RebalanceFromCurrentNode();
                    rightRotateErr != BinaryTreeErrorCode::OK)
                    return rightRotateErr;

                m_CurrentNode = m_CurrentNode->ParentNodePtr();  // new insertion site
                return BinaryTreeErrorCode::ReinsertNode;
    		}
            return BinaryTreeErrorCode::LeftNodeExists;
    	}

        const auto nodeErrorCode = m_CurrentNode->SetLeftChild(newLeftNode);
        const auto treeErrorCode = InterpretNodeErrorCodeAsTreeErrorCode(nodeErrorCode);

        if (treeErrorCode != BinaryTreeErrorCode::OK)
            return treeErrorCode;

        m_CurrentNode = m_CurrentNode->LeftChildPtr();
        m_NodeCount++; // update node count
        return treeErrorCode;
    }

    BinaryTreeErrorCode RecursiveBinaryTreeImplementation::InsertRightNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& newRightDataNode)
    {
        if (!newRightDataNode)
            return BinaryTreeErrorCode::InsertingNullNode;

        const auto newRightNode = std::make_shared<RecursiveBinaryTreeNode>(RecursiveBinaryTreeNode(m_TreeUUID));
        newRightNode->SetQueryDataNode(newRightDataNode);
    	
        if (!m_RootNode && !m_CurrentNode)
        {
            m_RootNode = newRightNode;
            m_CurrentNode = m_RootNode;
            return BinaryTreeErrorCode::OK;
        }

        if (!m_CurrentNode)
            m_CurrentNode = m_RootNode;

    	if (m_CurrentNode->HasRightChild())
    	{
            if (m_IsSelfBalancing && m_CurrentNode->ComputeAVLBalanceFactor() != 0) // left pre-rotate insertion site for AVL tree implementation
            {
                if (const auto leftRotateErr = RebalanceFromCurrentNode();
                    leftRotateErr != BinaryTreeErrorCode::OK)
                    return leftRotateErr;

                m_CurrentNode = m_CurrentNode->ParentNodePtr(); // new insertion site
                return BinaryTreeErrorCode::ReinsertNode;
            }
            return BinaryTreeErrorCode::RightNodeExists;
    	}

        const auto nodeErrorCode = m_CurrentNode->SetRightChild(newRightNode);
        const auto treeErrorCode = InterpretNodeErrorCodeAsTreeErrorCode(nodeErrorCode);

        if (treeErrorCode != BinaryTreeErrorCode::OK)
            return treeErrorCode;

        m_CurrentNode = m_CurrentNode->RightChildPtr();
        m_NodeCount++; // update node count
        return treeErrorCode;
    }

    void RecursiveBinaryTreeImplementation::ForceInsertLeftNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& insertedLeftDataNode)
    {
        if (!insertedLeftDataNode)
            return;

        const auto insertedLeftNode = std::make_shared<RecursiveBinaryTreeNode>(RecursiveBinaryTreeNode(m_TreeUUID));
        insertedLeftNode->SetQueryDataNode(insertedLeftDataNode);
    	
        if (!m_RootNode && !m_CurrentNode)  // inserting to an empty tree
        {
            m_RootNode = insertedLeftNode;
            m_CurrentNode = m_RootNode;
        }

        if (!m_CurrentNode)
            m_CurrentNode = m_RootNode;

        // update m_NodeCount
        m_NodeCount += (insertedLeftNode->CountChildren() - m_CurrentNode->LeftChildPtr()->CountChildren());
    	
        m_CurrentNode->ForceSetLeftChild(insertedLeftNode);
        m_CurrentNode = m_CurrentNode->LeftChildPtr();
    }

    void RecursiveBinaryTreeImplementation::ForceInsertRightNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& insertedRightDataNode)
    {
        if (!insertedRightDataNode)
            return;

        const auto insertedRightNode = std::make_shared<RecursiveBinaryTreeNode>(RecursiveBinaryTreeNode(m_TreeUUID));
        insertedRightNode->SetQueryDataNode(insertedRightDataNode);
    	
        if (!m_RootNode && !m_CurrentNode)  // inserting to an empty tree
        {
            m_RootNode = insertedRightNode;
            m_CurrentNode = m_RootNode;
        }

        if (!m_CurrentNode)
            m_CurrentNode = m_RootNode;

        // update m_NodeCount
        m_NodeCount += (insertedRightNode->CountChildren() - m_CurrentNode->RightChildPtr()->CountChildren());

        m_CurrentNode->ForceSetRightChild(insertedRightNode);
        m_CurrentNode = m_CurrentNode->RightChildPtr();
    }

    //
    // ======================== AVL Rebalancing ======================================================
    //

    BinaryTreeErrorCode RecursiveBinaryTreeImplementation::RebalanceFromCurrentNode()
    {
        return BinaryTreeErrorCode();
    }

    //
    // ======================== Node Deleters ======================================================
    //

    BinaryTreeErrorCode RecursiveBinaryTreeImplementation::DeleteNode(const std::shared_ptr<IBinaryTreeNode>& nodeForDeletion)
    {
        if (!nodeForDeletion ||                              // avoiding null nodes
            nodeForDeletion->GetTreeUUID() != m_TreeUUID)    // cheapest check for node inclusion: tree UUID
            return BinaryTreeErrorCode::NodeNotFound;

        std::stack<RecursiveBinaryTreeNode*> nodeStack{};
        nodeStack.push(m_RootNode.get());

        bool nodeFound = false;
    	while (!nodeStack.empty())
        {
            const auto nodeItem = nodeStack.top();
            nodeStack.pop();

            if (nodeItem->GetNodeUUID() == nodeForDeletion->GetTreeUUID())
            {
                nodeFound = true;
                // update m_NodeCount
                m_NodeCount -= (m_CurrentNode->RightChildPtr()->CountChildren() + 1);
                m_CurrentNode = std::make_shared<RecursiveBinaryTreeNode>(*nodeItem);
                break;
            }

            nodeStack.push(nodeItem->LeftChildPtr().get());
            nodeStack.push(nodeItem->RightChildPtr().get());
        }

    	if (nodeFound)
    	{
    		m_CurrentNode->DeleteChildren();
            m_CurrentNode = nullptr;
            return BinaryTreeErrorCode::OK;
    	}
    	
        return BinaryTreeErrorCode::NodeNotFound;
    }

    std::shared_ptr<IBinaryTreeQueryDataNode> RecursiveBinaryTreeImplementation::GetCurrentNodeQueryDataNode() const
    {
        if (!m_CurrentNode)
            return nullptr;
    	
        return m_CurrentNode->GetQueryDataNode();
    }

    std::shared_ptr<IBinaryTreeQueryDataNode> RecursiveBinaryTreeImplementation::GetCurrentNodeLeftChildQueryDataNode() const
    {
        if (!m_CurrentNode)
            return nullptr;

        if (!m_CurrentNode->HasLeftChild())
            return nullptr;

        return m_CurrentNode->LeftChildPtr()->GetQueryDataNode();
    }

    std::shared_ptr<IBinaryTreeQueryDataNode> RecursiveBinaryTreeImplementation::GetCurrentNodeRightChildQueryDataNode() const
    {
        if (!m_CurrentNode)
            return nullptr;

        if (!m_CurrentNode->HasRightChild())
            return nullptr;

        return m_CurrentNode->RightChildPtr()->GetQueryDataNode();
    }

    std::vector<std::shared_ptr<NodeDataWrapper>> RecursiveBinaryTreeImplementation::GetTreeDataFromDepthFirstTraversal() const
    {
        std::vector<std::shared_ptr<NodeDataWrapper>> resultData{};
        const size_t nodeCount = GetNodeCount();
        resultData.reserve(nodeCount);

        std::stack<const RecursiveBinaryTreeNode*> nodeStack{};
        nodeStack.push(m_RootNode.get());

        while (!nodeStack.empty())
        {
            const auto nodeItem = nodeStack.top();
            nodeStack.pop();

            resultData.emplace_back(nodeItem->GetQueryDataNode()->GetDataWrapper());

            if (nodeItem->HasRightChild())
                nodeStack.push(nodeItem->RightChildPtr().get());

            if (nodeItem->HasLeftChild())
                nodeStack.push(nodeItem->LeftChildPtr().get());
        }

        return resultData;
    }

    std::vector<std::shared_ptr<NodeDataWrapper>> RecursiveBinaryTreeImplementation::GetTreeDataFromBreadthFirstTraversal() const
    {
        std::vector<std::shared_ptr<NodeDataWrapper>> resultData{};
        const size_t nodeCount = GetNodeCount();
        resultData.reserve(nodeCount);

        std::queue<const RecursiveBinaryTreeNode*> nodeQueue{};
        nodeQueue.push(m_RootNode.get());

        while (!nodeQueue.empty())
        {
            const auto nodeItem = nodeQueue.front();
            nodeQueue.pop();

            resultData.emplace_back(nodeItem->GetQueryDataNode()->GetDataWrapper());

            if (nodeItem->HasLeftChild())
                nodeQueue.push(nodeItem->LeftChildPtr().get());

            if (nodeItem->HasRightChild())
                nodeQueue.push(nodeItem->RightChildPtr().get());
        }

        return resultData;
    }

    BinaryTreeErrorCode RecursiveBinaryTreeImplementation::SetCurrentNode(const std::shared_ptr<IBinaryTreeNode>& nodeAsCurrent)
    {
        if (!nodeAsCurrent || nodeAsCurrent->GetTreeUUID() != m_TreeUUID)
            return BinaryTreeErrorCode::NodeNotFound;

        m_CurrentNode = std::static_pointer_cast<RecursiveBinaryTreeNode>(nodeAsCurrent);
        return BinaryTreeErrorCode::OK;
    }

    BinaryTreeErrorCode RecursiveBinaryTreeImplementation::SetRootAsCurrent()
    {
        if (!m_RootNode)
            return BinaryTreeErrorCode::NodeNotFound;
    	
        return SetCurrentNode(m_RootNode);
    }

    BinaryTreeErrorCode RecursiveBinaryTreeImplementation::SetCurrentNodeLeftChildAsCurrent()
    {
        if (!m_CurrentNode)
            return BinaryTreeErrorCode::CurrentNodeNotSet;

        if (!m_CurrentNode->HasLeftChild())
            return BinaryTreeErrorCode::NodeNotFound;

    	return SetCurrentNode(m_CurrentNode->LeftChildPtr());
    }

    BinaryTreeErrorCode RecursiveBinaryTreeImplementation::SetCurrentNodeRightChildAsCurrent()
    {
        if (!m_CurrentNode)
            return BinaryTreeErrorCode::CurrentNodeNotSet;

        if (!m_CurrentNode->HasRightChild())
            return BinaryTreeErrorCode::NodeNotFound;

        return SetCurrentNode(m_CurrentNode->RightChildPtr());
    }


    void RecursiveBinaryTreeImplementation::SetHeightFromCompleteTree()
    {
        if (!m_RootNode)
        {
            m_TreeHeight = 0;
            return;
        }

        m_TreeHeight = m_RootNode->GetHeight();
    }

	//
	// ======================== Helper Functionality ======================================================
	//

    std::string RecursiveBinaryTreeImplementation::DebugPrint() const
    {
        std::string result = "          Recursive Binary Tree Implementation Debug Print       \n";
    	
        const size_t nodeCount = GetNodeCount();
        result += "    Node Count:            " + std::to_string(nodeCount) + "\n";
        result += "    Height    :            " + std::to_string(GetHeight()) + "\n";
        const std::string isBalancedStr = (IsBalanced() ? "YES" : "NO");
        result += "    Balanced  :            " + isBalancedStr + "\n";
        result += "..................................................................\n";
        result += "- - - - - - - - - - - -    N O D E S  - - - - - - - - - - - - - - \n";
        result += "..................................................................\n";

        std::stack<const RecursiveBinaryTreeNode*> nodeStack{};
        nodeStack.push(m_RootNode.get());

        while (!nodeStack.empty())
        {
            const auto nodeItem = nodeStack.top();
            nodeStack.pop();

            result += nodeItem->DebugPrint();

            if (nodeItem->HasLeftChild())
				nodeStack.push(nodeItem->LeftChildPtr().get());

        	if (nodeItem->HasRightChild())
				nodeStack.push(nodeItem->RightChildPtr().get());
        }

        result += "..................................................................\n";
        result += "- - - - - - - - - - - -  E N D    N O D E S   - - - - - - - - - - \n";
        result += "..................................................................\n";
    	
        return result;
    }

    std::string RecursiveBinaryTreeImplementation::PlantUMLPrint() const
    {
        std::string result = "title: Recursive Binary Tree Instance [";
        const std::string treeUUIDStr = Util::GetUUIDString(GetTreeUUID());
        result += treeUUIDStr + "]\n\n";

        if (!m_RootNode)
            return result;

        const std::string colorCodeRootNode = "#b7bbbd"; // gray-ish
        const std::string colorCodeLeftNode = "#6fcaed"; // light blue
        const std::string colorCodeRightNode = "#d68976"; // light red

        const bool isBalanced = IsBalanced();

        // print root node
        const std::string rootNodeClassBracketContent = "0, " + colorCodeRootNode;

        const auto rootNodeUUIDString = Util::GetUUIDString(m_RootNode->GetNodeUUID());
        result += "class \"" + rootNodeUUIDString + "\" << (";
        result += rootNodeClassBracketContent + ") >> {\n";
    	if (!isBalanced)
    	{
			const auto rootNodeBalanceFactor = m_RootNode->ComputeAVLBalanceFactor();
            result += "    ~BalanceFactor = " + std::to_string(rootNodeBalanceFactor) + "\n";
            result += "    --\n"; // separator
    	}
        result += m_RootNode->GetQueryDataNode()->PlantUMLPrint() + "}\n\n";

        if (m_RootNode->IsLeaf())
            return result;

        std::stack<const RecursiveBinaryTreeNode*> nodeStack{};
        nodeStack.push(m_RootNode.get());

        // fill connectivity information to UUID string maps
        std::map<std::string, std::string> leftUUIDToQueryDataNodePrint{};
        std::map<std::string, std::string> rightUUIDToQueryDataNodePrint{};
        std::map<std::string, std::string> leftUUIDConnectivityMap{};
        std::map<std::string, std::string> rightUUIDConnectivityMap{};

        std::map<std::string, long int> uuidToBalanceFactorMap{};

    	while (!nodeStack.empty())
    	{
            const auto nodeItem = nodeStack.top();
            nodeStack.pop();

            const auto uuidString = Util::GetUUIDString(nodeItem->GetNodeUUID());
            if (!isBalanced)
            {
                const auto balanceFactor = nodeItem->ComputeAVLBalanceFactor();
                uuidToBalanceFactorMap[uuidString] = balanceFactor;
            }

            if (nodeItem->HasLeftChild())
            {
                const auto leftChildPtr = nodeItem->LeftChildPtr();
                const auto leftChildUUIDString = Util::GetUUIDString(leftChildPtr->GetNodeUUID());
                leftUUIDConnectivityMap[uuidString] = leftChildUUIDString;

                const auto leftChildQueryDataNodePrint = leftChildPtr->GetQueryDataNode()->PlantUMLPrint();
				leftUUIDToQueryDataNodePrint[leftChildUUIDString] = leftChildQueryDataNodePrint;
            	
                nodeStack.push(leftChildPtr.get());
            }

            if (nodeItem->HasRightChild())
            {
                const auto rightChildPtr = nodeItem->RightChildPtr();
                const auto rightChildUUIDString = Util::GetUUIDString(rightChildPtr->GetNodeUUID());
                rightUUIDConnectivityMap[uuidString] = rightChildUUIDString;

                const auto rightChildQueryDataNodePrint = rightChildPtr->GetQueryDataNode()->PlantUMLPrint();
                rightUUIDToQueryDataNodePrint[rightChildUUIDString] = rightChildQueryDataNodePrint;
            	
                nodeStack.push(rightChildPtr.get());
            }
    	}

        // preallocate connectivity prints
        std::vector<std::string> leftConnectivityRelationPrints{};
        leftConnectivityRelationPrints.reserve(leftUUIDConnectivityMap.size());
        std::vector<std::string> rightConnectivityRelationPrints{};
        rightConnectivityRelationPrints.reserve(rightUUIDConnectivityMap.size());

        // fill connectivity prints and print child nodes with child color code identifiers
        const std::string leftChildNodeClassBracketContent = "L, " + colorCodeLeftNode;
    	for (const auto& [parentUUID, leftChildUUID] : leftUUIDConnectivityMap)
    	{
            result += "class \"" + leftChildUUID + "\" << (";
    		result += leftChildNodeClassBracketContent + ") >> {\n";
            if (!isBalanced)
            {
                result += "    ~BalanceFactor = " + std::to_string(uuidToBalanceFactorMap[leftChildUUID]) + "\n";
                result += "    --\n"; // separator
            }
    		result += leftUUIDToQueryDataNodePrint[leftChildUUID] + "}\n\n";

            const std::string leftConnectRelationPrint = "\"" + parentUUID + "\" ---> \"" + leftChildUUID + "\"\n";
            leftConnectivityRelationPrints.emplace_back(leftConnectRelationPrint);
    	}

        const std::string rightChildNodeClassBracketContent = "R, " + colorCodeRightNode;
        for (const auto& [parentUUID, rightChildUUID] : rightUUIDConnectivityMap)
        {
            result += "class \"" + rightChildUUID + "\" << (";
        	result += rightChildNodeClassBracketContent + ") >> {\n";
            if (!isBalanced)
            {
                result += "    ~BalanceFactor = " + std::to_string(uuidToBalanceFactorMap[rightChildUUID]) + "\n";
                result += "    --\n"; // separator
            }
            result += rightUUIDToQueryDataNodePrint[rightChildUUID] + "}\n\n";

            const std::string rightConnectRelationPrint = "\"" + parentUUID + "\" ---> \"" + rightChildUUID + "\"\n";
            rightConnectivityRelationPrints.emplace_back(rightConnectRelationPrint);
        }

        result += "\n\n";

        for (const auto& connectPrint : leftConnectivityRelationPrints) result += connectPrint;
        for (const auto& connectPrint : rightConnectivityRelationPrints) result += connectPrint;

        result += "\n";
    	
        return result;
    }

    //
    // ======================== Private Operation Functionality ======================================================
    //

    BinaryTreeErrorCode RecursiveBinaryTreeImplementation::RotateLeftAtCurrentNode()
    {
        return BinaryTreeErrorCode();
    }

    BinaryTreeErrorCode RecursiveBinaryTreeImplementation::RotateRightAtCurrentNode()
    {
        return BinaryTreeErrorCode();
    }

    BinaryTreeErrorCode RecursiveBinaryTreeImplementation::RotateLeftRightAtCurrentNode()
    {
        return BinaryTreeErrorCode();
    }

    BinaryTreeErrorCode RecursiveBinaryTreeImplementation::RotateRightLeftAtCurrentNode()
    {
        return BinaryTreeErrorCode();
    }

    void RecursiveBinaryTreeImplementation::UpdateNodeHeightsAndBalanceFactorsUpToRoot()
    {
    }

} // Symplektis::DataReps