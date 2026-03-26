#pragma once
#include <memory>

#include "../../INode/INode.h"

namespace Ai
{
    struct WeightedNode
    {
        std::unique_ptr<INode> node_;
        int weight_;
    };
}
