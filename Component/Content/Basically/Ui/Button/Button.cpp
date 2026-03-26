#include "Button.h"

#include <DxLib.h>

#include "../../../../../Entity/Entity.hpp"
#include "../../../../../Libs/ImGui/imgui.h"

void Ui::Button::SubscribeOnHoverEvent(const std::function<void()>& callback)
{
    onHover_.emplace_back(callback);
}

void Ui::Button::SubscribeOnClickEvent(const std::function<void(MouseState)>& callback)
{
    onClick_.emplace_back(callback);
}

void Ui::Button::SubscribeOnReleaseEvent(const std::function<void()>& callback)
{
    onRelease_.emplace_back(callback);
}

void Ui::Button::Init()
{
    transform_ = EntityRef().GetComponent<Transform>();
}

void Ui::Button::OnUpdate()
{
    OnTryHoverEvent();
    OnTryClickEvent();
    OnTryReleaseEvent();
}

void Ui::Button::OnDrawInspector()
{
    if (ImGui::TreeNode("eventAreaSize"))
    {
        eventAreaSize_.OnDrawDebug();
        ImGui::TreePop();
        ImGui::Spacing();
    }

    DrawBox(transform_->position_.x_ - eventAreaSize_.x_,
            transform_->position_.y_ - eventAreaSize_.y_,
            transform_->position_.x_ + eventAreaSize_.x_,
            transform_->position_.y_ + eventAreaSize_.y_,
            GetColor(0, 255, 0),
            false);
}

void Ui::Button::OnTryHoverEvent() const
{
    int mousePosX;
    int mousePosY;
    GetMousePoint(&mousePosX, &mousePosY);

    if (!CheckInnerMousePointer())
        return;

    for (const auto& callback : onHover_)
    {
        if (callback)
            callback();
    }
}

void Ui::Button::OnTryClickEvent()
{
    if (!CheckInnerMousePointer() || isPressing_)
        return;

    bool isClick = false;
    MouseState clickEventType = {};
    switch (GetMouseInput())
    {
    case MOUSE_INPUT_LEFT:
        isClick = true;
        clickEventType = LeftClick;
        break;
    case MOUSE_INPUT_MIDDLE:
        isClick = true;
        clickEventType = MiddleClick;
        break;
    case MOUSE_INPUT_RIGHT:
        isClick = true;
        clickEventType = RightClick;
        break;
    default:
        break;
    }

    if (!isClick)
        return;

    isPressing_ = true;
    for (const auto& callback : onClick_)
    {
        if (callback) callback(clickEventType);
    }
}

void Ui::Button::OnTryReleaseEvent()
{
    if (!isPressing_ || !CheckInnerMousePointer())
        return;

    const auto mouseInput = GetMouseInput();
    if (mouseInput == MOUSE_INPUT_LEFT || mouseInput == MOUSE_INPUT_MIDDLE || mouseInput == MOUSE_INPUT_RIGHT)
        return;

    isPressing_ = false;
    for (const auto& callback : onRelease_)
    {
        if (callback) callback();
    }
}

bool Ui::Button::CheckInnerMousePointer() const
{
    int mousePosX;
    int mousePosY;
    GetMousePoint(&mousePosX, &mousePosY);

    return
        transform_->position_.x_ - eventAreaSize_.x_ < mousePosX &&
        transform_->position_.x_ + eventAreaSize_.x_ > mousePosX &&
        transform_->position_.y_ - eventAreaSize_.y_ < mousePosY &&
        transform_->position_.y_ + eventAreaSize_.y_ > mousePosY;
}
