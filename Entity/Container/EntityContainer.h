#pragma once
#include <stack>
#include <unordered_map>
#include "../Entity.hpp"
#include "../../BasicallyParameter/Guid/Guid.h"
#include "../../BasicallyParameter/IContainer/IContainer.h"

class EntityContainer final : public virtual IContainer<Entity*>
{
public:
    Entity* CatchEntity(const Guid& guid);
    void AddContent(Entity* add) override;
    void AddSceneContent(Entity* add);
    void RemoveContent(Entity* remove) override;
    void OnUpdateForGameRoop() const;
    void OnUpdateBeginPhysics() const;
    void OnUpdateDraw()         const;
    void OnUpdateEndPhysics()   const;
    void OnEditorUpdate();
    void OnUpdateContentLifeCycle();
    std::unordered_map<Guid, Entity*, GuidHash> AllEntities() { return hashedContents_; }
    
    
private:
    std::unordered_map<Guid, Entity*, GuidHash> hashedContents_;
    std::stack<Entity*> addEntityForUpdateStack_;
    std::stack<Entity*> onSpawns_;
    std::stack<std::size_t> onDespawns_;
};