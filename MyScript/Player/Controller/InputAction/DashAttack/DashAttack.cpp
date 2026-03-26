#include "DashAttack.h"

#include <DxLib.h>

void Player::InputActionContent::DashAttack::OnUpdateForGameRoop()
{
    previewIsPress_ = CheckOnInputKey();
}

void Player::InputActionContent::DashAttack::SetActive(const bool active)
{
    isActive_ = active;
}

bool Player::InputActionContent::DashAttack::IsPressed() const
{
    return !previewIsPress_ && CheckOnInputKey() && isActive_;
}

bool Player::InputActionContent::DashAttack::IsUpdatePressed() const
{
    return CheckOnInputKey() && isActive_;
}

bool Player::InputActionContent::DashAttack::IsReleased() const
{
    return previewIsPress_ && !CheckOnInputKey() && isActive_;
}

void Player::InputActionContent::DashAttack::ReadValue() const
{
}

bool Player::InputActionContent::DashAttack::CheckOnInputKey()
{
    return CheckHitKey(KEY_INPUT_LSHIFT);
}
