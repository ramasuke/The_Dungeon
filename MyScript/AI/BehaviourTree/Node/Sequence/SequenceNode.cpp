#include "SequenceNode.h"

Ai::INode::Status Ai::SequenceNode::Tick()
{
    for (const auto& child : children_)
    {
        const auto status = child->Tick();

        if (status == Status::Abort)
            return Status::Abort;

        if (status != Status::Success)
            return status;
    }

    return Status::Success;
}

