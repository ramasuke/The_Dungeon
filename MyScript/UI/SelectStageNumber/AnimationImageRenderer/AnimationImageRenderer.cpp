#include "AnimationImageRenderer.h"

#include "../../../../../Render/Render.h"
#include "../../../../../Helper/ImGui/ImGuiHelper.h"
#include "../../../../../Libs/ImGui/imgui.h"
#include "../../../../Entity/Entity.hpp"

void AnimationImageRenderer::SetAnimation(const std::shared_ptr<Animation>& animation)
{
    animation_ = animation;
    RestartAnimation();
}

bool AnimationImageRenderer::IsPlayingAnim() const
{
    return currentHandleIndex_ < animation_->splitCount_;
}

void AnimationImageRenderer::Init()
{
    animation_->Init();
    transformRef_ = EntityRef().GetComponent<Transform>();
}

void AnimationImageRenderer::OnUpdate()
{
    if (!animation_)
        return;

    effectDuringFrame_++;

    if (effectDuringFrame_ < animation_->effectDuration_frame_)
        return;

    effectDuringFrame_ = 0;

    if (animation_->isRoop_ && currentHandleIndex_ >= animation_->splitCount_ - 1)
    {
        currentHandleIndex_ = 0;
    }
    else
    {
        currentHandleIndex_++;
    }
}

void AnimationImageRenderer::OnDraw()
{
    if (!transformRef_ || !animation_)
        return;

    if (animation_->handles_.empty())
        return;

    if (currentHandleIndex_ >= animation_->splitCount_)
        return;

    // ★ UIなので Camera を使わない
    Render::DrawRotaGraphF(
        transformRef_->position_ + offsetPos_,
        transformRef_->rotation_,
        transformRef_->scale_,
        renderOrder_,
        animation_->handles_[currentHandleIndex_],
        isReverseX_
    );
}

void AnimationImageRenderer::OnDrawInspector()
{
    if (!animation_)
        return;

    animation_->OnDrawInspector();

    ImGuiHelper::OnDrawInputField("renderOrder", renderOrder_);
    if (ImGui::TreeNode("offsetPos"))
    {
        offsetPos_.OnDrawDebug();
        ImGui::TreePop();
        ImGui::Spacing();
    }
    ImGui::Checkbox("isReverseX", &isReverseX_);

    if (ImGui::Button("RestartAnimation"))
    {
        RestartAnimation();
    }

    ImGui::Text("CurrentFrame : %d", currentHandleIndex_);
}

void AnimationImageRenderer::RestartAnimation()
{
    animation_->Init();
    effectDuringFrame_  = 0;
    currentHandleIndex_ = 0;
}
