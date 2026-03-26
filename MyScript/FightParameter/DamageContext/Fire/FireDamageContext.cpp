#include "FireDamageContext.h"

#include "../../../../../Entity/Entity.hpp"
#include "../../../../Component/Content/Basically/Transform/Transform.hpp"
#include "../IReceivable/IReceivableDamage.h"

FireDamageContext::FireDamageContext(Entity& fromEntity, const FirePower& damage)
    : fromPos_(fromEntity.GetComponent<Transform>()->position_)
{
    damage_ = damage;
}

void FireDamageContext::OnStartEffect(Entity& target, Health& healthRef)
{
    healthRef = Health(healthRef.Value() - damage_.HitDamage());
    if (target.GetComponent<IReceivableDamage<FirePower>>() == nullptr)
        return;

    target.GetComponent<IReceivableDamage<FirePower>>()->OnTypeDamage(damage_);
}

void FireDamageContext::OnUpdateEffect(Entity& target, Health& health)
{
    burnDuring_++;
    health = Health(health.Value() - damage_.BurnDamage());
}

bool FireDamageContext::CheckUpdateCondition(Entity& target, const Health& health)
{
    return damage_.BurnDuration() > burnDuring_;
}

void FireDamageContext::OnExitEffect(Entity& target, Health& health)
{
    burnDuring_ = 0;
}

const IDamageParam& FireDamageContext::GetParam()
{
    return damage_;
}
