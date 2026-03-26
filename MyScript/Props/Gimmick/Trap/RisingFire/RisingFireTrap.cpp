#include "RisingFireTrap.h"

#include "../../../../../Component/Content/Basically/Renderer/AnimationRenderer/AnimationRenderer.h"
#include "../../../../../Entity/Entity.hpp"
#include "../../../../FightParameter/Enemy/Behaviour/Action/SpawnAttackArea/SpawnBoxAttackArea.h"

void Prop::Trap::RisingFireTrap::Init()
{
    EntityRef().GetComponent<AnimationRenderer>()->SetAnimation(animation_);
}

void Prop::Trap::RisingFireTrap::OnUpdate()
{
    trapBootDuring_++;
    if (trapBootDuration_ > trapBootDuring_)
        return;
    
    const auto collider = Entity::Spawn<Enemy::EnemyBoxAttackArea>(ENEMY_BOX_ATTACK_AREA_PREFAB_PATH,
                                                            EntityRef().GetComponent<Transform>()->position_);
    
    collider->InitArea(std::make_shared<DamageContext::PhysicsDamageContext>(EntityRef(), damage_), boxAttackAreaModel_);
    
    trapBootDuring_ = 0;
}

void Prop::Trap::RisingFireTrap::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("animation"       , animation_        );
    ImGuiHelper::OnDrawInputField("trapBootDuration", trapBootDuration_ );
    ImGuiHelper::OnDrawInputField("trapBootDuring"  , trapBootDuring_   );
    ImGuiHelper::OnDrawInputField("damage"          , damage_           );
    
    if (ImGui::TreeNode("boxAttackArea"))
    {
        boxAttackAreaModel_.OnDrawInspector(EntityRef());
        ImGui::TreePop();
        ImGui::Spacing();
    }
}
