#pragma once
#include <memory>
#include <type_traits>

#include "INode/INode.h"

namespace Bt = Ai;

namespace Ai
{
    class BehaviourTree final
    {
    public:
        explicit BehaviourTree(std::unique_ptr<INode> node);

        void OnUpdate() const;

    private:
        std::unique_ptr<INode> behaviourNode_ = nullptr;
    };

    inline std::unique_ptr<BehaviourTree> CreateBehaviour(std::unique_ptr<INode> node)
    {
        return std::make_unique<BehaviourTree>(std::move(node));
    }
}
