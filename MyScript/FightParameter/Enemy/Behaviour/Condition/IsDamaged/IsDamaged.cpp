#include "IsDamaged.h"

#include <utility>

Enemy::Behaviour::Condition::IsDamaged::IsDamaged(std::queue<std::shared_ptr<DamageContext::IDamageContext>>& onDamages)
    : onDamagesRef_(onDamages)
{
}

bool Enemy::Behaviour::Condition::IsDamaged::operator()() const
{
    return !onDamagesRef_.empty();
}
