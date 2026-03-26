#include "WhileNode.h"

Ai::INode::Status Ai::WhileNode::Tick()
{
    while (currentIndex_ < children_.size())
    {
        const auto status = children_[currentIndex_]->Tick();

        if (status == Status::Abort)
        {
            currentIndex_ = 0;
            return Status::Abort;
        }

        if (status == Status::Failure)
        {
            currentIndex_ = 0;
            return Status::Failure;
        }

        if (status == Status::Running)
        {
            return Status::Running;
        }

        ++currentIndex_;
    }

    currentIndex_ = 0;
    return Status::Running;
}