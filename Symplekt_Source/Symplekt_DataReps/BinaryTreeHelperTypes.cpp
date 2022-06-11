/*! \file  BinaryTreeHelperTypes.cpp
 *  \brief Implementation of some helper types (enumerators and iterators) for BinaryTree objects.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   2.12.2021
 *
 */

#include "BinaryTreeHelperTypes.h"
#include "IterativeBinaryTreeNode.h"

namespace Symplektis::DataReps
{
	IterativeBinaryTreeNode& BinaryTreeNodeArray::operator[](const int& index)
	{
		if (index < 0 || index >= size())
		{
			throw std::range_error("BinaryTreeNodeArray::operator[]: Node array index out of range!\n");
		}

		return *(begin() + index);
	}

	const IterativeBinaryTreeNode& BinaryTreeNodeArray::operator[](const int& index) const
	{
		if (index < 0 || index >= size())
		{
			throw std::range_error("BinaryTreeNodeArray::operator[]: Node array index out of range!\n");
		}

		return *(begin() + index);
	}

	IterativeBinaryTreeNode& BinaryTreeNodeArray::operator[](const size_t& index)
	{
		if (index >= size())
		{
			throw std::range_error("BinaryTreeNodeArray::operator[]: Node array index out of range!\n");
		}
		return *(begin() + index);
	}

	const IterativeBinaryTreeNode& BinaryTreeNodeArray::operator[](const size_t& index) const
	{
		if (index >= size())
		{
			throw std::range_error("BinaryTreeNodeArray::operator[]: Node array index out of range!\n");
		}
		return *(begin() + index);
	}

	IterativeBinaryTreeNode& BinaryTreeNodeArray::operator[](const unsigned int& index)
	{
		if (index >= size())
		{
			throw std::range_error("BinaryTreeNodeArray::operator[]: Node array index out of range!\n");
		}
		return *(begin() + index);
	}

	const IterativeBinaryTreeNode& BinaryTreeNodeArray::operator[](const unsigned int& index) const
	{
		if (index >= size())
		{
			throw std::range_error("BinaryTreeNodeArray::operator[]: Node array index out of range!\n");
		}
		return *(begin() + index);
	}
	
	IterativeBinaryTreeNode& BinaryTreeNodeArray::operator[](const NodeArrayIndex& index)
	{
		if (!index.IsValid() || index.get() >= size())
		{
			throw std::range_error("BinaryTreeNodeArray::operator[]: Node array index out of range!\n");
		}
		
		return *(begin() + index.get());
	}

	const IterativeBinaryTreeNode& BinaryTreeNodeArray::operator[](const NodeArrayIndex& index) const
	{
		if (!index.IsValid() || index.get() >= size())
		{
			throw std::range_error("BinaryTreeNodeArray::operator[]: Node array index out of range!\n");
		}

		return *(begin() + index.get());
	}
	
	IterativeBinaryTreeNode& BinaryTreeNodeArray::at(const NodeArrayIndex& index)
	{
		if (!index.IsValid() || index.get() >= size())
		{
			throw std::range_error("BinaryTreeNodeArray::at: Node array index out of range!\n");
		}
		
		return *(begin() + index.get());
	}
} // Symplektis::DataReps