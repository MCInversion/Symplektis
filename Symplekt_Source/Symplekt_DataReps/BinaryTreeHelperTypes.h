/*! \file  BinaryTreeHelperTypes.h
 *  \brief Helper types (enumerators and iterators) for BinaryTree objects.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   6.10.2021
 *
 */

#pragma once

#include "Symplekt_UtilityGeneral/NamedValue.h"

#include <vector>

namespace Symplektis::DataReps
{
	//
	// ========== Error Codes =====================================================
	//
	
	//=============================================================================
	/// \enum BinaryNodeErrorCode
	/// \brief Error code for binary tree node operations
	///
	/// \ingroup DATA_REPS
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   31.10.2021
	//=============================================================================
	enum class [[nodiscard]] BinaryNodeErrorCode
	{
		OK                  = 0,  //>! Insertion operation with a binary tree node completed successfully.
		RightNodeExists     = 1,  //>! Insertion operation cannot take place because right child node already exists.
		LeftNodeExists      = 2,  //>! Insertion operation cannot take place because left child node already exists.
		NodeArrayIndexError = 3,  //>! Insertion operation cannot take place because provided iterative node array index is invalid.
		NullNode            = 4   //>! Operation cannot be completed because null node value is used.
	};

	//=============================================================================
	/// \enum BinaryTreeErrorCode
	/// \brief Error code for binary tree operations
	///
	/// \ingroup DATA_REPS
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   31.10.2021
	//=============================================================================
	enum class [[nodiscard]] BinaryTreeErrorCode
	{
		OK                    = 0,   //>! Operation with a binary tree completed successfully.
		NodeSaturated         = 1,   //>! Insertion operation cannot be completed because current node is saturated (has both left and right child).
		LeftNodeExists        = 2,   //>! Left insertion operation cannot be completed because current node already has a left child.
		RightNodeExists       = 3,   //>! Right insertion operation cannot be completed because current node already has a left child.
		NodeNotFound          = 4,   //>! Operation cannot be completed because specified node was not found.
		InsertingNullNode     = 5,   //>! Insertion operation cannot be completed because inserted node is null.
		NodeArrayIndexError   = 6,   //>! Operation cannot be completed because given node array index is invalid.
		CurrentNodeNotSet     = 7,   //>! Operation cannot be completed because current node cursor is not set.
		NodeNotPreLeaf        = 8,   //>! Operation (Pre-rotate) cannot be completed because current node is not "pre-leaf", i.e.: it has a strictly left or right subtree of height > 1 or is not a leaf.
		ReinsertNode          = 9,   //>! Insertion operation needs to be repeated with the same settings.
		InternalError         = 10   //>! Unspecified internal error.
	};

	//-----------------------------------------------------------------------------
	/*! \brief An error code interpreter that interprets node error codes as tree error codes.
	 *  \param[in] nodeError          a binary tree error code to be interpreted.
	 *
	 *  \return a binary tree error code
	 *
	 *  \author M. Cavarga (MCInversion)
	 *  \date   2.11.2021
	 */
	 //-----------------------------------------------------------------------------
	static [[nodiscard]] BinaryTreeErrorCode InterpretNodeErrorCodeAsTreeErrorCode(const BinaryNodeErrorCode& nodeError)
	{
		switch (nodeError)
		{
		case BinaryNodeErrorCode::OK:
			return BinaryTreeErrorCode::OK;
		case BinaryNodeErrorCode::RightNodeExists:
			return BinaryTreeErrorCode::RightNodeExists;
		case BinaryNodeErrorCode::LeftNodeExists:
			return BinaryTreeErrorCode::LeftNodeExists;
		case BinaryNodeErrorCode::NodeArrayIndexError:
			return BinaryTreeErrorCode::NodeArrayIndexError;
		case BinaryNodeErrorCode::NullNode:
			return BinaryTreeErrorCode::NodeNotFound;
		default:
			return BinaryTreeErrorCode::InternalError;
		}
	}

