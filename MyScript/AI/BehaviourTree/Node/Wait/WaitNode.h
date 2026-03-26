#pragma once
#include <chrono>

#include "../../INode/INode.h"

namespace Ai
{
    class WaitNode final : public virtual INode
    {
    public:
        explicit WaitNode(int waitFrameCount);

        Status Tick() override;

    private:
        int waitFrames_;
        mutable int frameCounter_ = 0;
    };
}