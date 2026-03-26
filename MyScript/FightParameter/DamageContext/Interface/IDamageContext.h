#pragma once
#include "../../../../BasicallyParameter/Vector2/Vector2.hpp"
#include "../../Health/Health.h"
#include "../../IDamageParam/IDamageParam.h"

class Entity;

namespace DamageContext
{
    struct IDamageContext
    {
        virtual ~IDamageContext() = default;
        virtual Vector2 FromPos() const = 0;
        virtual void OnStartEffect(Entity& target, Health& health) = 0;
        virtual void OnUpdateEffect(Entity& target, Health& health) = 0;
        virtual bool CheckUpdateCondition(Entity& target, const Health& health) = 0;
        virtual void OnExitEffect(Entity& target, Health& health) = 0;
        virtual const IDamageParam& GetParam() = 0;
    };
}
