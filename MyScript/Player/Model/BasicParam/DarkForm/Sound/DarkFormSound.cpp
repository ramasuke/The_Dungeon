#include "DarkFormSound.h"

#include "../../../../../../Helper/ImGui/ImGuiHelper.h"

void Player::DarkForm::DarkFormSound::Init()
{
    walkSound_          .Init();
    onAttackSound_      .Init();
    onDamageSound_      .Init();
    onReleaseFormSound_ .Init();
}

void Player::DarkForm::DarkFormSound::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("walkSound"           , walkSound_);
    ImGuiHelper::OnDrawInputField("onAttackSound"       , onAttackSound_);
    ImGuiHelper::OnDrawInputField("onDamageSound"       , onDamageSound_);
    ImGuiHelper::OnDrawInputField("onReleaseFormSound"  , onReleaseFormSound_);
}
