/*! \file  IterativeBinaryTreeNode.h
 *  \brief A generic node object for IterativeBinaryTreeImplementation, i.e.: \n
 *         contains iterator references to child node instances stored in an array.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   1.11.2021
 *
 */

#pragma once

#include "BinaryTreeHelperTypes.h"
#include "IBinaryTreeNode.h"

namespace Symplektis::DataReps
{
    //=============================================================================
    /// \class IterativeBinaryTreeNode
    /// \brief A Iterative extension of IBinaryTreeNode interface for binary tree node objects.
    ///        Contains iterator references to child node instances stored in an array.
    ///
    /// \ingroup DATA_REPS
    ///
    /// \author M. Cavarga (MCInversion)
    /// \date   1.11.2021
    //=============================================================================
	class IterativeBinaryTreeNode final
		: public IBinaryTreeNode
	{
	public:
        /// @{
		/// \name Default Special Members

        /// \brief Default constructor.
        IterativeBinaryTreeNode() = default;

        /// \brief Default move constructor.
        IterativeBinaryTreeNode(IterativeBinaryTreeNode&& other) = default;

        /// \brief Default move-assignment operator.
        IterativeBinaryTreeNode& operator=(IterativeBinaryTreeNode&& other) = default;

        /// \brief Default destructor.
        ~IterativeBinaryTreeNode() override = default;
		
        /// @{
        /// \name Constructors

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeNode::IBinaryTreeNode
        //-----------------------------------------------------------------------------
        IterativeBinaryTreeNode(const UUID& treeUuid, const std::shared_ptr<IBinaryTreeQueryDataNode>& queryDataNode)
	        : IBinaryTreeNode(treeUuid, queryDataNode) { }
		
        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeNode::IBinaryTreeNode
        //-----------------------------------------------------------------------------
        explicit IterativeBinaryTreeNode(const UUID& treeUuid)
            : IBinaryTreeNode(treeUuid) { }

        //-----------------------------------------------------------------------------
        /*! \brief Copy constructor.
         *  \param[in] other          other node to be copy constructed from.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   1.11.2021
         */
         //-----------------------------------------------------------------------------
        IterativeBinaryTreeNode(const IterativeBinaryTreeNode& other);

        /// @{
        /// \name Operators

        //-----------------------------------------------------------------------------
        /*! \brief Copy-assignment operator.
         *  \param[in] other          other node interface to be copy constructed from.
         *  \return reference to this binary tree node.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   27.11.2021
         */
         //-----------------------------------------------------------------------------
        IterativeBinaryTreeNode& operator=(const IterativeBinaryTreeNode& other);
		
        /// @{
        /// \name Setters

        //-----------------------------------------------------------------------------
        /*! \brief Tries to set left m_LeftChildId.
         *  \param[in] newLeftChildNodeId            index of the potential left child node in node array.
         *  \return BinaryNodeErrorCode::LeftNodeExists if this node already has a left child.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   30.11.2021
         *
         *   WARNING: NodeArrayIndex is valid only if the node instance has already been inserted to iterative tree implementation's m_NodeArray.
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] BinaryNodeErrorCode SetLeftChildId(const NodeArrayIndex& newLeftChildNodeId);


        //-----------------------------------------------------------------------------
        /*! \brief Force-sets m_LeftChildId without verification. Previous left child node is marked for deletion (m_MarkedForDelete).
         *  \param[in] insertedLeftChildNodeId            index of the inserted left child node in node array.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   30.11.2021
         *
		 *   WARNING: NodeArrayIndex is valid only if the node instance has already been inserted to iterative tree implementation's m_NodeArray.
         */
         //-----------------------------------------------------------------------------
        void ForceSetLeftChildId(const NodeArrayIndex& insertedLeftChildNodeId);


        //-----------------------------------------------------------------------------
        /*! \brief Tries to set right m_RightChildId.
         *  \param[in] newRightChildNodeId            index of the potential left child node in node array.
         *  \return BinaryNodeErrorCode::RightNodeExists if this node already has a right child.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   1.11.2021
         *
         *   WARNING: NodeArrayIndex is valid only if the node instance has already been inserted to iterative tree implementation's m_NodeArray.
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] BinaryNodeErrorCode SetRightChildId(const NodeArrayIndex& newRightChildNodeId);


        //-----------------------------------------------------------------------------
        /*! \brief Force-sets m_RightChildId without verification. Previous right child node is marked for deletion (m_MarkedForDelete).
         *  \param[in] insertedRightChildNodeId             index of the inserted right child node in node array.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   1.11.2021
         *   
         *   WARNING: NodeArrayIndex is valid only if the node instance has already been inserted to iterative tree implementation's m_NodeArray.
         */
         //-----------------------------------------------------------------------------
        void ForceSetRightChildId(const NodeArrayIndex& insertedRightChildNodeId);

        //-----------------------------------------------------------------------------
        /*! \brief Sets this node's m_MarkedForDelete flag.
         *  \param[in] value            bool value for m_MarkedForDelete flag.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   1.11.2021
         */
         //-----------------------------------------------------------------------------
        void SetMarkedForDelete(const bool value)
        {
            m_MarkedForDelete = value;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Sets the parent node index.
         *  \param[in] parentNodeId            index of the set parent node.
         *  \return BinaryNodeErrorCode::NodeArrayIndexError if parent index is invalid.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   4.12.2021
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] BinaryNodeErrorCode SetParentNodeId(const NodeArrayIndex& parentNodeId);

        //-----------------------------------------------------------------------------
        /*! \brief Force-sets the parent node index.
         *  \param[in] parentNodeId            index of the set parent node.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   20.1.2022
         */
         //-----------------------------------------------------------------------------
        void ForceSetParentNodeId(const NodeArrayIndex& parentNodeId);
		
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
        /*! \brief Left child m_NodeArray index getter.
         *  \return NodeArrayIndex of left child node.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   30.11.2021
         */
        //-----------------------------------------------------------------------------
        [[nodiscard]] NodeArrayIndex LeftChildId() const
        {
            return m_LeftChildId;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Right child m_NodeArray index getter.
         *  \return NodeArrayIndex of right child node.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   30.11.2021
         */
        //-----------------------------------------------------------------------------
        [[nodiscard]] NodeArrayIndex RightChildId() const
        {
            return m_RightChildId;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Parent node m_NodeArray index getter.
         *  \return NodeArrayIndex of this node's parent node.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   5.12.2021
         */
         //-----------------------------------------------------------------------------
		[[nodiscard]] NodeArrayIndex ParentNodeId() const
        {
            return m_ParentId;
        }

        /// @{
        /// \name Flags

        //-----------------------------------------------------------------------------
        /*! \brief Deletion flag for Iterative binary tree implementations.
         *  \return true if this node is marked for deletion.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   1.11.2021
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] bool IsMarkedForDelete() const
        {
            return m_MarkedForDelete;
        }

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeNode::HasLeftChild
        //-----------------------------------------------------------------------------
        [[nodiscard]] bool HasLeftChild() const override
        {
            return m_LeftChildId != NULL_NODE_INDEX;
        }

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeNode::HasRightChild
        //-----------------------------------------------------------------------------
        [[nodiscard]] bool HasRightChild() const override
        {
            return  m_RightChildId != NULL_NODE_INDEX;
        }

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeNode::HasParent
        //-----------------------------------------------------------------------------
		[[nodiscard]] bool HasParent() const override
        {
            return m_ParentId != NULL_NODE_INDEX;
        }

        /// @{
        /// \name Helper Functionality

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeNode::DebugPrint
        //-----------------------------------------------------------------------------
        [[nodiscard]] std::string DebugPrint() const override;

        //-----------------------------------------------------------------------------
        /*! \brief Prints this tree node's data node content as PlantUML class
         *  \param[in] classBracketContent          string containing class bracket content, e.g.: "(L, #6fcaed)" for left child node with hex color code #6fcaed.
         *  \param[in] nodeArrayIndex               index of this node in node array.
         *  \return a string of debug print lines.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   4.12.2021
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] std::string PlantUMLPrint(const std::string& classBracketContent, const int& nodeArrayIndex) const
        {
            std::string result = "class \"";
            result += Util::GetUUIDString(m_NodeUUID) + "\" << (" + classBracketContent + ") >> {\n";

        	result += "    -NodeArrayIndex = " + std::to_string(nodeArrayIndex) + "\n";
            result += "    ~Height = " + std::to_string(m_Height) + "\n";
            result += "    ~BalanceFactor = " + std::to_string(m_BalanceFactor) + "\n";
            result += "    --\n"; // separator
        	
            result += m_DataNode->PlantUMLPrint();
            result += "}\n\n";

            return result;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Prints this tree node's data node content as PlantUML class. No balance factor is printed.
         *  \param[in] classBracketContent          string containing class bracket content, e.g.: "(L, #6fcaed)" for left child node with hex color code #6fcaed.
         *  \param[in] nodeArrayIndex               index of this node in node array.
         *  \return a string of debug print lines.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   1.12.2021
         */
         //-----------------------------------------------------------------------------
		[[nodiscard]] std::string PlantUMLPrintBalanced(const std::string& classBracketContent, const int& nodeArrayIndex) const
        {
            std::string result = "class \"";
            result += Util::GetUUIDString(m_NodeUUID) + "\" << (" + classBracketContent + ") >> {\n";

            result += "    -NodeArrayIndex = " + std::to_string(nodeArrayIndex) + "\n";
            result += "    ~Height = " + std::to_string(m_Height) + "\n";
            result += "    ~BalanceFactor = " + std::to_string(m_BalanceFactor) + "\n";
            result += "    --\n"; // separator
        	
            result += m_DataNode->PlantUMLPrint();
            result += "}\n\n";

            return result;
        }
	
	private:

        //
        // =============== Data ========================================================
        //

        NodeArrayIndex m_LeftChildId = NULL_NODE_INDEX;     //>! left child node index
        NodeArrayIndex m_RightChildId = NULL_NODE_INDEX;    //>! right child node index

        NodeArrayIndex m_ParentId = NULL_NODE_INDEX;        //>! parent node index

        bool m_MarkedForDelete = false;                     //>! relevant for Iterative implementations array cleanup procedure.

        //size_t m_Height = 0;                                //>! tree node height.
	};
	
} // Symplektis::DataReps

