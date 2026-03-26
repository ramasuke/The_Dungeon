#include "DarkFormOnDamageState.h"

#include "../../Group/PlayerStateGroup.h"

void Player::DarkForm::DarkFormOnDamageState::OnEnter(
    BasicParam& basicParam,
    Transform& transform,
    Collider& collider,
    PlayerController& controller,
    AnimationRenderer& playerAnimRender,
    PlayerModel& playerModel)
{
    playerAnimRender.SetAnimation(basicParam.DarkFormParam().Animation().OnDamage());
    basicParam.NormalFormParam().OnDamage(basicParam.CurrentDamageStack(), transform.EntityRef());
}

void Player::DarkForm::DarkFormOnDamageState::OnUpdateForGameRoop(
    BasicParam& basicParam,
    Transform& transform,
    Collider& collider,
    PlayerController& controller,
    PlayerStateGroup& stateGroup,
    AnimationRenderer& animRender,
    PlayerModel& playerModel,
    const std::function<void(const std::shared_ptr<IPlayerState>&)> onChangeState)
{
    nextStateDuring_++;
    if (basicParam.DarkFormParam().IsOnReleaseForm())
    {
        onChangeState(stateGroup.DarkFormOnReleaseFormState());
        return;
    }
    if (basicParam.DarkFormParam().OnDamageStateDuration().Value() <= nextStateDuring_)
    {
        onChangeState(stateGroup.DarkFormIdleState());
    }
}

void Player::DarkForm::DarkFormOnDamageState::OnExit(
    Collider& collider,
    PlayerModel& playerModel)
{
    nextStateDuring_ = 0;
}
