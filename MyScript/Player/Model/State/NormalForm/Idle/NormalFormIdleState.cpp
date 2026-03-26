#include "NormalFormIdleState.h"

#include "../../../PlayerModel.h"
#include "../../../../../../Libs/Box2D/include/src/box2d/box2d.h"
#include "../../Group/PlayerStateGroup.h"

void Player::NormalForm::NormalFormIdleState::OnEnter(BasicParam& basicParam,
                                                      Transform& transform,
                                                      Collider& collider,
                                                      PlayerController& controller,
                                                      AnimationRenderer& playerAnimRender,
                                                      PlayerModel& playerModel)
{
    b2Body_SetLinearVelocity(collider.GetBodyId(), b2Vec2{0, 0});
    playerAnimRender.SetAnimation(basicParam.NormalFormParam().Animation().Idle());
}

void Player::NormalForm::NormalFormIdleState::OnUpdateForGameRoop(BasicParam& basicParam,
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
    if (basicParam.IsHitDamaged())
    {
        onChangeState(stateGroup.NormalFormOnDamageState());
    }
    if (controller.ConsumptionMadnessAction().IsUpdatePressed())
    {
        onChangeState(stateGroup.NormalFormConsumptionMadnessState());
        return;
    }
    if (controller.Move().IsUpdatePressed())
    {
        onChangeState(stateGroup.NormalFormWalkState());
        return;
    }
    if (controller.Attack().IsUpdatePressed())
    {
        onChangeState(stateGroup.NormalFormAttackState());
    }
}

void Player::NormalForm::NormalFormIdleState::OnExit(Collider& collider,
                                                     PlayerModel& playerModel)
{
}
