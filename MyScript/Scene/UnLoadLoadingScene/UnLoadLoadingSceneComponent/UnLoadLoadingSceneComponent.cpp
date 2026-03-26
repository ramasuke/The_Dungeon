#include "UnLoadLoadingSceneComponent.h"

#include "../../../../Application/IApplication/IApplication.hpp"

void LoadingScene::UnLoadLoadingSceneComponent::Awake()
{
    IApplication::GetInstance().SceneManager().OnUnloadScene("Resource/Scene/LoadingScene.json");
}
