#include "SelectorNode.h"

Ai::INode::Status Ai::SelectorNode::Tick()
{
    for (const auto& child : children_)
    {
        const auto status = child->Tick();

        if (status == Status::Abort)
            return Status::Abort;

        if (status == Status::Success || status == Status::Running)
            return status;
    }

    return Status::Failure;
}