	//
	// ========== Tree Balancing Types =====================================================
	//

	//=============================================================================
	/// \enum BalanceState
	/// \brief Encodes balance state of current node before rebalancing
	///
	/// \ingroup DATA_REPS
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   2.2.2022
	//=============================================================================
	enum class [[nodiscard]] BalanceState
	{
		Balanced   = 0,  //>! left and right child height difference is no larger than 1
		LeftHeavy  = 1,  //>! left and right child height difference (balance factor) is -2
		RightHeavy = 2,  //>! left and right child height difference (balance factor) is +2
	};

	//
	// ========== Implementation Types =====================================================
	//

	//=============================================================================
	/// \enum BinaryTreeImplementationType
	/// \brief Implementation type enumerator.
	///
	/// \ingroup DATA_REPS
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   21.11.2021
	//=============================================================================
	enum class [[nodiscard]] BinaryTreeImplementationType
	{
		Iterative = 0,  //>! Nodes of this binary tree implementation are stored in an array buffer and iterated over.
		Recursive = 1   //>! Nodes of this binary tree implementation are generated recursively as heap instances of each other.
	};


	//
	// =============== Iterative Implementation Types ==================================
	//

	//=============================================================================
	/// \class NodeArrayIndex
	/// \brief Binary tree node array index value.
	///
	/// \ingroup DATA_REPS
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   21.11.2021
	//=============================================================================
	class NodeArrayIndex : public Util::NamedValue<int, NodeArrayIndex>
	{
	public:
		using NamedValue::NamedValue;

		/// @{
		/// \name Constructors

		//-----------------------------------------------------------------------------
		/*! \brief Constructor. Initialized from a size_t value.
		 *  \param[in] value       size_t value.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   29.11.2021
		 */
		 //-----------------------------------------------------------------------------
		explicit NodeArrayIndex(const size_t& value)
			: NodeArrayIndex(static_cast<int>(value)) { }

		//-----------------------------------------------------------------------------
		/*! \brief Constructor. Initialized from an unsigned int value.
		 *  \param[in] value       unsigned int value.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   29.11.2021
		 */
		 //-----------------------------------------------------------------------------
		explicit NodeArrayIndex(const unsigned int& value)
			: NodeArrayIndex(static_cast<int>(value)) { }

		//-----------------------------------------------------------------------------
		/*! \brief Constructor. Initialized from an long int value.
		 *  \param[in] value       long int value.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   29.11.2021
		 */
		 //-----------------------------------------------------------------------------
		explicit NodeArrayIndex(const long int& value)
			: NodeArrayIndex(static_cast<int>(value)) { }

		/// @{
		/// \name Flags

