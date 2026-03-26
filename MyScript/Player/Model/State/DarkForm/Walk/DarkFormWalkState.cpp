#include "DarkFormWalkState.h"

#include "../../../../../Libs/Box2D/include/src/box2d/box2d.h"
#include "../../../../../Libs/Box2D/include/src/box2d/math_functions.h"
#include "../../Group/PlayerStateGroup.h"

void Player::DarkForm::DarkFormWalkState::OnEnter(BasicParam& basicParam,
                                                  Transform& transform,
                                                  Collider& collider,
                                                  PlayerController& controller,
                                                  AnimationRenderer& playerAnimRender,
                                                  PlayerModel& playerModel)
{
    playerAnimRender.SetAnimation(basicParam.DarkFormParam().Animation().Walk());
}

void Player::DarkForm::DarkFormWalkState::OnUpdateForGameRoop(BasicParam& basicParam,
                                                              Transform& transform,
                                                              Collider& collider,
                                                              PlayerController& controller,
                                                              PlayerStateGroup& stateGroup,
                                                              AnimationRenderer& animRender,
                                                              PlayerModel& playerModel,
                                                              const std::function<void(const std::shared_ptr<IPlayerState>&)>
                                                              onChangeState)
{
    const auto inputValue = controller.Move().ReadValue();
    if (inputValue != Vector2(0, 0))
    {
        const auto moveValue = inputValue * basicParam.DarkFormParam().WalkSpeed().Value();
        b2Body_SetLinearVelocity(collider.GetBodyId(), b2Vec2{moveValue.x_, moveValue.y_});
    }
    else
    {
        onChangeState(stateGroup.DarkFormIdleState());
    }

    if (inputValue.x_ > 0)
    {
        animRender.isReverseX_ = false;
    }
    else if (inputValue.x_ < 0)
    {
        animRender.isReverseX_ = true;
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

void Player::DarkForm::DarkFormWalkState::OnExit(Collider& collider,
                                                 PlayerModel& playerModel)
{
}
