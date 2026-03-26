#include "SpawnEntity.h"

#include "../../../../Application/Screen/ScreenHelper.h"
#include "../../../../Entity/Entity.hpp"
#include "../../../../Helper/ImGui/ImGuiHelper.h"
#include "../../../FightParameter/Enemy/SummonCircle/SummonEnemyCircle.h"

void Map::Room::Event::SpawnEntity::Execute()
{
    for (const auto& spawnEnemyModel : spawnEnemyModels_)
    {
        const auto summonEnemyCircle = Entity::Spawn<Enemy::SummonEnemyCircle>(
            summonEnemyParticlePrefabPath_, spawnEnemyModel.Position());
        summonEnemyCircle->SetSummonModel(spawnEnemyModel);
    }
}

void Map::Room::Event::SpawnEntity::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("spawnEnemyModels", spawnEnemyModels_, [this]()
    {
        OnDrawAddEnemyModelButton();
    });
}

void Map::Room::Event::SpawnEntity::OnDrawDebug() const
{
    for (auto& spawnEnemyModel : spawnEnemyModels_)
    {
        spawnEnemyModel.OnDrawDebug();
    }
}

void Map::Room::Event::SpawnEntity::OnDrawAddEnemyModelButton()
{
    if (ImGui::Button("add"))
    {
        spawnEnemyModels_.emplace_back(Vector2(Screen::CameraCenterWorldPos()));
    }
}