		//-----------------------------------------------------------------------------
		/*! \brief Validity flag based on the value sign.
		 *  \return true if the value is non-negative.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   29.11.2021
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] constexpr bool IsValid() const noexcept
		{
			return (m_value >= 0);
		}

		/// @{
		/// \name Operators

		//-----------------------------------------------------------------------------
		/*! \brief Not operator. Returns true if this index value is negative.
		 *  \return true if the value is negative.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   29.11.2021
		 */
		 //-----------------------------------------------------------------------------
		bool operator!() const
		{
			return m_value < 0;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Explicit bool conversion operator.
		 *  \return true if this index's value is more than or equal to 0.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   5.12.2021
		 */
		 //-----------------------------------------------------------------------------
		explicit operator bool() const
		{
			return m_value >= 0;
		}
		
		//-----------------------------------------------------------------------------
		/*! \brief Copy-assignment operator with size_t value.
		 *  \param[in] value          size_t value to be assigned.
		 *  \return reference to this NodeArrayIndex.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   29.11.2021
		 */
		 //-----------------------------------------------------------------------------
		NodeArrayIndex& operator= (const size_t& value)
		{
			m_value = static_cast<int>(value);
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Copy-assignment operator with int value.
		 *  \param[in] value          int value to be assigned.
		 *  \return reference to this NodeArrayIndex.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   29.11.2021
		 */
		 //-----------------------------------------------------------------------------
		NodeArrayIndex& operator= (const int& value)
		{
			m_value = value;
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Copy-assignment operator with unsigned int value.
		 *  \param[in] value          unsigned int value to be assigned.
		 *  \return reference to this NodeArrayIndex.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   29.11.2021
		 */
		 //-----------------------------------------------------------------------------
		NodeArrayIndex& operator= (const unsigned int& value)
		{
			m_value = value;
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief More-than-or-equal operator with size_t value.
		 *  \param[in] value          size_t value to be compared.
		 *  \return true if this index's value is more than or equal to the compared value.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   29.11.2021
		 */
		 //-----------------------------------------------------------------------------
		bool operator>= (const size_t& value) const
		{
			return m_value >= static_cast<int>(value);
		}

		//-----------------------------------------------------------------------------
		/*! \brief More-than-or-equal operator with NodeArrayIndex value.
		 *  \param[in] other          NodeArrayIndex to be compared.
		 *  \return true if this index's value is more than or equal to the compared value.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   29.11.2021
		 */
		 //-----------------------------------------------------------------------------
		bool operator>= (const NodeArrayIndex& other) const
		{
			return m_value >= static_cast<int>(other.m_value);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Comparison equal operator with another NodeArrayIndex.
		 *  \param[in] other          NodeArrayIndex to be compared.
		 *  \return true if this index's value is equal to the compared NodeArrayIndex's value.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   20.1.2022
		 */
		 //-----------------------------------------------------------------------------
		bool operator== (const NodeArrayIndex& other) const
		{
			return m_value == other.m_value;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Comparison equal operator with size_t value.
		 *  \param[in] value          size_t value to be compared.
		 *  \return true if this index's value is equal to the compared value.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   20.1.2022
		 */
		 //-----------------------------------------------------------------------------
		bool operator== (const size_t& value) const
		{
			if (m_value < 0)
				return false;
			
			return static_cast<size_t>(m_value) == value;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Comparison equal operator with int value.
		 *  \param[in] value          int value to be compared.
		 *  \return true if this index's value is equal to the compared value.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   5.12.2021
		 */
		 //-----------------------------------------------------------------------------
		bool operator== (const int& value) const
		{
			return m_value == value;
		}

	};

	/// \brief null index pointing no a non-existent position in binary tree node array.
	constexpr NodeArrayIndex NULL_NODE_INDEX{ -1 };

	// forward declarations
	class IterativeBinaryTreeNode;

	//=============================================================================
	/// \class BinaryTreeNodeArray
	/// \brief std::vector<IterativeBinaryTreeNode> extension supporting NodeArrayIndex.
	///
	/// \ingroup DATA_REPS
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   21.11.2021
	//=============================================================================
	class BinaryTreeNodeArray : public std::vector<IterativeBinaryTreeNode>
	{
	public:

		//-----------------------------------------------------------------------------
		/*! \brief Array index operator supporting int value.
		 *  \param[in] index          index of the picked node array element.
		 *  
		 *  \return reference to the IterativeBinaryTreeNode stored under a given index. If index is out of range, an std::range_error is thrown.
		 *  \except std::range_error if index is out of range.
		 *
		 *  \author M. Cavarga (MCInversion)
		 *  \date   1.12.2021
		 */
		 //-----------------------------------------------------------------------------
		IterativeBinaryTreeNode& operator[] (const int& index);

		//-----------------------------------------------------------------------------
		/*! \brief Const array index operator supporting int value.
		 *  \param[in] index          index of the picked node array element.
		 *  
		 *  \return const reference to the IterativeBinaryTreeNode stored under a given index. If index is out of range, an std::range_error is thrown.
		 *  \except std::range_error if index is out of range.
		 *
		 *  \author M. Cavarga (MCInversion)
		 *  \date   1.12.2021
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] const IterativeBinaryTreeNode& operator[] (const int& index) const;

		//-----------------------------------------------------------------------------
		/*! \brief Array index operator supporting size_t value.
		 *  \param[in] index          index of the picked node array element.
		 *  \return reference to the IterativeBinaryTreeNode stored under a given index. If index is out of range, an std::range_error is thrown.
		 *  \except std::range_error if index is out of range.
		 *
		 *  \author M. Cavarga (MCInversion)
		 *  \date   1.12.2021
		 */
		 //-----------------------------------------------------------------------------
		IterativeBinaryTreeNode& operator[] (const size_t& index);

		//-----------------------------------------------------------------------------
		/*! \brief Const array index operator supporting size_t value.
		 *  \param[in] index          index of the picked node array element.
		 *  \return const reference to the IterativeBinaryTreeNode stored under a given index. If index is out of range, an std::range_error is thrown.
		 *  \except std::range_error if index is out of range.
		 *
		 *  \author M. Cavarga (MCInversion)
		 *  \date   1.12.2021
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] const IterativeBinaryTreeNode& operator[] (const size_t& index) const;

		//-----------------------------------------------------------------------------
		/*! \brief Array index operator supporting unsigned int value.
		 *  \param[in] index          index of the picked node array element.
		 *  \return reference to the IterativeBinaryTreeNode stored under a given index. If index is out of range, an std::range_error is thrown.
		 *  \except std::range_error if index is out of range.
		 *
		 *  \author M. Cavarga (MCInversion)
		 *  \date   1.12.2021
		 */
		 //-----------------------------------------------------------------------------
		IterativeBinaryTreeNode& operator[] (const unsigned int& index);

		//-----------------------------------------------------------------------------
		/*! \brief Const array index operator supporting unsigned int value.
		 *  \param[in] index          index of the picked node array element.
		 *  \return const reference to the IterativeBinaryTreeNode stored under a given index. If index is out of range, an std::range_error is thrown.
		 *  \except std::range_error if index is out of range.
		 *
		 *  \author M. Cavarga (MCInversion)
		 *  \date   1.12.2021
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] const IterativeBinaryTreeNode& operator[] (const unsigned int& index) const;
		
		//-----------------------------------------------------------------------------
		/*! \brief Array index operator supporting NodeArrayIndex.
		 *  \param[in] index          index of the picked node array element.
		 *  \return reference to the IterativeBinaryTreeNode stored under a given index. If index is out of range, an std::range_error is thrown.
		 *  \except std::range_error if index is out of range.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   29.11.2021
		 */
		//-----------------------------------------------------------------------------
		IterativeBinaryTreeNode& operator[] (const NodeArrayIndex& index);

		//-----------------------------------------------------------------------------
		/*! \brief Array index operator supporting NodeArrayIndex.
		 *  \param[in] index          index of the picked node array element.
		 *  \return reference to the IterativeBinaryTreeNode stored under a given index. If index is out of range, an std::range_error is thrown.
		 *  \except std::range_error if index is out of range.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   29.11.2021
		 */
		 //-----------------------------------------------------------------------------
		[[nodiscard]] const IterativeBinaryTreeNode& operator[] (const NodeArrayIndex& index) const;

		//-----------------------------------------------------------------------------
		/*! \brief variant of "std::vector::at" function supporting NodeArrayIndex.
		 *  \param[in] index          index of the picked node array element.
		 *  \return reference to the IterativeBinaryTreeNode stored under a given index. If index is out of range, an std::range_error is thrown.
		 *  \except std::range_error if index is out of range.
		 *
		 *   \author M. Cavarga (MCInversion)
		 *   \date   29.11.2021
		 */
		//-----------------------------------------------------------------------------
		IterativeBinaryTreeNode& at(const NodeArrayIndex& index);
	};
	
} // Symplektis::DataReps