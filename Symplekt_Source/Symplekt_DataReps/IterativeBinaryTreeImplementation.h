/*! \file  IterativeBinaryTreeImplementation.h
 *  \brief A Iterative implementation of a generic BinaryTree object. An iterative implementation\n
 *         allocates nodes linearly storing them in a pre-defined array memory storage.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   29.10.2021
 *
 */

#pragma once

#include "IBinaryTreeImplementation.h"
#include "IterativeBinaryTreeNode.h"

#include <vector>

namespace Symplektis::DataReps
{
    //=============================================================================
    /// \class IterativeBinaryTreeImplementation
    /// \brief An iterative extension of IBinaryTreeImplementation interface.
    ///        Contains a node array (std::vector), interacting with this container and its iterators upon every operation.
    ///
    /// \ingroup DATA_REPS
    ///
    /// \author M. Cavarga (MCInversion)
    /// \date   3.11.2021
    //=============================================================================
    class IterativeBinaryTreeImplementation final
		: public IBinaryTreeImplementation
    {
    public:
        /// @{
        /// \name Default Special Members

        /// \brief Default copy constructor.
        IterativeBinaryTreeImplementation(const IterativeBinaryTreeImplementation& other) = default;
    	
        /// \brief Default move constructor.
        IterativeBinaryTreeImplementation(IterativeBinaryTreeImplementation&& other) = default;

        /// \brief Default copy-assignment operator.
        IterativeBinaryTreeImplementation& operator=(const IterativeBinaryTreeImplementation& other) = default;
    	
        /// \brief Default move-assignment operator.
        IterativeBinaryTreeImplementation& operator=(IterativeBinaryTreeImplementation&& other) = default;

        /// \brief Default destructor.
        ~IterativeBinaryTreeImplementation() override = default;
    	
        /// @{
        /// \name Constructors

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::IBinaryTreeImplementation
		//-----------------------------------------------------------------------------
    	IterativeBinaryTreeImplementation()
	        : IBinaryTreeImplementation() { }

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::IBinaryTreeImplementation
        //-----------------------------------------------------------------------------
    	explicit IterativeBinaryTreeImplementation(const UUID& treeUUID)
    		: IBinaryTreeImplementation(treeUUID) { }

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::IBinaryTreeImplementation
        //-----------------------------------------------------------------------------
    	explicit IterativeBinaryTreeImplementation(const bool isSelfBalancing)
    		: IBinaryTreeImplementation(isSelfBalancing) { }

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::IBinaryTreeImplementation
        //-----------------------------------------------------------------------------
        IterativeBinaryTreeImplementation(const UUID& treeUUID, const bool isSelfBalancing)
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
            if (m_CurrentNodeId.get() < 0)
                return nullptr;
        	
            return std::make_shared<IterativeBinaryTreeNode>(m_NodeArray[m_CurrentNodeId]);
        }

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::GetRootNode
        //-----------------------------------------------------------------------------
        [[nodiscard]] std::shared_ptr<IBinaryTreeNode> GetRootNode() const override
        {
            if (m_NodeArray.empty())
                return nullptr;

            return std::make_shared<IterativeBinaryTreeNode>(m_NodeArray[m_RootNodeId]);
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

        //-----------------------------------------------------------------------------
        /*! \brief Computes the current node's balance factor for AVL tree, i.e.: Height(RightSubtree(currentNode)) - Height(LeftSubtree(currentNode))
         *  \return this node's AVL balance factor.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   4.12.2021
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] long int ComputeCurrentNodeAVLBalanceFactor() const;

    	//-----------------------------------------------------------------------------
        /*! \brief Computes the given node's balance factor for AVL tree, i.e.: Height(RightSubtree(node)) - Height(LeftSubtree(node))
         *  \param[in] nodeId               index of the node whose balance factor should be computed.
         *  \return given node's AVL balance factor.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   4.12.2021
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] long int ComputeNodeAVLBalanceFactor(const NodeArrayIndex& nodeId) const;

        /// @{
        /// \name Setters

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
        /*! \brief Sets current node id to m_CurrentNodeId.
         *  \param[in] currentNodeId           current node id to be set.
         *  \return BinaryTreeErrorCode::NodeArrayIndexError if given index is out of range.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   30.11.2021
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] BinaryTreeErrorCode SetCurrentNodeId(const NodeArrayIndex& currentNodeId);

        //-----------------------------------------------------------------------------
        /*! \brief  Setter for a flag for always clearing node array after marking some nodes for delete (from within methods)
         *   \param[in] value          value to be set to m_ClearAfterMarkingForDelete flag.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   3.11.2021
         *
         */
         //-----------------------------------------------------------------------------
        void SetClearAfterMarkingForDelete(const bool value)
        {
            m_ClearAfterMarkingForDelete = value;
        }

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::SetHeightFromCompleteTree
        //-----------------------------------------------------------------------------
    	void SetHeightFromCompleteTree() override;
    	
        /// @{
        /// \name Flags

        //-----------------------------------------------------------------------------
        /*! \brief  Flag for always clearing node array after marking some nodes for delete (from within methods)
         *  \return m_ClearAfterMarkingForDelete
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   3.11.2021
         *
         */
         //-----------------------------------------------------------------------------
    	[[nodiscard]] bool ClearsAfterMarkingForDelete() const
        {
            return m_ClearAfterMarkingForDelete;
        }

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

        /// @{
        /// \name Misc Private Functionality
    	
        //-----------------------------------------------------------------------------
        /*! \brief Internal utility for updating m_NodeArray by re-initializing it with nodes not marked as deleted.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   2.11.2021
         */
         //-----------------------------------------------------------------------------
        void ClearNodesMarkedForDelete();

        //-----------------------------------------------------------------------------
        /*! \brief Sets m_TreeHeight as the maximum depth of all its nodes.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   3.11.2021
         */
         //-----------------------------------------------------------------------------
        void UpdateTreeHeight();

        //-----------------------------------------------------------------------------
        /*! \brief Updates the number of all nodes in this tree.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   6.11.2021
         *
         */
         //-----------------------------------------------------------------------------
        void UpdateNodeCount()
        {
            m_NodeCount = m_NodeArray.size();
        }

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeImplementation::UpdateNodeHeightsAndBalanceFactorsUpToRoot
        //-----------------------------------------------------------------------------
        void UpdateNodeHeightsAndBalanceFactorsUpToRoot() override;

        //
        // =============== Data ========================================================
        //

        //>! Array of tree nodes referring to their children via iterators in this vector.
        BinaryTreeNodeArray m_NodeArray{};

        //>! Current node (cursor) index.
        NodeArrayIndex m_CurrentNodeId = NULL_NODE_INDEX;

    	//>! Root node index.
        NodeArrayIndex m_RootNodeId = NULL_NODE_INDEX;

        //>! Flag for doing m_NodeArray cleanup after every operation that marks some nodes as deleted.
    	//   This flag should be set as false or high-performance usage.
        bool m_ClearAfterMarkingForDelete = true;
    };

} // Symplektis::DataReps