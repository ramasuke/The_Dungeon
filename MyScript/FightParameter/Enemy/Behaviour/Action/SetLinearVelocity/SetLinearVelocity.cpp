#include "SetLinearVelocity.h"

#include "../../../../../../Libs/Box2D/include/src/box2d/box2d.h"

Enemy::Behaviour::Action::SetLinearVelocity::SetLinearVelocity(Entity& entity, Vector2 setVelocity)
    : entity_(*entity.GetComponent<Collider>()), setVelocity_(setVelocity)
{
}

Ai::INode::Status Enemy::Behaviour::Action::SetLinearVelocity::operator()() const
{
    b2Body_SetLinearVelocity(entity_.GetBodyId(), setVelocity_.ToB2Vec2());
    return Ai::INode::Status::Success;
}
