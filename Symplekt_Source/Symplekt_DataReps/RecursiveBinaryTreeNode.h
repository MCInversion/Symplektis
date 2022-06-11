/*! \file  RecursiveBinaryTreeNode.h
 *  \brief A generic node object for RecursiveBinaryTreeImplementation, i.e.: \n
 *         contains pointer references to heap instances of child nodes.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   1.11.2021
 *
 */

#pragma once

#include "IBinaryTreeNode.h"
#include "BinaryTreeHelperTypes.h"

namespace Symplektis::DataReps
{
    //=============================================================================
    /// \class RecursiveBinaryTreeNode
    /// \brief A recursive extension of IBinaryTreeNode interface for binary tree node objects.
    ///        Contains pointer references to heap instances of child nodes.
    ///
    /// \ingroup DATA_REPS
    ///
    /// \author M. Cavarga (MCInversion)
    /// \date   1.11.2021
    //=============================================================================
	class RecursiveBinaryTreeNode final
        : public IBinaryTreeNode
	{
	public:

        /// @{
        /// \name Default Special Members

        /// \brief Default constructor.
        RecursiveBinaryTreeNode() = default;

        /// \brief Default move constructor.
        RecursiveBinaryTreeNode(RecursiveBinaryTreeNode&& other) = default;

        /// \brief Default move-assignment operator.
        RecursiveBinaryTreeNode& operator=(RecursiveBinaryTreeNode&& other) = default;

        /// \brief Default destructor.
        ~RecursiveBinaryTreeNode() override = default;
		
        /// @{
        /// \name Constructors

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeNode::IBinaryTreeNode
        //-----------------------------------------------------------------------------
        RecursiveBinaryTreeNode(const UUID& treeUuid, const std::shared_ptr<IBinaryTreeQueryDataNode>& queryDataNode)
            : IBinaryTreeNode(treeUuid, queryDataNode) { }
		
		//-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeNode::IBinaryTreeNode
        //-----------------------------------------------------------------------------
		explicit RecursiveBinaryTreeNode(const UUID& treeUuid)
				: IBinaryTreeNode(treeUuid) { }

        //-----------------------------------------------------------------------------
        /*! \brief Copy constructor.
         *  \param[in] other          other node to be copy constructed from.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   1.11.2021
         */
         //-----------------------------------------------------------------------------
        RecursiveBinaryTreeNode(const RecursiveBinaryTreeNode& other);

        /// @{
        /// \name Operators

        //-----------------------------------------------------------------------------
        /*! \brief Copy-assignment operator.
         *  \param[in] other          other node to be copy constructed from.
         *  \return reference to this binary tree node.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   27.11.2021
         */
         //-----------------------------------------------------------------------------
        RecursiveBinaryTreeNode& operator=(const RecursiveBinaryTreeNode& other);
		
        /// @{
        /// \name Setters
		
        //-----------------------------------------------------------------------------
        /*! \brief Tries to set left m_LeftChild node.
         *  \param[in] leftCandidate            left child node candidate.
         *  \return BinaryNodeErrorCode::LeftNodeExists if this node already has a left child.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   1.11.2021
         */
        //-----------------------------------------------------------------------------
		[[nodiscard]] BinaryNodeErrorCode SetLeftChild(const std::shared_ptr<IBinaryTreeNode>& leftCandidate);

		
        //-----------------------------------------------------------------------------
        /*! \brief Force-sets m_LeftChild without verification. Previous left child node pointer is discarded.
         *  \param[in] newLeftNode            new left child node.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   1.11.2021
         */
        //-----------------------------------------------------------------------------
        void ForceSetLeftChild(const std::shared_ptr<IBinaryTreeNode>& newLeftNode);


        //-----------------------------------------------------------------------------
        /*! \brief Tries to set right m_RightChild node.
         *  \param[in] rightCandidate            right child node candidate.
         *  \return BinaryNodeErrorCode::RightNodeExists if this node already has a right child.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   1.11.2021
         */
        //-----------------------------------------------------------------------------
        [[nodiscard]] BinaryNodeErrorCode SetRightChild(const std::shared_ptr<IBinaryTreeNode>& rightCandidate);


        //-----------------------------------------------------------------------------
        /*! \brief Force-sets m_RightChild without verification. Previous right child node pointer is discarded.
         *  \param[in] newRightNode            new right child node.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   1.11.2021
         */
        //-----------------------------------------------------------------------------
        void ForceSetRightChild(const std::shared_ptr<IBinaryTreeNode>& newRightNode);

        //-----------------------------------------------------------------------------
        /*! \brief Tries to set this node's parent node.
         *  \param[in] parentNode            parent node to be set.
         *  \return BinaryNodeErrorCode::NullNode if parentNode is null.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   4.12.2021
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] BinaryNodeErrorCode SetParentNode(const std::shared_ptr<IBinaryTreeNode>& parentNode);

        /// @{
        /// \name Deleters

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeNode::DeleteLeft
        //-----------------------------------------------------------------------------
        void DeleteLeft() override;

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeNode::DeleteRight
        //-----------------------------------------------------------------------------
        void DeleteRight() override;

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeNode::DeleteChildren
        //-----------------------------------------------------------------------------
        void DeleteChildren() override;

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeNode::DeleteParent
        //-----------------------------------------------------------------------------
		void DeleteParent() override;

        /// @{
		/// \name Getters

        //-----------------------------------------------------------------------------
        /*! \brief Returns pointer to the left child node.
         *  \return shared ptr to the left child node.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   24.11.2021
         */
        //-----------------------------------------------------------------------------
        [[nodiscard]] std::shared_ptr<RecursiveBinaryTreeNode> LeftChildPtr() const
        {
            return m_LeftChild;
        }


        //-----------------------------------------------------------------------------
        /*! \brief Returns pointer to the right child node.
         *  \return shared ptr to the right child node.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   24.11.2021
         */
        //-----------------------------------------------------------------------------
        [[nodiscard]] std::shared_ptr<RecursiveBinaryTreeNode> RightChildPtr() const
        {
            return m_RightChild;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Returns pointer to the parent node.
         *  \return shared ptr to the parent node.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   4.12.2021
         */
         //-----------------------------------------------------------------------------
		[[nodiscard]] std::shared_ptr<RecursiveBinaryTreeNode> ParentNodePtr() const
        {
            return m_Parent;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Recursively counts children of this node
         *  \return number of children of this node
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   6.11.2021
         */
        //-----------------------------------------------------------------------------
        [[nodiscard]] size_t CountChildren() const;

        //-----------------------------------------------------------------------------
		/*! \brief Computes this node's balance factor for AVL tree, i.e.: Height(RightSubtree(this)) - Height(LeftSubtree(this))
		 *  \return this node's AVL balance factor.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   4.12.2021
		 */
		 //-----------------------------------------------------------------------------
        [[nodiscard]] long int ComputeAVLBalanceFactor() const;

        /// @{
        /// \name Flags

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeNode::HasLeftChild
        //-----------------------------------------------------------------------------
        [[nodiscard]] bool HasLeftChild() const override
        {
            return m_LeftChild != nullptr;
        }

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeNode::HasRightChild
        //-----------------------------------------------------------------------------
        [[nodiscard]] bool HasRightChild() const override
        {
            return m_RightChild != nullptr;
        }

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeNode::HasParent
        //-----------------------------------------------------------------------------
        [[nodiscard]] bool HasParent() const override
        {
            return m_Parent != nullptr;
        }

        /// @{
        /// \name Helper Functionality

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeNode::DebugPrint
        //-----------------------------------------------------------------------------
        [[nodiscard]] std::string DebugPrint() const override;
	
	private:

        //
        // =============== Data ========================================================
        //

        std::shared_ptr<RecursiveBinaryTreeNode> m_LeftChild = nullptr;     //>! left child node ptr
        std::shared_ptr<RecursiveBinaryTreeNode> m_RightChild = nullptr;    //>! right child node ptr

        std::shared_ptr<RecursiveBinaryTreeNode> m_Parent = nullptr;        //>! parent node ptr
	};
	
} // Symplektis::DataReps