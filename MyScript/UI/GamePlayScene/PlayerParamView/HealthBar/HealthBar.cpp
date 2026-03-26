#include "HealthBar.h"

#include "../../../../../Component/Content/Basically/ImageRenderer/ImageRenderer.h"
#include "../../../../../Entity/Entity.hpp"
#include "../../../../../Helper/ImGui/ImGuiHelper.h"

void GamePlayScene::PlayerParamView::HealthBar::OnUpdateView(const Health health) const
{
    EntityRef().GetComponent<ImageRenderer>()->renderHandleId_ = barAnimation_->handles_.at(health.Value());
}

void GamePlayScene::PlayerParamView::HealthBar::Init()
{
    barAnimation_->Init();
}

void GamePlayScene::PlayerParamView::HealthBar::OnDrawInspector()
{
    ImGuiHelper::OnDrawTreeInspector("barAnimation", *barAnimation_);
}
