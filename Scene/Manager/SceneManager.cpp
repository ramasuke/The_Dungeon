#include "SceneManager.h"

#include "../../Application/IApplication/IApplication.hpp"

void SceneManager::OnLoadSceneAsync(const std::string& filePath)
{
    onLoadScenes_.push(filePath);
}

void SceneManager::OnUnloadScene(const std::string& unloadSceneResourceFilePath)
{
    onUnloadScenes_.push(unloadSceneResourceFilePath);
}

void SceneManager::OnUnloadAllScene()
{
    for (const auto& currentScene : currentScenes_)
    {
        onUnloadScenes_.push(currentScene->ResourceFilePath());
    }
}

void SceneManager::OnUpdate()
{
    while (!onUnloadScenes_.empty())
    {
        const auto unloadSceneFilePath = onUnloadScenes_.top();

        const auto it = std::find_if(currentScenes_.begin(), currentScenes_.end(),
                                     [&](const std::unique_ptr<Scene>& scene)
                                     {
                                         return scene->ResourceFilePath() == unloadSceneFilePath;
                                     });

        if (it != currentScenes_.end())
        {
            currentScenes_.erase(it);
        }

        if (unloadSceneFilePath == "Resource/Scene/SelectStageScene.json"
            || unloadSceneFilePath == "Resource/Scene/TutorialScene.json"
            || unloadSceneFilePath == "Resource/Scene/Dungeon1-1.json"
            || unloadSceneFilePath == "Resource/Scene/Dungeon1-2.json"
            || unloadSceneFilePath == "Resource/Scene/Dungeon1-3.json"
            || unloadSceneFilePath == "Resource/Scene/Dungeon1-4.json")
        {
            for (const auto& pair : IApplication::GetInstance().EntityContainer().AllEntities())
            {
                Entity* entity = pair.second;
                bool isFind = false;
                for (const auto& scene : currentScenes_)
                {
                    if (scene->FindEntity(entity->GetGuid()) == nullptr && !isFind)
                    {
                        isFind = false;
                    }
                    else
                    {
                        isFind = true;
                    }
                }
                if (isFind == false)
                {
                    if (entity->Name() != "Empty")
                    {
                        entity->OnDespawn();
                    }
                }
            }
        }

        onUnloadScenes_.pop();
    }

    while (!onLoadScenes_.empty())
    {
        const std::string& filePath = onLoadScenes_.top();
        auto scene = std::make_unique<Scene>();
        scene->OnDeserialize(filePath);
        currentScenes_.push_back(std::move(scene));
        onLoadScenes_.pop();
    }

    for (const auto& scene : currentScenes_)
    {
        scene->TryCompleteSceneLoad();
    }
}

bool SceneManager::OnTryRemoveSceneEntity(Entity* remove) const
{
    if (currentScenes_.empty())
        return false;

    bool isSuccessOnRemoveEntity = false;
    for (const auto& scene : currentScenes_)
    {
        isSuccessOnRemoveEntity = scene->OnTryRemoveSceneEntity(remove);

        if (isSuccessOnRemoveEntity)
            break;
    }
    return isSuccessOnRemoveEntity;
}
