#include "Barrel0Object.h"

#include "../../../Component/Content/Basically/Renderer/AnimationRenderer/AnimationRenderer.h"
#include "../../../Entity/Entity.hpp"
#include "../../../Libs/ImGui/imgui.h"
#include "../../DamageNotation/Physics/DamageNotation.h"
#include "../../FightParameter/MadnessEnergy/MadnessEnergyObject/MadnessEnergyObject.h"
#include "../../Player/PlayerAvatar.h"
#include "../../Player/Model/State/IState/IPlayerState.hpp"

void Prop::Barrel0Object::OnDrawInspector()
{
    if (ImGui::TreeNode("dropComboEnergy"))
    {
        dropComboEnergy_.OnDrawInspector();
        ImGui::TreePop();
        ImGui::Spacing();
    }
}

void Prop::Barrel0Object::OnDamage(const std::shared_ptr<DamageContext::IDamageContext> damage)
{
    auto& damageNotation = Entity::Spawn(DAMAGE_NOTATION_PREFAB_PATH, EntityRef().GetComponent<Transform>()->position_);
    damageNotation.GetComponent<DamageNotation>()->SetNotation(damage->GetParam().ToString(), damage->GetParam().Color());
    auto& dropEnergy = Entity::Spawn(MADNESS_ENERGY_OBJECT_PREFAB_PATH, EntityRef().GetComponent<Transform>()->position_);
    dropEnergy.GetComponent<MadnessEnergyObject>()->SetEnergy(dropComboEnergy_);
    auto& particle = Entity::Spawn(ON_DESTROY_OBJECT_PARTICLE0, EntityRef().GetComponent<Transform>()->position_);
    const auto onDamageDirection = damage->FromPos().x_ - EntityRef().GetComponent<Transform>()->position_.x_;
    particle.GetComponent<AnimationRenderer>()->isReverseX_ = onDamageDirection < 0;
    EntityRef().OnDespawn();
}

Vector2 Prop::Barrel0Object::Position() const
{
    return EntityRef().GetComponent<Transform>()->position_;
}
