#include "NormalFormOnDamageState.h"

#include "../../../../../../BasicallyParameter/Sound/Play/SoundPlay.h"
#include "../../../../../../Entity/Entity.hpp"
#include "../../Group/PlayerStateGroup.h"

void Player::NormalForm::NormalFormOnDamageState::OnEnter(
    BasicParam& basicParam,
    Transform& transform,
    Collider& collider,
    PlayerController& controller,
    AnimationRenderer& playerAnimRender,
    PlayerModel& playerModel)
{
    Sound::PlaySe(basicParam.NormalFormParam().Sound().OnDamage());
    playerAnimRender.SetAnimation(basicParam.NormalFormParam().Animation().OnDamage());
    basicParam.NormalFormParam().OnDamage(basicParam.CurrentDamageStack(), transform.EntityRef());
}

void Player::NormalForm::NormalFormOnDamageState::OnUpdateForGameRoop(
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
    
    if (basicParam.NormalFormParam().OnDamageStateDuration().Value() > nextStateDuring_)
        return;
    
    if (basicParam.NormalFormParam().IsDeath())
    {
        onChangeState(stateGroup.NormalFormOnDeathState());
        return;
    }
    
    onChangeState(stateGroup.NormalFormIdleState());
}

void Player::NormalForm::NormalFormOnDamageState::OnExit(
    Collider& collider,
    PlayerModel& playerModel)
{
    nextStateDuring_ = 0;
}
