/*! \file  IteratorHelperUtils.h
 *  \brief Tools for correct handling of iterator objects used in multiple containers.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   28.11.2021
 *
 */

#pragma once

#include "Assert.h"

#include <vector>

namespace Symplektis::Util
{
	//-----------------------------------------------------------------------------
	/*! \brief Transfers iterator to another container with the same size.
	 *  \tparam T    type stored in the vectors.
	 *  
	 *  \param[in] iteratorToUpdate            iterator to be updated.
	 *  \param[in] sourceContainer             source vector from which iteratorToUpdate should be.
	 *  \param[in] targetContainer             target vector into which iteratorToUpdate should be transferred.
	 *
	 *  Possible use:
	 *   TransferIteratorToContainer(iter, containerA, containerB);
	 *   TransferIteratorToContainer<MyType>(iter, containerA, containerB);
	 *  
	 *   \ingroup UTILITY_GENERAL
	 *   \author M. Cavarga (MCInversion)
	 *   \date   28.11.2021
	 */
	 //-----------------------------------------------------------------------------
	template <typename T>
	void TransferIteratorToContainer(
		typename std::vector<T>::iterator& iteratorToUpdate, 
		         std::vector<T>&           sourceContainer, 
		         std::vector<T>&           targetContainer)
	{
		if (sourceContainer.empty() || targetContainer.empty())
			return;

		if (sourceContainer.size() != targetContainer.size())
			return;

		try
		{
			if (iteratorToUpdate == sourceContainer.end())
			{
				iteratorToUpdate = targetContainer.end();
				return;
			}
			
			const size_t sourceContainerIteratorPosition = iteratorToUpdate - sourceContainer.begin();
			iteratorToUpdate = targetContainer.begin() + sourceContainerIteratorPosition;			
		}
		catch(...)
		{
			MSG_CHECK(false, "Symplektis::Util::TransferIteratorToContainer: Vector iterators likely incompatible!\n");
		}
	}

	//-----------------------------------------------------------------------------
	/*! \brief Transfers const iterator to another container with the same size.
	 *  \tparam T    type stored in the vectors.
	 *
	 *  \param[in] iteratorToUpdate            const iterator to be updated.
	 *  \param[in] sourceContainer             source vector from which iteratorToUpdate should be.
	 *  \param[in] targetContainer             target vector into which iteratorToUpdate should be transferred.
	 *
	 *  Possible use:
	 *   TransferIteratorToContainer(iter, containerA, containerB);
	 *   TransferIteratorToContainer<MyType>(iter, containerA, containerB);
	 *
	 *   \ingroup UTILITY_GENERAL
	 *   \author M. Cavarga (MCInversion)
	 *   \date   28.11.2021
	 */
	 //-----------------------------------------------------------------------------
	template <typename T>
	void TransferIteratorToContainer(
		typename std::vector<T>::const_iterator& iteratorToUpdate,
		   const std::vector<T>&                 sourceContainer,
		   const std::vector<T>&                 targetContainer)
	{
		if (sourceContainer.empty() || targetContainer.empty())
			return;

		if (sourceContainer.size() != targetContainer.size())
			return;

		try
		{
			if (iteratorToUpdate == sourceContainer.cend())
			{
				iteratorToUpdate = targetContainer.cend();
				return;
			}

			const size_t sourceContainerIteratorPosition = iteratorToUpdate - sourceContainer.cbegin();
			iteratorToUpdate = targetContainer.cbegin() + sourceContainerIteratorPosition;
		}
		catch (...)
		{
			MSG_CHECK(false, "Symplektis::Util::TransferIteratorToContainer: Vector iterators likely incompatible!\n");
		}
	}
	
} // Symplektis::Util