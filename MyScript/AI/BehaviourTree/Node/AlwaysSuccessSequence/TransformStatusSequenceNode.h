#pragma once
#include <memory>
#include <unordered_map>

#include "../../INode/INode.h"

namespace Ai
{
    class TransformStatusSequenceNode final : public INode
    {
    public:
        template <typename... Nodes>
        explicit TransformStatusSequenceNode(
            std::unordered_map<Status, Status> transformMap,
            Nodes&&... nodes
        )
            : transformMap_(std::move(transformMap)),
              currentIndex_(0)
        {
            using Expander = int[];
            (void)Expander{0, (children_.emplace_back(std::forward<Nodes>(nodes)), 0)...};
        }

        Status Tick() override;

    private:
        Status Transform(Status original) const;

        std::vector<std::unique_ptr<INode>> children_;
        std::unordered_map<Status, Status> transformMap_;
        size_t currentIndex_;
    };
}
