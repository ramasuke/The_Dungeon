#include "BreakingYellowPot.h"

#include "../../../../Component/Content/Basically/Renderer/AnimationRenderer/AnimationRenderer.h"
#include "../../../../Entity/Entity.hpp"

void Prop::BreakingYellowPot::Init()
{
    animation_->Init();
    EntityRef().GetComponent<AnimationRenderer>()->SetAnimation(animation_);
}

void Prop::BreakingYellowPot::OnDrawInspector()
{
    if (ImGui::TreeNode("animation"))
    {
        animation_->OnDrawInspector();
        ImGui::TreePop();
        ImGui::Spacing();
    }
}
