#include "DarkHealPowerUpItem.h"

void Player::DarkHealPowerUpItem::OnUpdate()
{
    despawnDuring_++;
    if (despawnDuration_ > despawnDuring_)
        return;

    PlayerAvatar::Model()
        .BasicParam()
        .NormalFormParam()
        .ReinforcementDarkHeal(value_);
}

void Player::DarkHealPowerUpItem::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("value"           , value_);
    ImGuiHelper::OnDrawInputField("despawnDuration" , despawnDuration_);
    ImGuiHelper::OnDrawInputField("despawnDuring"   , despawnDuring_);
}
