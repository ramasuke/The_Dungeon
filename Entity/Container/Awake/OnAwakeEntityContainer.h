#pragma once
#include <deque>
#include "../../Entity.hpp"
#include "../../../BasicallyParameter/IContainer/IContainer.h"

class OnAwakeEntityContainer final : public virtual IContainer<Entity*>
{
public:
    void OnUpdateForGameRoop();

private:
    void AddContent(Entity* add) override;
    void RemoveContent(Entity* remove) override;

    std::deque<Entity*> onAwakeQueue_;
};