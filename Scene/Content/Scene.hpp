#pragma once
#include <string>
#include <vector>
#include "../../Entity/Entity.hpp"
#include "../../Resource/IResource/IResource.h"

class Scene final : public virtual IResource
{
public:
    void OnSerialize(const std::string& filePath)   override;
    void OnDeserialize(const std::string& filePath) override;
    void TryCompleteSceneLoad();
    void OnDrawDebug() override;
    bool OnTryRemoveSceneEntity(Entity* remove);
    Entity* FindEntity(const Guid& guid)    const;
    const std::string& ResourceFilePath()   const { return resourceFilePath_; }
    const std::vector<std::unique_ptr<Entity>>& Entities();

    
private:
    std::string resourceFilePath_;
    std::vector<std::unique_ptr<Entity>> entities_;
    std::thread loaderThread_;
    
    std::mutex entitiesMutex_;
    std::atomic<bool> entitiesReady_ {false};
    bool entitiesInitialized_ = false;
};
