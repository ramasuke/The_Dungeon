#include "DarkFormIdleState.h"

#include "../../../../../../Libs/Box2D/include/src/box2d/box2d.h"
#include "../../Group/PlayerStateGroup.h"

void Player::DarkForm::DarkFormIdleState::OnEnter(BasicParam& basicParam,
                                                  Transform& transform,
                                                  Collider& collider,
                                                  PlayerController& controller,
                                                  AnimationRenderer& playerAnimRender,
                                                  PlayerModel& playerModel)
{
    b2Body_SetLinearVelocity(collider.GetBodyId(), b2Vec2{0, 0});
    playerAnimRender.SetAnimation(basicParam.DarkFormParam().Animation().Idle());
}

void Player::DarkForm::DarkFormIdleState::OnUpdateForGameRoop(BasicParam& basicParam,
                                                              Transform& transform,
                                                              Collider& collider,
                                                              PlayerController& controller,
                                                              PlayerStateGroup& stateGroup,
                                                              AnimationRenderer& animRender,
                                                              PlayerModel& playerModel,
                                                              const std::function<void(const std::shared_ptr<IPlayerState>&)>
                                                              onChangeState)
{
    if (controller.Move().IsUpdatePressed())
    {
        onChangeState(stateGroup.DarkFormWalkState());
    }
    if (controller.Attack().IsUpdatePressed())
    {
        onChangeState(stateGroup.DarkFormAttackState());
    }
    if (basicParam.IsHitDamaged())
    {
        onChangeState(stateGroup.DarkFormOnDamageState());
    }
}

void Player::DarkForm::DarkFormIdleState::OnExit(Collider& collider,
                                                 PlayerModel& playerModel)
{
}
