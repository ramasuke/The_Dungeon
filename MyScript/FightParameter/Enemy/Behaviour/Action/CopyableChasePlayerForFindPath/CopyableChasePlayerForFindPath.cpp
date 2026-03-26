#include "CopyableChasePlayerForFindPath.h"

Enemy::Behaviour::Action::CopyableChasePlayerForFindPath::CopyableChasePlayerForFindPath(Entity& self, float mv): impl_(
    std::make_shared<ChasePlayerForFindPath>(self, mv))
{
}

Ai::INode::Status Enemy::Behaviour::Action::CopyableChasePlayerForFindPath::operator()() const
{
    return (*impl_)();
}
