#include "NormalFormConsumptionMadnessState.h"

#include "../../../PlayerModel.h"
#include "../../../../../../Entity/Entity.hpp"
#include "../../Group/PlayerStateGroup.h"

void Player::NormalForm::NormalFormConsumptionMadnessState::OnEnter(BasicParam& basicParam,
                                                                    Transform& transform,
                                                                    Collider& collider,
                                                                    PlayerController& controller,
                                                                    AnimationRenderer& playerAnimRender,
                                                                    PlayerModel& playerModel)
{
    particle_ = &Entity::Spawn(consumptioningParticlePrefabPath_, transform.position_);
    particle_->GetComponent<Transform>()->position_ += particleOffsetPos_;
    playerAnimRender.SetAnimation(basicParam.NormalFormParam().Animation().ConsumptionMadness());
}

void Player::NormalForm::NormalFormConsumptionMadnessState::OnUpdateForGameRoop(
    BasicParam& basicParam,
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
    OnUpdateConsumptionParticle(playerModel, basicParam, controller);
    stateDuring_++;

    if (!controller.ConsumptionMadnessAction().IsReleased())
        return;

    OnConsumptionMadnessAction(playerModel,
                               controller,
                               basicParam,
                               stateGroup,
                               onChangeState);
}

void Player::NormalForm::NormalFormConsumptionMadnessState::OnExit(Collider& collider,
                                                                   PlayerModel& playerModel)
{
    particle_->OnDespawn();
    particle_ = nullptr;

    stateDuring_ = 0;
}

void Player::NormalForm::NormalFormConsumptionMadnessState::OnUpdateConsumptionParticle(
    PlayerModel& playerModel,
    BasicParam& basicParam,
    const PlayerController& controller) const
{
    float nextScale = 0;
    if (basicParam.NormalFormParam().CanChangeDarkForm())
    {
        nextScale = ClampToNOrMore(basicParam.NormalFormParam().ToDarkFormNeedDuration().Value()
                                   , controller.ConsumptionMadnessAction().ReadValue()) * particleScaleCoefficient_;
        
        if (basicParam.NormalFormParam().ToDarkFormNeedDuration().Value() == stateDuring_)
        {
            OnPlayPromptConsumptionParticle(playerModel);
        }
    }
    else if (basicParam.NormalFormParam().CanDarkHeal())
    {
        nextScale = ClampToNOrMore(basicParam.NormalFormParam().DarkHealNeedDuration().Value(),
                                   controller.ConsumptionMadnessAction().ReadValue()) * particleScaleCoefficient_;
        
        if (basicParam.NormalFormParam().DarkHealNeedDuration().Value() == stateDuring_)
        {
            OnPlayPromptConsumptionParticle(playerModel);
        }
    }
    else if (basicParam.NormalFormParam().CanEnableUseSkill())
    {
        nextScale = ClampToNOrMore(basicParam.NormalFormParam().UseSkillNeedMadness().Value().Value(),
                                   controller.ConsumptionMadnessAction().ReadValue()) * particleScaleCoefficient_;
        
        if (basicParam.NormalFormParam().UseSkillNeedMadness().Value().Value() == stateDuring_)
        {
            OnPlayPromptConsumptionParticle(playerModel);
        }
    }
    else
    {
        nextScale = 0;
    }

    particle_->GetComponent<Transform>()->scale_ = nextScale;
}

void Player::NormalForm::NormalFormConsumptionMadnessState::OnConsumptionMadnessAction(
    const PlayerModel& playerModel,
    const PlayerController& controller,
    BasicParam& basicParam,
    const PlayerStateGroup& stateGroup,
    const std::function<void(const std::shared_ptr<IPlayerState>&)>& onChangeState)
{
    if (controller.ConsumptionMadnessAction().ReadValue() > basicParam.NormalFormParam().ToDarkFormNeedDuration().
                                                                       Value() && basicParam.NormalFormParam().
        CanChangeDarkForm())
    {
        onChangeState(stateGroup.GoInsaneState());
    }
    else if (controller.ConsumptionMadnessAction().ReadValue() > basicParam.NormalFormParam().DarkHealNeedDuration().
                                                                            Value() && basicParam.NormalFormParam().
        CanDarkHeal())
    {
        onChangeState(stateGroup.NormalFormOnDarkHealState());
    }
    else if (basicParam.NormalFormParam().CanEnableUseSkill() && !basicParam.NormalFormParam().IsUseSkill())
    {
        basicParam.NormalFormParam().OnEnableUseSkill(*playerModel.Transform());
        onChangeState(stateGroup.NormalFormIdleState());
    }
    else
    {
        onChangeState(stateGroup.NormalFormIdleState());
    }
}

void Player::NormalForm::NormalFormConsumptionMadnessState::OnPlayPromptConsumptionParticle(
    const PlayerModel& playerModel) const
{
    Entity::Spawn(promptConsumptionParticlePrefabPath_, playerModel.Transform()->position_);
}
