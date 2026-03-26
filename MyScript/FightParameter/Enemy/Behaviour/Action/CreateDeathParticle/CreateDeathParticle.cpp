#include "CreateDeathParticle.h"

#include "../../../../../../Component/Content/Basically/Transform/Transform.hpp"

Enemy::Behaviour::Action::CreateDeathParticle::CreateDeathParticle(Entity& entity)
    : transform_(entity.GetComponent<Transform>())
{
}

Ai::INode::Status Enemy::Behaviour::Action::CreateDeathParticle::operator()() const
{
    Entity::Spawn(PREFAB_PATH, transform_->position_);
    return Ai::INode::Status::Success;
}
