#include <fstream>
#include <iostream>
#include "Entity.hpp"

#include <algorithm>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/polymorphic.hpp>

#include "../Application/IApplication/IApplication.hpp"
#include "../Component/Content/Basically/Ui/Button/Button.h"
#include "../Component/Content/Basically/Renderer/AnimationRenderer/AnimationRenderer.h"
#include "../Component/Content/Basically/Collider/Box/BoxCollider.h"
#include "../Component/Content/Basically/ImageRenderer/ImageRenderer.h"
#include "../Component/Content/Basically/MovieRenderer/MovieRenderer.h"
#include "../Component/Content/Basically/Particle/Particle.h"
#include "../Component/Content/Basically/Renderer/AnimationRenderer/SetIsReverse/SetIsReverse.h"
#include "../Component/Content/Basically/Renderer/SpriteRenderer/SpriteRenderer.h"
#include "../Component/Content/Basically/Renderer/TextRenderer/TextRenderer.h"
#include "../Component/Content/Basically/Transform/Transform.hpp"
#include "../Component/Content/Basically/Ui/UiEventCallback/UiEventCallBack.h"
#include "../Component/Content/TileMap/TileMap.h"
#include "../Libs/ImGui/imgui.h"
#include "../MyScript/AutoMove/AutoMove.h"
#include "../MyScript/Player/PlayerAvatar.h"
#include "../MyScript/DamageNotation/Physics/DamageNotation.h"
#include "../MyScript/Props/TorchObject/TorchObject.h"
#include "../MyScript/Door/DoorObject.h"
#include "../MyScript/DungeonRoom/DungeonRoom.h"
#include "../MyScript/FightParameter/PlayerAttackArea.h"
#include "../MyScript/FightParameter/Enemy/Skeleton/White/WhiteSkeleton.h"
#include "../MyScript/FightParameter/MadnessEnergy/MadnessEnergyObject/MadnessEnergyObject.h"
#include "../MyScript/FightParameter/Enemy/Slime/Blue/BlueSlime.h"
#include "../MyScript/FightParameter/Enemy/SummonCircle/SummonEnemyCircle.h"
#include "../MyScript/Item/Skill/SummonLighting/SummonLightning.h"
#include "../MyScript/Item/Skill/SummonLighting/Object/Thunder0Object.h"
#include "../MyScript/Item/Skill/SummonLighting/Object/Thunder0ObjectAttackArea.h"
#include "../MyScript/PauseScene/GameStartButton/GameStartButton.h"
#include "../MyScript/Portal/Portal.h"
#include "../MyScript/Props/Barrel0Object/Barrel0Object.h"
#include "../MyScript/Props/SignboardObject/SignboardObject.h"
#include "../MyScript/Props/Pot/BreakableYellowPot/BreakablePotObject.h"
#include "../MyScript/Props/Pot/BreakingYellowPot/BreakingYellowPot.h"
#include "../MyScript/DungeonRoom/EntranceArea/EntranceArea.h"
#include "../MyScript/FightParameter/Enemy/BoxAttackArea/EnemyBoxAttackArea.h"
#include "../MyScript/FightParameter/Enemy/DarkMushroom/DarkMushroom.h"
#include "../MyScript/FightParameter/Enemy/FlyingFox/FlyingFox.h"
#include "../MyScript/FightParameter/Enemy/FrostShadowKnight/FrostShadowKnight.h"
#include "../MyScript/FightParameter/Enemy/GhostWizard/GhostWizard.h"
#include "../MyScript/FightParameter/Enemy/SmallOrc/SmallOrc.h"
#include "../MyScript/FightParameter/Enemy/SummonBossCircle/SummonBossCircle.h"
#include "../MyScript/FightParameter/Projectile/FrostEnergyShoot/FrostEnergyShoot.h"
#include "../MyScript/FightParameter/Projectile/SmallFireBall/SmallFireBall.h"
#include "../MyScript/FightParameter/Projectile/StoneArrow/StoneArrow.h"
#include "../MyScript/Item/Drop/PowerUp/CollectMadness/CollectMadnessPowerUpItem.h"
#include "../MyScript/Item/Drop/PowerUp/DarkHeal/DarkHealPowerUpItem.h"
#include "../MyScript/Item/Drop/PowerUp/Physics/PhysicsPowerUpItem.h"
#include "../MyScript/OnUnloadSceneForInputAction/OnUnloadSceneForInputAction.h"
#include "../MyScript/Player/Model/CanUseSkillParticle.h"
#include "../MyScript/Portal/BeginPortal.h"
#include "../MyScript/Props/Gimmick/Content/StoneFence/CopperFence.h"
#include "../MyScript/Props/Gimmick/Thunder/ReceiveThunderGimmick.h"
#include "../MyScript/Props/Gimmick/Trap/RisingFire/RisingFireTrap.h"
#include "../MyScript/Props/Gimmick/Trap/StoneShootArrow/StoneShootArrowTrap.h"
#include "../MyScript/Props/Grass/Strange/GimmickStrangeGrass.h"
#include "../MyScript/Props/WoodChest/WoodChest.h"
#include "../MyScript/Props/WoodNail/WoodNail.h"
#include "../MyScript/Scene/Sound/SceneBgmPlayer/SceneBgmPlayer.h"
#include "../MyScript/Scene/UnLoadLoadingScene/UnLoadLoadingSceneComponent/UnLoadLoadingSceneComponent.h"
#include "../MyScript/UI/GameClearScene/GameClearText.h"
#include "../MyScript/UI/GameOverScene/StartOverButton.h"
#include "../MyScript/UI/GamePlayScene/PlayerParamView/MadnessBar/MadnessBar.h"
#include "../MyScript/UI/GamePlayScene/Presenter/Presenter.h"
#include "../MyScript/UI/LoadingScene/LoadingIcon/LoadingIcon.h"
#include "../MyScript/UI/SelectStageNumber/SelectStageNumber.h"
#include "../MyScript/UI/SelectStageNumber/AnimationImageRenderer/AnimationImageRenderer.h"

