#include "PlayerModel.h"

#include "../../../Application/ApplicationParameter.h"
#include "../../../Application/IApplication/IApplication.hpp"

Player::PlayerModel::PlayerModel()
{
    basicParam_ = IApplication::GetInstance().Extension().PlayerParam();
}

void Player::PlayerModel::Init(AnimationRenderer* animationRenderer,
                               ::Transform* transform,
                               ::Collider* collider,
                               PlayerController& controller)
{
    // basicParam_ = IApplication::GetInstance().Extension().PlayerParam();
    
    transform_ = transform;
    collider_ = collider;
    basicParam_->Init();
    currentState_ = stateGroup_.NormalFormIdleState();
    currentState_->OnEnter(*basicParam_,
                           *transform_,
                           *collider_,
                           controller,
                           *animationRenderer,
                           *this);
}

void Player::PlayerModel::OnUpdate(AnimationRenderer& animationRenderer, PlayerController& controller)
{
    IApplication::GetInstance().Camera().position_ = transform_->position_ * -1 + Vector2(
        WINDOW_WIDTH_SCALE / 2, WINDOW_HEIGHT_SCALE / 2);
    currentState_->OnUpdateForGameRoop(*basicParam_,
                                       *transform_,
                                       *collider_,
                                       controller,
                                       stateGroup_,
                                       animationRenderer,
                                       *this,
                                       [this, &controller, &animationRenderer](
                                       const std::shared_ptr<IPlayerState>& nextState)
                                       {
                                           OnChangeState(controller, animationRenderer, nextState);
                                       });
}

void Player::PlayerModel::OnChangeState(PlayerController& controller
                                        , AnimationRenderer& animationRenderer
                                        , const std::shared_ptr<IPlayerState>& nextState)
{
    currentState_->OnExit(*collider_, *this);
    currentState_ = nextState;
    currentState_->OnEnter(*basicParam_, *transform_, *collider_, controller, animationRenderer, *this);
}

void Player::PlayerModel::OnDrawInspector(AnimationRenderer& animationRenderer,
                                          PlayerController& controller)
{
    IApplication::GetInstance().Camera().position_ = transform_->position_ * -1 + Vector2(
        WINDOW_WIDTH_SCALE / 2, WINDOW_HEIGHT_SCALE / 2);
    if (ImGui::TreeNode("BasicParameters"))
    {
        basicParam_->OnDrawInspector();
        ImGui::TreePop();
        ImGui::Spacing();
    }

    if (ImGui::Button("OnChangeIdleState"))
    {
        OnChangeState(controller, animationRenderer, stateGroup_.NormalFormIdleState());
    }
    if (ImGui::Button("OnChangeWalkState"))
    {
        OnChangeState(controller, animationRenderer, stateGroup_.NormalFormWalkState());
    }
    if (ImGui::Button("OnChangeAttackState"))
    {
        OnChangeState(controller, animationRenderer, stateGroup_.NormalFormAttackState());
    }
}

void Player::PlayerModel::OnReset()
{
    collider_ = nullptr;
    transform_ = nullptr;
}

Collider* Player::PlayerModel::Collider() const
{
    return collider_;
}
