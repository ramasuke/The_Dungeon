#include "TorchObject.h"

#include "../../../Component/Content/Basically/Renderer/AnimationRenderer/AnimationRenderer.h"
#include "../../../Entity/Entity.hpp"
#include "../../../Libs/ImGui/imgui.h"
#include "../../DamageNotation/Physics/DamageNotation.h"
#include "../../FightParameter/MadnessEnergy/MadnessEnergyObject/MadnessEnergyObject.h"

void TorchObject::Init()
{
    animation_->Init();
    EntityRef().GetComponent<AnimationRenderer>()->SetAnimation(animation_);
}

void TorchObject::OnDrawInspector()
{
    if (ImGui::TreeNode("animation"))
    {
        animation_->OnDrawInspector();
        ImGui::TreePop();
        ImGui::Spacing();
    }
    if (ImGui::TreeNode("dropComboEnergy"))
    {
        dropComboEnergy_.OnDrawInspector();
        ImGui::TreePop();
        ImGui::Spacing();
    }
}

void TorchObject::OnDamage(const std::shared_ptr<DamageContext::IDamageContext> damage)
{
    auto& damageNotation = Entity::Spawn(DAMAGE_NOTATION_PREFAB_PATH, EntityRef().GetComponent<Transform>()->position_);
    damageNotation.GetComponent<DamageNotation>()->SetNotation(damage->GetParam().ToString(), damage->GetParam().Color());
    auto& dropEnergy = Entity::Spawn(MADNESS_ENERGY_OBJECT_PREFAB_PATH, EntityRef().GetComponent<Transform>()->position_);
    dropEnergy.GetComponent<MadnessEnergyObject>()->SetEnergy(dropComboEnergy_);
    Entity::Spawn(onDestroyParticlePrefabPath_, EntityRef().GetComponent<Transform>()->position_ + onDestroyParticleOffset_);
    EntityRef().OnDespawn();
}

Vector2 TorchObject::Position() const
{
    return EntityRef().GetComponent<Transform>()->position_;
}
