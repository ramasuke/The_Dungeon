#include "DoorObject.h"

#include "../../Entity/Entity.hpp"
#include "../DamageNotation/Physics/DamageNotation.h"
#include "../Player/PlayerAvatar.h"

void DoorObject::OnDamage(const std::shared_ptr<DamageContext::IDamageContext> damage)
{
    auto& damageNotation = Entity::Spawn(DAMAGE_NOTATION_PREFAB_PATH, EntityRef().GetComponent<Transform>()->position_);
    damageNotation.GetComponent<DamageNotation>()->SetNotation(damage->GetParam().ToString(), damage->GetParam().Color());
    EntityRef().OnDespawn();
}

void DoorObject::Despawned()
{
    auto& particle = Entity::Spawn(ON_DESTROY_OBJECT_PARTICLE0, EntityRef().GetComponent<Transform>()->position_);
    const auto onDamageDirection = Player::PlayerAvatar::Model().Transform()->position_.x_ - EntityRef().GetComponent<Transform>()->position_.x_;
    particle.GetComponent<AnimationRenderer>()->isReverseX_ = onDamageDirection < 0;
}

Vector2 DoorObject::Position() const
{
    return EntityRef().GetComponent<Transform>()->position_;
}
