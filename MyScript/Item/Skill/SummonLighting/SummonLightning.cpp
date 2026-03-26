#include "SummonLightning.h"

#include <DxLib.h>

#include "../../../../Entity/Entity.hpp"
#include "../../../../Libs/ImGui/imgui.h"
#include "../../../Player/Model/PlayerModel.h"
#include "Object/Thunder0Object.h"

void Skill::SummonLightning::Init()
{
    spriteHandle_ = LoadGraph(spriteResourceFilePath_.c_str());
}

void Skill::SummonLightning::OnExecuteNormalForm(
    Player::PlayerModel& playerModel,
    Player::PlayerController&,
    AnimationRenderer& animRenderer)
{
    const auto attackDirection = animRenderer.isReverseX_ ? Vector2(-1, 0) : Vector2(1, 0);

    auto& thunder = Entity::Spawn(summonLightningPrefabPath_,
                                  playerModel.Transform()->position_ + attackDirection * summonThunderDistance_ +
                                  summonThunderOffset_);

    thunder.GetComponent<Thunder0Object>()->SetThunderPower(thunderPower_);
}

void Skill::SummonLightning::OnExecuteDarkForm(
    Player::PlayerModel&,
    Player::PlayerController&,
    AnimationRenderer& animRenderer)
{
}

void Skill::SummonLightning::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("name"                        , name_);
    ImGuiHelper::OnDrawInputField("spriteResourceFilePath"      , spriteResourceFilePath_);
    ImGuiHelper::OnDrawInputField("summonLightningPrefabPath"   , summonLightningPrefabPath_);
    ImGuiHelper::OnDrawInputField("thunderPower"                , thunderPower_);
    ImGuiHelper::OnDrawInputField("summonThunderDistance"       , summonThunderDistance_);

    if (ImGui::TreeNode("summonThunderOffset"))
    {
        summonThunderOffset_.OnDrawDebug();
        ImGui::TreePop();
        ImGui::Spacing();
    }
}
