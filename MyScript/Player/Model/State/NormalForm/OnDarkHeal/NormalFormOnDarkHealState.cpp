#include "NormalFormOnDarkHealState.h"

#include "../../../../../../Entity/Entity.hpp"
#include "../../Group/PlayerStateGroup.h"

void Player::NormalForm::NormalFormOnDarkHealState::OnEnter(BasicParam& basicParam,
                                                            Transform& transform,
                                                            Collider& collider,
                                                            PlayerController& controller,
                                                            AnimationRenderer& playerAnimRender,
                                                            PlayerModel& playerModel)
{
    Entity::Spawn(particlePrefabPath_, transform.position_);
    basicParam.NormalFormParam().OnDarkHeal(basicParam.NormalFormParam().DarkHealCount());
}

void Player::NormalForm::NormalFormOnDarkHealState::OnUpdateForGameRoop(BasicParam& basicParam,
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
    onChangeState(stateGroup.NormalFormIdleState());
}

void Player::NormalForm::NormalFormOnDarkHealState::OnExit(Collider& collider,
                                                           PlayerModel& playerModel)
{
    nextStateDuring_ = 0;
}
