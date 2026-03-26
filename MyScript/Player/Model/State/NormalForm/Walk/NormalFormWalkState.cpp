#include "NormalFormWalkState.h"

#include "../../../../../../BasicallyParameter/Sound/Play/SoundPlay.h"
#include "../../../../../Libs/Box2D/include/src/box2d/box2d.h"
#include "../../../../../Libs/Box2D/include/src/box2d/math_functions.h"
#include "../../Group/PlayerStateGroup.h"

void Player::NormalForm::NormalFormWalkState::OnEnter(BasicParam& basicParam,
                                                      Transform& transform,
                                                      Collider& collider,
                                                      PlayerController& controller,
                                                      AnimationRenderer& playerAnimRender,
                                                      PlayerModel& playerModel)
{
    playerAnimRender.SetAnimation(basicParam.NormalFormParam().Animation().Walk());
}

void Player::NormalForm::NormalFormWalkState::OnUpdateForGameRoop(BasicParam& basicParam,
                                                                  Transform& transform,
                                                                  Collider& collider,
                                                                  PlayerController& controller,
                                                                  PlayerStateGroup& stateGroup,
                                                                  AnimationRenderer& animRender,
                                                                  PlayerModel& playerModel,
                                                                  const std::function<void(
                                                                      const std::shared_ptr<IPlayerState>&)> onChangeState)
{
    const auto inputValue = controller.Move().ReadValue();
    if (inputValue != Vector2(0, 0))
    {
        const auto moveValue = inputValue * basicParam.NormalFormParam().WalkSpeed().Value();
        b2Body_SetLinearVelocity(collider.GetBodyId(), b2Vec2{moveValue.x_, moveValue.y_});
    }
    else
    {
        onChangeState(stateGroup.NormalFormIdleState());
    }

    if (inputValue.x_ > 0)
    {
        animRender.isReverseX_ = false;
    }
    else if (inputValue.x_ < 0)
    {
        animRender.isReverseX_ = true;
    }

    UpdateWalkSound(basicParam);
    
    if (basicParam.IsHitDamaged())
    {
        onChangeState(stateGroup.NormalFormOnDamageState());
    }
    if (controller.ConsumptionMadnessAction().IsUpdatePressed())
    {
        onChangeState(stateGroup.NormalFormConsumptionMadnessState());
        return;
    }
    if (controller.Attack().IsUpdatePressed())
    {
        onChangeState(stateGroup.NormalFormAttackState());
        return;
    }
}

void Player::NormalForm::NormalFormWalkState::OnExit(Collider& collider,
                                                     PlayerModel& playerModel)
{
    walkSoundDuring_ = 0;
}

void Player::NormalForm::NormalFormWalkState::UpdateWalkSound(BasicParam& basicParam)
{
    walkSoundDuring_++;
    if (walkSoundDuration_ > walkSoundDuring_)
        return;

    walkSoundDuring_ = 0;
    Sound::PlaySe(basicParam.NormalFormParam().Sound().Walk());
}
