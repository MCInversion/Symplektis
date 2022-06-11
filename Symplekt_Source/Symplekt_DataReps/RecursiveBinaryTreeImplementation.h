/*! \file  RecursiveBinaryTreeImplementation.h
 *  \brief A recursive implementation of a generic BinaryTree object. Recursive implementation\n
 *         allocates nodes recursively storing them in heap memory.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   29.10.2021
 *
 */

#pragma once

#include "IBinaryTreeImplementation.h"
#include "RecursiveBinaryTreeNode.h"

namespace Symplektis::DataReps
{
    //=============================================================================
    /// \class RecursiveBinaryTreeImplementation
    /// \brief A recursive extension of IBinaryTreeImplementation interface.
    ///        Contains pointer reference to the heap instance of root node.
    ///
    /// \ingroup DATA_REPS
    ///
    /// \author M. Cavarga (MCInversion)
    /// \date   5.11.2021
    //=============================================================================
    class RecursiveBinaryTreeImplementation final
		: public IBinaryTreeImplementation
    {
    public:
        /// @{
        /// \name Default Special Members

        /// \brief Default copy constructor.
        RecursiveBinaryTreeImplementation(const RecursiveBinaryTreeImplementation& other) = default;
    	
        /// \brief Default move constructor.
        RecursiveBinaryTreeImplementation(RecursiveBinaryTreeImplementation&& other) = default;

        /// \brief Default copy-assignment operator.
        RecursiveBinaryTreeImplementation& operator=(const RecursiveBinaryTreeImplementation& other) = default;

        /// \brief Default move-assignment operator.
        RecursiveBinaryTreeImplementation& operator=(RecursiveBinaryTreeImplementation&& other) = default;

        /// \brief Default destructor.
        ~RecursiveBinaryTreeImplementation() override = default;

        /// @{
        /// \name Constructors

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::IBinaryTreeImplementation
        //-----------------------------------------------------------------------------
        RecursiveBinaryTreeImplementation()
            : IBinaryTreeImplementation() { }

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::IBinaryTreeImplementation
        //-----------------------------------------------------------------------------
        explicit RecursiveBinaryTreeImplementation(const UUID& treeUUID)
            : IBinaryTreeImplementation(treeUUID) { }

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::IBinaryTreeImplementation
        //-----------------------------------------------------------------------------
        explicit RecursiveBinaryTreeImplementation(const bool isSelfBalancing)
            : IBinaryTreeImplementation(isSelfBalancing) { }

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::IBinaryTreeImplementation
        //-----------------------------------------------------------------------------
        RecursiveBinaryTreeImplementation(const UUID& treeUUID, const bool isSelfBalancing)
            : IBinaryTreeImplementation(treeUUID, isSelfBalancing) { }
    	
        /// @{
        /// \name Functionality: Node Inserters

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::InsertNode
        //-----------------------------------------------------------------------------
        [[nodiscard]] BinaryTreeErrorCode InsertNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& newDataNode) override;

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::InsertLeftNode
        //-----------------------------------------------------------------------------
        [[nodiscard]] BinaryTreeErrorCode InsertLeftNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& newLeftDataNode) override;

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::InsertRightNode
        //-----------------------------------------------------------------------------
        [[nodiscard]] BinaryTreeErrorCode InsertRightNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& newRightDataNode) override;

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::ForceInsertLeftNode
        //-----------------------------------------------------------------------------
        void ForceInsertLeftNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& insertedLeftDataNode) override;

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::ForceInsertRightNode
        //-----------------------------------------------------------------------------
        void ForceInsertRightNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& insertedRightDataNode) override;
 	
        /// @{
        // \name Functionality: Node Deleters

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::DeleteNode
        //-----------------------------------------------------------------------------
        [[nodiscard]] BinaryTreeErrorCode DeleteNode(const std::shared_ptr<IBinaryTreeNode>& nodeForDeletion) override;

    	/// @{
        /// \name Getters

    	//-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::GetCurrentNode
        //-----------------------------------------------------------------------------
        [[nodiscard]] std::shared_ptr<IBinaryTreeNode> GetCurrentNode() const override
        {
            return m_CurrentNode;
        }

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::GetRootNode
        //-----------------------------------------------------------------------------
    	[[nodiscard]] std::shared_ptr<IBinaryTreeNode> GetRootNode() const override
        {
            return m_RootNode;
        }

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::GetCurrentNodeQueryDataNode
        //-----------------------------------------------------------------------------
        [[nodiscard]] std::shared_ptr<IBinaryTreeQueryDataNode> GetCurrentNodeQueryDataNode() const override;

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::GetCurrentNodeLeftChildQueryDataNode
        //-----------------------------------------------------------------------------
    	[[nodiscard]] std::shared_ptr<IBinaryTreeQueryDataNode> GetCurrentNodeLeftChildQueryDataNode() const override;

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::GetCurrentNodeRightChildQueryDataNode
        //-----------------------------------------------------------------------------
        [[nodiscard]] std::shared_ptr<IBinaryTreeQueryDataNode> GetCurrentNodeRightChildQueryDataNode() const override;

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::GetTreeDataFromDepthFirstTraversal
        //-----------------------------------------------------------------------------
        [[nodiscard]] std::vector<std::shared_ptr<NodeDataWrapper>> GetTreeDataFromDepthFirstTraversal() const override;

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::GetTreeDataFromBreadthFirstTraversal
        //-----------------------------------------------------------------------------
        [[nodiscard]] std::vector<std::shared_ptr<NodeDataWrapper>> GetTreeDataFromBreadthFirstTraversal() const override;
    	
        /// @{
        /// \name Setters

        //-----------------------------------------------------------------------------
        /*! \brief  Sets current node cursor to the given node.
         *  \param[in] nodeAsCurrent          Node to be set as current.
         *  \return BinaryTreeErrorCode::NodeNotFound if node.GetTreeUUID() does not match with m_TreeUUID.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   8.11.2021
         */
        //-----------------------------------------------------------------------------
        [[nodiscard]] BinaryTreeErrorCode SetCurrentNode(const std::shared_ptr<IBinaryTreeNode>& nodeAsCurrent);

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::SetRootAsCurrent
        //-----------------------------------------------------------------------------
        [[nodiscard]] BinaryTreeErrorCode SetRootAsCurrent() override;

        //-----------------------------------------------------------------------------
		/// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::SetCurrentNodeLeftChildAsCurrent
		//-----------------------------------------------------------------------------
        [[nodiscard]] BinaryTreeErrorCode SetCurrentNodeLeftChildAsCurrent() override;

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::SetCurrentNodeRightChildAsCurrent
        //-----------------------------------------------------------------------------
        [[nodiscard]] BinaryTreeErrorCode SetCurrentNodeRightChildAsCurrent() override;

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::SetHeightFromCompleteTree
        //-----------------------------------------------------------------------------
        void SetHeightFromCompleteTree() override;
    	
        /// @{
        /// \name Helper Functionality

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::DebugPrint
        //-----------------------------------------------------------------------------
        [[nodiscard]] std::string DebugPrint() const override;

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::PlantUMLPrint
        //-----------------------------------------------------------------------------
        [[nodiscard]] std::string PlantUMLPrint() const override;
    
    private:

        /// @{
        /// \name Private Operation Functionality

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::RebalanceFromCurrentNode
        //-----------------------------------------------------------------------------
        [[nodiscard]] BinaryTreeErrorCode RebalanceFromCurrentNode() override;
    	
        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::RotateLeftAtCurrentNode
        //-----------------------------------------------------------------------------
        [[nodiscard]] BinaryTreeErrorCode RotateLeftAtCurrentNode() override;

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::RotateRightAtCurrentNode
        //-----------------------------------------------------------------------------
        [[nodiscard]] BinaryTreeErrorCode RotateRightAtCurrentNode() override;

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::RotateLeftRightAtCurrentNode
        //-----------------------------------------------------------------------------
        [[nodiscard]] BinaryTreeErrorCode RotateLeftRightAtCurrentNode() override;

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::RotateRightLeftAtCurrentNode
        //-----------------------------------------------------------------------------
        [[nodiscard]] BinaryTreeErrorCode RotateRightLeftAtCurrentNode() override;

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::UpdateNodeHeightsAndBalanceFactorsUpToRoot
        //-----------------------------------------------------------------------------
        void UpdateNodeHeightsAndBalanceFactorsUpToRoot() override;

        //
        // =============== Data ========================================================
        //

        //>! Root node instance pointer
        std::shared_ptr<RecursiveBinaryTreeNode> m_RootNode = nullptr;

        //>! Current node cursor
        std::shared_ptr<RecursiveBinaryTreeNode> m_CurrentNode = nullptr;
    };

} // Symplektis::DataReps