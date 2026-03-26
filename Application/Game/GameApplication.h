#pragma once

#include "../../Entity/Container/EntityContainer.h"
#include "../../Physics/Physics.h"
#include "../Fps/ApplicationFps.h"
#include "../IApplication/IApplication.hpp"
#include "Camera/GameCamera.h"

class GameApplication final : public virtual IApplication
{
public:
    void Init() override;
    void OnStartGameRoopAsync() override;
    void OnExit() override;
    static bool CheckContinueGameRoop();

private:
    void OnUpdateGameRoop() override;
    void OnUpdateLifeCycle();

    ::SceneManager& SceneManager()  override { return sceneManager_;    }
    ::Physics& Physics()            override { return physics_;         }

    ::EntityContainer& EntityContainer()            override { return entityContainer_;             }
    IContainer<Entity*>& OnAwakeEntityContainer()   override { return onAwakeEntityContainer_;      }
    IContainer<Entity*>& OnDeSpawnEntityContainer() override { return onDespawnEntityContainer_;    }
    CameraBase& Camera()                            override { return camera_;                      }


    ::SceneManager sceneManager_;
    ::Physics physics_;
    ApplicationFps fps_ = ApplicationFps(60.0f);

    ::EntityContainer entityContainer_;
    ::OnAwakeEntityContainer onAwakeEntityContainer_;
    ::OnDeSpawnEntityContainer onDespawnEntityContainer_;
    GameCamera camera_;
};