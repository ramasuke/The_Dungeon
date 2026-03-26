#pragma once
#include "../../../FightParameter/Enemy/Behaviour/Action/ChaseToPlayer/ChasePlayer.h"
#include "../../../FightParameter/Enemy/Behaviour/Condition/RaycastToPlayer/RaycastToPlayer.h"
#include "../Node/Abort/AbortNode.h"
#include "../Node/Action/ActionNode.h"
#include "../Node/AlwaysSuccessSequence/TransformStatusSequenceNode.h"
#include "../Node/BreakPoint/BreakPointNode.h"
#include "../Node/Condition/ConditionNode.h"
#include "../Node/Random/Selector/RandomSelector.h"
#include "../Node/PersistentSelector/PersistentSelectorNode.h"
#include "../Node/PersistentSequence/PersistentSequenceNode.h"
#include "../Node/Selector/SelectorNode.h"
#include "../Node/Sequence/SequenceNode.h"
#include "../Node/While/WhileNode.h"
#include "../Node/Wait/WaitNode.h"

namespace Condition = Enemy::Behaviour::Condition;
namespace Action = Enemy::Behaviour::Action;

namespace Ai
{
    // 汎用ノード作成
    template <typename T, typename... Args>
    static std::unique_ptr<INode> CreateNode(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    // DSL化：条件ノード
    template <typename TCondition, typename... Args>
    auto When(Args&&... args)
    {
        return CreateNode<ConditionNode>(TCondition(std::forward<Args>(args)...));
    }

    //DSL化: 条件反転ノード
    template <typename TCondition, typename... Args>
    auto Unless(Args&&... args)
    {
        return CreateNode<ConditionNode>(
            [cond = TCondition(std::forward<Args>(args)...)]() -> bool
            {
                return !cond();
            }
        );
    }

    // DSL化：アクションノード
    template <typename TAction, typename... Args>
    auto Then(Args&&... args)
    {
        return CreateNode<ActionNode>(TAction(std::forward<Args>(args)...));
    }

    // DSL化：PersistentSelectorノード
    template <typename... Nodes>
    auto Selector(Nodes&&... nodes)
    {
        return CreateNode<PersistentSelectorNode>(std::forward<Nodes>(nodes)...);
    }

    // DSL化：即時評価のSelectorノード
    template <typename... Nodes>
    auto PromptSelector(Nodes&&... nodes)
    {
        return CreateNode<SelectorNode>(std::forward<Nodes>(nodes)...);
    }

    // DSL化：PersistentSequenceノード
    template <typename... Nodes>
    auto Sequence(Nodes&&... nodes)
    {
        return CreateNode<PersistentSequenceNode>(std::forward<Nodes>(nodes)...);
    }

    // DSL化：即時評価のSequenceノード
    template <typename... Nodes>
    auto PromptSequence(Nodes&&... nodes)
    {
        return CreateNode<SequenceNode>(std::forward<Nodes>(nodes)...);
    }


    // DSL化：Waitノード
    inline auto Wait(int waitFrame)
    {
        return CreateNode<WaitNode>(waitFrame);
    }

    // DSL化：Randomノード
    template <typename... Nodes>
    auto RandomSelect(Nodes&&... nodes)
    {
        return CreateNode<RandomSelector>(std::forward<Nodes>(nodes)...);
    }

    //DSL化: Whileノード
    template <typename... Nodes>
    auto While(Nodes&&... nodes)
    {
        return CreateNode<WhileNode>(std::forward<Nodes>(nodes)...);
    }

    //DSL化：Abortノード
    inline auto Abort()
    {
        return CreateNode<AbortNode>();
    }
    
    //DSL化: BreakPointノード
    inline auto BreakPoint()
    {
        return CreateNode<BreakPointNode>();
    }
    
    //DSL化: Transformノード
    template <typename... Nodes>
    auto Transform(Nodes&&... nodes)
    {
        return CreateNode<TransformStatusSequenceNode>(std::forward<Nodes>(nodes)...);
    }
    
}
