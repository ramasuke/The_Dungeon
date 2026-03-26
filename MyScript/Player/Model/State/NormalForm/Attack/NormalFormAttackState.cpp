#include "NormalFormAttackState.h"

#include "../../../PlayerModel.h"
#include "../../../../../../BasicallyParameter/Sound/Play/SoundPlay.h"
#include "../../../../../../Libs/Box2D/include/src/box2d/box2d.h"
#include "../../../../../Entity/Entity.hpp"
#include "../../../../../FightParameter/PlayerAttackArea.h"
#include "../../Group/PlayerStateGroup.h"

void Player::NormalForm::NormalFormAttackState::OnEnter(BasicParam& basicParam,
                                                        Transform& transform,
                                                        Collider& collider,
                                                        PlayerController& controller,
                                                        AnimationRenderer& playerAnimRender,
                                                        PlayerModel& playerModel)
{
    b2Body_SetLinearVelocity(collider.GetBodyId(), b2Vec2{0, 0});
    playerAnimRender.SetAnimation(basicParam.NormalFormParam().Animation().Attack());
}

void Player::NormalForm::NormalFormAttackState::OnUpdateForGameRoop(BasicParam& basicParam,
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
    if (basicParam.NormalFormParam().AttackStateOnAttackDamageDuration().Value() == nextStateDuring_)
    {
        SpawnAttackArea(basicParam, transform, animRender.isReverseX_);
        Sound::PlaySe(basicParam.NormalFormParam().Sound().OnAttack());
        if (basicParam.Inventory().Skill().Value() != nullptr && basicParam.NormalFormParam().IsUseSkill())
        {
            basicParam.Inventory().Skill().Value()->OnExecuteNormalForm(playerModel, controller, animRender);
            basicParam.NormalFormParam().OnUseSkill();
        }
    }

    if (basicParam.NormalFormParam().AttackStateDuration().Value() >= nextStateDuring_)
        return;

    onChangeState(stateGroup.NormalFormIdleState());
}

void Player::NormalForm::NormalFormAttackState::OnExit(Collider& collider,
                                                       PlayerModel& playerModel)
{
    attackArea_->OnDespawn();
    attackArea_ = nullptr;
    nextStateDuring_ = 0;
}

void Player::NormalForm::NormalFormAttackState::SpawnAttackArea(BasicParam& basicParam, const Transform& transform,
                                                                const bool isReverseX)
{
    Vector2 attackAreaSpawnPos;
    if (isReverseX)
    {
        attackAreaSpawnPos = Vector2(-1, 0) * basicParam.NormalFormParam().AttackDistance().Value() + transform.
            position_;
    }
    else
    {
        attackAreaSpawnPos = Vector2(1, 0) * basicParam.NormalFormParam().AttackDistance().Value() + transform.
            position_;
    }

    attackArea_ = &Entity::Spawn(attackAreaPrefabPath_, attackAreaSpawnPos);
    attackArea_->GetComponent<PlayerAttackArea>()->SetDamage(
        std::make_shared<DamageContext::PhysicsDamageContext>(*attackArea_,
                                                              basicParam.NormalFormParam().PhysicsAttackPower().
                                                                         Value()));
}
