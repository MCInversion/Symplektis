
#pragma once

#include "BinaryTreeHelperTypes.h"

namespace Symplektis::DataReps
{
	// forward declarations
	class IBinaryTreeNode;

    //-----------------------------------------------------------------------------
    /*! \brief Evaluates whether the node is left-heavy, right-heavy or balanced
     *  \param[in] node           node to be evaluated
     *  \return balance state of given node.
     *
     *   \author M. Cavarga (MCInversion)
     *   \date   2.2.2022
     */
     //-----------------------------------------------------------------------------
	BalanceState EvaluateNodeBalanceState(const IBinaryTreeNode& node);
	
}  // Symplektis::DataReps