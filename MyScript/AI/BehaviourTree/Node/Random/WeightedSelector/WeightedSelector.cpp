#include "WeightedSelector.h"

Ai::WeightedSelector::WeightedSelector(std::vector<WeightedNode> children)
    : weightedChildren_(std::move(children)), selectedIndex_(0), rng_(std::random_device{}())
{
}

Ai::INode::Status Ai::WeightedSelector::Tick()
{
    if (!selected_)
    {
        int totalWeight = 0;
        for (const auto& wc : weightedChildren_) totalWeight += wc.weight_;

        std::uniform_int_distribution<int> dist(0, totalWeight - 1);

        int sum = 0;
        for (size_t i = 0; i < weightedChildren_.size(); ++i)
        {
            sum += weightedChildren_[i].weight_;
            if (dist(rng_) < sum)
            {
                selectedIndex_ = i;
                break;
            }
        }

        selected_ = true;
    }

    const auto status = weightedChildren_[selectedIndex_].node_->Tick();
    if (status != Status::Running)
        selected_ = false;

    return status;
}
