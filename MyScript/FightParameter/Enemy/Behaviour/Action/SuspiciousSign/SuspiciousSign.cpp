#include "SuspiciousSign.h"

#include "../../../../../../Component/Content/Basically/Transform/Transform.hpp"


Enemy::Behaviour::Action::SuspiciousSign::SuspiciousSign(Entity& self, float offsetPosY)
    : self_(self), offsetPosY_(offsetPosY)
{
}

Ai::INode::Status Enemy::Behaviour::Action::SuspiciousSign::operator()() const
{
    Entity::Spawn(SUSPICIOUS_PREFAB_PATH, self_.GetComponent<Transform>()->position_ + Vector2(0, offsetPosY_));
    return Ai::INode::Status::Success;
}
