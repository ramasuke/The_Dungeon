#include "SceneResourceManageContainer.h"

void SceneResourceManageContainer::OnUpdate()
{
    for (auto& content : contents_)
    {
        std::get<1>(content).get()->TryCompleteSceneLoad();
    }
}

bool SceneResourceManageContainer::OnTryRemoveContent(Entity* resource)
{
    for (auto& content : contents_)
    {
        if (std::get<1>(content).get()->OnTryRemoveSceneEntity(resource))
        {
            return true;
        }
    }
    return false;
}
