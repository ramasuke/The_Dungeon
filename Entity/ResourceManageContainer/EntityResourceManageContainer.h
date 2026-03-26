#pragma once
#include "../Entity.hpp"
#include "../../Resource/ManageContainer/ResourceManageContainerBase.h"

class EntityResourceManageContainer final : public virtual ResourceManageContainerBase<Entity, Entity>
{
public:
    explicit EntityResourceManageContainer(const std::string& resourceFolderPath)
        : ResourceManageContainerBase<Entity, Entity>(resourceFolderPath)
    {
    }

    void OnUpdate() override;
    bool OnTryRemoveContent(Entity* resource) override;
};
