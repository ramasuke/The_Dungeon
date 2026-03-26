#pragma once
#include "../../INode/INode.h"

namespace Ai
{
    class AbortNode final : public INode
    {
    public:
        Status Tick() override;
    };
}
