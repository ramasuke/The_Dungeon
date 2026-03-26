#include "LoadingIcon.h"

#include "../../../../Component/Content/Basically/ImageRenderer/ImageRenderer.h"
#include "../../../../Entity/Entity.hpp"
#include "../../../../Helper/ImGui/ImGuiHelper.h"

void LoadingScene::LoadingIcon::Init()
{
    animation_->Init();
    imageRenderer_ = EntityRef().GetComponent<ImageRenderer>();
}

void LoadingScene::LoadingIcon::OnUpdate()
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
    
    imageRenderer_->renderHandleId_ = animation_->handles_[currentHandleIndex_];
}

void LoadingScene::LoadingIcon::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("animation", animation_);
}
