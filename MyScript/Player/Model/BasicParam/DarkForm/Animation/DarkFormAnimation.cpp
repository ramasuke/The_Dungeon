#include "DarkFormAnimation.h"

#include "../../../../../../Helper/ImGui/ImGuiHelper.h"

void Player::DarkForm::DarkFormAnimation::Init() const
{
    idleAnimation_->Init();
    walkAnimation_->Init();
    attackAnimation_->Init();
    dashAttackAnimation_->Init();
    onDamageAnimation_->Init();
    onReleaseFormAnimation_->Init();
}

void Player::DarkForm::DarkFormAnimation::OnDrawInspector() const
{
    ImGuiHelper::OnDrawTreeInspector("idleAnimation", *idleAnimation_);
    ImGuiHelper::OnDrawTreeInspector("walkAnimation", *walkAnimation_);
    ImGuiHelper::OnDrawTreeInspector("attackAnimation", *attackAnimation_);
    ImGuiHelper::OnDrawTreeInspector("dashAttackAnimation", *dashAttackAnimation_);
    ImGuiHelper::OnDrawTreeInspector("onDamageAnimation", *onDamageAnimation_);
    ImGuiHelper::OnDrawTreeInspector("onReleaseFormAnimation", *onReleaseFormAnimation_);
}
