/*! \file  BinaryTree.cpp
 *  \brief Implementation of a generic binary tree interface.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   29.10.2021
 *
 */

#include "BinaryTree.h"

#include "Symplekt_UtilityGeneral/Assert.h"

#include "IterativeBinaryTreeImplementation.h"
#include "RecursiveBinaryTreeImplementation.h"

 // TODO: Perhaps revive Symplekt_DataReps and move general data structures there.

namespace Symplektis::DataReps
{
    //-----------------------------------------------------------------------------
	/*! \brief  Gets string name of implementation type enumerator.
	 *  \param[in] implType          implementation type enumerator.
	 *  \return implementation type name string.
	 *
	 *   \author M. Cavarga (MCInversion)
	 *   \date   28.11.2021
	 */
	 //-----------------------------------------------------------------------------
	static std::string DebugPrintImplementationType(const BinaryTreeImplementationType& implType)
    {
        if (implType == BinaryTreeImplementationType::Iterative)
            return "Iterative";

        if (implType == BinaryTreeImplementationType::Recursive)
            return "Recursive";

        return "N/A";
    }
	
    std::string BinaryTree::DebugPrint() const
    {
        std::string result = "===============================================================\n";
        result += "              Binary Tree Debug Print     [" + Util::GetTimestampString() + "]    \n";
        result += "---------------------------------------------------------------\n";
        result += "    Tree Name: " + m_Name + "\n";

        if (!m_TreeImplementation)
            return "> > > > > > > > > ERROR: Missing implementation! < < < < < < < < < \n";
    	
        const std::string treeUUIDStr = Util::GetUUIDString(m_TreeImplementation->GetTreeUUID());    	
        result += "    Tree UUID:             " + treeUUIDStr + "\n";
        result += "    Implementation Type:   " + DebugPrintImplementationType(m_ImplementationType) + "\n";
    	result += "===============================================================\n";

		if (!m_IsValid)
		{
            result += "> > > > > > > > > ERROR: Tree state invalid! < < < < < < < < < \n";
            result += "                  Construction incomplete                      \n";
            result += "===============================================================\n";
            result += "...................... END DEBUG PRINT ........................\n";
            result += "===============================================================\n";
            return result;
		}

        result += m_TreeImplementation->DebugPrint();
		
		result += "===============================================================\n";
        result += "...................... END DEBUG PRINT ........................\n";
        result += "===============================================================\n";
    	
        return result;
    }

    std::string BinaryTree::PlantUMLPrint() const
    {
        if (!m_TreeImplementation)
            return "> > > > > > > > > ERROR: Missing implementation! < < < < < < < < < \n";

        std::string result = "@startuml\n\n";

        result += m_TreeImplementation->PlantUMLPrint();

        result += "@enduml";
		
        return result;
    }
	
    void BinaryTree::SetAndInitImplementationType(const BinaryTreeImplementationType& implType)
    {
        if (implType == m_ImplementationType)
            return;

        if (!m_TreeImplementation)
        {
            InternalSetAndInitImplementationType(implType);
            return;
        }
    	
        const auto treeUUID = m_TreeImplementation->GetTreeUUID();    	
        m_TreeImplementation = nullptr;
    	
        InternalSetAndInitImplementationTypeWithUUID(implType, treeUUID);
    }

    std::vector<std::shared_ptr<NodeDataWrapper>> BinaryTree::GetTreeDataFromDepthFirstTraversal() const
    {
        if (!m_TreeImplementation)
            return {};

        return m_TreeImplementation->GetTreeDataFromDepthFirstTraversal();
    }

    std::vector<std::shared_ptr<NodeDataWrapper>> BinaryTree::GetTreeDataFromBreadthFirstTraversal() const
    {
        if (!m_TreeImplementation)
            return {};

        return m_TreeImplementation->GetTreeDataFromBreadthFirstTraversal();
    }
	
