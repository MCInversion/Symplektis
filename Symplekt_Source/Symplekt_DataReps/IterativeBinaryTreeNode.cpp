/*! \file  IterativeBinaryTreeNode.cpp
 *  \brief An implementation of a generic node object for IterativeBinaryTreeImplementation,\n
 *         i.e.: contains iterator references to child node instances stored in an array.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   1.11.2021
 *
 */

#include "IterativeBinaryTreeNode.h"

namespace Symplektis::DataReps
{
	IterativeBinaryTreeNode::IterativeBinaryTreeNode(const IterativeBinaryTreeNode& other)
		: IBinaryTreeNode(other)
	{
		m_MarkedForDelete = other.m_MarkedForDelete;

		m_LeftChildId = other.m_LeftChildId;
		m_RightChildId = other.m_RightChildId;
		m_ParentId = other.m_ParentId;
	}
	
	IterativeBinaryTreeNode& IterativeBinaryTreeNode::operator=(const IterativeBinaryTreeNode& other)
	{
		if (this == &other)
			return *this;

		SetBase(other);

		m_MarkedForDelete = other.m_MarkedForDelete;

		m_LeftChildId = other.m_LeftChildId;
		m_RightChildId = other.m_RightChildId;
		m_ParentId = other.m_ParentId;

		return *this;
	}

	BinaryNodeErrorCode IterativeBinaryTreeNode::SetLeftChildId(const NodeArrayIndex& newLeftChildNodeId)
	{
		if (!newLeftChildNodeId.IsValid())
			return BinaryNodeErrorCode::NodeArrayIndexError;
		
		if (HasLeftChild())
			return BinaryNodeErrorCode::LeftNodeExists;

		m_LeftChildId = newLeftChildNodeId;
		m_IsLeaf = false;
		return BinaryNodeErrorCode::OK;
	}

	void IterativeBinaryTreeNode::ForceSetLeftChildId(const NodeArrayIndex& insertedLeftChildNodeId)
	{
		auto leftChildIdToBeSet = insertedLeftChildNodeId;
		if (insertedLeftChildNodeId < NULL_NODE_INDEX)
			leftChildIdToBeSet = NULL_NODE_INDEX;
		
		if (HasLeftChild())
			DeleteLeft();

		m_LeftChildId = leftChildIdToBeSet;
		m_IsLeaf = false;
	}
	
	BinaryNodeErrorCode IterativeBinaryTreeNode::SetRightChildId(const NodeArrayIndex& newRightChildNodeId)
	{
		if (!newRightChildNodeId.IsValid())
			return BinaryNodeErrorCode::NodeArrayIndexError;
		
		if (HasRightChild())
			return BinaryNodeErrorCode::RightNodeExists;

		m_RightChildId = newRightChildNodeId;
		m_IsLeaf = false;
		return BinaryNodeErrorCode::OK;
	}

	void IterativeBinaryTreeNode::ForceSetRightChildId(const NodeArrayIndex& insertedRightChildNodeId)
	{
		auto rightChildToBeSet = insertedRightChildNodeId;
		if (insertedRightChildNodeId < NULL_NODE_INDEX)
			rightChildToBeSet = NULL_NODE_INDEX;
		
		if (HasRightChild())
			DeleteRight();

		m_RightChildId = rightChildToBeSet;
		m_IsLeaf = false;
	}

	BinaryNodeErrorCode IterativeBinaryTreeNode::SetParentNodeId(const NodeArrayIndex& parentNodeId)
	{
		if (!parentNodeId.IsValid())
			return BinaryNodeErrorCode::NodeArrayIndexError;

		m_ParentId = parentNodeId;
		
		return BinaryNodeErrorCode::OK;
	}

	void IterativeBinaryTreeNode::ForceSetParentNodeId(const NodeArrayIndex& parentNodeId)
	{
		if (parentNodeId < NULL_NODE_INDEX)
		{
			m_ParentId = NULL_NODE_INDEX;
			return;			
		}
		m_ParentId = parentNodeId;
	}

	void IterativeBinaryTreeNode::DeleteLeft()
	{
		m_LeftChildId = NULL_NODE_INDEX;
	}
	
	void IterativeBinaryTreeNode::DeleteRight()
	{
		m_RightChildId = NULL_NODE_INDEX;
	}
	
	void IterativeBinaryTreeNode::DeleteChildren()
	{
		DeleteLeft();
		DeleteRight();
	}

	void IterativeBinaryTreeNode::DeleteParent()
	{
		m_ParentId = NULL_NODE_INDEX;
	}

	//
	// ======================== Helper Functionality ======================================================
	//

	std::string IterativeBinaryTreeNode::DebugPrint() const
	{
		std::string result = "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n";
		result += "|     (Iterative) Node   :   " + Util::GetUUIDString(m_NodeUUID) + " |\n";
		if (m_MarkedForDelete)
			result += "           > > > > > >     D E L E T E D     < < < < < \n";
		result += "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
		result += "      Height     :   " + std::to_string(m_Height) + "\n";
		const size_t nChildren = static_cast<size_t>(HasLeftChild()) + static_cast<size_t>(HasRightChild());
		result += "      Children  :   " + std::to_string(nChildren) + "\n";
		if (HasLeftChild())
			result += "      Left Child Node Index:    " + std::to_string(m_LeftChildId.get()) + "\n";

		if (HasRightChild())
			result += "      Right Child Node Index:    " + std::to_string(m_RightChildId.get()) + "\n";
		result += "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";

		result += m_DataNode->DebugPrint();
		result += "^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^\n";
		
		return result;
	}

} // Symplektis::DataReps