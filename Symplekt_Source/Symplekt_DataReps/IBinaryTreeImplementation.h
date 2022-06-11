/*! \file  IBinaryTreeImplementation.h
 *  \brief An interface for an implementation of a generic BinaryTree object.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   31.10.2021
 *
 */

#pragma once

#include "BinaryTreeHelperTypes.h"
#include "IBinaryTreeNode.h"
#include "../Symplekt_UtilityGeneral/UUIDTools.h"

#include <cmath>
#include <memory>

namespace Symplektis::DataReps
{
    //=============================================================================
    /// \class IBinaryTreeImplementation
    /// \brief An interface to binary tree implementation offering basic getters and tree data.
    ///
    /// \ingroup DATA_REPS
    ///
    /// \author M. Cavarga (MCInversion)
    /// \date   2.11.2021
    //=============================================================================
    class IBinaryTreeImplementation
    {
    public:
        /// @{
        /// \name Default Special Members

        /// \brief Default move constructor.
        IBinaryTreeImplementation(IBinaryTreeImplementation&& other) = default;

        /// \brief Default copy-assignment operator.
        IBinaryTreeImplementation& operator=(const IBinaryTreeImplementation& other) = default;

        /// \brief Default move-assignment operator.
        IBinaryTreeImplementation& operator=(IBinaryTreeImplementation&& other) = default;

    	/// \brief Default destructor.
        virtual ~IBinaryTreeImplementation() = default;
    	
        /// @{
		/// \name Constructors

        //-----------------------------------------------------------------------------
        /*! \brief A default constructor which also generates m_TreeUUID.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   1.11.2021
         */
         //-----------------------------------------------------------------------------
        IBinaryTreeImplementation()
        {
            m_TreeUUID = Util::CreateUUID();
        }

        //-----------------------------------------------------------------------------
        /*! \brief Copy constructor.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   21.11.2021
         */
         //-----------------------------------------------------------------------------
    	IBinaryTreeImplementation(const IBinaryTreeImplementation& other)
        {
            SetBase(other);
        }

        //-----------------------------------------------------------------------------
        /*! \brief Constructor. Initialize from a given UUID.
         *  \param[in] treeUUID            UUID to initialize with.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   21.11.2021
         */
         //-----------------------------------------------------------------------------
    	explicit IBinaryTreeImplementation(const UUID& treeUUID)
        {
            m_TreeUUID = treeUUID;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Constructor. Initialize with an "isSelfBalancing" flag.
         *  \param[in] isSelfBalancing            if true, this tree implementation will be initialized as self-balancing.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   4.12.2021
         */
         //-----------------------------------------------------------------------------
    	explicit IBinaryTreeImplementation(const bool isSelfBalancing)
    		: IBinaryTreeImplementation()
        {
            SetSelfBalancing(isSelfBalancing);
        }

        //-----------------------------------------------------------------------------
        /*! \brief Constructor. Initialize from a given UUID, and with an "isSelfBalancing" flag.
         *  \param[in] treeUUID            UUID to initialize with.
         *  \param[in] isSelfBalancing     if true, this tree implementation will be initialized as self-balancing.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   4.12.2021
         */
         //-----------------------------------------------------------------------------
        IBinaryTreeImplementation(const UUID& treeUUID, const bool isSelfBalancing)
            : IBinaryTreeImplementation(treeUUID)
        {
            SetSelfBalancing(isSelfBalancing);
        }

        /// @{
        /// \name Functionality: Node Inserters

        //-----------------------------------------------------------------------------
        /*! \brief Tries to insert a new node with a given data node at CurrentNode. Left node is prioritized if current node is a leaf.
         *  \param[in] newDataNode           data node to be inserted
         *  \return BinaryTreeErrorCode::NodeSaturated if CurrentNode already has both children.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   5.11.2021
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] virtual BinaryTreeErrorCode InsertNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& newDataNode) = 0;

        //-----------------------------------------------------------------------------
        /*! \brief Tries to insert a new left node with a given data node at CurrentNode.
         *  \param[in] newLeftDataNode           data node to be inserted
         *  \return BinaryTreeErrorCode::LeftNodeExists if there's already a left child.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   5.11.2021
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] virtual BinaryTreeErrorCode InsertLeftNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& newLeftDataNode) = 0;

        //-----------------------------------------------------------------------------
        /*! \brief Tries to insert a new right node with a given data node at CurrentNode.
         *  \param[in] newRightDataNode            data node to be inserted
         *  \return BinaryTreeErrorCode::RightNodeExists if there's already a right child.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   5.11.2021
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] virtual BinaryTreeErrorCode InsertRightNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& newRightDataNode) = 0;

        //-----------------------------------------------------------------------------
        /*! \brief Force-inserts a new left child node as data node at CurrentNode. Previous children of CurrentNode are marked for deletion.
         *  \param[in] insertedLeftDataNode            data node to be inserted
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   5.11.2021
         *
         *   Be careful, this method erases all previous children
         */
         //-----------------------------------------------------------------------------
        virtual void ForceInsertLeftNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& insertedLeftDataNode) = 0;

