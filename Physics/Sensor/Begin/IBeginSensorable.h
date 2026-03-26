#pragma once
#include "../../../Libs/Box2D/include/src/box2d/types.h"

template<typename SensorT>
class IBeginSensorable
{
public:
    virtual ~IBeginSensorable() = default;
    virtual void OnBeginSensor(b2SensorBeginTouchEvent*, SensorT*) = 0;
};
