#include "OnAwakeEntityContainer.h"

void OnAwakeEntityContainer::OnUpdateForGameRoop()
{
    while (!onAwakeQueue_.empty())
    {
        const Entity* content = onAwakeQueue_.back();
        content->OnAwakeComponents();
        onAwakeQueue_.pop_back();
    }
}

void OnAwakeEntityContainer::AddContent(Entity* add)
{
    onAwakeQueue_.push_back(add); 
}

void OnAwakeEntityContainer::RemoveContent(Entity* remove)
{
    const auto it = std::find(onAwakeQueue_.begin(), onAwakeQueue_.end(), remove);
    if (it != onAwakeQueue_.end())
    {
        onAwakeQueue_.erase(it); 
    }
}