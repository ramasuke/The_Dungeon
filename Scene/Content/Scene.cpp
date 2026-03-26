#include <cereal/types/memory.hpp>
#include <fstream>
#include <cereal/types/vector.hpp>
#include <cereal/archives/json.hpp>
#include "Scene.hpp"

#include "../../Application/ApplicationParameter.h"
#include "../../Application/IApplication/IApplication.hpp"
#include "../../Application/Screen/ScreenHelper.h"
#include "../../Component/Content/Basically/Transform/Transform.hpp"

void Scene::OnSerialize(const std::string& filePath)
{
    std::ofstream ofStream(filePath);
    cereal::JSONOutputArchive archive(ofStream);
    archive(cereal::make_nvp("Entities", entities_));
}

void Scene::OnDeserialize(const std::string& filePath)
{
    resourceFilePath_ = filePath;
    entitiesReady_ = false;
    entitiesInitialized_ = false;

    loaderThread_ = std::thread([this, filePath]() {
        std::ifstream ifStream(filePath);
        cereal::JSONInputArchive archive(ifStream);

        std::vector<std::unique_ptr<Entity>> loadedEntities;
        archive(cereal::make_nvp("Entities", loadedEntities));
        {
            std::lock_guard<std::mutex> lock(entitiesMutex_);
            entities_ = std::move(loadedEntities);
        }

        entitiesReady_ = true;
    });
    loaderThread_.detach(); // 非同期で走らせる
}

void Scene::TryCompleteSceneLoad()
{
    if (entitiesReady_ && !entitiesInitialized_)
    {
        std::lock_guard<std::mutex> lock(entitiesMutex_);

        for (const auto& entity : entities_) {
            entity->InitSceneEntity();
        }
        for (const auto& entity : entities_) {
            entity->Init();
        }

        entitiesInitialized_ = true;
    }
}

void Scene::OnDrawDebug()
{
    for (const auto& entity : entities_)
    {
        entity->OnDrawDebug();
    }

    static std::string filePath = "Resource/Prefab/Sample.json";
    char nameBuffer[256];
    strncpy_s(nameBuffer, filePath.c_str(), sizeof(nameBuffer));
    ImGui::InputText("filePath: ", nameBuffer, sizeof(nameBuffer));
    filePath = nameBuffer;
    if (ImGui::Button("New Entity From Prefab"))
    {
        auto entity = std::make_unique<Entity>();
        entity->OnDeserialize(filePath);
        entity->GetComponent<Transform>()->position_ = Screen::CameraCenterWorldPos();
        entities_.push_back(std::move(entity));
    }
    if (ImGui::Button("New Entity"))
    {
        auto entity = std::make_unique<Entity>();
        entity->AddComponent<Transform>();
        entity->GetComponent<Transform>()->position_ = Screen::CameraCenterWorldPos();
        entities_.push_back(std::move(entity));
    }
    if (ImGui::TreeNode("delete Entity"))
    {
        static Guid guid;
        ImGuiHelper::OnDrawInputField("guid", guid);

        if (ImGui::Button("delete"))
        {
            const auto deleteEntity = FindEntity(guid);
            if (deleteEntity != nullptr)
            {
                deleteEntity->OnDespawn();
            }
        }
        ImGui::TreePop();
        ImGui::Spacing();
    }
}

bool Scene::OnTryRemoveSceneEntity(Entity* remove)
{
    const auto it = std::remove_if(entities_.begin(), entities_.end(),
                                   [remove](const std::unique_ptr<Entity>& e)
                                   {
                                       return e.get() == remove;
                                   });

    if (it != entities_.end())
    {
        entities_.erase(it, entities_.end());
        return true;
    }
    return false;
}

const std::vector<std::unique_ptr<Entity>>& Scene::Entities()
{
    return entities_;
}

Entity* Scene::FindEntity(const Guid& guid) const
{
    for (const auto& entity : entities_)
    {
        if (entity && entity->GetGuid() == guid)
        {
            return entity.get();
        }
    }
    return nullptr;
}
