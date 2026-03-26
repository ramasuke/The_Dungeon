#pragma once
#include "../../Resource/ManageContainer/ResourceManageContainerBase.h"
#include "../Content/Scene.hpp"

class SceneResourceManageContainer final : public virtual ResourceManageContainerBase<Scene, Entity> 
{
public:
    explicit SceneResourceManageContainer(const std::string& resourceFolderPath)
        : ResourceManageContainerBase<Scene, Entity>(resourceFolderPath)
    {
        
    }

protected:
    void OnUpdate() override;
    bool OnTryRemoveContent(Entity* resource) override;
};
