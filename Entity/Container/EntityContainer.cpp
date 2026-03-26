#include "EntityContainer.h"

Entity* EntityContainer::CatchEntity(const Guid& guid)
{
    const auto it = hashedContents_.find(guid);
    return (it != hashedContents_.end()) ? it->second : nullptr;
}

void EntityContainer::AddContent(Entity* add)
{
    if (!add) return;

    const Guid& guid = add->GetGuid(); // Entity に Guid を持たせている前提

    // すでに存在している場合は追加しない
    if (hashedContents_.find(guid) != hashedContents_.end())
    {
        return;
    }

    // まだ存在していないなら、スタックに追加
    addEntityForUpdateStack_.push(add);
}

void EntityContainer::AddSceneContent(Entity* add)
{
    hashedContents_[add->GetGuid()] = add;
}

void EntityContainer::RemoveContent(Entity* remove)
{
    hashedContents_.erase(remove->GetGuid());
}

void EntityContainer::OnUpdateBeginPhysics() const
{
    for (const auto& it : hashedContents_)
    {
        it.second->OnUpdateBeginPhysics();
    }
}

void EntityContainer::OnUpdateDraw() const
{
    for (const auto& it : hashedContents_)
    {
        it.second->OnUpdateDraw();
    }
}

void EntityContainer::OnUpdateForGameRoop() const
{
    for (const auto& it : hashedContents_)
    {
        it.second->OnUpdateForGameRoop();
    }
}

void EntityContainer::OnUpdateEndPhysics() const
{
    for (const auto& it : hashedContents_)
    {
        it.second->OnUpdateEndPhysics();
    }
}

void EntityContainer::OnEditorUpdate()
{
    for (const auto& it : hashedContents_)
    {
        it.second->OnEditorUpdate();
    }
}

void EntityContainer::OnUpdateContentLifeCycle()
{
    //Add
    while (!addEntityForUpdateStack_.empty())
    {
        Entity* content = addEntityForUpdateStack_.top();
        hashedContents_[content->GetGuid()] = content;
        addEntityForUpdateStack_.pop();
    }
}
