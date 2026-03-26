#include "WoodChest.h"

#include "../../../Entity/Entity.hpp"
#include "../../../Helper/ImGui/ImGuiHelper.h"

void Prop::WoodChest::Init()
{
    EntityRef().GetComponent<AnimationRenderer>()->SetAnimation(idleAnimation_);
}

void Prop::WoodChest::OnUpdate()
{
    if (!isOpen_)
        return;
    
    openDuring_++;
    if (openDuration_ > openDuring_)
        return;
    
    Entity::Spawn(powerUpItemPrefabPath_, EntityRef().GetComponent<Transform>()->position_);
    EntityRef().OnDespawn();
}

void Prop::WoodChest::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("idleAnimation"           , idleAnimation_);
    ImGuiHelper::OnDrawInputField("openAnimation"           , openAnimation_);
    ImGuiHelper::OnDrawInputField("openDuration"            , openDuration_);
    ImGui::Checkbox("isOpen"                                  , &isOpen_);
    ImGuiHelper::OnDrawInputField("dropItemPrefabPath_"     , powerUpItemPrefabPath_);
}

void Prop::WoodChest::OnBeginSensor(b2SensorBeginTouchEvent*, Player::PlayerAvatar* playerAvatar)
{
    if (isOpen_)
        return;
    
    EntityRef().GetComponent<AnimationRenderer>()->SetAnimation(openAnimation_);
    isOpen_ = true;
}
