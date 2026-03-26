#include "Presenter.h"

#include "../../../Player/PlayerAvatar.h"

void GamePlayScene::Presenter::Awake()
{
    playerParamView_.Init();

    SubscribeModelEventToView();
    // SubscribeViewEventToModel();
}

void GamePlayScene::Presenter::OnDrawInspector()
{
    playerParamView_.OnDrawInspector();
}

void GamePlayScene::Presenter::SubscribeModelEventToView()
{
    const auto& normalFormParam = Player::PlayerAvatar::Model().BasicParam().NormalFormParam();
    
    normalFormParam.Health().Subscribe(
        OnDespawnSubscription(), [&](const Health health)
        {
            playerParamView_.HealthBar().Value()->OnUpdateView(health);
        });
    normalFormParam.CurrentMadness().Subscribe(
        OnDespawnSubscription(), [&](const MadnessEnergy madness)
        {
            playerParamView_.MadnessBar().Value()->OnUpdateView(madness);
        });

    Player::PlayerAvatar::Model().BasicParam().Inventory().Skill().Subscribe(
        OnDespawnSubscription(), [&](const std::shared_ptr<Skill::SkillBase>& skill)
        {
            playerParamView_.SkillSlot().Value()->OnUpdateView(skill);
        }
    );
}

// void GamePlayScene::Presenter::SubscribeViewEventToModel()
// {
//     
// }
