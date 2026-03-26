#include "RaycastToPlayer.h"

#include "../../../../../Player/PlayerAvatar.h"
#include "../../../Helper/EnemyHelper.h"

Enemy::Behaviour::Condition::RaycastToPlayer::RaycastToPlayer(
    Entity& self, const float raycastRangeCoefficient)
    : self_(self), raycastRangeCoefficient_(raycastRangeCoefficient)
{
}

bool Enemy::Behaviour::Condition::RaycastToPlayer::operator()() const
{
    return EnemyHelper::FindPlayerForRaycast(self_.GetComponent<Transform>()->position_, raycastRangeCoefficient_);
}
