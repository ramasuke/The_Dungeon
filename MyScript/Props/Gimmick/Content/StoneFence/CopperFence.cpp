#include "CopperFence.h"
#include "../../../../../Entity/Entity.hpp"
#include "../../../../../Helper/ImGui/ImGuiHelper.h"

void Prop::CopperFence::Init()
{
    downFenceAnimation_->Init();
    idleFenceAnimation_->Init();
}

void Prop::CopperFence::Awake()
{
    const auto animationRenderer = EntityRef().GetComponent<AnimationRenderer>();
    animationRenderer->SetAnimation(idleFenceAnimation_);
}

void Prop::CopperFence::OnUpdate()
{
    if (!EntityRef().GetComponent<AnimationRenderer>()->IsPlayingAnim())
    {
        EntityRef().OnDespawn();
    }
}

void Prop::CopperFence::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("idleFenceAnimation", idleFenceAnimation_);
    ImGuiHelper::OnDrawInputField("downFenceAnimation", downFenceAnimation_);
}

void Prop::CopperFence::OnStartGimmick()
{
    if (isGimmicked_)
        return;

    isGimmicked_ = true;
    const auto animationRenderer = EntityRef().GetComponent<AnimationRenderer>();
    animationRenderer->SetAnimation(downFenceAnimation_);
}
