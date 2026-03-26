#pragma once
#include <functional>

#include "../../INode/INode.h"

namespace Ai
{
    class ConditionNode final : public virtual INode
    {
    public:
        explicit ConditionNode(std::function<bool()> condition);
        
    private:
        Status Tick() override;
        
        std::function<bool()> condition_;
    };
}
