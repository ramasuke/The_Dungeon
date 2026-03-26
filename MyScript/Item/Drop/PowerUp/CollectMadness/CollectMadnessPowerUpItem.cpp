#include "CollectMadnessPowerUpItem.h"

void Player::CollectMadnessPowerUpItem::OnUpdate()
{
    despawnDuring_++;
    if (despawnDuration_ > despawnDuring_)
        return;

    PlayerAvatar::Model().BasicParam().NormalFormParam().ReinforceCollectMadness(value_);
}

void Player::CollectMadnessPowerUpItem::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("value"           , value_);
    ImGuiHelper::OnDrawInputField("despawnDuration" , despawnDuration_);
    ImGuiHelper::OnDrawInputField("despawnDuring"   , despawnDuring_);
}