Entity::~Entity()
{
    onDespawnSubscription_.unsubscribe();
    IApplication::GetInstance().EntityContainer().RemoveContent(this);
    IApplication::GetInstance().OnAwakeEntityContainer().RemoveContent(this);
}

void Entity::InitSceneEntity()
{
    IApplication::GetInstance().EntityContainer().AddSceneContent(this);
}

void Entity::Init()
{
    IApplication::GetInstance().EntityContainer().AddContent(this);
    for (const auto& component : components_)
    {
        component->SetEntityRef(*this);
    }
    InitComponents();
    IApplication::GetInstance().OnAwakeEntityContainer().AddContent(this);
}

void Entity::InitComponents() const
{
    for (const auto& component : components_)
    {
        component->Init();
    }
}

void Entity::OnAwakeComponents() const
{
    for (const auto& component : components_)
    {
        component->Awake();
    }
}

Entity& Entity::Spawn(const std::string& filePath, const Vector2 position)
{
    const auto entity = new Entity();
    entity->OnDeserialize(filePath);
    entity->GetComponent<Transform>()->position_ = position;
    return *entity;
}

void Entity::OnDespawn()
{
    IApplication::GetInstance().OnDeSpawnEntityContainer().AddContent(this);
    for (const auto& component : components_)
    {
        component->Despawned();
    }
}

Guid& Entity::GetGuid()
{
    return guid_;
}

void Entity::OnUpdateBeginPhysics() const
{
    for (const auto& component : components_)
    {
        component->OnBeginUpdatePhysics();
    }
}

void Entity::OnUpdateForGameRoop() const
{
    for (const auto& component : components_)
    {
        component->OnUpdate();
    }
}

void Entity::OnUpdateDraw() const
{
    for (const auto& component : components_)
    {
        component->OnDraw();
    }
}

void Entity::OnUpdateEndPhysics() const
{
    for (const auto& component : components_)
    {
        component->OnEndUpdatePhysics();
    }
}

void Entity::OnEditorUpdate() const
{
    for (const auto& component : components_)
    {
        component->OnEditorUpdate();
    }
}

