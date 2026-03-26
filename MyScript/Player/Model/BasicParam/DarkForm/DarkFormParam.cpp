#include "DarkFormParam.h"

void Player::DarkForm::DarkFormParam::Init()
{
    animation_.Init();
    sound_.Init();
}

void Player::DarkForm::DarkFormParam::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("health", health_);
    ImGuiHelper::OnDrawInputField("physicsAttackPower", physicsAttackPower_);
    ImGuiHelper::OnDrawInputField("walkSpeed", walkSpeed_);
    ImGuiHelper::OnDrawInputField("attackStateDuration", attackStateDuration_);
    ImGuiHelper::OnDrawInputField("attackStateOnAttackDamageDuration", attackStateOnAttackDamageDuration_);
    ImGuiHelper::OnDrawInputField("attackDistance", attackDistance_);
    ImGuiHelper::OnDrawInputField("dashAttackOffsetPosX", dashAttackOffsetPosX_);
    ImGuiHelper::OnDrawInputField("dashAttackStateDuration", dashAttackStateDuration_);
    ImGuiHelper::OnDrawInputField("dashAttackStateOnAttackDamageDuration", dashAttackStateOnAttackDamageDuration_);
    ImGuiHelper::OnDrawInputField("dashAttackDistance", dashAttackDistance_);
    ImGuiHelper::OnDrawInputField("onDamageStateDuration", onDamageStateDuration_);
    ImGuiHelper::OnDrawInputField("onReleaseFormStateDuration", onReleaseFormStateDuration_);
    ImGuiHelper::OnDrawInputField("animation", animation_);
    ImGuiHelper::OnDrawInputField("sound", sound_);
}

void Player::DarkForm::DarkFormParam::OnDamage(std::stack<DamageContext::IDamageContext>& damageStack,
                                               Entity& entityRef)
{
    while (!damageStack.empty())
    {
        auto& context = damageStack.top();
        auto health = health_.get();
        context.OnStartEffect(entityRef, health);
        health_.OnNext(health);
        damageStack.pop();
    }
}
