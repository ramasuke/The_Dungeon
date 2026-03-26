#pragma once
#include <memory>
#include <vector>

#include "../../INode/INode.h"

namespace Ai
{
    class SelectorNode final : public virtual INode
    {
    public:
        template <typename... Nodes>
        explicit SelectorNode(Nodes&&... nodes)
        {
            using Expander = int[];
            (void)Expander{
                0, (children_.emplace_back(std::forward<Nodes>(nodes)), 0)...
            };
        }
        
        Status Tick() override;

    private:
        std::vector<std::unique_ptr<INode>> children_;
    };
}
