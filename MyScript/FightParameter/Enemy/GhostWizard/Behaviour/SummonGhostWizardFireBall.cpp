#include "SummonGhostWizardFireBall.h"

#include "../../../../../Component/Content/Basically/Transform/Transform.hpp"
#include "../../../../../Helper/MyCalculator/MyCalculator.h"
#include "../../../DamageContext/Fire/FireDamageContext.h"
#include "../../../DamageContext/Fire/FirePower/FirePower.h"
#include "../../BoxAttackArea/EnemyBoxAttackArea.h"

Enemy::Behaviour::Action::SummonGhostWizardFireBall::SummonGhostWizardFireBall(
    Entity& self,
    const float offsetDistance,
    const FirePower& firePower)
    : self_(self), firePower_(firePower), offsetDistance_(offsetDistance)
{
}

Ai::INode::Status Enemy::Behaviour::Action::SummonGhostWizardFireBall::operator()() const
{
    const Vector2 toPlayerDirection = (Player::PlayerAvatar::Model().
        Transform()->position_ - self_.GetComponent<Transform>()->position_).Normalize();

    const auto fireBall = Entity::Spawn<EnemyBoxAttackArea>(summonFireBallPrefabPath_,
                                                        self_.GetComponent<Transform>()->position_ + toPlayerDirection *
                                                        offsetDistance_);
    fireBall->InitDamage(std::make_shared<FireDamageContext>(self_, firePower_), despawnFireBallDuration_);
    fireBall->EntityRef().GetComponent<Transform>()->rotation_ =  toPlayerDirection.ToDegree();

    return Ai::INode::Status::Success;
}
