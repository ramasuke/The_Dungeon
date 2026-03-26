#pragma once
#include "../../BasicallyParameter/IContainer/IContainer.h"
#include "../../Entity/Container/EntityContainer.h"
#include "../../Entity/Container/Awake/OnAwakeEntityContainer.h"
#include "../../Entity/Container/OnDespawn/OnDeSpawnEntityContainer.h"
#include "../../MyScript/ApplicationExtension/ApplicationExtension.h"
#include "../../Physics/Physics.h"
#include "../../Scene/Manager/SceneManager.h"
#include "../Camera/Base/CameraBase.hpp"

class IApplication
{
    static IApplication* instance_;

public:
    IApplication() { instance_ = this; }
    virtual ~IApplication() = default;
    static IApplication& GetInstance() { return *instance_; }
    virtual SceneManager& SceneManager() = 0;
    virtual Physics& Physics() = 0;
    virtual EntityContainer& EntityContainer() = 0;
    virtual IContainer<Entity*>& OnAwakeEntityContainer() = 0;
    virtual IContainer<Entity*>& OnDeSpawnEntityContainer() = 0;

    virtual CameraBase& Camera() = 0;
    ApplicationExtension& Extension() { return applicationExtension_; }
    void OnSerialize();
    void OnDeserialize();

protected:
    virtual void Init();
    virtual void OnStartGameRoopAsync() = 0;
    virtual void OnUpdateGameRoop() = 0;
    virtual void OnExit() = 0;

    std::string applicationFilePath_ = "Resource/ApplicationExtension/ApplicationExtension.json";
    ApplicationExtension applicationExtension_;
};
