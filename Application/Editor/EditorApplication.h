#pragma once
#include <memory>

#include "../../Entity/Container/EntityContainer.h"
#include "../../Physics/Physics.h"
#include "../../Resource/ManageContainer/Group/ResourceManageContainerGroup.h"
#include "../Fps/ApplicationFps.h"
#include "../IApplication/IApplication.hpp"
#include "Camera/EditorCamera.hpp"

class EditorApplication final : public virtual IApplication
{
public:
    void Init() override;
    void OnStartGameRoopAsync() override;
    void OnExit() override;
    static bool CheckContinueGameRoop();

private:
    void OnUpdateGameRoop() override;
    void OnUpdateLifeCycle();
    void OnDrawChangeDebugModeWindow();

    ::SceneManager& SceneManager()  override { return sceneManager_;    }
    ::Physics&      Physics()       override { return physics_;         }

    ::EntityContainer&      EntityContainer()          override { return entityContainer_;          }
    IContainer<Entity*>&    OnAwakeEntityContainer()   override { return onAwakeEntityContainer_ ;  }
    IContainer<Entity*>&    OnDeSpawnEntityContainer() override { return onDespawnEntityContainer_; }
    CameraBase&             Camera()                   override { return camera_;                   }
    
    ::SceneManager sceneManager_;
    ::Physics physics_;
    ApplicationFps fps_ = ApplicationFps(60.0f);

    ::EntityContainer entityContainer_;
    ::OnAwakeEntityContainer onAwakeEntityContainer_;
    ::OnDeSpawnEntityContainer onDespawnEntityContainer_;
    EditorCamera camera_;

    std::unique_ptr<ResourceManageContainerGroup> resourceManageContainerGroup_;

    bool isPlayMode_ = true;
};
