#include "PhysicsDamageContext.h"

#include "../../../../Component/Content/Basically/Collider/Collider.h"
#include "../../../../Component/Content/Basically/Transform/Transform.hpp"
#include "../../../../Entity/Entity.hpp"
#include "../../../../Libs/Box2D/include/src/box2d/box2d.h"

DamageContext::PhysicsDamageContext::PhysicsDamageContext(Entity& fromEntity, const PhysicsPower& damage)
    : fromPos_(fromEntity.GetComponent<Transform>()->position_)
{
    damage_ = damage;
}

void DamageContext::PhysicsDamageContext::OnStartEffect(Entity& target, Health& health)
{
    health = Health(health.Value() - damage_.HitDamage());
}

void DamageContext::PhysicsDamageContext::OnUpdateEffect(Entity& target, Health& health)
{
    knockBackDuring_++;
    
    const auto knockBackDirection = (target.GetComponent<Transform>()->position_ - fromPos_).Normalize();

    b2Body_SetLinearVelocity(target.GetComponent<Collider>()->GetBodyId(),
                             (knockBackDirection * KNOCK_BACK_FORCE).ToB2Vec2());
}

bool DamageContext::PhysicsDamageContext::CheckUpdateCondition(Entity& target, const Health& health)
{
    return KNOCK_BACK_DURATION > knockBackDuring_;
}

void DamageContext::PhysicsDamageContext::OnExitEffect(Entity& target, Health& health)
{
}

const IDamageParam& DamageContext::PhysicsDamageContext::GetParam()
{
    return damage_;
}
