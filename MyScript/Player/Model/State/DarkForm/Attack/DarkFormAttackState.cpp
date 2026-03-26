#include "DarkFormAttackState.h"

#include "../../../../../../Libs/Box2D/include/src/box2d/box2d.h"
#include "../../../../../Entity/Entity.hpp"
#include "../../../../../FightParameter/PlayerAttackArea.h"
#include "../../Group/PlayerStateGroup.h"

void Player::DarkForm::DarkFormAttackState::OnEnter(BasicParam& basicParam,
                                                    Transform& transform,
                                                    Collider& collider,
                                                    PlayerController& controller,
                                                    AnimationRenderer& playerAnimRender,
                                                    PlayerModel& playerModel)
{
    b2Body_SetLinearVelocity(collider.GetBodyId(), b2Vec2{0, 0});
    playerAnimRender.SetAnimation(basicParam.DarkFormParam().Animation().Attack());
}

void Player::DarkForm::DarkFormAttackState::OnUpdateForGameRoop(BasicParam& basicParam,
                                                                Transform& transform,
                                                                Collider& collider,
                                                                PlayerController& controller,
                                                                PlayerStateGroup& stateGroup,
                                                                AnimationRenderer& animRender,
                                                                PlayerModel& playerModel,
                                                                const std::function<void
                                                                    (const std::shared_ptr<IPlayerState>&)>
                                                                onChangeState)
{
    nextStateDuring_++;
    if (basicParam.DarkFormParam().AttackStateOnAttackDamageDuration().Value() == nextStateDuring_)
    {
        attackArea_ = SpawnAttackArea(basicParam, transform, animRender.isReverseX_);
        if (basicParam.Inventory().Skill().Value() != nullptr)
        {
            basicParam.Inventory().Skill().Value()->OnExecuteNormalForm(playerModel, controller, animRender);
        }
    }

    if (basicParam.DarkFormParam().AttackStateDuration().Value() >= nextStateDuring_)
        return;

    onChangeState(stateGroup.DarkFormIdleState());
}

void Player::DarkForm::DarkFormAttackState::OnExit(Collider& collider,
                                                   PlayerModel& playerModel)
{
    if (attackArea_ == nullptr)
        return;
    
    attackArea_->OnDespawn();
    attackArea_ = nullptr;
    nextStateDuring_ = 0;
}

Entity* Player::DarkForm::DarkFormAttackState::SpawnAttackArea(BasicParam& basicParam,
                                                               const Transform& transform,
                                                               const bool isReverseX) const
{
    Vector2 attackAreaSpawnPos;
    if (isReverseX)
    {
        attackAreaSpawnPos = Vector2(-1, 0) * basicParam.DarkFormParam().AttackDistance().Value() + transform.position_;
    }
    else
    {
        attackAreaSpawnPos = Vector2(1, 0) * basicParam.DarkFormParam().AttackDistance().Value() + transform.position_;
    }

    const auto attackArea = &Entity::Spawn(attackAreaPrefabPath_, attackAreaSpawnPos);
    attackArea->GetComponent<PlayerAttackArea>()->SetDamage(std::make_shared<DamageContext::PhysicsDamageContext>(*attackArea, basicParam.DarkFormParam().PhysicsAttackPower().Value()));
    return attackArea;
}
