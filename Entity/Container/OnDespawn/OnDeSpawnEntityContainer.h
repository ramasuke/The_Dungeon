#pragma once
#include <stack>
#include "../../Entity.hpp"
#include "../../../BasicallyParameter/IContainer/IContainer.h"

class ResourceManageContainerGroup;
class EntityContainer;

class OnDeSpawnEntityContainer final : public virtual IContainer<Entity*>
{
public:
    void AddContent(Entity* add) override;
    void OnUpdateForGameRoop(EntityContainer& entityContainer,
                             const ResourceManageContainerGroup* resourceContainerGroup);

    static void OnDespawnAllEntities(const std::vector<Entity*>& onDespawnEntities);

private:
    void RemoveContent(Entity* remove) override;

    std::stack<Entity*> onDespawnStack_;
    std::unordered_set<Entity*> despawnedEntities_;
};