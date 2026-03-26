#include "ResourceManageContainerGroup.h"

#include "../../../Application/IApplication/IApplication.hpp"
#include "../../../Entity/ResourceManageContainer/EntityResourceManageContainer.h"
#include "../../../Libs/ImGui/imgui.h"
#include "../../../Scene/ResourceManageContaienr/SceneResourceManageContainer.h"

ResourceManageContainerGroup::ResourceManageContainerGroup()
{
    entityResourceContainer_    = std::make_unique<EntityResourceManageContainer>("Resource/Prefab");
    sceneResourceContainer_     = std::make_unique<SceneResourceManageContainer>("Resource/Scene");
}

void ResourceManageContainerGroup::OnDrawDebugWindow()
{
    ImGui::Begin("Resources");
    if (ImGui::Button("OnSaveResource"))
    {
        entityResourceContainer_->OnSaveResources();
        sceneResourceContainer_->OnSaveResources();
        IApplication::GetInstance().OnSerialize();
    }
    OnDrawContainerDebugWindow(entityResourceContainer_);
    OnDrawContainerDebugWindow(sceneResourceContainer_);
    ImGui::End();

    entityResourceContainer_->OnUpdate();
    sceneResourceContainer_->OnUpdate();
}

ResourceManageContainerBase<Entity, Entity>& ResourceManageContainerGroup::EntityResourceContainer() const
{
    return *entityResourceContainer_;
}

ResourceManageContainerBase<Scene, Entity>& ResourceManageContainerGroup::SceneResourceContainer() const
{
    return *sceneResourceContainer_;
}
