#pragma once
#include "../../../Libs/Box2D/include/src/box2d/types.h"

template<typename ContactT>
class IBeginContactable
{
public:
    virtual ~IBeginContactable() = default;
    virtual void OnBeginContact(b2ContactBeginTouchEvent*, ContactT*) = 0;
};
