/*! \file  RecursiveBinaryTreeNode.cpp
 *  \brief An implementation of a generic node object for RecursiveBinaryTreeImplementation, i.e.: \n
 *         contains pointer references to heap instances of child nodes.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   1.11.2021
 *
 */

#include "RecursiveBinaryTreeNode.h"

#include "minwindef.h" // max
#include <stack>

namespace Symplektis::DataReps
{
	RecursiveBinaryTreeNode::RecursiveBinaryTreeNode(const RecursiveBinaryTreeNode& other)
		: IBinaryTreeNode(other)
	{
		if (other.m_LeftChild)
		{
			m_LeftChild = other.m_LeftChild;
		}
		else if (m_LeftChild)
		{
			m_LeftChild = nullptr;
		}

		if (other.m_RightChild)
		{
			m_RightChild = other.m_RightChild;
		}
		else if (m_RightChild)
		{
			m_RightChild = nullptr;
		}
	}

	RecursiveBinaryTreeNode& RecursiveBinaryTreeNode::operator=(const RecursiveBinaryTreeNode& other)
	{
		if (this == &other)
			return *this;

		SetBase(other);

		if (other.m_LeftChild)
		{
			m_LeftChild = other.m_LeftChild;
		}
		else if (m_LeftChild)
		{
			m_LeftChild = nullptr;
		}

		if (other.m_RightChild)
		{
			m_RightChild = other.m_RightChild;
		}
		else if (m_RightChild)
		{
			m_RightChild = nullptr;
		}

		return *this;
	}

	
	BinaryNodeErrorCode RecursiveBinaryTreeNode::SetLeftChild(const std::shared_ptr<IBinaryTreeNode>& leftCandidate)
	{
		if (m_LeftChild)
			return BinaryNodeErrorCode::LeftNodeExists;

		m_LeftChild = std::static_pointer_cast<RecursiveBinaryTreeNode>(leftCandidate);
		m_LeftChild->SetHeight(1);
		m_IsLeaf = false;
		return BinaryNodeErrorCode::OK;
	}
	
	void RecursiveBinaryTreeNode::ForceSetLeftChild(const std::shared_ptr<IBinaryTreeNode>& newLeftNode)
	{
		m_LeftChild = std::static_pointer_cast<RecursiveBinaryTreeNode>(newLeftNode);
		m_LeftChild->SetHeight(1);
		m_IsLeaf = false;
	}
	
	BinaryNodeErrorCode RecursiveBinaryTreeNode::SetRightChild(const std::shared_ptr<IBinaryTreeNode>& rightCandidate)
	{
		if (m_RightChild)
			return BinaryNodeErrorCode::RightNodeExists;
		
		m_RightChild = std::static_pointer_cast<RecursiveBinaryTreeNode>(rightCandidate);
		m_RightChild->SetHeight(1);
		m_IsLeaf = false;
		return BinaryNodeErrorCode::OK;
	}
	
	void RecursiveBinaryTreeNode::ForceSetRightChild(const std::shared_ptr<IBinaryTreeNode>& newRightNode)
	{
		m_RightChild = std::static_pointer_cast<RecursiveBinaryTreeNode>(newRightNode);
		m_RightChild->SetHeight(1);
		m_IsLeaf = false;
	}

	BinaryNodeErrorCode RecursiveBinaryTreeNode::SetParentNode(const std::shared_ptr<IBinaryTreeNode>& parentNode)
	{
		if (!parentNode)
			return BinaryNodeErrorCode::NullNode;

		m_Parent = std::dynamic_pointer_cast<RecursiveBinaryTreeNode>(parentNode);		
		return BinaryNodeErrorCode::OK;
	}
	
	void RecursiveBinaryTreeNode::DeleteLeft()
	{
		m_LeftChild = nullptr;

		if (!HasRightChild())
			m_IsLeaf = true;
	}
	
	void RecursiveBinaryTreeNode::DeleteRight()
	{
		m_RightChild = nullptr;

		if (!HasLeftChild())
			m_IsLeaf = true;
	}
	
	void RecursiveBinaryTreeNode::DeleteChildren()
	{
		m_LeftChild = nullptr;
		m_RightChild = nullptr;
		m_IsLeaf = true;
	}

	void RecursiveBinaryTreeNode::DeleteParent()
	{
		m_Parent = nullptr;
	}

	size_t RecursiveBinaryTreeNode::CountChildren() const
	{
		if (IsLeaf())
			return 0;
		
		size_t result = 0;

		std::stack<RecursiveBinaryTreeNode*> nodeStack{};
		if (HasLeftChild())
			nodeStack.push(m_LeftChild.get());
		if (HasRightChild())
			nodeStack.push(m_RightChild.get());

		while (!nodeStack.empty())
		{
			const auto nodeItem = nodeStack.top();
			nodeStack.pop();

			if (nodeItem->IsLeaf())
				continue;

			result += (nodeItem->HasLeftChild() ? 1 : 0);
			result += (nodeItem->HasRightChild() ? 1 : 0);

			nodeStack.push(nodeItem->LeftChildPtr().get());
			nodeStack.push(nodeItem->RightChildPtr().get());
		}

		return result;
	}

	/*size_t RecursiveBinaryTreeNode::GetHeight() const
	{
		if (IsLeaf())
			return 1;

		size_t leftHeight = 1;
		if (m_LeftChild)
			leftHeight += m_LeftChild->GetHeight();

		size_t rightHeight = 1;
		if (m_RightChild)
			rightHeight += m_RightChild->GetHeight();

		return max(leftHeight, rightHeight);
	}*/

	long int RecursiveBinaryTreeNode::ComputeAVLBalanceFactor() const
	{
		if (IsLeaf())
			return 0;
		
		const size_t leftSubtreeHeight = (HasLeftChild() ? m_LeftChild->GetHeight() : 0);
		const size_t rightSubtreeHeight = (HasRightChild() ? m_RightChild->GetHeight() : 0);		
		
		return static_cast<long int>(rightSubtreeHeight) - static_cast<long int>(leftSubtreeHeight);
	}

	//
	// ======================== Helper Functionality ======================================================
	//

	std::string RecursiveBinaryTreeNode::DebugPrint() const
	{
		std::string result = "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n";
		result += "|     (Recursive) Node   :   " + Util::GetUUIDString(m_NodeUUID) + " |\n";
		result += "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
		result += "      Height     :   " + std::to_string(m_Height) + "\n";
		const size_t nChildren = static_cast<size_t>(HasLeftChild()) + static_cast<size_t>(HasRightChild());
		result += "      Children  :   " + std::to_string(nChildren) + "\n";
		if (HasLeftChild())
			result += "      Left Child Node:    " + Util::GetUUIDString(m_LeftChild->GetNodeUUID()) + "\n";

		if (HasRightChild())
			result += "      Right Child Node:    " + Util::GetUUIDString(m_RightChild->GetNodeUUID()) + "\n";
		result += "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";

		result += m_DataNode->DebugPrint();
		result += "^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^\n";

		return result;
	}
	
} // Symplektis::DataReps