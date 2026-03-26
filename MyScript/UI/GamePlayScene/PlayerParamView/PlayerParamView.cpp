#include "PlayerParamView.h"

void GamePlayScene::PlayerParamView::PlayerParamView::Init()
{
    healthBarRef_.Init();
    madnessBarRef_.Init();
    skillSlotRef_.Init();
}

void GamePlayScene::PlayerParamView::PlayerParamView::OnDrawInspector()
{
    ImGuiHelper::OnDrawTreeInspector("healthBarRef", healthBarRef_);
    ImGuiHelper::OnDrawTreeInspector("madnessBarRef", madnessBarRef_);
    ImGuiHelper::OnDrawTreeInspector("skillSlotRef", skillSlotRef_);
}
