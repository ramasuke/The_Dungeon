#include "Portal.h"

#include "../../Application/IApplication/IApplication.hpp"

void Portal::Portal::Init()
{
    animation_->Init();
    EntityRef().GetComponent<AnimationRenderer>()->SetAnimation(animation_);
}

void Portal::Portal::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("animation", animation_);

    ImGuiHelper::OnDrawInputField("unloadSceneFilePaths", unloadSceneFilePaths_, [this]()
    {
        OnDrawAddButton(unloadSceneFilePaths_);
    });
    ImGuiHelper::OnDrawInputField("nextSceneFilePaths", nextSceneFilePaths_, [this]()
    {
        OnDrawAddButton(nextSceneFilePaths_);
    });
}


void Portal::Portal::OnDrawAddButton(std::vector<std::string>& container)
{
    if (ImGui::Button("add"))
    {
        container.emplace_back("Resource/Scene/TutorialScene.json");
    }
}

void Portal::Portal::OnBeginSensor(b2SensorBeginTouchEvent*, Player::PlayerAvatar* collisionPlayer)
{
    collisionPlayer->Controller().SetActive(false);
    for (const auto& unloadSceneFilePath : unloadSceneFilePaths_)
    {
        IApplication::GetInstance().SceneManager().OnUnloadScene(unloadSceneFilePath);
    }
    for (const auto& nextSceneFilePath : nextSceneFilePaths_)
    {
        IApplication::GetInstance().SceneManager().OnLoadSceneAsync(nextSceneFilePath);
    }
}
