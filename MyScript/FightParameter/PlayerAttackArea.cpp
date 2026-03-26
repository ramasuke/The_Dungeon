#include "PlayerAttackArea.h"

#include "../../Component/Content/Basically/Collider/Collider.h"
#include "../../Entity/Entity.hpp"
#include "../../Physics/Physics.h"

void PlayerAttackArea::SetDamage(const std::shared_ptr<DamageContext::IDamageContext>& damage)
{
    damage_ = damage;
}

void PlayerAttackArea::Awake()
{
    EntityRef().GetComponent<Collider>()->SetLayer(b2Filter{
        PlayerAttackAreaLayer, static_cast<uint16_t>(~PlayerAttackAreaLayer), 0
    });
}

void PlayerAttackArea::OnBeginSensor(b2SensorBeginTouchEvent*, IReceivablePlayerAttack* collision)
{
    collision->OnDamage(damage_);
}
