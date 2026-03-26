#include "ConditionNode.h"

#include <utility>

Ai::ConditionNode::ConditionNode(std::function<bool()> condition)
    : condition_(std::move(condition))
{
}

Ai::INode::Status Ai::ConditionNode::Tick()
{
    return condition_() ? Status::Success : Status::Failure;
}
