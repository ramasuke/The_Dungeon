#include "NormalFormAnimation.h"

#include "../../../../../../Helper/ImGui/ImGuiHelper.h"

void Player::NormalForm::NormalFormAnimation::Init() const
{
    idleAnimation_->Init();
    walkAnimation_->Init();
    attackAnimation_->Init();
    goInsaneAnimation_->Init();
    consumptionMadnessAnimation_->Init();
    onDamageAnimation_->Init();
    onDeathAnimation_->Init();
}

void Player::NormalForm::NormalFormAnimation::OnDrawInspector() const
{
    ImGuiHelper::OnDrawTreeInspector("idleAnimation", *idleAnimation_);
    ImGuiHelper::OnDrawTreeInspector("walkAnimation", *walkAnimation_);
    ImGuiHelper::OnDrawTreeInspector("attackAnimation", *attackAnimation_);
    ImGuiHelper::OnDrawTreeInspector("goInsaneAnimation", *goInsaneAnimation_);
    ImGuiHelper::OnDrawTreeInspector("consumptionMadnessAnimation", * consumptionMadnessAnimation_);
    ImGuiHelper::OnDrawTreeInspector("onDamageAnimation", *onDamageAnimation_);
    ImGuiHelper::OnDrawTreeInspector("onDeathAnimation", *onDeathAnimation_);
}
