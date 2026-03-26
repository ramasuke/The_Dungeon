#include "MyCalculator.h"
#include <cmath>

Vector2 MyCalculator::GetDirection(const float degree)
{
    const float radians = DegToRadF(degree);
    return Vector2(std::cos(radians), std::sin(radians));
}

float MyCalculator::DegToRadF(const float degree)
{
    return degree * (3.14159265358979323846f / 180.0f);
}
