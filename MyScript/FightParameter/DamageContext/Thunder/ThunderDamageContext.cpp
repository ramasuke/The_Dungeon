#include "ThunderDamageContext.h"

#include "../../../../Component/Content/Basically/Collider/Collider.h"
#include "../../../../Component/Content/Basically/Transform/Transform.hpp"
#include "../../../../Entity/Entity.hpp"
#include "../../../../Libs/Box2D/include/src/box2d/box2d.h"
#include "../IReceivable/IReceivableDamage.h"

DamageContext::ThunderDamageContext::ThunderDamageContext(Entity& fromEntity, const ThunderPower& damage)
    :fromPos_(fromEntity.GetComponent<Transform>()->position_)
{
    damage_ = damage;
}

void DamageContext::ThunderDamageContext::OnStartEffect(Entity& target, Health& healthRef)
{
    healthRef = Health(healthRef.Value() - damage_.HitDamage());
    if (target.GetComponent<IReceivableDamage<ThunderPower>>() == nullptr)
        return;

    target.GetComponent<IReceivableDamage<ThunderPower>>()->OnTypeDamage(damage_);
}

void DamageContext::ThunderDamageContext::OnUpdateEffect(Entity& target, Health& health)
{
    numbDuring_++;
    b2Body_SetLinearVelocity(target.GetComponent<Collider>()->GetBodyId(), b2Vec2{0, 0});
}

bool DamageContext::ThunderDamageContext::CheckUpdateCondition(Entity& target, const Health& health)
{
    return damage_.NumbDuration() > numbDuring_;
}

void DamageContext::ThunderDamageContext::OnExitEffect(Entity& target, Health& health)
{
}

const IDamageParam& DamageContext::ThunderDamageContext::GetParam()
{
    return damage_;
}