void Entity::OnDrawDebug()
{
    if (ImGui::TreeNode(
        (name_ + "                                                                 " + guid_.Value()).c_str()))
    {
        const auto selfPos = GetComponent<Transform>()->position_ + IApplication::GetInstance().Camera().position_;
        DrawCircle(static_cast<int>(selfPos.x_), static_cast<int>(selfPos.y_), 4, GetColor(178, 45, 53), 1);

        guid_.OnDrawInspector();

        char nameBuffer[256] = {};
        strncpy_s(nameBuffer, name_.c_str(), sizeof(nameBuffer) - 1);
        if (ImGui::InputText(("name: " + guid_.Value()).c_str(), nameBuffer, sizeof(nameBuffer)))
        {
            name_ = std::string(nameBuffer);
        }

        bool isOnRemoveComponent = false;
        std::vector<std::unique_ptr<Component>>::iterator onRemoveComponent;
        for (const auto& component : components_)
        {
            ImGui::Spacing();
            if (component == nullptr)
            {
                continue;
            }
            if (ImGui::CollapsingHeader(typeid(*component).name()))
            {
                component->OnDrawInspector();
                if (ImGui::Button("RemoveComponent"))
                {
                    isOnRemoveComponent = true;
                    onRemoveComponent = std::remove(components_.begin(), components_.end(), component);
                }
            }
        }
        if (isOnRemoveComponent)
        {
            components_.erase(onRemoveComponent, components_.end());
        }
        ImGui::Spacing();
        ImGui::Spacing();
        if (ImGui::TreeNode(("AddComponent" + guid_.Value()).c_str()))
        {
            DrawAddComponentButton<Transform>();
            DrawAddComponentButton<Particle>();
            DrawAddComponentButton<Player::PlayerAvatar>();
            DrawAddComponentButton<DamageNotation>();
            DrawAddComponentButton<PlayerAttackArea>();
            DrawAddComponentButton<DoorObject>();
            DrawAddComponentButton<Thunder0Object>();
            DrawAddComponentButton<Thunder0ObjectAttackArea>();
            DrawAddComponentButton<SkillBookDropItemObject>();
            DrawAddComponentButton<MadnessEnergyObject>();
            if (ImGui::TreeNode("Map"))
            {
                DrawAddComponentButton<TileMap>();
                DrawAddComponentButton<Map::Room::DungeonRoom>();
                DrawAddComponentButton<Map::Room::EntranceArea>();
                ImGui::TreePop();
                ImGui::Spacing();
            }
            if (ImGui::TreeNode("Renderer"))
            {
                DrawAddComponentButton<SpriteRenderer>();
                DrawAddComponentButton<AnimationRenderer>();
                DrawAddComponentButton<ImageRenderer>();
                DrawAddComponentButton<AnimationImageRenderer>();
                DrawAddComponentButton<TextRenderer>();
                DrawAddComponentButton<MovieRenderer>();
                DrawAddComponentButton<SetIsReverse>();
                ImGui::TreePop();
                ImGui::Spacing();
            }
            if (ImGui::TreeNode("Sound"))
            {
                DrawAddComponentButton<Sound::SceneBgmPlayer>();
                ImGui::TreePop();
                ImGui::Spacing();
            }
            if (ImGui::TreeNode("Collider"))
            {
                DrawAddComponentButton<BoxCollider>();
                ImGui::TreePop();
                ImGui::Spacing();
            }
            if (ImGui::TreeNode("UI"))
            {
                DrawAddComponentButton<Ui::Button>();
                DrawAddComponentButton<Ui::UiEventCallBack>();
                if (ImGui::TreeNode("TitleScene"))
                {
                    DrawAddComponentButton<PauseScene::GameStartButton>();
                    ImGui::TreePop();
                    ImGui::Spacing();
                }
                if (ImGui::TreeNode("GamePlayScene"))
                {
                    DrawAddComponentButton<GamePlayScene::Presenter>();
                    DrawAddComponentButton<GamePlayScene::PlayerParamView::HealthBar>();
                    DrawAddComponentButton<GamePlayScene::PlayerParamView::MadnessBar>();
                    DrawAddComponentButton<GamePlayScene::PlayerParamView::SkillSlotView>();
                    ImGui::TreePop();
                    ImGui::Spacing();
                }
                if (ImGui::TreeNode("LoadingScene"))
                {
                    DrawAddComponentButton<LoadingScene::LoadingIcon>();
                    ImGui::TreePop();
                    ImGui::Spacing();
                }
                if (ImGui::TreeNode("GameOverScene"))
                {
                    DrawAddComponentButton<GameOverScene::StartOverButton>();
                    ImGui::TreePop();
                    ImGui::Spacing();
                }
                if (ImGui::TreeNode("StageSelectScene"))
                {
                    DrawAddComponentButton<StageSelectScene::SelectStageNumber>();
                    ImGui::TreePop();
                    ImGui::Spacing();
                }
                if (ImGui::TreeNode("GameClearScene"))
                {
                    DrawAddComponentButton<GameClearScene::GameClearText>();
                    ImGui::TreePop();
                    ImGui::Spacing();
                }
                ImGui::TreePop();
                ImGui::Spacing();
            }
            if (ImGui::TreeNode("Props"))
            {
                DrawAddComponentButton<Prop::WoodChest>();
                DrawAddComponentButton<TorchObject>();
                DrawAddComponentButton<Prop::Barrel0Object>();
                DrawAddComponentButton<Prop::SignboardObject>();
                DrawAddComponentButton<Prop::BreakablePotObject>();
                DrawAddComponentButton<Prop::BreakingYellowPot>();
                if (ImGui::TreeNode("Gimmick"))
                {
                    DrawAddComponentButton<Prop::WoodNail>();
                    DrawAddComponentButton<Prop::Gimmick::ReceiveThunderGimmick>();
                    if (ImGui::TreeNode("Trap"))
                    {
                        DrawAddComponentButton<Prop::Trap::StoneShootArrowTrap>();
                        DrawAddComponentButton<Prop::Trap::RisingFireTrap>();
                        ImGui::TreePop();
                        ImGui::Spacing();
                    }

                    if (ImGui::TreeNode("Content"))
                    {
                        DrawAddComponentButton<Prop::CopperFence>();
                        DrawAddComponentButton<Prop::Gimmick::GimmickStrangeGrass>();
                        ImGui::TreePop();
                        ImGui::Spacing();
                    }
                    ImGui::TreePop();
                    ImGui::Spacing();
                }
                ImGui::TreePop();
                ImGui::Spacing();
            }
            if (ImGui::TreeNode("Portal"))
            {
                DrawAddComponentButton<Portal::Portal>();
                DrawAddComponentButton<Portal::BeginPortal>();
                DrawAddComponentButton<Enemy::FrostShadowKnight>();
                ImGui::TreePop();
                ImGui::Spacing();
            }
            if (ImGui::TreeNode("Enemy"))
            {
                if (ImGui::TreeNode("AttackArea"))
                {
                    DrawAddComponentButton<Enemy::EnemyBoxAttackArea>();
                    ImGui::TreePop();
                    ImGui::Spacing();
                }
                DrawAddComponentButton<Enemy::SummonEnemyCircle>();
                DrawAddComponentButton<Enemy::SummonBossCircle>();
                DrawAddComponentButton<Enemy::BlueSlime>();
                DrawAddComponentButton<Enemy::WhiteSkeleton>();
                DrawAddComponentButton<Enemy::FlyingFox>();
                DrawAddComponentButton<Enemy::GhostWizard>();
                DrawAddComponentButton<Enemy::SmallOrc>();
                DrawAddComponentButton<Enemy::FrostShadowKnight>();
                DrawAddComponentButton<Enemy::DarkMushroom>();
                ImGui::TreePop();
                ImGui::Spacing();
            }
            if (ImGui::TreeNode("Other"))
            {
                DrawAddComponentButton<OnUnloadSceneForInputAction>();
                DrawAddComponentButton<AutoMove>();
                DrawAddComponentButton<LoadingScene::UnLoadLoadingSceneComponent>();
                DrawAddComponentButton<Player::CanUseSkillParticle>();
                if (ImGui::TreeNode("PowerUpItem"))
                {
                    DrawAddComponentButton<Player::PhysicsPowerUpItem>();
                    DrawAddComponentButton<Player::DarkHealPowerUpItem>();
                    DrawAddComponentButton<Player::CollectMadnessPowerUpItem>();
                    ImGui::TreePop();
                    ImGui::Spacing();
                }
                if (ImGui::TreeNode("Projectile"))
                {
                    DrawAddComponentButton<Projectile::SmallFireBall>();
                    DrawAddComponentButton<Projectile::StoneArrow>();
                    DrawAddComponentButton<Projectile::FrostEnergyShoot>();
                    ImGui::TreePop();
                    ImGui::Spacing();
                }
                ImGui::TreePop();
                ImGui::Spacing();
            }

            ImGui::TreePop();
            ImGui::Spacing();
        }
        ImGui::TreePop();
        ImGui::Spacing();
    }
}

void Entity::OnSerialize(const std::string& filePath)
{
    if (!GetComponent<Transform>())
    {
        AddComponent<Transform>();
    }

    std::ofstream ofStream(filePath);
    cereal::JSONOutputArchive archive(ofStream);
    archive(
        cereal::make_nvp("name"         , name_         ),
        cereal::make_nvp("Components"   , components_   )
    );
}

void Entity::OnDeserialize(const std::string& filePath)
{
    std::ifstream ifStream(filePath);
    cereal::JSONInputArchive archive(ifStream);
    archive(
        cereal::make_nvp("name"         , name_         ),
        cereal::make_nvp("Components"   , components_   )
    );
    Init();
}

const rxcpp::composite_subscription& Entity::OnDespawnSubscription() const
{
    return onDespawnSubscription_;
}
