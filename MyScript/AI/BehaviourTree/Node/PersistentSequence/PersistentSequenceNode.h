#pragma once
#include <memory>
#include <vector>

#include "../../INode/INode.h"

namespace Ai
{
    class PersistentSequenceNode final : public virtual INode
    {
    public:
        template <typename... Nodes>
        explicit PersistentSequenceNode(Nodes&&... nodes)
        {
            using Expander = int[];
            (void)Expander{
                0, (children_.emplace_back(std::forward<Nodes>(nodes)), 0)...
            };
        }

        Status Tick() override;

    private:
        std::vector<std::unique_ptr<INode>> children_;
        size_t currentIndex_ = 0;
    };
}
