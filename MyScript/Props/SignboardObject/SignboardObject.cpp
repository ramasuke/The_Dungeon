#include "SignboardObject.h"

#include "../../../Component/Content/Basically/Renderer/AnimationRenderer/AnimationRenderer.h"
#include "../../../Entity/Entity.hpp"
#include "../../DamageNotation/Physics/DamageNotation.h"

void Prop::SignboardObject::OnDrawInspector()
{
    
}

void Prop::SignboardObject::OnDamage(const std::shared_ptr<DamageContext::IDamageContext> damage)
{
    auto& damageNotation = Entity::Spawn(DAMAGE_NOTATION_PREFAB_PATH, EntityRef().GetComponent<Transform>()->position_);
    damageNotation.GetComponent<DamageNotation>()->SetNotation(damage->GetParam().ToString(), damage->GetParam().Color());
    Entity::Spawn(ON_DESTROY_OBJECT_PARTICLE0, EntityRef().GetComponent<Transform>()->position_);
    EntityRef().OnDespawn();
}

Vector2 Prop::SignboardObject::Position() const
{
    return EntityRef().GetComponent<Transform>()->position_;
}
