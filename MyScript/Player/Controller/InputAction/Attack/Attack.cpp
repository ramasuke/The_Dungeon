#include "Attack.h"

#include <DxLib.h>

void Player::InputActionContent::Attack::OnUpdateForGameRoop()
{
    previewIsPress_ = CheckOnInputKey();
}

void Player::InputActionContent::Attack::SetActive(const bool active)
{
    isActive_ = active;
}

bool Player::InputActionContent::Attack::IsPressed() const
{
    return !previewIsPress_ && CheckOnInputKey() && isActive_;
}

bool Player::InputActionContent::Attack::IsUpdatePressed() const
{
    return CheckOnInputKey() && isActive_;
}

bool Player::InputActionContent::Attack::IsReleased() const
{
    return previewIsPress_ && !CheckOnInputKey() && isActive_;
}

void Player::InputActionContent::Attack::ReadValue() const
{
}

bool Player::InputActionContent::Attack::CheckOnInputKey()
{
    return GetMouseInput() == MOUSE_INPUT_LEFT;
}
