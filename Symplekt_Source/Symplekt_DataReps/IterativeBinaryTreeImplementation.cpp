/*! \file  IterativeBinaryTreeImplementation.cpp
 *  \brief Implementation of an iterative implementation of a generic BinaryTree object.\n
 *         Allocates nodes Iteratively storing them in a pre-defined array memory storage.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   29.10.2021
 *
 */

#include "IterativeBinaryTreeImplementation.h"

#include "BinaryTreeUtils.h"

#include "../Symplekt_UtilityGeneral/Assert.h"

#include <functional>
#include <map>
#include <stack>
#include <queue>

namespace Symplektis::DataReps
{

    //-----------------------------------------------------------------------------
    /*! \brief Counts nodes marked for delete.
     *  \param[in] nodeArray           node array
     *  \return count of node elements marked for delete.
     *
     *   \author M. Cavarga (MCInversion)
     *   \date   2.11.2021
     */
     //-----------------------------------------------------------------------------
    static size_t CountNodesMarkedForDelete(const std::vector<IterativeBinaryTreeNode>& nodeArray)
    {
        size_t count = 0;
        for (const auto& node : nodeArray)
        {
            if (node.IsMarkedForDelete()) count++;
        }
        return count;
    }

    BinaryTreeErrorCode IterativeBinaryTreeImplementation::InsertNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& newDataNode)
    {
        if (!newDataNode)
            return BinaryTreeErrorCode::InsertingNullNode;
    	
        if (m_NodeArray.empty() && !m_CurrentNodeId && !m_RootNodeId) // inserting to an empty tree
        {
            if (m_NodeArray.insert(m_NodeArray.end(), IterativeBinaryTreeNode(m_TreeUUID, newDataNode)) == m_NodeArray.end())
                return BinaryTreeErrorCode::InternalError;

            m_RootNodeId = 0;
            m_CurrentNodeId = m_RootNodeId;
            UpdateNodeCount();
            return BinaryTreeErrorCode::OK;
        }

        if (!m_NodeArray.empty() && (!m_CurrentNodeId || !m_RootNodeId))
        {
            // somehow, the node array has nodes, but current node or root node are not set
            m_RootNodeId = (!m_RootNodeId ? 0 : m_RootNodeId.get());
            m_CurrentNodeId = m_RootNodeId;
        }

        const auto& currentNodeInitialRef = m_NodeArray[m_CurrentNodeId];

        if (  currentNodeInitialRef.IsLeaf() ||      // if current node is a leaf prefer insertion to the left.
            (!currentNodeInitialRef.IsLeaf() &&
             !currentNodeInitialRef.HasLeftChild())) // left insertion also allowed when non leaf current node has no left child
        {
        	const auto newNodeIter = m_NodeArray.insert(m_NodeArray.end(), IterativeBinaryTreeNode(m_TreeUUID, newDataNode));
            if (newNodeIter == m_NodeArray.end())
                return BinaryTreeErrorCode::InternalError;
        	
            UpdateNodeCount();
			auto& currentNode = m_NodeArray[m_CurrentNodeId];  // currentNode ref needs to be set after m_NodeArray.insert    
        	
            const size_t newNodeArrayPos = newNodeIter - m_NodeArray.begin();
            auto nodeErrorCode = currentNode.SetLeftChildId(NodeArrayIndex{ newNodeArrayPos });
            auto treeErrorCode = InterpretNodeErrorCodeAsTreeErrorCode(nodeErrorCode);

            if (treeErrorCode != BinaryTreeErrorCode::OK)
                return treeErrorCode;

            nodeErrorCode = m_NodeArray[newNodeArrayPos].SetParentNodeId(m_CurrentNodeId);
            treeErrorCode = InterpretNodeErrorCodeAsTreeErrorCode(nodeErrorCode);

        	if (treeErrorCode != BinaryTreeErrorCode::OK)
                return treeErrorCode;

            const auto previousCurrentNodeId = m_CurrentNodeId;
            m_CurrentNodeId = newNodeArrayPos;

            // the height of the current node updates when it used to be a leaf before successful insertion    	
            UpdateNodeHeightsAndBalanceFactorsUpToRoot();

            if (m_IsSelfBalancing)
            {
                m_CurrentNodeId = previousCurrentNodeId; // reset current node to pivot for rebalancing

                // rebalance up to root
                if (const auto rebalanceErr = RebalanceFromCurrentNode();
                    rebalanceErr != BinaryTreeErrorCode::OK)
                    return rebalanceErr;

                m_CurrentNodeId = newNodeArrayPos;
            }
        	
            return treeErrorCode;
        }

        if (!currentNodeInitialRef.HasRightChild())
        {
            const auto newNodeIter = m_NodeArray.insert(m_NodeArray.end(), IterativeBinaryTreeNode(m_TreeUUID, newDataNode));
            if (newNodeIter == m_NodeArray.end())
                return BinaryTreeErrorCode::InternalError;
        	
            UpdateNodeCount();
            auto& currentNode = m_NodeArray[m_CurrentNodeId];  // currentNode ref needs to be set after m_NodeArray.insert    

            const size_t newNodeArrayPos = newNodeIter - m_NodeArray.begin();
            auto nodeErrorCode = currentNode.SetRightChildId(NodeArrayIndex{ newNodeArrayPos });        	
            auto treeErrorCode = InterpretNodeErrorCodeAsTreeErrorCode(nodeErrorCode);

            if (treeErrorCode != BinaryTreeErrorCode::OK)
                return treeErrorCode;

            nodeErrorCode = m_NodeArray[newNodeArrayPos].SetParentNodeId(m_CurrentNodeId);
            treeErrorCode = InterpretNodeErrorCodeAsTreeErrorCode(nodeErrorCode);

            if (treeErrorCode != BinaryTreeErrorCode::OK)
                return treeErrorCode;

            const auto previousCurrentNodeId = m_CurrentNodeId;
            m_CurrentNodeId = newNodeArrayPos;

            // the height of the current node updates when it used to be a leaf before successful insertion    	
            UpdateNodeHeightsAndBalanceFactorsUpToRoot();

            if (m_IsSelfBalancing)
            {
                m_CurrentNodeId = previousCurrentNodeId; // reset current node to pivot for rebalancing

                // rebalance up to root
                if (const auto rebalanceErr = RebalanceFromCurrentNode();
                    rebalanceErr != BinaryTreeErrorCode::OK)
                    return rebalanceErr;

                m_CurrentNodeId = newNodeArrayPos;
            }
        	
            return treeErrorCode;
        }

        // no insertion options left
        return BinaryTreeErrorCode::NodeSaturated;
    }

    BinaryTreeErrorCode IterativeBinaryTreeImplementation::InsertLeftNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& newLeftDataNode)
    {
        if (!newLeftDataNode)
            return BinaryTreeErrorCode::InsertingNullNode;
    	
        if (m_NodeArray.empty() && !m_CurrentNodeId && !m_RootNodeId) // inserting to an empty tree
        {
            if (m_NodeArray.insert(m_NodeArray.end(), IterativeBinaryTreeNode(m_TreeUUID, newLeftDataNode)) == m_NodeArray.end())
                return BinaryTreeErrorCode::InternalError;

            m_RootNodeId = 0;
            m_CurrentNodeId = m_RootNodeId;
            UpdateNodeCount();
            return BinaryTreeErrorCode::OK;
        }

        if (!m_NodeArray.empty() && (!m_CurrentNodeId || !m_RootNodeId))
        {
            // somehow, the node array has nodes, but current node or root node are not set
            m_RootNodeId = (!m_RootNodeId ? 0 : m_RootNodeId.get());
            m_CurrentNodeId = m_RootNodeId;
        }

        if (m_NodeArray[m_CurrentNodeId].HasLeftChild())
        {
            return BinaryTreeErrorCode::LeftNodeExists;
        }

        const auto newLeftNodeIter = m_NodeArray.insert(m_NodeArray.end(), IterativeBinaryTreeNode(m_TreeUUID, newLeftDataNode));
        if (newLeftNodeIter == m_NodeArray.end())
            return BinaryTreeErrorCode::InternalError;

        UpdateNodeCount();
        auto& currentNode = m_NodeArray[m_CurrentNodeId]; // currentNode ref needs to be set after m_NodeArray.insert    	

        const size_t newLeftNodeArrayPos = newLeftNodeIter - m_NodeArray.begin();
        auto nodeErrorCode = currentNode.SetLeftChildId(NodeArrayIndex{ newLeftNodeArrayPos });
        auto treeErrorCode = InterpretNodeErrorCodeAsTreeErrorCode(nodeErrorCode);

        if (treeErrorCode != BinaryTreeErrorCode::OK)
            return treeErrorCode;

        nodeErrorCode = newLeftNodeIter->SetParentNodeId(m_CurrentNodeId);
        treeErrorCode = InterpretNodeErrorCodeAsTreeErrorCode(nodeErrorCode);

        if (treeErrorCode != BinaryTreeErrorCode::OK)
            return treeErrorCode;

        const auto previousCurrentNodeId = m_CurrentNodeId;
        m_CurrentNodeId = newLeftNodeArrayPos;
    	
        // the height of the current node updates when it used to be a leaf before successful insertion    	
        UpdateNodeHeightsAndBalanceFactorsUpToRoot();
    	
        if (m_IsSelfBalancing)
        {
            m_CurrentNodeId = previousCurrentNodeId; // reset current node to pivot for rebalancing
        	
            // rebalance up to root
            if (const auto rebalanceErr = RebalanceFromCurrentNode();
                rebalanceErr != BinaryTreeErrorCode::OK)
                return rebalanceErr;

            m_CurrentNodeId = newLeftNodeArrayPos;
        }
    	
        return treeErrorCode;
    }

    BinaryTreeErrorCode IterativeBinaryTreeImplementation::InsertRightNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& newRightDataNode)
    {
        if (!newRightDataNode)
            return BinaryTreeErrorCode::InsertingNullNode;
    	
        if (m_NodeArray.empty() && !m_CurrentNodeId && !m_RootNodeId) // inserting to an empty tree
        {
            if (m_NodeArray.insert(m_NodeArray.end(), IterativeBinaryTreeNode(m_TreeUUID, newRightDataNode)) == m_NodeArray.end())
                return BinaryTreeErrorCode::InternalError;

            m_RootNodeId = 0;
            m_CurrentNodeId = m_RootNodeId;
            UpdateNodeCount();
            return BinaryTreeErrorCode::OK;
        }

        if (!m_NodeArray.empty() && (!m_CurrentNodeId || !m_RootNodeId))
        {
            // somehow, the node array has nodes, but current node or root node are not set
            m_RootNodeId = (!m_RootNodeId ? 0 : m_RootNodeId.get());
            m_CurrentNodeId = m_RootNodeId;
        }

        if (m_NodeArray[m_CurrentNodeId].HasRightChild())
        {
            return BinaryTreeErrorCode::RightNodeExists;
        }

        const auto newRightNodeIter = m_NodeArray.insert(m_NodeArray.end(), IterativeBinaryTreeNode(m_TreeUUID, newRightDataNode));
        if (newRightNodeIter == m_NodeArray.end())
            return BinaryTreeErrorCode::InternalError;
    	
        UpdateNodeCount();
        auto& currentNode = m_NodeArray[m_CurrentNodeId]; // currentNode ref needs to be set after m_NodeArray.insert    
    	
        const size_t newRightNodeArrayPos = newRightNodeIter - m_NodeArray.begin();
        auto nodeErrorCode = currentNode.SetRightChildId(NodeArrayIndex{ newRightNodeArrayPos });
        auto treeErrorCode = InterpretNodeErrorCodeAsTreeErrorCode(nodeErrorCode);

        if (treeErrorCode != BinaryTreeErrorCode::OK)
            return treeErrorCode;

        nodeErrorCode = newRightNodeIter->SetParentNodeId(m_CurrentNodeId);
        treeErrorCode = InterpretNodeErrorCodeAsTreeErrorCode(nodeErrorCode);

        if (treeErrorCode != BinaryTreeErrorCode::OK)
            return treeErrorCode;

        const auto previousCurrentNodeId = m_CurrentNodeId;
        m_CurrentNodeId = newRightNodeArrayPos;

        // the height of the current node updates when it used to be a leaf before successful insertion    	
        UpdateNodeHeightsAndBalanceFactorsUpToRoot();

        if (m_IsSelfBalancing)
        {
            m_CurrentNodeId = previousCurrentNodeId; // reset current node to pivot for rebalancing

            // rebalance up to root
            if (const auto rebalanceErr = RebalanceFromCurrentNode();
                rebalanceErr != BinaryTreeErrorCode::OK)
                return rebalanceErr;

            m_CurrentNodeId = newRightNodeArrayPos;
        }
    	
        return treeErrorCode;
    }

    void IterativeBinaryTreeImplementation::ForceInsertLeftNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& insertedLeftDataNode)
    {
        if (!insertedLeftDataNode)
            return;
    	
        auto insertedIterativeLeftNode = IterativeBinaryTreeNode(m_TreeUUID); // create node instance
        insertedIterativeLeftNode.SetQueryDataNode(insertedLeftDataNode);     // assign data node to iterative node instance

        if (m_NodeArray.empty() && !m_CurrentNodeId && !m_RootNodeId) // inserting to an empty tree
        {
            if(m_NodeArray.insert(m_NodeArray.end(), IterativeBinaryTreeNode(m_TreeUUID, insertedLeftDataNode)) == m_NodeArray.end())
                return;

            m_RootNodeId = 0;
            m_CurrentNodeId = m_RootNodeId;
            UpdateNodeCount();
            return;
        }

        if (!m_NodeArray.empty() && (!m_CurrentNodeId || !m_RootNodeId))
        {
            // somehow, the node array has nodes, but current node or root node are not set
            m_RootNodeId = (!m_RootNodeId ? 0 : m_RootNodeId.get());
            m_CurrentNodeId = m_RootNodeId;
        }

        const auto insertedLeftNodeIter = m_NodeArray.insert(m_NodeArray.end(), IterativeBinaryTreeNode(m_TreeUUID, insertedLeftDataNode));
        if (insertedLeftNodeIter == m_NodeArray.end())
            return;

        UpdateNodeCount();
        auto& currentNode = m_NodeArray[m_CurrentNodeId];

    	/*
    	// TODO: Figure out whether node deletion implies deletion of entire left and right subtree.
    	if (currentNode.HasLeftChild())
    	{
    		// mark entire left subtree as deleted

            std::vector<NodeArrayIndex> nodeIndicesForDeletion{};
            const size_t expectedSubtreeSize = pow(2, currentNode.GetHeight());
            nodeIndicesForDeletion.reserve(expectedSubtreeSize);
            nodeIndicesForDeletion.emplace_back(currentNode.LeftChildId());

    		while (!nodeIndicesForDeletion.empty())
    		{
                const auto childId = nodeIndicesForDeletion[nodeIndicesForDeletion.size() - 1];
                nodeIndicesForDeletion.pop_back();
    			
                auto& child = m_NodeArray[childId];
                child.SetMarkedForDelete(true);

                if (child.HasLeftChild())
                    nodeIndicesForDeletion.emplace_back(child.LeftChildId());

    			if (child.HasRightChild())
                    nodeIndicesForDeletion.emplace_back(child.RightChildId());
    		}    		
    	}*/
        
        const size_t insertedLeftNodeArrayPos = insertedLeftNodeIter - m_NodeArray.begin();
        currentNode.ForceSetLeftChildId(NodeArrayIndex{ insertedLeftNodeArrayPos });
        if (insertedLeftNodeIter->SetParentNodeId(m_CurrentNodeId) != BinaryNodeErrorCode::OK)
            return;
    	
        m_CurrentNodeId = insertedLeftNodeArrayPos;
    	
        if (m_ClearAfterMarkingForDelete)
            ClearNodesMarkedForDelete();
    }

    void IterativeBinaryTreeImplementation::ForceInsertRightNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& insertedRightDataNode)
    {
        if (!insertedRightDataNode)
            return;

        auto insertedIterativeRightNode = IterativeBinaryTreeNode(m_TreeUUID, insertedRightDataNode); // create node instance
        insertedIterativeRightNode.SetQueryDataNode(insertedRightDataNode);    // assign data node to iterative node instance
    	
        if (m_NodeArray.empty() && !m_CurrentNodeId && !m_RootNodeId) // inserting to an empty tree
        {
            if (m_NodeArray.insert(m_NodeArray.end(), IterativeBinaryTreeNode(m_TreeUUID, insertedRightDataNode)) == m_NodeArray.end())
                return;

            m_RootNodeId = 0;
            m_CurrentNodeId = m_RootNodeId;
            UpdateNodeCount();
            return;
        }

        if (!m_NodeArray.empty() && (!m_CurrentNodeId || !m_RootNodeId))
        {
            // somehow, the node array has nodes, but current node or root node are not set
            m_RootNodeId = (!m_RootNodeId ? 0 : m_RootNodeId.get());
            m_CurrentNodeId = m_RootNodeId;
        }

        const auto insertedRightNodeIter = m_NodeArray.insert(m_NodeArray.end(), IterativeBinaryTreeNode(m_TreeUUID, insertedRightDataNode));
    	if (insertedRightNodeIter == m_NodeArray.end())
            return;

        UpdateNodeCount();
        auto& currentNode = m_NodeArray[m_CurrentNodeId];
        
        /*
        // TODO: Figure out whether node deletion implies deletion of entire left and right subtree.
        if (currentNode.HasRightChild())
        {
            // mark entire right subtree as deleted

            std::vector<NodeArrayIndex> nodeIndicesForDeletion{};
            const size_t expectedSubtreeSize = pow(2, currentNode.GetHeight());
            nodeIndicesForDeletion.reserve(expectedSubtreeSize);
            nodeIndicesForDeletion.emplace_back(currentNode.RightChildId());

            while (!nodeIndicesForDeletion.empty())
            {
                const auto childId = nodeIndicesForDeletion[nodeIndicesForDeletion.size() - 1];
                nodeIndicesForDeletion.pop_back();

                auto& child = m_NodeArray[childId];
                child.SetMarkedForDelete(true);

                if (child.HasLeftChild())
                    nodeIndicesForDeletion.emplace_back(child.LeftChildId());

                if (child.HasRightChild())
                    nodeIndicesForDeletion.emplace_back(child.RightChildId());
            }
        }*/

        const size_t insertedRightNodeArrayPos = insertedRightNodeIter - m_NodeArray.begin();
        currentNode.ForceSetRightChildId(NodeArrayIndex{ insertedRightNodeArrayPos });
        if (insertedRightNodeIter->SetParentNodeId(m_CurrentNodeId) != BinaryNodeErrorCode::OK)
            return;
    	
        m_CurrentNodeId = insertedRightNodeArrayPos;
    }
	
    //
    // ======================== Node Deleters ======================================================
    //

    BinaryTreeErrorCode IterativeBinaryTreeImplementation::DeleteNode(const std::shared_ptr<IBinaryTreeNode>& nodeForDeletion)
    {
    	if (!nodeForDeletion ||                             // avoiding null nodes
            nodeForDeletion->GetTreeUUID() != m_TreeUUID)   // cheapest check for node inclusion: tree UUID
            return BinaryTreeErrorCode::NodeNotFound;

        for (auto& node : m_NodeArray)
        {
	        if (node.GetNodeUUID() == nodeForDeletion->GetNodeUUID())
	        {
                node.SetMarkedForDelete(true);
                node.DeleteChildren();

	        	/*
	        	// TODO: Figure out whether node deletion implies deletion of entire left and right subtree.
	        	if (node.HasLeftChild())
    			{
    				// mark entire left subtree as deleted

		            std::vector<NodeArrayIndex> nodeIndicesForDeletion{};
		            const size_t expectedSubtreeSize = pow(2, node.GetHeight());
		            nodeIndicesForDeletion.reserve(expectedSubtreeSize);
		            nodeIndicesForDeletion.emplace_back(node.LeftChildId());

    				while (!nodeIndicesForDeletion.empty())
    				{
		                const auto childId = nodeIndicesForDeletion[nodeIndicesForDeletion.size() - 1];
		                nodeIndicesForDeletion.pop_back();
    					
		                auto& child = m_NodeArray[childId];
		                child.SetMarkedForDelete(true);

		                if (child.HasLeftChild())
		                    nodeIndicesForDeletion.emplace_back(child.LeftChildId());

    					if (child.HasRightChild())
		                    nodeIndicesForDeletion.emplace_back(child.RightChildId());
    				}    		
    			}

		        if (node.HasRightChild())
		        {
		            // mark entire right subtree as deleted

		            std::vector<NodeArrayIndex> nodeIndicesForDeletion{};
		            const size_t expectedSubtreeSize = pow(2, node.GetHeight());
		            nodeIndicesForDeletion.reserve(expectedSubtreeSize);
		            nodeIndicesForDeletion.emplace_back(node.RightChildId());

		            while (!nodeIndicesForDeletion.empty())
		            {
		                const auto childId = nodeIndicesForDeletion[nodeIndicesForDeletion.size() - 1];
		                nodeIndicesForDeletion.pop_back();

		                auto& child = m_NodeArray[childId];
		                child.SetMarkedForDelete(true);

		                if (child.HasLeftChild())
		                    nodeIndicesForDeletion.emplace_back(child.LeftChildId());

		                if (child.HasRightChild())
		                    nodeIndicesForDeletion.emplace_back(child.RightChildId());
		            }
		        }
	        	 */

                if (m_NodeArray[m_CurrentNodeId].GetNodeUUID() == node.GetNodeUUID())
                    m_CurrentNodeId = m_RootNodeId; // set current node to root if deleted

                if (m_ClearAfterMarkingForDelete)
                    ClearNodesMarkedForDelete();

                return BinaryTreeErrorCode::OK;
	        }
        }
    	
        return BinaryTreeErrorCode::NodeNotFound;
    }

    std::shared_ptr<IBinaryTreeQueryDataNode> IterativeBinaryTreeImplementation::GetCurrentNodeQueryDataNode() const
    {
        if (!m_CurrentNodeId || m_CurrentNodeId >= m_NodeArray.size())
            return nullptr;

        return m_NodeArray[m_CurrentNodeId].GetQueryDataNode();
    }

    std::shared_ptr<IBinaryTreeQueryDataNode> IterativeBinaryTreeImplementation::GetCurrentNodeLeftChildQueryDataNode() const
    {
        if (!m_CurrentNodeId || m_CurrentNodeId >= m_NodeArray.size())
            return nullptr;

        auto& currentNode = m_NodeArray[m_CurrentNodeId];
        if (!currentNode.HasLeftChild())
            return nullptr;
    	
        return m_NodeArray[currentNode.LeftChildId()].GetQueryDataNode();
    }

    std::shared_ptr<IBinaryTreeQueryDataNode> IterativeBinaryTreeImplementation::GetCurrentNodeRightChildQueryDataNode() const
    {
        if (!m_CurrentNodeId || m_CurrentNodeId >= m_NodeArray.size())
            return nullptr;

        auto& currentNode = m_NodeArray[m_CurrentNodeId];
        if (!currentNode.HasRightChild())
            return nullptr;

        return m_NodeArray[currentNode.RightChildId()].GetQueryDataNode();
    }

    std::vector<std::shared_ptr<NodeDataWrapper>> IterativeBinaryTreeImplementation::GetTreeDataFromDepthFirstTraversal() const
    {
        std::vector<std::shared_ptr<NodeDataWrapper>> resultData{};
        const size_t nodeCount = GetNodeCount();
        resultData.reserve(nodeCount);

        std::stack<NodeArrayIndex> nodeIdStack{};
        nodeIdStack.push(m_RootNodeId);

        while (!nodeIdStack.empty())
        {
            const auto nodeItemId = nodeIdStack.top();
            const auto& nodeItem = m_NodeArray[nodeItemId];
            nodeIdStack.pop();

            resultData.emplace_back(nodeItem.GetQueryDataNode()->GetDataWrapper());

            if (nodeItem.HasRightChild())
                nodeIdStack.push(nodeItem.RightChildId());

            if (nodeItem.HasLeftChild())
                nodeIdStack.push(nodeItem.LeftChildId());
        }

        return resultData;
    }

    std::vector<std::shared_ptr<NodeDataWrapper>> IterativeBinaryTreeImplementation::GetTreeDataFromBreadthFirstTraversal() const
    {
        std::vector<std::shared_ptr<NodeDataWrapper>> resultData{};
        const size_t nodeCount = GetNodeCount();
        resultData.reserve(nodeCount);

        std::queue<NodeArrayIndex> nodeIdQueue{};
        nodeIdQueue.push(m_RootNodeId);

        while (!nodeIdQueue.empty())
        {
            const auto nodeItemId = nodeIdQueue.front();
            const auto& nodeItem = m_NodeArray[nodeItemId];
            nodeIdQueue.pop();

            resultData.emplace_back(nodeItem.GetQueryDataNode()->GetDataWrapper());

            if (nodeItem.HasLeftChild())
                nodeIdQueue.push(nodeItem.LeftChildId());

            if (nodeItem.HasRightChild())
                nodeIdQueue.push(nodeItem.RightChildId());
        }

        return resultData;
    }

    long int IterativeBinaryTreeImplementation::ComputeCurrentNodeAVLBalanceFactor() const
    {
        if (!m_CurrentNodeId || m_CurrentNodeId >= m_NodeArray.size())
            return 0;

        if (m_NodeArray[m_CurrentNodeId].IsLeaf())
            return 0;

        size_t leftSubtreeHeight = (m_NodeArray[m_CurrentNodeId].HasLeftChild() ? 1 : 0);
        size_t rightSubtreeHeight = (m_NodeArray[m_CurrentNodeId].HasRightChild() ? 1 : 0);

        std::stack<NodeArrayIndex> nodeIdStack{};
        if (m_NodeArray[m_CurrentNodeId].HasLeftChild())
            nodeIdStack.push(m_NodeArray[m_CurrentNodeId].LeftChildId());
        if (m_NodeArray[m_CurrentNodeId].HasRightChild())
            nodeIdStack.push(m_NodeArray[m_CurrentNodeId].RightChildId());

    	while (!nodeIdStack.empty())
    	{
            const auto nodeId = nodeIdStack.top();
            nodeIdStack.pop();

    		if (m_NodeArray[nodeId].HasLeftChild())
    		{
                leftSubtreeHeight++;
                nodeIdStack.push(m_NodeArray[nodeId].LeftChildId());
    		}

            if (m_NodeArray[nodeId].HasRightChild())
            {
                rightSubtreeHeight++;
                nodeIdStack.push(m_NodeArray[nodeId].RightChildId());
            }
    	}    	
    	
        return static_cast<long int>(rightSubtreeHeight) - static_cast<long int>(leftSubtreeHeight);
    }

    long int IterativeBinaryTreeImplementation::ComputeNodeAVLBalanceFactor(const NodeArrayIndex& nodeId) const
    {
        if (!nodeId || nodeId >= m_NodeArray.size())
            return 0;

        if (m_NodeArray[nodeId].IsLeaf())
            return 0;

        size_t leftSubtreeHeight = (m_NodeArray[nodeId].HasLeftChild() ? 1 : 0);
        size_t rightSubtreeHeight = (m_NodeArray[nodeId].HasRightChild() ? 1 : 0);

        std::stack<NodeArrayIndex> nodeIdStack{};
        if (m_NodeArray[nodeId].HasLeftChild())
            nodeIdStack.push(m_NodeArray[nodeId].LeftChildId());

    	// left subtree counting
        while (!nodeIdStack.empty())
        {
            const auto nodeId = nodeIdStack.top();
            nodeIdStack.pop();

            bool shouldIncrement = false;
        	
            if (m_NodeArray[nodeId].HasLeftChild())
            {
                shouldIncrement = true;
                nodeIdStack.push(m_NodeArray[nodeId].LeftChildId());
            }

            if (m_NodeArray[nodeId].HasRightChild())
            {
                shouldIncrement = true;
                nodeIdStack.push(m_NodeArray[nodeId].RightChildId());
            }

            if (shouldIncrement)
                leftSubtreeHeight++;
        }

        if (m_NodeArray[nodeId].HasRightChild())
            nodeIdStack.push(m_NodeArray[nodeId].RightChildId());

    	// right subtree counting
        while (!nodeIdStack.empty())
        {
            const auto nodeId = nodeIdStack.top();
            nodeIdStack.pop();

            bool shouldIncrement = false;

            if (m_NodeArray[nodeId].HasLeftChild())
            {
                shouldIncrement = true;
                nodeIdStack.push(m_NodeArray[nodeId].LeftChildId());
            }

            if (m_NodeArray[nodeId].HasRightChild())
            {
                shouldIncrement = true;
                nodeIdStack.push(m_NodeArray[nodeId].RightChildId());
            }

            if (shouldIncrement)
                rightSubtreeHeight++;
        }
    	
        return static_cast<long int>(rightSubtreeHeight) - static_cast<long int>(leftSubtreeHeight);
    }

    BinaryTreeErrorCode IterativeBinaryTreeImplementation::SetRootAsCurrent()
    {
        if (m_NodeArray.empty())
            return BinaryTreeErrorCode::NodeNotFound;

        return SetCurrentNodeId(m_RootNodeId);
    }

    BinaryTreeErrorCode IterativeBinaryTreeImplementation::SetCurrentNodeLeftChildAsCurrent()
    {
        if (!m_CurrentNodeId)
            return BinaryTreeErrorCode::CurrentNodeNotSet;

    	if (!m_NodeArray[m_CurrentNodeId].HasLeftChild())
            return BinaryTreeErrorCode::NodeNotFound;
    	
        return SetCurrentNodeId(m_NodeArray[m_CurrentNodeId].LeftChildId());
    }

    BinaryTreeErrorCode IterativeBinaryTreeImplementation::SetCurrentNodeRightChildAsCurrent()
    {
        if (!m_CurrentNodeId)
            return BinaryTreeErrorCode::CurrentNodeNotSet;

        if (!m_NodeArray[m_CurrentNodeId].HasRightChild())
            return BinaryTreeErrorCode::NodeNotFound;

        return SetCurrentNodeId(m_NodeArray[m_CurrentNodeId].RightChildId());
    }

    BinaryTreeErrorCode IterativeBinaryTreeImplementation::SetCurrentNodeId(const NodeArrayIndex& currentNodeId)
    {
        if (!currentNodeId || currentNodeId >= m_NodeArray.size())
            return BinaryTreeErrorCode::NodeArrayIndexError;

        m_CurrentNodeId = currentNodeId;    	
        return BinaryTreeErrorCode::OK;
    }

    void IterativeBinaryTreeImplementation::SetHeightFromCompleteTree()
    {
        UpdateTreeHeight();
    }

    //
    // ======================== Helper Functionality ======================================================
    //

    std::string IterativeBinaryTreeImplementation::DebugPrint() const
    {
        std::string result = "          Iterative Binary Tree Implementation Debug Print       \n";

        const size_t nodeCount = GetNodeCount();
        result += "    Node Count:            " + std::to_string(nodeCount) + "\n";
        result += "    Height    :            " + std::to_string(GetHeight()) + "\n";
        const std::string isBalancedStr = (IsBalanced() ? "YES" : "NO");
        result += "    Balanced  :            " + isBalancedStr + "\n";
        result += "..................................................................\n";
        result += "- - - - - - - - - - - -    N O D E S  - - - - - - - - - - - - - - \n";
        result += "..................................................................\n";

        for (const auto& node : m_NodeArray)
            result += node.DebugPrint();

        result += "..................................................................\n";
        result += "- - - - - - - - - - - -  E N D    N O D E S   - - - - - - - - - - \n";
        result += "..................................................................\n";

        return result;
    }

    std::string IterativeBinaryTreeImplementation::PlantUMLPrint() const
    {
        std::string result = "title: Iterative Binary Tree Instance [";
        const std::string treeUUIDStr = Util::GetUUIDString(GetTreeUUID());
        result += treeUUIDStr + "]\n\n";

        if (m_NodeArray.empty())
            return result;

        const std::string colorCodeRootNode = "#b7bbbd"; // gray-ish
        const std::string colorCodeLeftNode = "#6fcaed"; // light blue
        const std::string colorCodeRightNode = "#d68976"; // light red

        std::map<unsigned int, std::pair<NodeArrayIndex, UUID>> leftConnectivityMap;
        std::map<unsigned int, std::pair<NodeArrayIndex, UUID>> rightConnectivityMap;
    	
    	// node connectivity preprocessing
    	for (unsigned int nodeID = 0; const auto& node : m_NodeArray)
    	{
            if (node.HasLeftChild())
            {
                const auto leftChildId = node.LeftChildId();
                leftConnectivityMap[nodeID] = { leftChildId, m_NodeArray[leftChildId].GetNodeUUID() };
            }
            
            if (node.HasRightChild())
            {
                const auto rightChildId = node.RightChildId();
                rightConnectivityMap[nodeID] = { rightChildId, m_NodeArray[rightChildId].GetNodeUUID() };
            }

            nodeID++;
    	}

        const bool isBalanced = IsBalanced();

    	// print root node
        const std::string rootNodeClassBracketContent = "0, " + colorCodeRootNode;
    	if (!isBalanced)
    	{
	        result += m_NodeArray[m_RootNodeId].PlantUMLPrint(rootNodeClassBracketContent, m_RootNodeId.get());
    	}
        else
        {
            result += m_NodeArray[m_RootNodeId].PlantUMLPrintBalanced(rootNodeClassBracketContent, m_RootNodeId.get());
        }

    	// preallocate connectivity prints
        std::vector<std::string> leftConnectivityRelationPrints{};
        leftConnectivityRelationPrints.reserve(leftConnectivityMap.size());
        std::vector<std::string> rightConnectivityRelationPrints{};
        rightConnectivityRelationPrints.reserve(rightConnectivityMap.size());

    	// fill connectivity prints and print child nodes with child color code identifiers

        const std::string leftChildNodeClassBracketContent = "L, " + colorCodeLeftNode;
    	for (const auto& [parentID, leftChildData] : leftConnectivityMap)
    	{
            const std::string leftConnectRelationPrint = "\"" + Util::GetUUIDString(m_NodeArray[parentID].GetNodeUUID()) + "\" ---> \"" + Util::GetUUIDString(leftChildData.second) + "\"\n";
            leftConnectivityRelationPrints.emplace_back(leftConnectRelationPrint);

            if (!isBalanced)
            {
                result += m_NodeArray[leftChildData.first].PlantUMLPrint(leftChildNodeClassBracketContent, leftChildData.first.get());
            }
            else
            {
                result += m_NodeArray[leftChildData.first].PlantUMLPrintBalanced(leftChildNodeClassBracketContent, leftChildData.first.get());
            }
    	}

        const std::string rightChildNodeClassBracketContent = "R, " + colorCodeRightNode;
        for (const auto& [parentID, rightChildData] : rightConnectivityMap)
        {
            const std::string rightConnectRelationPrint = "\"" + Util::GetUUIDString(m_NodeArray[parentID].GetNodeUUID()) + "\" ---> \"" + Util::GetUUIDString(rightChildData.second) + "\"\n";
            rightConnectivityRelationPrints.emplace_back(rightConnectRelationPrint);

            if (!isBalanced)
            {
                result += m_NodeArray[rightChildData.first].PlantUMLPrint(rightChildNodeClassBracketContent, rightChildData.first.get());
            }
            else
            {
                result += m_NodeArray[rightChildData.first].PlantUMLPrintBalanced(rightChildNodeClassBracketContent, rightChildData.first.get());
            }
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

    BinaryTreeErrorCode IterativeBinaryTreeImplementation::RebalanceFromCurrentNode()
    {
        auto pivotChildNodeId = m_CurrentNodeId;
        for (auto pivotNodeId = m_NodeArray[pivotChildNodeId].ParentNodeId(); pivotNodeId.IsValid(); pivotNodeId = m_NodeArray[pivotNodeId].ParentNodeId())
        {
            const auto balanceState = EvaluateNodeBalanceState(m_NodeArray[pivotNodeId]);
            if (balanceState == BalanceState::Balanced)
                continue; // end if |BF(X)| < 2 (no rebalancing required)

            auto nodeInsteadOfPivotId = NULL_NODE_INDEX;
            auto pivotParentNodeId = NULL_NODE_INDEX;
            if (balanceState == BalanceState::RightHeavy)
            {
                // the right subtree is heavier
                if (m_NodeArray[pivotNodeId].GetBalanceFactor() > 0)
                {
                    // X ( m_NodeArray[pivotNodeId] ) is right-heavy
                    // the temporary balance factor of X is 2
                    pivotParentNodeId = m_NodeArray[pivotNodeId].ParentNodeId(); // save parent G of X ( m_NodeArray[pivotNodeId] ) around rotations
                    m_CurrentNodeId = pivotNodeId;

                    if (m_NodeArray[pivotChildNodeId].GetBalanceFactor() < 0) // Right-Left case
                    {
                        // double rotation, Z ( m_NodeArray[pivotChildNodeId] ) to the right and then X ( m_NodeArray[pivotNodeId] ) to the left
                        if (const auto rotateRLErr = RotateRightLeftAtCurrentNode();
                            rotateRLErr != BinaryTreeErrorCode::OK)
                            return rotateRLErr;
                    }
                    else // Right-Right case
                    {
                        // single rotation, X ( m_NodeArray[pivotNodeId] ) to the left
                        if (const auto rotateLeftErr = RotateLeftAtCurrentNode();
                            rotateLeftErr != BinaryTreeErrorCode::OK)
                            return rotateLeftErr;
                    }
                    nodeInsteadOfPivotId = m_CurrentNodeId;

                    // parent link needs to be adapted after rotation
                }
                else
                {
                    if (m_NodeArray[pivotNodeId].GetBalanceFactor() < 0)
                    {
                        // Z's ( m_NodeArray[pivotChildNodeId]'s ) height increase is absorbed at X.
                        m_NodeArray[pivotNodeId].SetBalanceFactor(0);
                        break; // leave the loop
                    }
                    m_NodeArray[pivotNodeId].SetBalanceFactor(1);
                    m_NodeArray[pivotChildNodeId].SetHeight(m_NodeArray[pivotChildNodeId].GetHeight() + 1);
                    pivotChildNodeId = pivotNodeId; // Height(Z) increases by 1
                    continue;
                }
            }
            else // balanceState == BalanceState::LeftHeavy
            {
                // the left subtree is heavier
                if (m_NodeArray[pivotNodeId].GetBalanceFactor() < 0)
                {
                    // X ( m_NodeArray[pivotNodeId] ) is left-heavy
                    // the temporary balance factor of X is -2
                    pivotParentNodeId = m_NodeArray[pivotNodeId].ParentNodeId(); // save parent G of X ( m_NodeArray[pivotNodeId] ) around rotations
                    m_CurrentNodeId = pivotNodeId;

                    if (m_NodeArray[pivotChildNodeId].GetBalanceFactor() > 0) // Left-Right case
                    {
                        // double rotation, Z ( m_NodeArray[pivotChildNodeId] ) to the left and then X ( m_NodeArray[pivotNodeId] ) to the right
                        if (const auto rotateLRErr = RotateLeftRightAtCurrentNode();
                            rotateLRErr != BinaryTreeErrorCode::OK)
                            return rotateLRErr;
                    }
                    else // Left-Left case
                    {
                        // single rotation, X ( m_NodeArray[pivotNodeId] ) to the right
                        if (const auto rotateRightErr = RotateRightAtCurrentNode();
                            rotateRightErr != BinaryTreeErrorCode::OK)
                            return rotateRightErr;
                    }
                    nodeInsteadOfPivotId = m_CurrentNodeId;

                    // parent link needs to be adapted after rotation
                }
                else
                {
                    if (m_NodeArray[pivotNodeId].GetBalanceFactor() > 0)
                    {
                        // Z's ( m_NodeArray[pivotChildNodeId]'s ) height increase is absorbed at X.
                        m_NodeArray[pivotNodeId].SetBalanceFactor(0);
                        break; // leave the loop
                    }
                    m_NodeArray[pivotNodeId].SetBalanceFactor(-1);
                    m_NodeArray[pivotChildNodeId].SetHeight(m_NodeArray[pivotChildNodeId].GetHeight() + 1);
                    pivotChildNodeId = pivotNodeId; // Height(Z) increases by 1
                    continue;
                }
            }
            // Parent link adaptation after rotation:
            m_NodeArray[nodeInsteadOfPivotId].ForceSetParentNodeId(pivotParentNodeId);

            if (pivotParentNodeId.IsValid())
            {
                if (pivotNodeId == m_NodeArray[pivotParentNodeId].LeftChildId())
                {
                    m_NodeArray[pivotParentNodeId].ForceSetLeftChildId(nodeInsteadOfPivotId);
                }
                else
                {
                    m_NodeArray[pivotParentNodeId].ForceSetRightChildId(nodeInsteadOfPivotId);
                }
            }
            else
            {
                // m_NodeArray[nodeInsteadOfPivotId] is now the new root node
                m_RootNodeId = nodeInsteadOfPivotId;
                break;
            }
        }

        return BinaryTreeErrorCode::OK;
    }
	
    /// Note: using notation from https://en.wikipedia.org/wiki/AVL_tree in the comments, e.g.: X, Y, Z, t1, t2, t23, t3, t4

    BinaryTreeErrorCode IterativeBinaryTreeImplementation::RotateLeftAtCurrentNode()
    {
    	// X is the pivot node ( m_NodeArray[m_CurrentNodeId] )
    	// Z is the pivot node's right child node to be raised ( m_NodeArray[nodeToBeRaisedId] )
        const auto nodeToBeRaisedId = m_NodeArray[m_CurrentNodeId].RightChildId();
        if (!nodeToBeRaisedId.IsValid())
            return BinaryTreeErrorCode::NodeNotFound;

    	// t23 ( m_NodeArray[weightLeftChildId] ) is the left child of Z ( m_NodeArray[nodeToBeRaisedId] )
        const auto weightLeftChildId = m_NodeArray[nodeToBeRaisedId].LeftChildId();

    	// set t23 ( m_NodeArray[weightLeftChildId] ) as the right child of X ( m_NodeArray[m_CurrentNodeId] )
        m_NodeArray[m_CurrentNodeId].ForceSetRightChildId(weightLeftChildId);

    	// if t23 ( m_NodeArray[weightLeftChildId] ) isn't a null node, set X ( m_NodeArray[m_CurrentNodeId] )
    	// as the parent of t23 ( m_NodeArray[weightLeftChildId] )
        if (weightLeftChildId.IsValid())
        {
            m_NodeArray[weightLeftChildId].ForceSetParentNodeId(m_CurrentNodeId);
        }

    	// set X ( m_NodeArray[m_CurrentNodeId] ) as the left child of Z ( m_NodeArray[nodeToBeRaisedId] )
        m_NodeArray[nodeToBeRaisedId].ForceSetLeftChildId(m_CurrentNodeId);

    	// set Z ( m_NodeArray[nodeToBeRaisedId] ) as the parent of X ( m_NodeArray[m_CurrentNodeId] )
        m_NodeArray[m_CurrentNodeId].ForceSetParentNodeId(nodeToBeRaisedId);

    	// Set correct balance factors of the rebalanced nodes:
    	if (m_NodeArray[nodeToBeRaisedId].GetBalanceFactor() == 0)
    	{
            m_NodeArray[m_CurrentNodeId].SetBalanceFactor(1);
            m_NodeArray[nodeToBeRaisedId].SetBalanceFactor(-1);
    	}
        else
        {
            m_NodeArray[m_CurrentNodeId].SetBalanceFactor(0);
            m_NodeArray[nodeToBeRaisedId].SetBalanceFactor(0);
        }

    	// update heights of rotated nodes
        const auto weightLeftmostChildId = m_NodeArray[m_CurrentNodeId].LeftChildId(); // t1
        const size_t weightLeftmostChildHeight = (weightLeftmostChildId.IsValid() ? m_NodeArray[weightLeftmostChildId].GetHeight() : 0); // height(t1)
        const size_t weightLeftChildHeight = (weightLeftChildId.IsValid() ? m_NodeArray[weightLeftChildId].GetHeight() : 0); // height(t23)
        const size_t pivotNodeFinalHeight = std::max<size_t>(weightLeftmostChildHeight, weightLeftChildHeight) + 1;
        m_NodeArray[m_CurrentNodeId].SetHeight(pivotNodeFinalHeight);
    	
        const size_t nodeToBeRaisedFinalHeight = std::max<size_t>(m_NodeArray[nodeToBeRaisedId].GetHeight(), pivotNodeFinalHeight);
        m_NodeArray[nodeToBeRaisedId].SetHeight(nodeToBeRaisedFinalHeight);

        m_CurrentNodeId = nodeToBeRaisedId;
    	
        return BinaryTreeErrorCode::OK;
    }

    BinaryTreeErrorCode IterativeBinaryTreeImplementation::RotateRightAtCurrentNode()
    {
        // X is the pivot node ( m_NodeArray[m_CurrentNodeId] )
        // Z is the pivot node's left child node to be raised ( m_NodeArray[nodeToBeRaisedId] )
        const auto nodeToBeRaisedId = m_NodeArray[m_CurrentNodeId].LeftChildId();
        if (!nodeToBeRaisedId.IsValid())
            return BinaryTreeErrorCode::NodeNotFound;

        // t23 ( m_NodeArray[weightLeftChildId] ) is the right child of Z ( m_NodeArray[nodeToBeRaisedId] )
        const auto weightRightChildId = m_NodeArray[nodeToBeRaisedId].RightChildId();

        // set t23 ( m_NodeArray[weightRightChildId] ) as the left child of X ( m_NodeArray[m_CurrentNodeId] )
        m_NodeArray[m_CurrentNodeId].ForceSetLeftChildId(weightRightChildId);

        // if t23 ( m_NodeArray[weightRightChildId] ) isn't a null node, set X ( m_NodeArray[m_CurrentNodeId] )
        // as the parent of t23 ( m_NodeArray[weightLeftChildId] )
        if (weightRightChildId.IsValid())
        {
            m_NodeArray[weightRightChildId].ForceSetParentNodeId(m_CurrentNodeId);
        }

        // set X ( m_NodeArray[m_CurrentNodeId] ) as the right child of Z ( m_NodeArray[nodeToBeRaisedId] )
        m_NodeArray[nodeToBeRaisedId].ForceSetRightChildId(m_CurrentNodeId);

        // set Z ( m_NodeArray[nodeToBeRaisedId] ) as the parent of X ( m_NodeArray[m_CurrentNodeId] )
        m_NodeArray[m_CurrentNodeId].ForceSetParentNodeId(nodeToBeRaisedId);

        // Set correct balance factors of the rebalanced nodes:
        if (m_NodeArray[nodeToBeRaisedId].GetBalanceFactor() == 0)
        {
            m_NodeArray[m_CurrentNodeId].SetBalanceFactor(-1);
            m_NodeArray[nodeToBeRaisedId].SetBalanceFactor(1);
        }
        else
        {
            m_NodeArray[m_CurrentNodeId].SetBalanceFactor(0);
            m_NodeArray[nodeToBeRaisedId].SetBalanceFactor(0);
        }

        // update heights of rotated nodes
        const size_t weightRightChildHeight = (weightRightChildId.IsValid() ? m_NodeArray[weightRightChildId].GetHeight() : 0); // height(t23)
        const auto weightRightmostChildId = m_NodeArray[m_CurrentNodeId].RightChildId();
        const size_t weightRightmostChildHeight = (weightRightmostChildId.IsValid() ? m_NodeArray[weightRightmostChildId].GetHeight() : 0); // height(t4)
        const size_t pivotNodeFinalHeight = std::max<size_t>(weightRightChildHeight, weightRightmostChildHeight) + 1;    	
        m_NodeArray[m_CurrentNodeId].SetHeight(pivotNodeFinalHeight);
    	
        const size_t nodeToBeRaisedFinalHeight = std::max<size_t>(m_NodeArray[nodeToBeRaisedId].GetHeight(), pivotNodeFinalHeight);
        m_NodeArray[nodeToBeRaisedId].SetHeight(nodeToBeRaisedFinalHeight);

        m_CurrentNodeId = nodeToBeRaisedId;
    	
        return BinaryTreeErrorCode::OK;
    }

    BinaryTreeErrorCode IterativeBinaryTreeImplementation::RotateLeftRightAtCurrentNode()
    {
        // X is the pivot node ( m_NodeArray[m_CurrentNodeId] )
        // Z is the pivot node's left child node ==> node to be lowered in the first rotation ( m_NodeArray[nodeToBeLoweredId] )
        const auto nodeToBeLoweredId = m_NodeArray[m_CurrentNodeId].RightChildId();
        if (!nodeToBeLoweredId.IsValid())
            return BinaryTreeErrorCode::NodeNotFound;

        // Y is the "inner weight node", the pivot node's left child node's right child ==> first node to be raised ( m_NodeArray[nodeToBeRaisedId] )
        const auto nodeToBeRaisedId = m_NodeArray[nodeToBeLoweredId].LeftChildId();
        if (!nodeToBeRaisedId.IsValid())
            return BinaryTreeErrorCode::NodeNotFound;

        // t2 ( m_NodeArray[innerWeightChildId] ) is the left child of Y ( m_NodeArray[nodeToBeRaisedId] )
        const auto innerWeightLeftChildId = m_NodeArray[nodeToBeRaisedId].LeftChildId();

        // set t2 ( m_NodeArray[innerWeightRightChildId] ) as the right child of Z ( m_NodeArray[nodeToBeLoweredId] )
        m_NodeArray[m_CurrentNodeId].ForceSetRightChildId(innerWeightLeftChildId);

        // if t2 ( m_NodeArray[innerWeightLeftChildId] ) is not a null node, set Z ( m_NodeArray[nodeToBeLoweredId] )
        // as the parent of t2.
        if (innerWeightLeftChildId.IsValid())
        {
            m_NodeArray[innerWeightLeftChildId].ForceSetParentNodeId(nodeToBeLoweredId);
        }

        // set Z ( m_NodeArray[nodeToBeLoweredId] ) as the left child node of Y ( m_NodeArray[nodeToBeRaisedId] )
        m_NodeArray[nodeToBeRaisedId].ForceSetLeftChildId(nodeToBeLoweredId);

        // set Y ( m_NodeArray[nodeToBeRaisedId] ) as the parent of Z ( m_NodeArray[nodeToBeLoweredId] )
        m_NodeArray[nodeToBeLoweredId].ForceSetParentNodeId(nodeToBeRaisedId);

        // t3 ( m_NodeArray[innerWeightRightChildId] ) is the right child of Y ( m_NodeArray[nodeToBeRaisedId] )
        const auto innerWeightRightChildId = m_NodeArray[nodeToBeRaisedId].RightChildId();

        // set t3 ( m_NodeArray[innerWeightRightChildId] ) as the left child of X ( m_NodeArray[m_CurrentNodeId] )
        m_NodeArray[m_CurrentNodeId].ForceSetLeftChildId(innerWeightRightChildId);

        // if t3 (  m_NodeArray[innerWeightRightChildId] ) is not a null node, set X ( m_NodeArray[m_CurrentNodeId] )
        // as the parent node of t3.
        if (innerWeightRightChildId.IsValid())
        {
            m_NodeArray[innerWeightRightChildId].ForceSetParentNodeId(m_CurrentNodeId);
        }

        // Set correct balance factors of the rebalanced nodes:
        if (m_NodeArray[nodeToBeRaisedId].GetBalanceFactor() == 0)
        {
            m_NodeArray[m_CurrentNodeId].SetBalanceFactor(0);
            m_NodeArray[nodeToBeLoweredId].SetBalanceFactor(0);
        }
        else
        {
            if (m_NodeArray[nodeToBeRaisedId].GetBalanceFactor() > 0)
            {
                m_NodeArray[m_CurrentNodeId].SetBalanceFactor(-1);
                m_NodeArray[nodeToBeLoweredId].SetBalanceFactor(0);
            }
            else
            {
                m_NodeArray[m_CurrentNodeId].SetBalanceFactor(0);
                m_NodeArray[nodeToBeLoweredId].SetBalanceFactor(1);
            }
        }
        m_NodeArray[nodeToBeRaisedId].SetBalanceFactor(0);

        // update heights of rotated nodes

    	// compute new height(Z)
        const auto outerWeightLeftChildId = m_NodeArray[nodeToBeLoweredId].LeftChildId(); // t1
        const size_t outerWeightLeftChildHeight = (outerWeightLeftChildId.IsValid() ? m_NodeArray[outerWeightLeftChildId].GetHeight() : 0); // height(t1)        
        const size_t innerWeightLeftChildHeight = (innerWeightLeftChildId.IsValid() ? m_NodeArray[innerWeightLeftChildId].GetHeight() : 0); // height(t2)
        const size_t nodeToBeLoweredFinalHeight = std::max<size_t>(outerWeightLeftChildHeight, innerWeightLeftChildHeight) + 1;
        m_NodeArray[nodeToBeLoweredId].SetHeight(nodeToBeLoweredFinalHeight);

    	// compute new height(X)
        const size_t innerWeightRightChildHeight = (innerWeightRightChildId.IsValid() ? m_NodeArray[innerWeightRightChildId].GetHeight() : 0); // height(t3)
        const auto outerWeightRightChildId = m_NodeArray[m_CurrentNodeId].RightChildId(); // t4
        const size_t outerWeightRightChildHeight = (outerWeightRightChildId.IsValid() ? m_NodeArray[outerWeightRightChildId].GetHeight() : 0); // height(t4)        
        const size_t pivotNodeFinalHeight = std::max<size_t>(innerWeightRightChildHeight, outerWeightRightChildHeight) + 1;
        m_NodeArray[m_CurrentNodeId].SetHeight(pivotNodeFinalHeight);
    	
    	// compute new height(Y)
        const size_t nodeToBeRaisedFinalHeight = std::max<size_t>(pivotNodeFinalHeight, nodeToBeLoweredFinalHeight);
        m_NodeArray[nodeToBeRaisedId].SetHeight(nodeToBeRaisedFinalHeight);

        m_CurrentNodeId = nodeToBeRaisedId;
    	
        return BinaryTreeErrorCode::OK;
    }

    BinaryTreeErrorCode IterativeBinaryTreeImplementation::RotateRightLeftAtCurrentNode()
    {
        // X is the pivot node ( m_NodeArray[m_CurrentNodeId] )
    	// Z is the pivot node's right child node ==> first node to be lowered ( m_NodeArray[firstNodeToBeLoweredId] )
        const auto nodeToBeLoweredId = m_NodeArray[m_CurrentNodeId].RightChildId();
        if (!nodeToBeLoweredId.IsValid())
            return BinaryTreeErrorCode::NodeNotFound;

    	// Y is the "inner weight node", the pivot node's right child node's left child ==> first node to be raised ( m_NodeArray[nodeToBeRaisedId] )
        const auto nodeToBeRaisedId = m_NodeArray[nodeToBeLoweredId].LeftChildId();
        if (!nodeToBeRaisedId.IsValid())
            return BinaryTreeErrorCode::NodeNotFound;

    	// t3 ( m_NodeArray[innerWeightChildId] ) is the right child of Y ( m_NodeArray[nodeToBeRaisedId] )
        const auto innerWeightRightChildId = m_NodeArray[nodeToBeRaisedId].RightChildId();

    	// set t3 ( m_NodeArray[innerWeightRightChildId] ) as the left child of Z ( m_NodeArray[nodeToBeLoweredId] )
        m_NodeArray[m_CurrentNodeId].ForceSetLeftChildId(innerWeightRightChildId);

    	// if t3 ( m_NodeArray[innerWeightRightChildId] ) is not a null node, set Z ( m_NodeArray[nodeToBeLoweredId] )
    	// as the parent of t3.
        if (innerWeightRightChildId.IsValid())
        {
            m_NodeArray[innerWeightRightChildId].ForceSetParentNodeId(nodeToBeLoweredId);
        }

    	// set Z ( m_NodeArray[nodeToBeLoweredId] ) as the right child node of Y ( m_NodeArray[nodeToBeRaisedId] )
        m_NodeArray[nodeToBeRaisedId].ForceSetRightChildId(nodeToBeLoweredId);

    	// set Y ( m_NodeArray[nodeToBeRaisedId] ) as the parent of Z ( m_NodeArray[nodeToBeLoweredId] )
        m_NodeArray[nodeToBeLoweredId].ForceSetParentNodeId(nodeToBeRaisedId);

    	// t2 ( m_NodeArray[innerWeightLeftChildId] ) is the left child of Y ( m_NodeArray[nodeToBeRaisedId] )
        const auto innerWeightLeftChildId = m_NodeArray[nodeToBeRaisedId].LeftChildId();

    	// set t2 ( m_NodeArray[innerWeightLeftChildId] ) as the right child of X ( m_NodeArray[m_CurrentNodeId] )
        m_NodeArray[m_CurrentNodeId].ForceSetRightChildId(innerWeightLeftChildId);

    	// if t2 (  m_NodeArray[innerWeightLeftChildId] ) is not a null node, set X ( m_NodeArray[m_CurrentNodeId] )
    	// as the parent node of t2.
        if (innerWeightLeftChildId.IsValid())
        {
            m_NodeArray[innerWeightLeftChildId].ForceSetParentNodeId(m_CurrentNodeId);
        }

        // Set correct balance factors of the rebalanced nodes:
    	if (m_NodeArray[nodeToBeRaisedId].GetBalanceFactor() == 0)
    	{
            m_NodeArray[m_CurrentNodeId].SetBalanceFactor(0);
            m_NodeArray[nodeToBeLoweredId].SetBalanceFactor(0);
    	}
        else
        {
	        if (m_NodeArray[nodeToBeRaisedId].GetBalanceFactor() > 0)
	        {
                m_NodeArray[m_CurrentNodeId].SetBalanceFactor(-1);
                m_NodeArray[nodeToBeLoweredId].SetBalanceFactor(0);
	        }
            else
            {
                m_NodeArray[m_CurrentNodeId].SetBalanceFactor(0);
                m_NodeArray[nodeToBeLoweredId].SetBalanceFactor(1);
            }
        }
        m_NodeArray[nodeToBeRaisedId].SetBalanceFactor(0);

        // update heights of rotated nodes

        // compute new height(X)
        const auto outerWeightLeftChildId = m_NodeArray[m_CurrentNodeId].LeftChildId(); // t1
        const size_t outerWeightLeftChildHeight = (outerWeightLeftChildId.IsValid() ? m_NodeArray[outerWeightLeftChildId].GetHeight() : 0); // height(t1)        
        const size_t innerWeightLeftChildHeight = (innerWeightLeftChildId.IsValid() ? m_NodeArray[innerWeightLeftChildId].GetHeight() : 0); // height(t2)
        const size_t pivotNodeFinalHeight = std::max<size_t>(outerWeightLeftChildHeight, innerWeightLeftChildHeight) + 1;
        m_NodeArray[m_CurrentNodeId].SetHeight(pivotNodeFinalHeight);

        // compute new height(Z)
        const size_t innerWeightRightChildHeight = (innerWeightRightChildId.IsValid() ? m_NodeArray[innerWeightRightChildId].GetHeight() : 0); // height(t3)
        const auto outerWeightRightChildId = m_NodeArray[nodeToBeLoweredId].RightChildId(); // t4
        const size_t outerWeightRightChildHeight = (outerWeightRightChildId.IsValid() ? m_NodeArray[outerWeightRightChildId].GetHeight() : 0); // height(t4)        
        const size_t nodeToBeLoweredFinalHeight = std::max<size_t>(innerWeightRightChildHeight, outerWeightRightChildHeight) + 1;
        m_NodeArray[nodeToBeLoweredId].SetHeight(nodeToBeLoweredFinalHeight);

        // compute new height(Y)
        const size_t nodeToBeRaisedFinalHeight = std::max<size_t>(pivotNodeFinalHeight, nodeToBeLoweredFinalHeight);
        m_NodeArray[nodeToBeRaisedId].SetHeight(nodeToBeRaisedFinalHeight);
    	
        m_CurrentNodeId = nodeToBeRaisedId;
    	
        return BinaryTreeErrorCode::OK;
    }

    //
    // ======================== Misc Private Functionality ======================================================
    //

    void IterativeBinaryTreeImplementation::ClearNodesMarkedForDelete()
    {
        const size_t deletedCount = CountNodesMarkedForDelete(m_NodeArray);
        const auto oldUnclearedNodes = m_NodeArray;
        m_NodeArray.clear();
        m_NodeArray.reserve(oldUnclearedNodes.size() - deletedCount);

        for (const auto& node : oldUnclearedNodes)
        {
            if (node.IsMarkedForDelete())
                continue;

            m_NodeArray.emplace_back(node);
        }

        UpdateNodeCount();
    }

    void IterativeBinaryTreeImplementation::UpdateTreeHeight()
    {
        m_TreeHeight = m_NodeArray[m_RootNodeId].GetHeight();
    }

    void IterativeBinaryTreeImplementation::UpdateNodeHeightsAndBalanceFactorsUpToRoot()
    {
        auto nodeId = m_CurrentNodeId;
        size_t heightCounterFromCurrentNode = (m_NodeArray[nodeId].IsLeaf() ? 0 : m_NodeArray[nodeId].GetHeight() - 1);
    	while (nodeId.IsValid())
    	{
            heightCounterFromCurrentNode++;

    		// === update current node balance factor ====
            const auto leftNeighborId = m_NodeArray[nodeId].LeftChildId();
            const auto rightNeighborId = m_NodeArray[nodeId].RightChildId();

            const size_t leftNeighborHeight = (leftNeighborId.IsValid() ? m_NodeArray[leftNeighborId].GetHeight() : 0);
            const size_t rightNeighborHeight = (rightNeighborId.IsValid() ? m_NodeArray[rightNeighborId].GetHeight() : 0);

            m_NodeArray[nodeId].SetBalanceFactor(static_cast<long int>(rightNeighborHeight) - static_cast<long int>(leftNeighborHeight));

    		// === update current node height ============            
    		
    		// height will be incremented only when it exceeds node's old height
            if (heightCounterFromCurrentNode > m_NodeArray[nodeId].GetHeight())
            {
                m_NodeArray[nodeId].SetHeight(heightCounterFromCurrentNode);	            
            }
    		// height could be decremented if the parent node height exceeds maximum neighbor height by more than 1
    		else if (const size_t maximumNeighborHeight = std::max<size_t>(leftNeighborHeight, rightNeighborHeight);
                m_NodeArray[nodeId].GetHeight() > maximumNeighborHeight + 1)
    		{
                heightCounterFromCurrentNode = maximumNeighborHeight + 1; // reset height counter
    			m_NodeArray[nodeId].SetHeight(heightCounterFromCurrentNode);
    		}

            nodeId = m_NodeArray[nodeId].ParentNodeId();
    	}
    }
	
} // Symplektis::DataReps