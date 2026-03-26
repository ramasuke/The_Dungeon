#include "SurprisedSign.h"

#include "../../../../../../Component/Content/Basically/Transform/Transform.hpp"

Enemy::Behaviour::Action::SurprisedSign::SurprisedSign(Entity& self, const float offsetPosY)
    : self_(self), offsetPosY_(offsetPosY)
{
}

Ai::INode::Status Enemy::Behaviour::Action::SurprisedSign::operator()() const
{
    Entity::Spawn(SURPRISED_PREFAB_PATH, self_.GetComponent<Transform>()->position_ + Vector2(0, offsetPosY_));
    return Ai::INode::Status::Success;
}
