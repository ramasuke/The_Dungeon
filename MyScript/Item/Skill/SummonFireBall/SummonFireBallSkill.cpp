#include "SummonFireBallSkill.h"

#include <DxLib.h>

#include "../../../../Entity/Entity.hpp"
#include "../../../../Helper/ImGui/ImGuiHelper.h"
#include "../../../../Helper/MyCalculator/MyCalculator.h"
#include "../../../FightParameter/PlayerAttackArea.h"
#include "../../../FightParameter/DamageContext/Fire/FireDamageContext.h"
#include "../../../Player/PlayerAvatar.h"

void Skill::SummonFireBallSkill::Init()
{
    spriteHandle_ = LoadGraph(spriteResourceFilePath_.c_str());
}

void Skill::SummonFireBallSkill::OnExecuteNormalForm(Player::PlayerModel& playerModel, Player::PlayerController& controller,
                                                     AnimationRenderer&)
{
    SummmonFireBalls(playerModel, controller);
}

void Skill::SummonFireBallSkill::OnExecuteDarkForm(Player::PlayerModel& playerModel, Player::PlayerController& controller, AnimationRenderer&)
{
    SummmonFireBalls(playerModel, controller);
}

void Skill::SummonFireBallSkill::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("name"                    , name_);
    ImGuiHelper::OnDrawInputField("summonFireBallPrefabPath", summonFireBallPrefabPath_);
    ImGuiHelper::OnDrawInputField("spriteResourceFilePath"  , spriteResourceFilePath_);
    ImGuiHelper::OnDrawInputField("spriteHandle"            , spriteHandle_);
    ImGuiHelper::OnDrawInputField("firePower"               , firePower_);
    ImGuiHelper::OnDrawInputField("summonDistance"          , summonDistance_);
    ImGuiHelper::OnDrawInputField("summonAmount"            , summonAmount_);
    ImGuiHelper::OnDrawInputField("startAngle"              , startAngle_);
    ImGuiHelper::OnDrawInputField("endAngle"                , endAngle_);
}

void Skill::SummonFireBallSkill::SummmonFireBalls(const Player::PlayerModel& playerModel, const Player::PlayerController& controller)
{
    const auto moveAngle = controller.Move().ReadValue().ToDegree();

    // SoundManager.Instance.PlaySE(shotSound);

    for (float angle = startAngle_; angle < endAngle_; angle += (std::abs(startAngle_) + endAngle_) / summonAmount_)
    {
        const auto attackAngle = angle + moveAngle;
        const auto summonFireBallPos = MyCalculator::GetDirection(attackAngle) * summonDistance_ +
            Player::PlayerAvatar::Model().Transform()->position_;
        const auto summonFireBall = Entity::Spawn<PlayerAttackArea>(summonFireBallPrefabPath_, summonFireBallPos);
        summonFireBall->SetDamage(std::make_shared<FireDamageContext>(playerModel.Transform()->EntityRef(), firePower_));
        summonFireBall->EntityRef().GetComponent<Transform>()->rotation_ = attackAngle;
    }
}
