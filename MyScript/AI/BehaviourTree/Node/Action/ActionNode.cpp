#include "ActionNode.h"

#include <utility>

Ai::ActionNode::ActionNode(std::function<Status()> action)
    : action_(std::move(action))
{
}

Ai::INode::Status Ai::ActionNode::Tick()
{
    return action_();
}
