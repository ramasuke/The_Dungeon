#include "RandomSelector.h"

Ai::INode::Status Ai::RandomSelector::Tick()
{
    if (!selected_)
    {
        std::uniform_int_distribution<size_t> dist(0, children_.size() - 1);
        selectedIndex_ = dist(rng_);
        selected_ = true;
    }

    const auto status = children_[selectedIndex_]->Tick();

    if (status == Status::Abort)
    {
        selected_ = false;
        return Status::Abort;
    }

    if (status != Status::Running)
        selected_ = false;

    return status;
}