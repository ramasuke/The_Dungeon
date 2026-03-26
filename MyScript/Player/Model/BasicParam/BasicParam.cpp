#include "BasicParam.h"

#include "../../../../Libs/ImGui/imgui.h"

void Player::BasicParam::Init()
{
    normalFormParam_.Init();
    darkFormParam_.Init();
}

void Player::BasicParam::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("inventory", inventory_);
    ImGuiHelper::OnDrawInputField("normalFormParam", normalFormParam_);
    ImGuiHelper::OnDrawInputField("darkFormParam", darkFormParam_);
}

void Player::BasicParam::OnHitDamage(const std::shared_ptr<DamageContext::IDamageContext>& damage)
{
    currentDamageStack_.push(damage);
}

bool Player::BasicParam::IsHitDamaged() const
{
    return !currentDamageStack_.empty();
}

Player::Inventory& Player::BasicParam::Inventory()
{
    return inventory_;
}
