#pragma once
#include <functional>

#include "../../INode/INode.h"

namespace Ai
{
    class ActionNode final : public virtual INode
    {
    public:
        explicit ActionNode(std::function<Status()> action);

    private:
        Status Tick() override;
        
        std::function<Status()> action_;
    };
}
