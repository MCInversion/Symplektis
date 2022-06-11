
#include "BinaryTreeUtils.h"

#include "IBinaryTreeNode.h"

namespace Symplektis::DataReps
{
    BalanceState EvaluateNodeBalanceState(const IBinaryTreeNode& node)
    {
        const int balanceFactor = node.GetBalanceFactor();

        if (balanceFactor <= -2)
            return BalanceState::LeftHeavy;

        if (balanceFactor >= 2)
            return BalanceState::RightHeavy;

        return BalanceState::Balanced;
    }
}  // Symplektis::DataReps