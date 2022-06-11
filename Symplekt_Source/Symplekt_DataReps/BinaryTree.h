/*! \file  BinaryTree.h
 *  \brief A generic binary tree interface.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   29.10.2021
 *
 */

#pragma once

#include "IBinaryTreeNode.h"
#include "IBinaryTreeImplementation.h"

#include <memory>
#include <string>

namespace Symplektis::DataReps
{
	//=============================================================================
	/// \class BinaryTree
	/// \brief A base class for a binary search tree witch a changeable implementation.
	///
	/// \ingroup DATA_REPS
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   21.11.2021
	//=============================================================================
	class BinaryTree
	{
	public:
		/// @{
		/// \name Default Special Members

		/// \brief Default constructor.
		BinaryTree() = default;

		/// \brief Default copy constructor.
		BinaryTree(const BinaryTree& other) = default;

		/// \brief Default move constructor.
		BinaryTree(BinaryTree&& other) = default;

		/// \brief Default copy-assignment operator.
		BinaryTree& operator=(const BinaryTree& other) = default;

		/// \brief Default move-assignment operator.
		BinaryTree& operator=(BinaryTree&& other) = default;

		/// \brief Default destructor.
		virtual ~BinaryTree() = default;

		/// @{
		/// \name Constructors

		//-----------------------------------------------------------------------------
		/*! \brief Constructor. Initialize this BinaryTree from implementation type.
		*   \param[in] implType           implementation type enumerator.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   23.11.2021
		*/
		//-----------------------------------------------------------------------------
		explicit BinaryTree(const BinaryTreeImplementationType& implType)
		{
			InternalSetAndInitImplementationType(implType);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Constructor. Initialize this BinaryTree from implementation type, and isSelfBalancing flag.
		*   \param[in] implType           implementation type enumerator.
		*   \param[in] isSelfBalancing    true if this tree is to be balanced while built.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   23.11.2021
		*/
		//-----------------------------------------------------------------------------
		BinaryTree(const BinaryTreeImplementationType& implType, const bool& isSelfBalancing)
		{
			InternalSetAndInitImplementationType(implType, isSelfBalancing);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Constructor. Initialize this BinaryTree with a given name string.
		*   \param[in] treeName          name string of this tree.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   23.11.2021
		*/
		//-----------------------------------------------------------------------------
		explicit BinaryTree(std::string& treeName)
			: m_Name(treeName)
		{
		}

		//-----------------------------------------------------------------------------
		/*! \brief Constructor. Initialize this BinaryTree from name string, implementation type, and isSelfBalancing flag.
		*   \param[in] treeName           name string of this tree.
		*   \param[in] implType           implementation type enumerator.
		*   \param[in] isSelfBalancing    true if this tree is to be balanced while built.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   23.11.2021
		*/
		//-----------------------------------------------------------------------------
		BinaryTree(std::string& treeName, const BinaryTreeImplementationType& implType, const bool& isSelfBalancing)
			: m_Name(treeName)
		{
			InternalSetAndInitImplementationType(implType, isSelfBalancing);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Constructor. Initialize this BinaryTree from name string, and implementation type.
		*   \param[in] treeName           name string of this tree.
		*   \param[in] implType           implementation type enumerator.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   23.11.2021
		*/
		//-----------------------------------------------------------------------------
		BinaryTree(std::string& treeName, const BinaryTreeImplementationType& implType)
			: m_Name(treeName)
		{
			InternalSetAndInitImplementationType(implType);
		}
		
		/// @{
		/// \name Functionality

		//-----------------------------------------------------------------------------
		/*! \brief Builds this tree from given data, using m_TreeImplementation and sets m_IsValid state.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.11.2021
		*/
		//-----------------------------------------------------------------------------
		void BuildFromData()
		{
			const auto treeErrorCode = InternalBuildFromData();
			InternalSetIsValid(treeErrorCode == BinaryTreeErrorCode::OK);
		}

		
		/// @{
		/// \name Setters

		//-----------------------------------------------------------------------------
		/*! \brief Set m_IsSelfBalancing flag.
		 *  \param[in] value       bool value to be set.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   21.11.2021
		*/
		//-----------------------------------------------------------------------------
		void SetSelfBalancing(const bool value) const
		{
			if (!m_TreeImplementation)
				return;
			
			m_TreeImplementation->SetSelfBalancing(value);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Set implementation type, and initialize implementation if necessary.
		 *  \param[in] implType       implementation type to be set
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   21.11.2021
		*/
		//-----------------------------------------------------------------------------
		void SetAndInitImplementationType(const BinaryTreeImplementationType& implType);

		/// @{
		/// \name Getters

		//-----------------------------------------------------------------------------
		/*! \brief Implementation type const getter.
		 *  \return const reference to this tree's implementation type
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   21.11.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] const BinaryTreeImplementationType& GetImplementationType() const
		{
			return m_ImplementationType;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Implementation type getter.
		 *  \return reference to this tree's implementation type
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   21.11.2021
		*/
		//-----------------------------------------------------------------------------
		BinaryTreeImplementationType& GetImplementationType()
		{
			return m_ImplementationType;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Getter for a container of node data wrapper pointers from depth-first tree traversal.
		 *  \return a container of node data wrapper pointers
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   14.1.2022
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] std::vector<std::shared_ptr<NodeDataWrapper>> GetTreeDataFromDepthFirstTraversal() const;

		//-----------------------------------------------------------------------------
		/*! \brief Getter for a container of node data wrapper pointers from breadth-first tree traversal.
		 *  \return a container of node data wrapper pointers
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   14.1.2022
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] std::vector<std::shared_ptr<NodeDataWrapper>> GetTreeDataFromBreadthFirstTraversal() const;

		/// @{
		/// \name Flags

		//-----------------------------------------------------------------------------
		/*! \brief Flag for self-balancing construction of this binary tree.
		 *  \return true if this tree is self-balancing.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   21.11.2021
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] bool IsSelfBalancing() const
		{
			if (!m_TreeImplementation)
				return false;
			
			return m_TreeImplementation->IsSelfBalancing();
		}

		//-----------------------------------------------------------------------------
		/*! \brief Whether this tree is balanced, i.e.: its balance factor BF at root is from set {-1, 0, 1}.
		 *  \return true if this tree is balanced.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   17.1.2022
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] bool IsBalanced() const
		{
			if (!m_TreeImplementation)
				return false;

			return m_TreeImplementation->IsBalanced();
		}

		//-----------------------------------------------------------------------------
		/*! \brief Empty identifier for this tree's implementation (based on node count)
		 *  \return true if this tree has no nodes.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   21.11.2021
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] bool IsEmpty() const
		{
			return (m_TreeImplementation->GetNodeCount() == 0);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Returns the valid flag set after successful construction of the binary tree.
		 *  \return true if this tree is valid.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   27.11.2021
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] bool IsValid() const
		{
			return m_IsValid;
		}

		/// @{
		/// \name Helper Functionality

		//-----------------------------------------------------------------------------
		/*! \brief Prints this tree's nodes and connectivity information.
		 *  \return a string of debug print lines.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   21.11.2021
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] std::string DebugPrint() const;

		//-----------------------------------------------------------------------------
		/*! \brief Prints the tree implementation's nodes and connectivity information as a PlantUML input (https://www.planttext.com/).
		 *  \return a string of plantUML print lines.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   1.12.2021
		 *
		 *   DISCLAIMER: The PlantUML plugin does not parse large trees!
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] std::string PlantUMLPrint() const;

		//-----------------------------------------------------------------------------
		/*! \brief Tree name getter.
		 *  \return a name string of this tree.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   21.11.2021
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] std::string GetTreeName() const
		{
			return m_Name;
		}
	
	protected:

		/// @{
		/// \name Internal Initializers

		//-----------------------------------------------------------------------------
		/*! \brief Set implementation type, and initialize implementation with a new UUID.
		 *  \param[in] implType       implementation type to be set
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   23.11.2021
		*/
		//-----------------------------------------------------------------------------
		void InternalSetAndInitImplementationType(const BinaryTreeImplementationType& implType);

		//-----------------------------------------------------------------------------
		/*! \brief Set implementation type, and initialize implementation with a new UUID.
		*   \param[in] implType            implementation type to be set.
		*   \param[in] isSelfBalancing     self-balancing flag to be set.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   4.12.2021
		*/
		//-----------------------------------------------------------------------------
		void InternalSetAndInitImplementationType(const BinaryTreeImplementationType& implType, const bool isSelfBalancing);

		//-----------------------------------------------------------------------------
		/*! \brief Set implementation type, and initialize implementation with a given UUID.
		*   \param[in] implType       implementation type to be set.
		*   \param[in] treeUUID       UUID of the implementation to be initialized.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   23.11.2021
		*/
		//-----------------------------------------------------------------------------
		void InternalSetAndInitImplementationTypeWithUUID(const BinaryTreeImplementationType& implType, const UUID& treeUUID);

		//-----------------------------------------------------------------------------
		/*! \brief Set implementation type, and initialize implementation with a new UUID.
		*   \param[in] implType            implementation type to be set.
		*   \param[in] treeUUID            UUID of the implementation to be initialized.
		*   \param[in] isSelfBalancing     self-balancing flag to be set.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   4.12.2021
		*/
		//-----------------------------------------------------------------------------
		void InternalSetAndInitImplementationType(const BinaryTreeImplementationType& implType, const UUID& treeUUID, const bool isSelfBalancing);

		//-----------------------------------------------------------------------------
		/*! \brief Builds this tree from given data, using m_TreeImplementation
		 *  \return tree error code.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   21.11.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] virtual BinaryTreeErrorCode InternalBuildFromData() = 0;
		
		/// @{
		/// \name Internal Functionality
		
		//-----------------------------------------------------------------------------
		/*! \brief Tries to insert a new node with a given data node at m_TreeImplementation's m_CurrentNode. Left node is prioritized if current node is a leaf.
		 *  \param[in] newDataNode           data node to be inserted
		 *  \return BinaryTreeErrorCode::NodeSaturated if m_CurrentNode already has both children, and BinaryTreeErrorCode::InternalError if implementation is not found.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.11.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] BinaryTreeErrorCode InternalInsertNodeAsDataNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& newDataNode) const;

		//-----------------------------------------------------------------------------
		/*! \brief Tries to insert a new left node with a given data node at m_TreeImplementation's m_CurrentNode.
		 *  \param[in] newLeftDataNode           data node to be inserted
		 *  \return BinaryTreeErrorCode::LeftNodeExists if there's already a left child, and BinaryTreeErrorCode::InternalError if implementation is not found.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.11.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] BinaryTreeErrorCode InternalInsertLeftNodeAsDataNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& newLeftDataNode) const;

		//-----------------------------------------------------------------------------
		/*! \brief Tries to insert a new right node with a given data node at m_TreeImplementation's m_CurrentNode.
		 *  \param[in] newRightDataNode           data node to be inserted
		 *  \return BinaryTreeErrorCode::RightNodeExists if there's already a right child, and BinaryTreeErrorCode::InternalError if implementation is not found.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   27.11.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] BinaryTreeErrorCode InternalInsertRightNodeAsDataNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& newRightDataNode) const;

		//-----------------------------------------------------------------------------
		/*! \brief Force-inserts a new left child node as data node at m_TreeImplementation's m_CurrentNode. Previous children of m_CurrentNode are marked for deletion.
		 *  \param[in] insertedLeftDataNode            data node to be inserted
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   27.11.2021
		 *
		 *   Be careful, this method erases all previous children
		 */
		 //-----------------------------------------------------------------------------
		void InternalForceInsertLeftNodeAsDataNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& insertedLeftDataNode) const;

		//-----------------------------------------------------------------------------
		/*! \brief Force-inserts a new right child node as data node at m_TreeImplementation's m_CurrentNode. Previous left children of m_CurrentNode are marked for deletion.
		 *  \param[in] insertedRightDataNode            data node to be inserted
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   27.11.2021
		 *
		 *   Be careful, this method erases all previous children
		 */
		 //-----------------------------------------------------------------------------
		void InternalForceInsertRightNodeAsDataNode(const std::shared_ptr<IBinaryTreeQueryDataNode>& insertedRightDataNode) const;

		/// @{
		/// \name Internal Getters

		//-----------------------------------------------------------------------------
		/*! \brief Gets the (non-const) shared pointer to current tree node.
		 *  \return a shared_ptr to the current node.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   27.11.2021
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] std::shared_ptr<IBinaryTreeNode> InternalGetCurrentNode() const;

		//-----------------------------------------------------------------------------
		/*! \brief Gets the (non-const) shared pointer to root tree node.
		 *  \return a shared_ptr to the root node.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   28.11.2021
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] std::shared_ptr<IBinaryTreeNode> InternalGetRootNode() const;

		/// @{
		/// \name Internal Setters

		//-----------------------------------------------------------------------------
		/*! \brief  Sets current node cursor to the root node.
		 *  \return BinaryTreeErrorCode::NodeNotFound if tree is empty.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   28.11.2021
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] BinaryTreeErrorCode InternalSetRootAsCurrent() const;

		//-----------------------------------------------------------------------------
		/*! \brief  Sets current node cursor to the left child node of the current node (if set).
		 *  \return BinaryTreeErrorCode::CurrentNodeNotSet if current node is undefined, and BinaryTreeErrorCode::NodeNotFound if current node does not have a left child.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   30.11.2021
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] BinaryTreeErrorCode InternalSetCurrentNodeLeftChildAsCurrent() const;

		//-----------------------------------------------------------------------------
		/*! \brief  Sets current node cursor to the right child node of the current node (if set).
		 *  \return BinaryTreeErrorCode::CurrentNodeNotSet if current node is undefined, and BinaryTreeErrorCode::NodeNotFound if current node does not have a right child.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   30.11.2021
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] BinaryTreeErrorCode InternalSetCurrentNodeRightChildAsCurrent() const;

		//-----------------------------------------------------------------------------
		/*! \brief  Gets the current node's query data node object (if current node is set).
		 *  \return pointer to the current node's left child query data node. nullptr if current node is not set, or current node does not have a left child.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   30.11.2021
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] std::shared_ptr<IBinaryTreeQueryDataNode> InternalGetCurrentNodeQueryDataNode() const;

		//-----------------------------------------------------------------------------
		/*! \brief  Gets the current node's left child's query data node object (if current node is set and if it has a left child).
		 *  \return pointer to the current node's left child query data node. nullptr if current node is not set, or current node does not have a left child.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   30.11.2021
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] std::shared_ptr<IBinaryTreeQueryDataNode> InternalGetCurrentNodeLeftChildQueryDataNode() const;

		//-----------------------------------------------------------------------------
		/*! \brief  Gets the current node's left child's query data node object (if current node is set and if it has a left child).
		 *  \return pointer to the current node's right child query data node. nullptr if current node is not set, or current node does not have a right child.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   30.11.2021
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] std::shared_ptr<IBinaryTreeQueryDataNode> InternalGetCurrentNodeRightChildQueryDataNode() const;
		
		//-----------------------------------------------------------------------------
		/*! \brief Sets the validity state of this tree upon successful/unsuccessful construction.
		 *  \param[in] value       validity value to be set.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   27.11.2021
		 */
		 //-----------------------------------------------------------------------------
		void InternalSetIsValid(const bool value)
		{
			m_IsValid = value;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Computes and sets tree height from complete tree nodes.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   28.11.2021
		 */
		 //-----------------------------------------------------------------------------
		void InternalSetHeight() const
		{
			if (!m_TreeImplementation)
				return;

			m_TreeImplementation->SetHeightFromCompleteTree();
		}
	
	private:

		//
		// =============== Data ========================================================
		//
		
		//>! an implementation type of this tree.
		BinaryTreeImplementationType m_ImplementationType{ BinaryTreeImplementationType::Iterative };

		//>! an implementation of this tree accessed via an object interface.
		std::shared_ptr<IBinaryTreeImplementation> m_TreeImplementation = nullptr;

		//>! binary tree name
		std::string m_Name;

		//>! binary tree validity state flag
		bool m_IsValid = false;
	};


	

} // Symplektis::DataReps
