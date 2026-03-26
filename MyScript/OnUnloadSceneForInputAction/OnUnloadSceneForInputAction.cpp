#include "OnUnloadSceneForInputAction.h"

#include "../../Application/IApplication/IApplication.hpp"
#include "../Player/Model/State/IState/IPlayerState.hpp"

void OnUnloadSceneForInputAction::OnUpdate()
{
    static Player::PlayerController controller;
    
    if (controller.ConsumptionMadnessAction().IsUpdatePressed())
    {
        IApplication::GetInstance().SceneManager().OnUnloadScene(unloadSceneFilePath_);
    }
}

void OnUnloadSceneForInputAction::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("unloadSceneFilePath", unloadSceneFilePath_);
}
