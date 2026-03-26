#include "BossFight.h"

#include "../../../../Application/Screen/ScreenHelper.h"
#include "../../../../BasicallyParameter/Sound/Play/SoundPlay.h"
#include "../../../../Entity/Entity.hpp"
#include "../../../../Helper/ImGui/ImGuiHelper.h"
#include "../../../FightParameter/Enemy/Enemy.h"
#include "../../../FightParameter/Enemy/SummonBossCircle/SummonBossCircle.h"

void Map::Room::Event::BossFight::Init()
{
    bossBgm_        .Init();
    spawnBossSound_ .Init();
}

void Map::Room::Event::BossFight::Execute()
{
        const auto summonBossCircle = Entity::Spawn<Enemy::SummonBossCircle>(
            summonBossEnemyParticlePrefabPath_, spawnBoss_.Position());
        summonBossCircle->SetSummonModel(spawnBoss_, [this] { OnDeathBossEvent(); });
        
        Sound::PlayBgm(bossBgm_);
        Sound::PlaySe(spawnBossSound_);
}

void Map::Room::Event::BossFight::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("spawnBoss"       , spawnBoss_        );
    ImGuiHelper::OnDrawInputField("spawnBossSound"  , spawnBossSound_   );
    ImGuiHelper::OnDrawInputField("bossBgm"         , bossBgm_          );
    ImGuiHelper::OnDrawInputField("onDeathBossSummonPrefabPaths", onDeathBossSummonModels_, [this]
    {
        if (!ImGui::Button("add"))
            return;

        onDeathBossSummonModels_.emplace_back(Vector2(Screen::CameraCenterWorldPos()));
    });
}

void Map::Room::Event::BossFight::OnDrawDebug() const
{
    spawnBoss_.OnDrawDebug();
}

void Map::Room::Event::BossFight::OnDeathBossEvent() const
{
    for (const auto& onDeathBossSummonModel : onDeathBossSummonModels_)
    {
        Entity::Spawn(onDeathBossSummonModel.PrefabPath(), onDeathBossSummonModel.Position());
    }
}
