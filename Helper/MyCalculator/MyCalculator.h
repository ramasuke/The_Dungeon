#pragma once
#include "../../BasicallyParameter/Vector2/Vector2.hpp"

class MyCalculator final
{
public:
    static Vector2 GetDirection(float degree);
    static float DegToRadF(float degree);
};

