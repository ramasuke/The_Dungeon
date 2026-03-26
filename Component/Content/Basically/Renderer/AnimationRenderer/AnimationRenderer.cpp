#include "AnimationRenderer.h"

#include "../../../../../Application/IApplication/IApplication.hpp"
#include "../../../../../Helper/MyCalculator/MyCalculator.h"
#include "../../../../../Libs/ImGui/imgui.h"
#include "../../../../../Render/Render.h"

void AnimationRenderer::SetAnimation(const std::shared_ptr<Animation>& animation)
{
    animation_ = animation;
    OnRestaratAnimation();
}

bool AnimationRenderer::IsPlayingAnim() const
{
    return currentHandleIndex_ < animation_->splitCount_;
}

void AnimationRenderer::Init()
{
    transformRef_ = EntityRef().GetComponent<Transform>();
}

void AnimationRenderer::OnUpdate()
{
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

void AnimationRenderer::OnDraw()
{
    if (!animation_)
        return;

    if (!transformRef_ || animation_->handles_.empty())
        return;

    if (currentHandleIndex_ >= animation_->splitCount_)
        return;
    
    Render::DrawRotaGraphF(IApplication::GetInstance().Camera().position_ + transformRef_->position_ + offsetPos_,
                          transformRef_->rotation_,
                          transformRef_->scale_,
                          renderOrder_,
                          animation_->handles_[currentHandleIndex_],
                          isReverseX_);
}

void AnimationRenderer::OnDrawInspector()
{
    if (!animation_)
        return;

    animation_->OnDrawInspector();

    ImGuiHelper::OnDrawInputField("renderOrder_"      , renderOrder_        );
    ImGuiHelper::OnDrawInputField("effectDuring_frame", effectDuringFrame_  );
    if (ImGui::Button("RestartAnimation"))
    {
        OnRestaratAnimation();
    }
    ImGui::Text(std::to_string(currentHandleIndex_).c_str());
}

void AnimationRenderer::OnRestaratAnimation()
{
    animation_->Init();
    effectDuringFrame_ = 0;
    currentHandleIndex_ = 0;
}
