/*! \file  IBinaryTreeNode.h
 *  \brief A generic node object interface for binary trees.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   31.10.2021
 *
 */

#pragma once

#include "IBinaryTreeQueryDataNode.h"
#include "../Symplekt_UtilityGeneral/UUIDTools.h"

#include <memory>

namespace Symplektis::DataReps
{
    //=============================================================================
    /// \class IBinaryTreeNode
    /// \brief A node class interface for generic BinaryTree objects.
    ///
    /// \ingroup DATA_REPS
    ///
    /// \author M. Cavarga (MCInversion)
    /// \date   1.11.2021
    //=============================================================================
    class IBinaryTreeNode
    {
    public:

        /// @{
        /// \name Default Special Members

    	/// \brief Default constructor.
        IBinaryTreeNode() = default;

        /// \brief Default move constructor.
        IBinaryTreeNode(IBinaryTreeNode&& other) = default;

        /// \brief Default move-assignment operator.
        IBinaryTreeNode& operator=(IBinaryTreeNode&& other) = default;

        /// \brief Default destructor.
        virtual ~IBinaryTreeNode() = default;

        /// @{
        /// \name Constructors

        //-----------------------------------------------------------------------------
        /*! \brief Construct a node with a given tree ID, a query data node, and generate a new UUID for this node.
         *  \param[in] treeUuid            tree UUID
         *  \param[in] queryDataNode       this node's query data node.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   29.11.2021
         */
         //-----------------------------------------------------------------------------
    	IBinaryTreeNode(
            const UUID& treeUuid, 
            const std::shared_ptr<IBinaryTreeQueryDataNode>& queryDataNode)
	            : IBinaryTreeNode(treeUuid)
    	{
            SetQueryDataNode(queryDataNode);
    	}
    	
        //-----------------------------------------------------------------------------
        /*! \brief Construct an empty node with a given tree ID, and generate a new UUID for this node.
         *  \param[in] treeUuid            tree UUID
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   1.11.2021
         */
        //-----------------------------------------------------------------------------
        explicit IBinaryTreeNode(const UUID& treeUuid)
    		: m_TreeUUID(treeUuid)
        {
            m_NodeUUID = Util::CreateUUID();
        }
    	
        //-----------------------------------------------------------------------------
        /*! \brief Copy constructor.
         *  \param[in] other          other node interface to be copy constructed from.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   1.11.2021
         */
         //-----------------------------------------------------------------------------
        IBinaryTreeNode(const IBinaryTreeNode& other)
        {
            SetBase(other);
        }

        /// @{
        /// \name Operators

        //-----------------------------------------------------------------------------
        /*! \brief Copy-assignment operator.
         *  \param[in] other          other node interface to be copy constructed from.
         *  \return reference to this binary tree node interface.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   1.11.2021
         */
         //-----------------------------------------------------------------------------
        IBinaryTreeNode& operator=(const IBinaryTreeNode& other)
        {
            if (this == &other)
                return *this;
        	
            SetBase(other);
            return *this;
        }
    	
        /// @{
        /// \name Deleters

        //-----------------------------------------------------------------------------
        /*! \brief Force-deletes left child node.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   1.11.2021
         *
         */
         //-----------------------------------------------------------------------------
        virtual void DeleteLeft() = 0;

        //-----------------------------------------------------------------------------
        /*! \brief Force-deletes right child node.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   1.11.2021
         *
         */
         //-----------------------------------------------------------------------------
        virtual void DeleteRight() = 0;

        //-----------------------------------------------------------------------------
        /*! \brief Force-deletes both child nodes.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   1.11.2021
         *
         */
         //-----------------------------------------------------------------------------
        virtual void DeleteChildren() = 0;

        //-----------------------------------------------------------------------------
        /*! \brief Force-deletes parent node.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   5.12.2021
         *
         */
         //-----------------------------------------------------------------------------
        virtual void DeleteParent() = 0;

        /// @{
        /// \name Setters