        //-----------------------------------------------------------------------------
        /*! \brief Force-inserts a new right child node as data node at CurrentNode. Previous left children of CurrentNode are marked for deletion.
         *  \param[in] insertedRightDataNode            data node to be inserted
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   5.11.2021
         *
         *   Be careful, this method erases all previous children
         */
         //-----------------------------------------------------------------------------
        virtual void ForceInsertRightNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& insertedRightDataNode) = 0;

        /// @{
        /// \name Functionality: Node Deleters

        //-----------------------------------------------------------------------------
        /*! \brief Deletes a node and all of its children. CurrentNode is set to parent of node upon successful deletion.
         *  \param[in] nodeForDeletion            node to be deleted
         *  \return Returns BinaryTreeErrorCode::NodeNotFound if node is not found in the tree.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   5.11.2021
         *
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] virtual BinaryTreeErrorCode DeleteNode(const std::shared_ptr<IBinaryTreeNode>& nodeForDeletion) = 0;

        /// @{
		/// \name Getters

        //-----------------------------------------------------------------------------
        /*! \brief Gets the number of all nodes in this tree.
         *  \return the number of all nodes in this tree.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   1.11.2021
         *
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] size_t GetNodeCount() const
        {
            return m_NodeCount;
        }


        //-----------------------------------------------------------------------------
        /*! \brief Gets the total tree Height.
         *  \return the total Height of this tree.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   1.11.2021
         *
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] size_t GetHeight() const
        {
            return m_TreeHeight;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Gets the tree UUID
         *  \return returns tree UUID.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   1.11.2021
         */
         //----------------------------------------------------------------------------- 
        [[nodiscard]] UUID GetTreeUUID() const
        {
            return m_TreeUUID;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Gets the pointer to current tree node.
         *  \return pointer to the current tree node
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   8.11.2021
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] virtual std::shared_ptr<IBinaryTreeNode> GetCurrentNode() const = 0;

        //-----------------------------------------------------------------------------
        /*! \brief Gets the pointer to tree's root node.
         *  \return pointer to the tree's root node
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   28.11.2021
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] virtual std::shared_ptr<IBinaryTreeNode> GetRootNode() const = 0;

        //-----------------------------------------------------------------------------
        /*! \brief Gets the pointer to the current node query data node.
        *  \return pointer to the current node query data node. nullptr if current node is not set.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   30.11.2021
        */
        //-----------------------------------------------------------------------------
        [[nodiscard]] virtual std::shared_ptr<IBinaryTreeQueryDataNode> GetCurrentNodeQueryDataNode() const = 0;

