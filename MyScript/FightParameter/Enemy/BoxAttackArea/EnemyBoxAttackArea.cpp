#include "EnemyBoxAttackArea.h"

#include "../../../../Entity/Entity.hpp"
#include "../../../../Physics/Physics.h"
#include "../../SpawnAttackAreaModel/SpawnAttackAreaModel.h"
#include "../Helper/EnemyHelper.h"

void Enemy::EnemyBoxAttackArea::InitDamage(const std::shared_ptr<DamageContext::IDamageContext>& damage,
                                           const int despawnDuration)
{
    damage_ = damage;
    despawnDuration_ = despawnDuration;
}

void Enemy::EnemyBoxAttackArea::InitArea(const std::shared_ptr<DamageContext::IDamageContext>& damage,
                                         const SpawnAttackAreaModel& attackAreaModel)
{
    EntityRef().GetComponent<Transform>()->position_ += attackAreaModel.Offset();
    damage_ = damage;
    auto& boxCollider = *EntityRef().GetComponent<BoxCollider>();
    boxCollider.SetSize(attackAreaModel.AreaSize());
    despawnDuration_ = attackAreaModel.DespawnDuration();
}

void Enemy::EnemyBoxAttackArea::Awake()
{
    auto& boxCollider = *EntityRef().GetComponent<BoxCollider>();
    boxCollider.SetLayer(EnemyHelper::EnemyAttackAreaFilter());
}

void Enemy::EnemyBoxAttackArea::OnUpdate()
{
    despawnDuring_++;
    if (despawnDuring_ >= despawnDuration_)
    {
        EntityRef().OnDespawn();
    }
}

void Enemy::EnemyBoxAttackArea::OnBeginSensor(b2SensorBeginTouchEvent*, IReceivableEnemyAttack* target)
{
    target->OnDamage(damage_);
}
