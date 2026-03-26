#include "OnDeSpawnEntityContainer.h"

#include "../EntityContainer.h"
#include "../../../Application/IApplication/IApplication.hpp"
#include "../../../Resource/ManageContainer/Group/ResourceManageContainerGroup.h"

void OnDeSpawnEntityContainer::AddContent(Entity* add)
{
    if (despawnedEntities_.find(add) == despawnedEntities_.end())
    {
        onDespawnStack_.push(add);
        despawnedEntities_.insert(add);
    }
}


void OnDeSpawnEntityContainer::OnUpdateForGameRoop(EntityContainer& entityContainer,
                                                   const ResourceManageContainerGroup* resourceContainerGroup)
{
    while (!onDespawnStack_.empty())
    {
        auto* content = onDespawnStack_.top();
        RemoveContent(content);
        try
        {
            entityContainer.RemoveContent(content);
        } catch (std::exception)
        {
        }

        if (!IApplication::GetInstance().SceneManager().OnTryRemoveSceneEntity(content))
        {
            if (resourceContainerGroup != nullptr)
            {
                if (!resourceContainerGroup->EntityResourceContainer().OnTryRemoveContent(content))
                {
                    if (!resourceContainerGroup->SceneResourceContainer().OnTryRemoveContent(content))
                    {
                        delete content;
                    }
                }
            }
            else
            {
                delete content;
            }
        }
        onDespawnStack_.pop();
        despawnedEntities_.erase(content);
    }
}

void OnDeSpawnEntityContainer::OnDespawnAllEntities(const std::vector<Entity*>& onDespawnEntities)
{
    for (const auto& entity : onDespawnEntities)
    {
        entity->OnDespawn();
    }
}

void OnDeSpawnEntityContainer::RemoveContent(Entity* remove)
{
}
