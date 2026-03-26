#include "IsDeath.h"

Enemy::Behaviour::Condition::IsDeath::IsDeath(Health& hp)
    : hp_(hp)
{
}

bool Enemy::Behaviour::Condition::IsDeath::operator()() const
{
    return hp_.IsDeath();
}
