#pragma once
#include "../../INode/INode.h"

namespace Ai
{
    class BreakPointNode final : public virtual INode
    {
    public:
        explicit BreakPointNode() = default;

    private:
        Status Tick() override;
    };
}
