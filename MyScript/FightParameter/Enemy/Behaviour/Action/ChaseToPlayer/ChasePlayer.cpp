#include "ChasePlayer.h"

#include "../../../../../../Entity/Entity.hpp"
#include "../../../../../Libs/Box2D/include/src/box2d/box2d.h"
#include "../../../../../Player/PlayerAvatar.h"

Enemy::Behaviour::Action::ChasePlayer::ChasePlayer(Entity& self, const float speed)
    : self_(self), speed_(speed)
{
}

Ai::INode::Status Enemy::Behaviour::Action::ChasePlayer::operator()() const
{
    const auto toPlayerDirection
        = (Player::PlayerAvatar::Model().Transform()->position_ - self_.GetComponent<
            Transform>()->position_).Normalize() * speed_;
    
    b2Body_SetLinearVelocity(self_.GetComponent<Collider>()->GetBodyId(), toPlayerDirection.ToB2Vec2());

    
    
    return Ai::INode::Status::Success;
}
