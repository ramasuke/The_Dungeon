#include "WoodNail.h"

#include "../../DamageNotation/Physics/DamageNotation.h"

void Prop::WoodNail::Awake()
{
    trapRoomRef_.Init();
}

void Prop::WoodNail::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("trapRoomRef", trapRoomRef_);
}

void Prop::WoodNail::OnDamage(const std::shared_ptr<DamageContext::IDamageContext> damageContext)
{
    auto& damageNotation = Entity::Spawn(DAMAGE_NOTATION_PREFAB_PATH, EntityRef().GetComponent<Transform>()->position_);
    damageNotation.GetComponent<DamageNotation>()->SetNotation(damageContext->GetParam().ToString(), damageContext->GetParam().Color());
    EntityRef().OnDespawn();
}

void Prop::WoodNail::Despawned()
{
    auto& particle = Entity::Spawn(ON_DESTROY_OBJECT_PARTICLE0, EntityRef().GetComponent<Transform>()->position_);
    const auto onDamageDirection = Player::PlayerAvatar::Model().Transform()->position_.x_ - EntityRef().GetComponent<Transform>()->position_.x_;
    particle.GetComponent<AnimationRenderer>()->isReverseX_ = onDamageDirection < 0;
    trapRoomRef_.Value()->EntityRef().OnDespawn();
}

Vector2 Prop::WoodNail::Position() const
{
    return EntityRef().GetComponent<Transform>()->position_;
}