    void BinaryTree::InternalSetAndInitImplementationType(const BinaryTreeImplementationType& implType)
    {
        m_ImplementationType = implType;

        if (implType == BinaryTreeImplementationType::Iterative)
        {
            const auto iterImplPtr = std::make_shared<IterativeBinaryTreeImplementation>(IterativeBinaryTreeImplementation());
            m_TreeImplementation = std::static_pointer_cast<IBinaryTreeImplementation>(iterImplPtr);
        }
        else if (implType == BinaryTreeImplementationType::Recursive)
        {
            const auto recurImplPtr = std::make_shared<RecursiveBinaryTreeImplementation>(RecursiveBinaryTreeImplementation());
            m_TreeImplementation = std::static_pointer_cast<IBinaryTreeImplementation>(recurImplPtr);
        }
        else
        {
            MSG_CHECK(false, "BinaryTree::SetImplementationType: Invalid implementation enumerator!\n");
        }
    }

    void BinaryTree::InternalSetAndInitImplementationType(const BinaryTreeImplementationType& implType, const bool isSelfBalancing)
    {
        m_ImplementationType = implType;

        if (implType == BinaryTreeImplementationType::Iterative)
        {
            const auto iterImplPtr = std::make_shared<IterativeBinaryTreeImplementation>(IterativeBinaryTreeImplementation(isSelfBalancing));
            m_TreeImplementation = std::static_pointer_cast<IBinaryTreeImplementation>(iterImplPtr);
        }
        else if (implType == BinaryTreeImplementationType::Recursive)
        {
            const auto recurImplPtr = std::make_shared<RecursiveBinaryTreeImplementation>(RecursiveBinaryTreeImplementation(isSelfBalancing));
            m_TreeImplementation = std::static_pointer_cast<IBinaryTreeImplementation>(recurImplPtr);
        }
        else
        {
            MSG_CHECK(false, "BinaryTree::SetImplementationType: Invalid implementation enumerator!\n");
        }
    }
	
    void BinaryTree::InternalSetAndInitImplementationTypeWithUUID(const BinaryTreeImplementationType& implType, const UUID& treeUUID)
    {
        m_ImplementationType = implType;

        if (implType == BinaryTreeImplementationType::Iterative)
        {
            const auto iterImplPtr = std::make_shared<IterativeBinaryTreeImplementation>(IterativeBinaryTreeImplementation(treeUUID));
            m_TreeImplementation = std::static_pointer_cast<IBinaryTreeImplementation>(iterImplPtr);
        }
        else if (implType == BinaryTreeImplementationType::Recursive)
        {
            const auto recurImplPtr = std::make_shared<RecursiveBinaryTreeImplementation>(RecursiveBinaryTreeImplementation(treeUUID));
            m_TreeImplementation = std::static_pointer_cast<IBinaryTreeImplementation>(recurImplPtr);
        }
        else
        {
            MSG_CHECK(false, "BinaryTree::SetImplementationType: Invalid implementation enumerator!\n");
        }
    }

    void BinaryTree::InternalSetAndInitImplementationType(const BinaryTreeImplementationType& implType, const UUID& treeUUID, const bool isSelfBalancing)
    {
        m_ImplementationType = implType;

        if (implType == BinaryTreeImplementationType::Iterative)
        {
            const auto iterImplPtr = std::make_shared<IterativeBinaryTreeImplementation>(IterativeBinaryTreeImplementation(treeUUID, isSelfBalancing));
            m_TreeImplementation = std::static_pointer_cast<IBinaryTreeImplementation>(iterImplPtr);
        }
        else if (implType == BinaryTreeImplementationType::Recursive)
        {
            const auto recurImplPtr = std::make_shared<RecursiveBinaryTreeImplementation>(RecursiveBinaryTreeImplementation(treeUUID, isSelfBalancing));
            m_TreeImplementation = std::static_pointer_cast<IBinaryTreeImplementation>(recurImplPtr);
        }
        else
        {
            MSG_CHECK(false, "BinaryTree::SetImplementationType: Invalid implementation enumerator!\n");
        }
    }

