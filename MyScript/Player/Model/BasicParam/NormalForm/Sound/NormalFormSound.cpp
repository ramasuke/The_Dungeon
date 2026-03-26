#include "NormalFormSound.h"

#include "../../../../../../Helper/ImGui/ImGuiHelper.h"

void Player::NormalForm::NormalFormSound::Init()
{
    walkSound_      .Init();
    onAttackSound_  .Init();
    onDamageSound_  .Init();
    onDarkHealSound_.Init();
    onDeathSound_   .Init();
}

void Player::NormalForm::NormalFormSound::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("walkSound"       , walkSound_);
    ImGuiHelper::OnDrawInputField("onAttackSound"   , onAttackSound_);
    ImGuiHelper::OnDrawInputField("onDamageSound"   , onDamageSound_);
    ImGuiHelper::OnDrawInputField("onDarkHealSound" , onDarkHealSound_);
    ImGuiHelper::OnDrawInputField("onDeathSound"    , onDeathSound_);
}
