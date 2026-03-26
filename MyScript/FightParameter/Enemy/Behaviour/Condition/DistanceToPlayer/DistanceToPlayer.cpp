#include "DistanceToPlayer.h"

#include "../../../../../../Component/Content/Basically/Transform/Transform.hpp"
#include "../../../../../Player/PlayerAvatar.h"

Enemy::Behaviour::Condition::DistanceToPlayer::DistanceToPlayer(Entity& self, const float range)
    : self_(self), range_(range * range)
{
}

bool Enemy::Behaviour::Condition::DistanceToPlayer::operator()() const
{
    if (Player::PlayerAvatar::Model().Transform() == nullptr)
        return false;
    
    return (self_.GetComponent<Transform>()->position_ - Player::PlayerAvatar::Model().Transform()->position_).Magnitude() < range_;
}
