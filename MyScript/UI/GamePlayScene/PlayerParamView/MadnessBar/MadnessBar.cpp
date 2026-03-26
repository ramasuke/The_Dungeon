#include "MadnessBar.h"

#include "../../../../../Component/Content/Basically/ImageRenderer/ImageRenderer.h"
#include "../../../../../Entity/Entity.hpp"
#include "../../../../../Helper/ImGui/ImGuiHelper.h"

void GamePlayScene::PlayerParamView::MadnessBar::OnUpdateView(const MadnessEnergy madnessEnergy) const
{
    EntityRef().GetComponent<ImageRenderer>()->renderHandleId_ = barAnimation_->handles_.at(madnessEnergy.Value());
}

void GamePlayScene::PlayerParamView::MadnessBar::Init()
{
    barAnimation_->Init();
}

void GamePlayScene::PlayerParamView::MadnessBar::OnDrawInspector()
{
    ImGuiHelper::OnDrawTreeInspector("barAnimation", *barAnimation_);
}
