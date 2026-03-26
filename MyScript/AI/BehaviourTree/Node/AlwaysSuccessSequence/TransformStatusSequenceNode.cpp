#include "TransformStatusSequenceNode.h"

Ai::INode::Status Ai::TransformStatusSequenceNode::Tick()
{
    while (currentIndex_ < children_.size())
    {
        const auto status = children_[currentIndex_]->Tick();
        const auto transformed = Transform(status);

        switch (transformed)
        {
        case Status::Success:
            ++currentIndex_;
            break;

        case Status::Running:
        case Status::Abort:
            return transformed;
        default: ;
        }
    }

    currentIndex_ = 0;
    return Status::Success;
}

Ai::INode::Status Ai::TransformStatusSequenceNode::Transform(const Status original) const
{
    const auto it = transformMap_.find(original);
    return (it != transformMap_.end()) ? it->second : original;
}
