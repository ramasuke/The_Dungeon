#pragma once
#include <memory>
#include "../ResourceManageContainerBase.h"
#include "../../../Entity/Entity.hpp"
#include "../../../Scene/Content/Scene.hpp"

class SceneResourceManageContainer;

class ResourceManageContainerGroup final
{
public:
    ResourceManageContainerGroup();
    void OnDrawDebugWindow();
    ResourceManageContainerBase<Entity, Entity>& EntityResourceContainer() const;
    ResourceManageContainerBase<Scene, Entity>& SceneResourceContainer() const;

private:
    template <typename T, typename T1>
    void OnDrawContainerDebugWindow(std::unique_ptr<ResourceManageContainerBase<T, T1>>&);
    std::unique_ptr<ResourceManageContainerBase<Entity, Entity>> entityResourceContainer_;
    std::unique_ptr<ResourceManageContainerBase<Scene, Entity>> sceneResourceContainer_;
};

template <typename T, typename T1>
void ResourceManageContainerGroup::OnDrawContainerDebugWindow(std::unique_ptr<ResourceManageContainerBase<T, T1>>& onDrawDebugContainer)
{
    const auto drawResourceWindowName = "Resource " + std::string(typeid(T).name());

    if (ImGui::TreeNode(drawResourceWindowName.c_str()))
    {
        onDrawDebugContainer->OnDrawDebug();
        ImGui::TreePop();
        ImGui::Spacing();
    }
}

