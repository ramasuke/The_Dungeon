#include "StoneShootArrowTrap.h"

#include "../../../../../Component/Content/Basically/Collider/Collider.h"
#include "../../../../../Component/Content/Basically/Renderer/AnimationRenderer/AnimationRenderer.h"
#include "../../../../../Entity/Entity.hpp"
#include "../../../../../Helper/ImGui/ImGuiHelper.h"
#include "../../../../FightParameter/Enemy/BoxAttackArea/EnemyBoxAttackArea.h"

void Prop::Trap::StoneShootArrowTrap::Init()
{
    EntityRef().GetComponent<AnimationRenderer>()->SetAnimation(animation_);
}

void Prop::Trap::StoneShootArrowTrap::OnUpdate()
{
    summonArrowDuring_++;
    if (summonArrowDuration_ > summonArrowDuring_)
        return;

    summonArrowDuring_ = 0;
    auto& arrow = Entity::Spawn(summonArrowPrefabPath_,
                                EntityRef().GetComponent<Transform>()->position_ + summonArrowOffset_);
    arrow.GetComponent<Transform>()->rotation_ = summonArrowVelocity_.ToDegree();
}

void Prop::Trap::StoneShootArrowTrap::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("animation", animation_);
    ImGuiHelper::OnDrawInputField("summonArrowDuring", summonArrowDuring_);
    ImGuiHelper::OnDrawInputField("summonArrowDuration", summonArrowDuration_);
    if (ImGui::TreeNode("summonArrowOffset"))
    {
        summonArrowOffset_.OnDrawDebug();
        ImGui::TreePop();
        ImGui::Spacing();
    }
    if (ImGui::TreeNode("summonArrowVelocity"))
    {
        summonArrowVelocity_.OnDrawDebug();
        ImGui::TreePop();
        ImGui::Spacing();
    }
    ImGuiHelper::OnDrawInputField("summonArrowPrefabPath", summonArrowPrefabPath_);
}
