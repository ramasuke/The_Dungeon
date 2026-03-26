#pragma once
#include <vector>
#include <memory>
#include "../../INode/INode.h"

namespace Ai
{
    class WhileNode final : public virtual INode
    {
    public:
        template <typename... Nodes>
        explicit WhileNode(Nodes&&... nodes)
        {
            using Expander = int[];
            (void)Expander{
                0, (children_.emplace_back(std::forward<Nodes>(nodes)), 0)...
            };
        }

        Status Tick() override;

    private:
        std::vector<std::unique_ptr<INode>> children_;
        mutable size_t currentIndex_ = 0;
    };
}