        //-----------------------------------------------------------------------------
        /*! \brief Gets the pointer to the current node's left child query data node.
        *  \return pointer to the current node's left child query data node. nullptr if current node is not set, or current node does not have a left child.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   30.11.2021
        */
        //-----------------------------------------------------------------------------
    	[[nodiscard]] virtual std::shared_ptr<IBinaryTreeQueryDataNode> GetCurrentNodeLeftChildQueryDataNode() const = 0;

        //-----------------------------------------------------------------------------
		/*! \brief Gets the pointer to the current node's right child query data node.
		*  \return pointer to the current node's right child query data node. nullptr if current node is not set, or current node does not have a right child.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   30.11.2021
		*/
		//-----------------------------------------------------------------------------
        [[nodiscard]] virtual std::shared_ptr<IBinaryTreeQueryDataNode> GetCurrentNodeRightChildQueryDataNode() const = 0;

        //-----------------------------------------------------------------------------
        /*! \brief Fills a container with pointers to node data in the order of depth-first traversal of this tree.
        *  \return pointers to node data from depth-first traversal.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   14.1.2022
        */
        //-----------------------------------------------------------------------------
        [[nodiscard]] virtual std::vector<std::shared_ptr<NodeDataWrapper>> GetTreeDataFromDepthFirstTraversal() const = 0;

        //-----------------------------------------------------------------------------
        /*! \brief Fills a container with pointers to node data in the order of breadth-first traversal of this tree.
        *  \return pointers to node data from breadth-first traversal.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   14.1.2022
        */
        //-----------------------------------------------------------------------------
        [[nodiscard]] virtual std::vector<std::shared_ptr<NodeDataWrapper>> GetTreeDataFromBreadthFirstTraversal() const = 0;

        /// @{
        /// \name Setters

