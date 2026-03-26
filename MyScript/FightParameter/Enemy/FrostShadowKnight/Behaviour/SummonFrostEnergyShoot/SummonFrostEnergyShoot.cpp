#include "SummonFrostEnergyShoot.h"

#include "../../../BoxAttackArea/EnemyBoxAttackArea.h"

Action::SummonFrostEnergyShoot::SummonFrostEnergyShoot(Entity& self, const Vector2 offsetDistance)
    : self_(self), offsetDistance_(offsetDistance)
{
}

Ai::INode::Status Action::SummonFrostEnergyShoot::operator()() const
{
    const auto shootOffset = Vector2(self_.GetComponent<AnimationRenderer>()->ToTurnDirction().x_ * offsetDistance_.x_,
                                     offsetDistance_.y_);

    auto& shootEntity = Entity::Spawn(summonShootPrefabPath_, self_.GetComponent<Transform>()->position_ + shootOffset);
    shootEntity.GetComponent<AnimationRenderer>()->isReverseX_ = self_.GetComponent<AnimationRenderer>()->isReverseX_;

    return Ai::INode::Status::Success;
}
