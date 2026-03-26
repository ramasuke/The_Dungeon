#pragma once
#include "../../../BasicallyParameter/Vector2/Vector2.hpp"

class CameraBase
{
public:
    virtual ~CameraBase() = default;

    Vector2 position_;
};
