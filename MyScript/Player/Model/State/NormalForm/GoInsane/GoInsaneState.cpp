#include "GoInsaneState.h"

#include "../../../../../../Entity/Entity.hpp"
#include "../../Group/PlayerStateGroup.h"

void Player::NormalForm::GoInsaneState::OnEnter(BasicParam& basicParam,
                                                Transform& transform,
                                                Collider& collider,
                                                PlayerController& controller,
                                                AnimationRenderer& playerAnimRender,
                                                PlayerModel& playerModel)
{
    Entity::Spawn(particlePrfabPath_, transform.position_);
}

void Player::NormalForm::GoInsaneState::OnUpdateForGameRoop(BasicParam& basicParam,
                                                            Transform& transform,
                                                            Collider& collider,
                                                            PlayerController& controller,
                                                            PlayerStateGroup& stateGroup,
                                                            AnimationRenderer& animRender,
                                                            PlayerModel& playerModel,
                                                            const std::function<void(const std::shared_ptr<IPlayerState>&)>
                                                            onChangeState)
{
    goInsaneDuring_++;

    if (goInsaneDuring_ >= basicParam.NormalFormParam().GoInsaneDuration().Value())
    {
        basicParam.NormalFormParam().OnCostMadness(basicParam.NormalFormParam().ToGoInsaneNeedMadness().Value());
        onChangeState(stateGroup.DarkFormIdleState());
    }
}

void Player::NormalForm::GoInsaneState::OnExit(Collider& collider,
                                               PlayerModel& playerModel)
{
    goInsaneDuring_ = 0;
}
