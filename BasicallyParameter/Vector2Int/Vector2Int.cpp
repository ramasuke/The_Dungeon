#include "Vector2Int.h"

#include "../../Application/ApplicationParameter.h"
#include "../../Libs/ImGui/imgui.h"

Vector2Int Vector2Int::operator+(const Vector2Int& other) const
{
    return Vector2Int(x_ + other.x_, y_ + other.y_);
}

Vector2Int Vector2Int::operator-(const Vector2Int& other) const
{
    return Vector2Int(x_ - other.x_, y_ - other.y_);
}

Vector2Int& Vector2Int::operator+=(const Vector2Int& other)
{
    x_ += other.x_;
    y_ += other.y_;
    return *this;
}

Vector2Int& Vector2Int::operator-=(const Vector2Int& other)
{
    x_ -= other.x_;
    y_ -= other.y_;
    return *this;
}

float Vector2Int::Dot(const Vector2Int& other) const
{
    return x_ * other.x_ + y_ * other.y_;
}

float Vector2Int::Magnitude() const
{
    return std::sqrt(x_ * x_ + y_ * y_);
}

std::string Vector2Int::ToString() const
{
    std::string stringBuilder = std::to_string(x_);
    stringBuilder.append(", ");
    stringBuilder.append(std::to_string(y_));
    return stringBuilder;
}

void Vector2Int::OnDrawDebug()
{
    ImGui::InputInt("x", &x_, 0, WINDOW_WIDTH_SCALE);
    ImGui::InputInt("y", &y_, 0, WINDOW_HEIGHT_SCALE);
}

Vector2Int Vector2Int::One()
{
    return Vector2Int(1, 1);
}