#include "DarkFormOnReleaseFormState.h"

#include "../../Group/PlayerStateGroup.h"

void Player::DarkForm::DarkFormOnReleaseFormState::OnEnter(BasicParam& basicParam,
                                                      Transform& transform,
                                                      Collider& collider,
                                                      PlayerController& controller,
                                                      AnimationRenderer& playerAnimRender,
                                                      PlayerModel& playerModel)
{
    playerAnimRender.SetAnimation(basicParam.DarkFormParam().Animation().OnReleaseForm());
}

void Player::DarkForm::DarkFormOnReleaseFormState::OnUpdateForGameRoop(BasicParam& basicParam,
                                                                  Transform& transform,
                                                                  Collider& collider,
                                                                  PlayerController& controller,
                                                                  PlayerStateGroup& stateGroup,
                                                                  AnimationRenderer& animRender,
                                                                  PlayerModel& playerModel,
                                                                  const std::function<void(
                                                                      const std::shared_ptr<IPlayerState>&)>
                                                                  onChangeState)
{
    nextStateDuring_++;
    if (basicParam.DarkFormParam().OnReleaseFormStateDuration().Value() > nextStateDuring_)
        return;

    onChangeState(stateGroup.NormalFormIdleState());
}

void Player::DarkForm::DarkFormOnReleaseFormState::OnExit(Collider& collider,
                                                     PlayerModel& playerModel)
{
    nextStateDuring_ = 0;
}
