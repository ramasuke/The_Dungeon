#include "PersistentSelectorNode.h"

Ai::INode::Status Ai::PersistentSelectorNode::Tick()
{
    while (currentIndex_ < children_.size())
    {
        const Status status = children_[currentIndex_]->Tick();

        if (status == Status::Abort)
        {
            currentIndex_ = 0;
            return Status::Abort;
        }

        if (status == Status::Running)
            return Status::Running;

        if (status == Status::Success)
        {
            currentIndex_ = 0;
            return Status::Success;
        }

        ++currentIndex_;
    }

    currentIndex_ = 0;
    return Status::Failure;
}