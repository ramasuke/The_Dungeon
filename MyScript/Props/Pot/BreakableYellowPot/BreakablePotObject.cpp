#include "BreakablePotObject.h"

#include "../../../../Component/Content/Basically/Transform/Transform.hpp"
#include "../../../../Entity/Entity.hpp"

void Prop::BreakablePotObject::OnDamage(std::shared_ptr<DamageContext::IDamageContext> damage)
{
    OnBreakPot();
}

void Prop::BreakablePotObject::OnBreakPot() const
{
    Entity::Spawn(breakingPotPrefabPath_, EntityRef().GetComponent<Transform>()->position_);
    EntityRef().OnDespawn();
}

Vector2 Prop::BreakablePotObject::Position() const
{
    return EntityRef().GetComponent<Transform>()->position_;
}
