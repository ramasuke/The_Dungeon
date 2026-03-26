#include "EntranceArea.h"

#include "../../../Application/IApplication/IApplication.hpp"
#include "../../../Entity/Entity.hpp"

void Map::Room::EntranceArea::OnBeginSensor(b2SensorBeginTouchEvent*, Player::PlayerAvatar*)
{
    onEnterPlayer_.get_subscriber().on_next(unit{});

    // for (const auto& spawnModel : spawnEnemyModels_)
    // {
    //     Enemy::Enemy::DropDustSpawn(spawnModel);
    // }

    EntityRef().OnDespawn();
}

void Map::Room::EntranceArea::OnDrawInspector()
{
    // ImGuiHelper::OnDrawInputField("spawnEnemyModels",
    //                               spawnEnemyModels_,
    //                               [&]() { EntranceArea::OnDrawAddEnemyModelButton(); });
    //
    //
    // for (const auto& model : spawnEnemyModels_)
    // {
    //     DrawCircle(static_cast<int>(model->Position().x_ + IApplication::GetInstance().Camera().position_.x_),
    //                static_cast<int>(model->Position().y_ + IApplication::GetInstance().Camera().position_.y_),
    //                4, GetColor(178, 45, 53), 1);
    // }
}
