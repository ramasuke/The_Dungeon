#include "CreateBloodParticle.h"

#include "../../../../../../Component/Content/Basically/Transform/Transform.hpp"

Enemy::Behaviour::Action::CreateBloodParticle::CreateBloodParticle(Entity& self)
    : self_(self)
{
}

Ai::INode::Status Enemy::Behaviour::Action::CreateBloodParticle::operator()() const
{
    Entity::Spawn(BloodParticlePrefabPath, self_.GetComponent<Transform>()->position_); 
    return Ai::INode::Status::Success;
}
