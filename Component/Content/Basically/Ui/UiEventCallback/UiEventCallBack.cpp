#include "UiEventCallBack.h"

#include <DxLib.h>

#include "../../../../../BasicallyParameter/MouseState/MouseState.h"
#include "../../../../../Entity/Entity.hpp"
#include "../../../../../Libs/ImGui/imgui.h"

void Ui::UiEventCallBack::Init()
{
    transform_ = EntityRef().GetComponent<Transform>();
}

void Ui::UiEventCallBack::OnUpdate()
{
    OnTryHoverEvent();
    OnTryClickEvent();
    OnTryReleaseEvent();
}

void Ui::UiEventCallBack::OnDrawInspector()
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

void Ui::UiEventCallBack::OnTryStartHover() const
{
    onStartHover_.get_subscriber().on_next(unit{});
}

void Ui::UiEventCallBack::OnTryHoverEvent()
{
    int mousePosX;
    int mousePosY;
    GetMousePoint(&mousePosX, &mousePosY);

    if (!CheckInnerMousePointer())
    {
        isHovering_ = false;
        onEndHover_.get_subscriber().on_next(unit{});
        return;
    }

    if (!isHovering_)
    {
        onStartHover_.get_subscriber().on_next(unit{});
        isHovering_ = true;
    }
    
    onHovering_.get_subscriber().on_next(unit{});
}

void Ui::UiEventCallBack::OnTryClickEvent()
{
    if (!CheckInnerMousePointer() || isPressing_)
        return;

    auto mouseEvent = GetMouseEventType();

    if (mouseEvent == None)
        return;

    isPressing_ = true;
    onClick_.get_subscriber().on_next(mouseEvent);
}

void Ui::UiEventCallBack::OnTryReleaseEvent()
{
    if (!isPressing_ || !CheckInnerMousePointer())
        return;

    const auto mouseInput = GetMouseInput();
    if (mouseInput == MOUSE_INPUT_LEFT || mouseInput == MOUSE_INPUT_MIDDLE || mouseInput == MOUSE_INPUT_RIGHT)
        return;

    isPressing_ = false;
    onRelease_.get_subscriber().on_next(unit{});
}

MouseState Ui::UiEventCallBack::GetMouseEventType()
{
    switch (GetMouseInput())
    {
    case MOUSE_INPUT_LEFT:
        return LeftClick;
    case MOUSE_INPUT_MIDDLE:
        return MiddleClick;
    case MOUSE_INPUT_RIGHT:
        return RightClick;
    default:
        return None;
    }
}

bool Ui::UiEventCallBack::CheckInnerMousePointer() const
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
