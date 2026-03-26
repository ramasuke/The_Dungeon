#pragma once
#include "../DamageContext/Physics/PhysicsDamageContext.h"

class IReceivableEnemyAttack
{
public:
    virtual ~IReceivableEnemyAttack() = default;
    virtual void OnDamage(std::shared_ptr<DamageContext::IDamageContext> damage) = 0;
};
