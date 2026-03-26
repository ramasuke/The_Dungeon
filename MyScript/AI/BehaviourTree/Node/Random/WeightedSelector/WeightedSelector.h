#pragma once
#include <memory>
#include <random>
#include <vector>

#include "../../../INode/INode.h"
#include "../../Weighted/WeightedNode.h"

namespace Ai
{
    class WeightedSelector final : public virtual INode
    {
    public:
        explicit WeightedSelector(std::vector<WeightedNode> children);

        Status Tick() override;

    private:
        std::vector<WeightedNode> weightedChildren_;
        bool selected_ = false;
        size_t selectedIndex_;
        std::mt19937 rng_;
    };
}
