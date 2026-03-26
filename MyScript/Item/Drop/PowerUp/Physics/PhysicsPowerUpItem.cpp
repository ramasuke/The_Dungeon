#include "PhysicsPowerUpItem.h"

#include "../../../../../Entity/Entity.hpp"

void Player::PhysicsPowerUpItem::OnUpdate()
{
    EntityRef().GetComponent<Transform>()->position_.y_ += ON_UPDATE_UP_MOVE_SPEED;
    
    despawnDuring_++;
    if (ON_PICKUP_DURATION == despawnDuring_)
    {
        PlayerAvatar::Model()
            .BasicParam()
            .NormalFormParam()
            .ReinforcementPhysicsAttackPower(value_);
    }
    
    if (despawnDuration_ > despawnDuring_)
        return;
    
    EntityRef().OnDespawn();
}

void Player::PhysicsPowerUpItem::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("value"           , value_);
    ImGuiHelper::OnDrawInputField("despawnDuration" , despawnDuration_);
    ImGuiHelper::OnDrawInputField("despawnDuring"   , despawnDuring_);
}
