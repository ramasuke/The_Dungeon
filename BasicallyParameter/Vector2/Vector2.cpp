#include "Vector2.hpp"

#include <DxLib.h>

#include "../../Application/ApplicationParameter.h"
#include "../../Application/IApplication/IApplication.hpp"
#include "../../Libs/ImGui/imgui.h"

Vector2 Vector2::operator+(const Vector2& other) const
{
    return Vector2(x_ + other.x_, y_ + other.y_);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
    return Vector2(x_ - other.x_, y_ - other.y_);
}

Vector2 Vector2::operator*(const float scalar) const
{
    return Vector2(x_ * scalar, y_ * scalar);
}

Vector2 Vector2::operator/(const float scalar) const
{
    return Vector2(x_ / scalar, y_ / scalar);
}

Vector2& Vector2::operator+=(const Vector2& other)
{
    x_ += other.x_;
    y_ += other.y_;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
    x_ -= other.x_;
    y_ -= other.y_;
    return *this;
}

Vector2& Vector2::operator*=(float scalar)
{
    x_ *= scalar;
    y_ *= scalar;
    return *this;
}

float Vector2::Dot(const Vector2& other) const
{
    return x_ * other.x_ + y_ * other.y_;
}

float Vector2::Magnitude() const
{
    return x_ * x_ + y_ * y_;
}

Vector2 Vector2::Normalize() const
{
    const float mag = SqrtMagnitude();
    return (mag > 0) ? (*this / mag) : Vector2();
}

float Vector2::SqrtMagnitude() const
{
    return std::sqrt(Magnitude());
}

std::string Vector2::ToString() const
{
    std::string stringBuilder = std::to_string(x_);
    stringBuilder.append(", ");
    stringBuilder.append(std::to_string(y_));
    return stringBuilder;
}

void Vector2::OnDrawDebug()
{
    ImGui::InputFloat("x", &x_, 0, WINDOW_WIDTH_SCALE);
    ImGui::InputFloat("y", &y_, 0, WINDOW_HEIGHT_SCALE);
}

b2Vec2 Vector2::ToB2Vec2() const
{
    return b2Vec2{x_, y_};
}