    BinaryTreeErrorCode BinaryTree::InternalInsertNodeAsDataNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& newDataNode) const
    {
        if (!m_TreeImplementation)
            return BinaryTreeErrorCode::InternalError;
    	
        return m_TreeImplementation->InsertNode(newDataNode);
    }
	
    BinaryTreeErrorCode BinaryTree::InternalInsertLeftNodeAsDataNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& newLeftDataNode) const
    {
        if (!m_TreeImplementation)
            return BinaryTreeErrorCode::InternalError;
    	
        return m_TreeImplementation->InsertLeftNode(newLeftDataNode);
    }
	
    BinaryTreeErrorCode BinaryTree::InternalInsertRightNodeAsDataNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& newRightDataNode) const
    {
        if (!m_TreeImplementation)
            return BinaryTreeErrorCode::InternalError;
    	
        return m_TreeImplementation->InsertRightNode(newRightDataNode);
    }
	
    void BinaryTree::InternalForceInsertLeftNodeAsDataNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& insertedLeftDataNode) const
    {
        if (!m_TreeImplementation)
            return;

        m_TreeImplementation->ForceInsertLeftNode(insertedLeftDataNode);
    }
	
    void BinaryTree::InternalForceInsertRightNodeAsDataNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& insertedRightDataNode) const
    {
        if (!m_TreeImplementation)
            return;

        m_TreeImplementation->ForceInsertRightNode(insertedRightDataNode);
    }

    std::shared_ptr<IBinaryTreeNode> BinaryTree::InternalGetCurrentNode() const
    {
        if (!m_TreeImplementation)
            return nullptr;

        return m_TreeImplementation->GetCurrentNode();
    }

    std::shared_ptr<IBinaryTreeNode> BinaryTree::InternalGetRootNode() const
    {
        if (!m_TreeImplementation)
            return nullptr;

        return m_TreeImplementation->GetRootNode();
    }

    BinaryTreeErrorCode BinaryTree::InternalSetRootAsCurrent() const
    {
        if (!m_TreeImplementation)
            return BinaryTreeErrorCode::InternalError;

        return m_TreeImplementation->SetRootAsCurrent();
    }

    BinaryTreeErrorCode BinaryTree::InternalSetCurrentNodeLeftChildAsCurrent() const
    {
        if (!m_TreeImplementation)
            return BinaryTreeErrorCode::InternalError;

        return m_TreeImplementation->SetCurrentNodeLeftChildAsCurrent();
    }

    BinaryTreeErrorCode BinaryTree::InternalSetCurrentNodeRightChildAsCurrent() const
    {
        if (!m_TreeImplementation)
            return BinaryTreeErrorCode::InternalError;

        return m_TreeImplementation->SetCurrentNodeRightChildAsCurrent();
    }

    std::shared_ptr<IBinaryTreeQueryDataNode> BinaryTree::InternalGetCurrentNodeQueryDataNode() const
    {
        if (!m_TreeImplementation)
            return nullptr;

        return m_TreeImplementation->GetCurrentNodeQueryDataNode();
    }

    std::shared_ptr<IBinaryTreeQueryDataNode> BinaryTree::InternalGetCurrentNodeLeftChildQueryDataNode() const
    {
        if (!m_TreeImplementation)
            return nullptr;

        return m_TreeImplementation->GetCurrentNodeLeftChildQueryDataNode();
    }

    std::shared_ptr<IBinaryTreeQueryDataNode> BinaryTree::InternalGetCurrentNodeRightChildQueryDataNode() const
    {
        if (!m_TreeImplementation)
            return nullptr;

        return m_TreeImplementation->GetCurrentNodeRightChildQueryDataNode();
    }
	
} // Symplektis::DataReps