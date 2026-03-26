#pragma once
#include "../../../Component/Content/Basically/Color/Color.h"

class Entity;

struct IDamageParam
{
    virtual ~IDamageParam() = default;
    virtual Color Color() const = 0;
    virtual std::string ToString() const = 0;
    virtual int HitDamage() const = 0;
};
