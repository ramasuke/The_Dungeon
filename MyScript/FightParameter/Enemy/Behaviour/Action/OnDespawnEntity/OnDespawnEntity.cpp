#include "OnDespawnEntity.h"

Enemy::Behaviour::Action::OnDespawnEntity::OnDespawnEntity(Entity& self)
    : self_(self)
{
}

Ai::INode::Status Enemy::Behaviour::Action::OnDespawnEntity::operator()() const
{
    self_.OnDespawn();
    return Ai::INode::Status::Success;
}
