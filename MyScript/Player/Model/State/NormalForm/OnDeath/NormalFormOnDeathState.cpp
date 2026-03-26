#include "NormalFormOnDeathState.h"

void Player::NormalForm::NormalFormOnDeathState::OnEnter(BasicParam& basicParam,
                                                         Transform& transform,
                                                         Collider& collider,
                                                         PlayerController& controller,
                                                         AnimationRenderer& playerAnimRender,
                                                         PlayerModel& playerModel)
{
    playerAnimRender.SetAnimation(basicParam.NormalFormParam().Animation().OnDeath());
}

void Player::NormalForm::NormalFormOnDeathState::OnUpdateForGameRoop(BasicParam& basicParam,
                                                                     Transform& transform,
                                                                     Collider& collider,
                                                                     PlayerController& controller,
                                                                     PlayerStateGroup& stateGroup,
                                                                     AnimationRenderer& animRender,
                                                                     PlayerModel& playerModel,
                                                                     std::function<void(
                                                                         const std::shared_ptr<IPlayerState>&)>
                                                                     onChangeState)
{
    onDeathDuring_++;
    if (onDeathDuring_ < basicParam.NormalFormParam().OnDeathStateDuration().Value())
        return;
    
    basicParam.NormalFormParam().OnDeath();
}

void Player::NormalForm::NormalFormOnDeathState::OnExit(Collider& collider,
                                                        PlayerModel& playerModel)
{
    onDeathDuring_ = 0;
}