    	//-----------------------------------------------------------------------------
        /*! \brief  Sets current node cursor to the root node.
         *  \return BinaryTreeErrorCode::NodeNotFound if tree is empty.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   28.11.2021
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] virtual BinaryTreeErrorCode SetRootAsCurrent() = 0;

        //-----------------------------------------------------------------------------
        /*! \brief  Sets current node cursor to the left child of current node.
         *  \return BinaryTreeErrorCode::CurrentNodeNotSet if current node is undefined, and BinaryTreeErrorCode::NodeNotFound if current node does not have a left child.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   30.11.2021
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] virtual BinaryTreeErrorCode SetCurrentNodeLeftChildAsCurrent() = 0;

        //-----------------------------------------------------------------------------
        /*! \brief  Sets current node cursor to the right child of current node.
         *  \return BinaryTreeErrorCode::CurrentNodeNotSet if current node is undefined, and BinaryTreeErrorCode::NodeNotFound if current node does not have a left child.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   30.11.2021
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] virtual BinaryTreeErrorCode SetCurrentNodeRightChildAsCurrent() = 0;

        //-----------------------------------------------------------------------------
        /*! \brief  Sets this implementation base data from another implementation instance.
         *  \param[in] other          other implementation to be copy constructed from.
         *  \return reference to this binary tree implementation.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   8.11.2021
         */
         //-----------------------------------------------------------------------------
        IBinaryTreeImplementation& SetBase(const IBinaryTreeImplementation& other)
        {
            m_TreeHeight = other.m_TreeHeight;
            m_TreeUUID = other.m_TreeUUID;
            m_NodeCount = other.m_NodeCount;
            m_IsSelfBalancing = other.m_IsSelfBalancing;

            return *this;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Computes tree height from complete nodes.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   30.11.2021
         */
         //-----------------------------------------------------------------------------
        virtual void SetHeightFromCompleteTree() = 0;

        //-----------------------------------------------------------------------------
        /*! \brief Sets the self-balancing flag of this tree implementation.
         *  \param[in] value            self-balancing flag to be set
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   4.12.2021
         */
        //-----------------------------------------------------------------------------
    	void SetSelfBalancing(const bool value)
    	{
            m_IsSelfBalancing = value;
    	}
    	
        /// @{
        /// \name Flags

        //-----------------------------------------------------------------------------
        /*! \brief IsBalanced flag for this binary tree implementation. 
         *  \return Returns false if total tree height is larger than minimum depth based on node count.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   1.11.2021
         */
         //----------------------------------------------------------------------------- 
        [[nodiscard]] bool IsBalanced() const
        {
            return m_TreeHeight < static_cast<size_t>(std::ceil(log2(m_NodeCount + 1) /*- 1*/ ));
        }

        //-----------------------------------------------------------------------------
        /*! \brief IsSelfBalancing flag for this binary tree implementation.
         *  \return Returns true if this tree implementation is self-balancing.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   4.12.2021
         */
         //----------------------------------------------------------------------------- 
    	[[nodiscard]] bool IsSelfBalancing() const
    	{
            return m_IsSelfBalancing;
    	}

        /// @{
        /// \name Helper Functionality

        //-----------------------------------------------------------------------------
        /*! \brief Prints this tree implementation's nodes and connectivity information.
         *  \return a string of debug print lines.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   27.11.2021
         */
        //-----------------------------------------------------------------------------
        [[nodiscard]] virtual std::string DebugPrint() const = 0;

        //-----------------------------------------------------------------------------
        /*! \brief Prints this tree implementation's nodes and connectivity information as a PlantUML input (https://www.planttext.com/).
         *  \return a string of plantUML print lines.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   1.12.2021
         *
         *   DISCLAIMER: The PlantUML plugin does not parse large trees!
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] virtual std::string PlantUMLPrint() const = 0;
    
    protected:

        /// @{
        /// \name Protected Operation Functionality 

    	//-----------------------------------------------------------------------------
        /*! \brief Rebalances this tree from the current node using single-step LeftRotate, RightRotate or double LeftRightRotate and RightLeftRotate operations.
         *
         *  \return BinaryTreeErrorCode::InternalError if an internal error occurs
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   18.1.2022
         *
         *   DISCLAIMER: this method assumes that the node set as current is the root of a balanced subtree.
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] virtual BinaryTreeErrorCode RebalanceFromCurrentNode() = 0;

        ///-----------------------------------------------------------------------------
		/// \brief Using current node X as rotation pivot (highest node), it is replaced by its right child node Z while \n
		///        the left child t23 of Z is then transferred to X as a right child, and both the right child t4 of Z   \n
		///        and the left child t1 of X keep their position.
		///
		/// \return BinaryTreeErrorCode::InternalError if an internal error occurs
		///
		/// \author M. Cavarga (MCInversion)
		/// \date   18.1.2022
		///
		///	\verbatim
		///	    Note: using notation from https://en.wikipedia.org/wiki/AVL_tree
        ///
        ///      ( X )                     ( Z )
        ///      /   \                     /   \
        ///     t1   ( Z )    ===>      ( X )   t4
        ///          /   \              /   \ 
        ///        t23   t4            t1   t23
        ///
        /// \endverbatim
	    ///
		///-----------------------------------------------------------------------------
        [[nodiscard]] virtual BinaryTreeErrorCode RotateLeftAtCurrentNode() = 0;

        ///-----------------------------------------------------------------------------
        /// \brief Using current node X as rotation pivot (highest node), it is replaced by its left child node Z while \n
        ///        the right child t23 of Z is then transferred to X as a left child, and both the right child t4 of X    \n
        ///        and the left child t1 of Z keep their position.
        ///
        /// \return BinaryTreeErrorCode::InternalError if an internal error occurs
        ///
        /// \author M. Cavarga (MCInversion)
        /// \date   18.1.2022
        ///
        ///	\verbatim
        ///	    Note: using notation from https://en.wikipedia.org/wiki/AVL_tree
        ///
        ///      ( X )                   ( Z )
        ///      /   \                   /   \
        ///   ( Z )   t4    ===>       t1   ( X )
        ///   /   \                         /   \
        ///  t1   t23                      t23   t4
        ///
        /// \endverbatim
        ///
        ///-----------------------------------------------------------------------------
        [[nodiscard]] virtual BinaryTreeErrorCode RotateRightAtCurrentNode() = 0;

        ///-----------------------------------------------------------------------------
        /// \brief Using current node X as rotation pivot (highest node).                                        \n
        ///        In step (I.), the right child Z of X is replaced by its left child node Y while               \n
        ///        the right child t3 of Y is then transferred to Z as a left child, and the left child t1 of X, \n
        ///        the left child t2 of Y, and the right child t4 of Z keep their position.                      \n
        ///        In step (II.), X is replaced by Y while transferring the left child t2 of Y to X as a right   \n
        ///        child, and t1, t3, and t4 keeping their positions.
        ///
        /// \return BinaryTreeErrorCode::InternalError if an internal error occurs
        ///
        /// \author M. Cavarga (MCInversion)
        /// \date   18.1.2022
        ///
        ///	\verbatim
        ///	    Note: using notation from https://en.wikipedia.org/wiki/AVL_tree
        ///
        ///     ( X )              (I.)         ( X )           (II.)            ( Y )
        ///     /    \                         /    \                            /   \
        ///    t1    ( Z )      ======>      t1    ( Y )       =======>       ( X )  ( Z )
        ///          /    \                        /   \                     /   \   /   \
        ///        ( Y )   t4                     t2   ( Z )                t1   t2  t3   t4
        ///        /   \                               /   \
        ///       t2   t3                             t3   t4
        ///
        /// \endverbatim
        ///
        ///-----------------------------------------------------------------------------
        [[nodiscard]] virtual BinaryTreeErrorCode RotateLeftRightAtCurrentNode() = 0;

        ///-----------------------------------------------------------------------------
        /// \brief Using current node X as rotation pivot (highest node).                                        \n
        ///        In step (I.), the left child Z of X is replaced by its right child node Y while               \n
        ///        the left child t2 of Y is then transferred to Z as a right child, and the left child t1 of Z, \n
        ///        the right child t3 of Y, and the right child t4 of X keep their position.                     \n
        ///        In step (II.), X is replaced by Y while transferring the right child t3 of Y to X as a left   \n
        ///        child, and t1, t2, and t4 keeping their positions.
        ///
        /// \return BinaryTreeErrorCode::InternalError if an internal error occurs
        ///
        /// \author M. Cavarga (MCInversion)
        /// \date   18.1.2022
        ///
        ///	\verbatim
        ///	    Note: using notation from https://en.wikipedia.org/wiki/AVL_tree
        ///
        ///        ( X )           (I.)           ( X )       (II.)           ( Y )
        ///       /    \                         /    \                       /   \
        ///    ( Z )     t4      ======>      ( Y )   t4     =======>      ( Z )  ( X )
        ///    /   \                          /   \                        /  \   /   \
        ///   t1   ( Y )                   ( Z )   t3                    t1   t2  t3   t4
        ///        /   \                   /   \
        ///       t2   t3                 t1   t2
        ///
        /// \endverbatim
        ///
        ///-----------------------------------------------------------------------------
        [[nodiscard]] virtual BinaryTreeErrorCode RotateRightLeftAtCurrentNode() = 0;

        //-----------------------------------------------------------------------------
        /*! \brief Updates balance factor from current node up to root node after insertion/deletion operation.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   23.1.2022
         */
         //-----------------------------------------------------------------------------
        virtual void UpdateNodeHeightsAndBalanceFactorsUpToRoot() = 0;

    	//
        // =============== Data ========================================================
        //

        size_t m_TreeHeight = 0;       //>! Tree Height (computed from max node depth)
        size_t m_NodeCount = 0;        //>! Tree node count

        UUID m_TreeUUID = GUID_NULL;   //>! Tree UUID for verifying whether a BinaryTreeNode belongs to this tree.

        bool m_IsSelfBalancing = false; //>! Self-balancing flag. If true, the tree with this implementation balances itself upon each insertion/deletion operation.
    };

} // Symplektis::DataReps