#include "ConsumptionMadness.h"

#include <DxLib.h>

void Player::InputActionContent::ConsumptionMadness::OnUpdateForGameRoop()
{
    previewIsPress_ = CheckOnInputKey();
    
    if (previewIsPress_)
    {
        pressDuring_++;
    }
    else
    {
        pressDuring_ = 0;
    }
}

void Player::InputActionContent::ConsumptionMadness::SetActive(const bool active)
{
    isActive_ = active;
}

bool Player::InputActionContent::ConsumptionMadness::IsPressed() const
{
    return !previewIsPress_ && CheckOnInputKey() && isActive_;
}

bool Player::InputActionContent::ConsumptionMadness::IsUpdatePressed() const
{
    return CheckOnInputKey() && isActive_;
}

bool Player::InputActionContent::ConsumptionMadness::IsReleased() const
{
    return previewIsPress_ && !CheckOnInputKey() && isActive_;
}

int Player::InputActionContent::ConsumptionMadness::ReadValue() const
{
    return pressDuring_;
}

bool Player::InputActionContent::ConsumptionMadness::CheckOnInputKey()
{
    return GetMouseInput() == MOUSE_INPUT_RIGHT;
}
