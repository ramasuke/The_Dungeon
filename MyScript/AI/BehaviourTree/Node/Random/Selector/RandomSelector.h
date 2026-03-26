#pragma once
#include <memory>
#include <random>
#include <vector>

#include "../../../INode/INode.h"

namespace Ai
{
    class RandomSelector final : public virtual INode
    {
    public:
        template <typename... Nodes>
        explicit RandomSelector(Nodes&&... nodes): selected_(false), selectedIndex_(0)
        {
            using Expander = int[];
            (void)Expander{
                0, (children_.emplace_back(std::forward<Nodes>(nodes)), 0)...
            };
        }

        Status Tick() override;

    private:
        std::vector<std::unique_ptr<INode>> children_;
        bool selected_;
        size_t selectedIndex_;
        std::mt19937 rng_;
    };
}
