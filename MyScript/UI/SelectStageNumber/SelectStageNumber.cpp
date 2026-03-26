#include "SelectStageNumber.h"

#include "../../../BasicallyParameter/Sound/Play/SoundPlay.h"
#include "../../../Component/Content/Basically/ImageRenderer/ImageRenderer.h"
#include "../../../Component/Content/Basically/Renderer/TextRenderer/TextRenderer.h"
#include "../../../Helper/ImGui/ImGuiHelper.h"
#include "../../../Libs/ImGui/imgui.h"
#include "../../Sound/HandleContainer/HandleContainer.h"

void StageSelectScene::SelectStageNumber::Awake()
{
    Sound::PlaySe(Sound::StageSelect::OpenBook());
    onNextStageSelect_ .Init();
    onMinusStageSelect_.Init();
    stageMovieRenderer_.Init();
    stageMovieRenderer_.Value()->SetResourceFilePath(stageMovieResourcePaths_.at(currentSelectStageNumber_));
    
    if (!onNextStageSelect_.Value())
        return;

    onMinusStageSelect_.Value()->EntityRef().GetComponent<ImageRenderer>()->isReverseX_ = true;
    onNextStageSelect_.Value()->SubscribeOnClickEvent([this](MouseState)
    {
        if (currentSelectStageNumber_ >= stageMovieResourcePaths_.size() - 1)
            return;

        currentSelectStageNumber_++;
        stageMovieRenderer_.Value()->SetResourceFilePath(stageMovieResourcePaths_.at(currentSelectStageNumber_));
    });
    onMinusStageSelect_.Value()->SubscribeOnClickEvent([this](MouseState)
    {
        if (currentSelectStageNumber_ < 1)
            return;
        
        currentSelectStageNumber_--;
        stageMovieRenderer_.Value()->SetResourceFilePath(stageMovieResourcePaths_.at(currentSelectStageNumber_));
    });
}

void StageSelectScene::SelectStageNumber::OnUpdate()
{
    EntityRef().GetComponent<TextRenderer>()->text_ = stageNames_.at(currentSelectStageNumber_);
}

void StageSelectScene::SelectStageNumber::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("stageNames_", stageNames_, [this]
    {
        if (ImGui::Button("Add StageName"))
        {
            stageNames_.emplace_back("");
        }
    });
    ImGui::InputInt("stageNumber_", &currentSelectStageNumber_);
    ImGuiHelper::OnDrawInputField("onNextStageSelect_", onNextStageSelect_);
    ImGuiHelper::OnDrawInputField("onMinusStageSelect_", onMinusStageSelect_);
    ImGuiHelper::OnDrawInputField("stageMovieRenderer_", stageMovieRenderer_);
}
