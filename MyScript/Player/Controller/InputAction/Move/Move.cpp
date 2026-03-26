#include "Move.h"

#include <DxLib.h>

#include "../../../../../Libs/ImGui/imgui.h"

void Player::InputActionContent::Move::OnUpdateForGameRoop()
{
    previewIsPress_ = CheckOnInputKey();
}

void Player::InputActionContent::Move::SetActive(const bool active)
{
    isActive_ = active;
}

bool Player::InputActionContent::Move::IsPressed() const
{
    return !previewIsPress_ && CheckOnInputKey() && isActive_;
}

bool Player::InputActionContent::Move::IsUpdatePressed() const
{
    return CheckOnInputKey() && isActive_;
}

bool Player::InputActionContent::Move::IsReleased() const
{
    return previewIsPress_ && !CheckOnInputKey() && isActive_;
}

Vector2 Player::InputActionContent::Move::ReadValue() const
{
    auto moveValue = Vector2(0, 0);

    if (CheckHitKey(KEY_INPUT_D))
        moveValue += Vector2(1, 0);

    if (CheckHitKey(KEY_INPUT_A))
        moveValue += Vector2(-1, 0);

    if (CheckHitKey(KEY_INPUT_W))
        moveValue += Vector2(0, -1);

    if (CheckHitKey(KEY_INPUT_S))
        moveValue += Vector2(0, 1);

    return moveValue.Normalize();
}

bool Player::InputActionContent::Move::CheckOnInputKey()
{
    return CheckHitKey(KEY_INPUT_D) ||
           CheckHitKey(KEY_INPUT_A) ||
           CheckHitKey(KEY_INPUT_W) ||
           CheckHitKey(KEY_INPUT_S);
}
