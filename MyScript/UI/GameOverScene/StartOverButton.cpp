#include "StartOverButton.h"

#include <DxLib.h>

#include "../../../Application/IApplication/IApplication.hpp"
#include "../../../Component/Content/Basically/Ui/Button/Button.h"
#include "../../../Entity/Entity.hpp"

void GameOverScene::StartOverButton::Init()
{
    SetMouseDispFlag(true);
}

void GameOverScene::StartOverButton::Awake()
{
    EntityRef().GetComponent<Ui::Button>()->SubscribeOnClickEvent([this](MouseState)
    {
        OnClickEvent();
    });
}

void GameOverScene::StartOverButton::OnClickEvent()
{
    IApplication::GetInstance().SceneManager().OnUnloadAllScene();
    IApplication::GetInstance().SceneManager().OnLoadSceneAsync("Resource/Scene/Dungeon1-1.json");
    IApplication::GetInstance().SceneManager().OnLoadSceneAsync("Resource/Scene/PlayerParamScene.json");
    IApplication::GetInstance().SceneManager().OnLoadSceneAsync("Resource/Scene/MoveControllExplainUiScene.json");
    SetMouseDispFlag(false);
    IApplication::GetInstance().OnDeserialize();
}
