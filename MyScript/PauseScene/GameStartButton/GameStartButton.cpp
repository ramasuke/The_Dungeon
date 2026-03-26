#include "GameStartButton.h"

#include <DxLib.h>

#include "../../../BasicallyParameter/Sound/Play/SoundPlay.h"
#include "../../../Component/Content/Basically/Ui/Button/Button.h"
#include "../../../Entity/Entity.hpp"
#include "../../Player/PlayerAvatar.h"

void PauseScene::GameStartButton::Init()
{
    gameStartText_.Init();
}

void PauseScene::GameStartButton::Awake()
{
    SetMouseDispFlag(true);
    EntityRef().GetComponent<Ui::Button>()->SubscribeOnReleaseEvent(
        [this] { OnReleaseButton(); }
    );
    selectStageNumber_.Init();
}

void PauseScene::GameStartButton::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("selectStageNumber_", selectStageNumber_);
    ImGuiHelper::OnDrawInputField("sceneNames_", sceneNames_, [this]
    {
        if (ImGui::Button("Add sceneNames_"))
        {
            sceneNames_.emplace_back("");
        }
    });
    
    if (ImGui::TreeNode("playerAvatar"))
    {
        ImGui::TreePop();
        ImGui::Spacing();
    }
    if (ImGui::TreeNode("gameStartText"))
    {
        gameStartText_.OnDrawInspector();
        ImGui::TreePop();
        ImGui::Spacing();
    }
}

void PauseScene::GameStartButton::OnReleaseButton()
{
    SetMouseDispFlag(false);
    IApplication::GetInstance().SceneManager().OnUnloadScene("Resource/Scene/StageSeleScene.json");
    IApplication::GetInstance().SceneManager().OnUnloadScene("Resource/Scene/SelectStageScene.json");
    IApplication::GetInstance().SceneManager().OnUnloadScene("Resource/Scene/TutorialScene.json");
    IApplication::GetInstance().SceneManager().OnUnloadScene("Resource/Scene/Dungeon1-1.json");
    IApplication::GetInstance().SceneManager().OnUnloadScene("Resource/Scene/Dungeon1-2.json");
    IApplication::GetInstance().SceneManager().OnUnloadScene("Resource/Scene/Dungeon1-3.json");
    IApplication::GetInstance().SceneManager().OnUnloadScene("Resource/Scene/Dungeon1-4.json");
    IApplication::GetInstance().SceneManager().OnLoadSceneAsync(sceneNames_.at(selectStageNumber_.Value()->CurrentStageNumber()));
    IApplication::GetInstance().SceneManager().OnLoadSceneAsync("Resource/Scene/LoadingScene.json");
}
