#include "WaitNode.h"

Ai::WaitNode::WaitNode(const int waitFrameCount)
    : waitFrames_(waitFrameCount)
{
}

Ai::INode::Status Ai::WaitNode::Tick()
{
    if (frameCounter_ >= waitFrames_)
    {
        frameCounter_ = 0;
        return Status::Success;
    }

    ++frameCounter_;
    return Status::Running;
}