        //-----------------------------------------------------------------------------
        /*! \brief Node height setter.
         *  \param[in] height         height to be set
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   23.1.2022
         */
         //-----------------------------------------------------------------------------
        void SetHeight(const size_t& height)
        {
            m_Height = height;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Node m_IsLeaf flag setter
         *  \param[in] value        m_IsLeaf flag value to be set.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   28.11.2021
         */
         //-----------------------------------------------------------------------------
    	void SetIsLeaf(const bool value)
        {
            m_IsLeaf = value;
        }
    	
        //-----------------------------------------------------------------------------
        /*! \brief Query data node setter.
         *  \param[in] dataNode         pointer to dataNode instance to be set.
         *  \return Reference to this node.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   27.11.2021
         */
         //-----------------------------------------------------------------------------
        IBinaryTreeNode& SetQueryDataNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& dataNode)
        {
            m_DataNode = dataNode;
            return *this;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Sets the value of this node's balance factor.
         *  \param[in] value         balance factor value to be set.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   19.1.2022
         *
         */
         //-----------------------------------------------------------------------------
    	void SetBalanceFactor(const int& value)
        {
            m_BalanceFactor = value;
        }


        //-----------------------------------------------------------------------------
        /*! \brief  Sets this binary tree node's base data from another node instance.
         *  \param[in] other          other node interface to be copy constructed from.
         *  \return reference to this binary tree node interface.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   27.11.2021
         */
         //-----------------------------------------------------------------------------
        IBinaryTreeNode& SetBase(const IBinaryTreeNode& other)
        {
            m_TreeUUID = other.m_TreeUUID;
            m_NodeUUID = other.m_NodeUUID;
            m_IsLeaf = other.m_IsLeaf;
            m_DataNode = other.m_DataNode;
            m_Height = other.m_Height;
            m_BalanceFactor = other.m_BalanceFactor;

            return *this;
        }

    	/// @{
        /// \name Getters

        //-----------------------------------------------------------------------------
		/*! \brief Node UUID getter.
		 *  \return this node's UUID.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   1.11.2021
		 */
		 //-----------------------------------------------------------------------------
    	[[nodiscard]] UUID GetNodeUUID() const
        {
            return m_NodeUUID;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Tree UUID getter.
         *  \return this node's tree UUID.
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
        /*! \brief Query data node getter.
         *  \return this node's query data node.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   27.11.2021
         */
         //-----------------------------------------------------------------------------
    	[[nodiscard]] std::shared_ptr<IBinaryTreeQueryDataNode> GetQueryDataNode() const
    	{
            return m_DataNode;
    	}

        //-----------------------------------------------------------------------------
		/*! \brief Node balance factor getter.
		 *  \return this node's balance factor, i.e.: Height(leftSubtree) - Height(rightSubtree)
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   19.1.2022
		 */
		 //-----------------------------------------------------------------------------
    	[[nodiscard]] int GetBalanceFactor() const
        {
            return m_BalanceFactor;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Node height getter.
         *  \return this node's height, i.e.: the height of subtree with rooted at this node.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   23.1.2022
         */
         //-----------------------------------------------------------------------------
    	[[nodiscard]] size_t GetHeight() const
        {
            return m_Height;
        }
    	
        /// @{
		/// \name Flags

        //-----------------------------------------------------------------------------
        /*! \brief "Is a leaf" flag.
         *  \return true if this node is a leaf
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   1.11.2021
         */
        //-----------------------------------------------------------------------------
        [[nodiscard]] bool IsLeaf() const
        {
            return m_IsLeaf;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Flag for this node having left child.
         *  \return true if this node has a left child.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   5.11.2021
         */
         //-----------------------------------------------------------------------------
         [[nodiscard]] virtual bool HasLeftChild() const = 0;

        //-----------------------------------------------------------------------------
        /*! \brief Flag for this node having right child.
         *  \return true if this node has a right child.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   5.11.2021
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] virtual bool HasRightChild() const = 0;

        //-----------------------------------------------------------------------------
        /*! \brief Flag for this node having a parent node.
         *  \return true if this node has a parent.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   4.12.2021
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] virtual bool HasParent() const = 0;

        /// @{
        /// \name Data Node Functionality

        //-----------------------------------------------------------------------------
        /*! \brief Evaluates whether given query data "intersects" (set-wise) this node's data node content.
         *  \param[in] queryData        query data for comparison.
         *  \return true if given queryData intersects this node data.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   24.11.2021
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] virtual bool IntersectsData(const std::shared_ptr<NodeDataWrapper>& queryData) const
        {
            if (!m_DataNode)
                return false;

            return m_DataNode->IntersectsData(queryData);
        }

        /// @{
        /// \name Helper Functionality

        //-----------------------------------------------------------------------------
        /*! \brief Prints this tree node's data node content and connectivity information
         *  \return a string of debug print lines.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   27.11.2021
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] virtual std::string DebugPrint() const = 0;
    
    protected:

        //
        // =============== Data ========================================================
        //
    	
        //size_t m_Depth{ 0 };            //>! Tree node depth from root node.
        size_t m_Height{ 1 };           //>! Tree node height
        int m_BalanceFactor{ 0 };       //>! A balance factor value for this node equal to: Height(leftSubtree) - Height(rightSubtree)

        bool m_IsLeaf = true;           //>! true if this node is a leaf node (has no children)

        UUID m_TreeUUID = GUID_NULL;    //>! Tree UUID for verifying whether this BinaryTreeNode belongs to a tree.
        UUID m_NodeUUID = GUID_NULL;    //>! Node UUID for identifying this node.

        //>! Data node instance. A "mirror node" in the data context, holding and giving access to query data.
        std::shared_ptr<IBinaryTreeQueryDataNode> m_DataNode;
    };

} // Symplektis::DataReps