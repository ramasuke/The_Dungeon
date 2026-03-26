#include "EntityResourceManageContainer.h"

void EntityResourceManageContainer::OnUpdate()
{
}

bool EntityResourceManageContainer::OnTryRemoveContent(Entity* resource)
{
    const auto before = contents_.size();

    contents_.erase(
        std::remove_if(contents_.begin(), contents_.end(),
                       [&](auto& content)
                       {
                           return std::get<1>(content).get() == resource;
                       }),
        contents_.end());

    return contents_.size() != before;
}
