#include <cmath>

#include "EnemyHelper.h"

#include "../../../../Application/IApplication/IApplication.hpp"
#include "../../../Player/PlayerAvatar.h"

bool Enemy::EnemyHelper::CheckRaycast(const Vector2 origin, const Collider& collider, const float distanceCoefficient,
                                      const b2QueryFilter filter)
{
    const auto direction = (collider.EntityRef().GetComponent<Transform>()->position_ - origin) * distanceCoefficient;

    return IApplication::GetInstance().Physics().CheckHitRaycast(origin, direction, collider.GetBodyId(), filter);
}

bool Enemy::EnemyHelper::FindPlayerForRaycast(const Vector2 origin, const float distanceCoefficient)
{
    constexpr uint16_t excludedLayer = EnemyLayer | PlayerAttackAreaLayer | MadnessEnergyLayer | EnemyAttackAreaLayer;
    constexpr b2QueryFilter filter = {0x0001, ~excludedLayer & 0xFFFF};
    
    if (Player::PlayerAvatar::Model().Collider() == nullptr)
        return false;
    
    return CheckRaycast(origin, *Player::PlayerAvatar::Model().Collider(), distanceCoefficient, filter);
}

b2Filter Enemy::EnemyHelper::CollisionableFilter()
{
    return b2Filter{Layer::EnemyLayer, 0xFFFF, 0};
}

b2Filter Enemy::EnemyHelper::EnemyAttackAreaFilter()
{
    constexpr uint16_t excludedLayer = MadnessEnergyLayer | EnemyAttackAreaLayer;
    constexpr uint16_t mask = static_cast<uint16_t>(~excludedLayer & 0xFFFF);
    return b2Filter{EnemyAttackAreaLayer, mask, 0};
}

std::list<Vector2> Enemy::EnemyHelper::FindPath(const Vector2 originPos, const Vector2 endPos)
{
    const auto origin = originPos / 43;
    const auto originInt = Vector2Int(
        static_cast<int>(std::round(origin.x_)),
        static_cast<int>(std::round(origin.y_))
    );

    const auto end = endPos / 43;
    const auto endInt = Vector2Int(
        static_cast<int>(std::round(end.x_)),
        static_cast<int>(std::round(end.y_))
    );

    const auto paths = IApplication::GetInstance().Extension().AStar().FindRoute(originInt, endInt);
    std::list<Vector2> floatPaths;
    for (const auto& p : paths)
    {
        floatPaths.emplace_back(static_cast<float>(p.x_) * 43, static_cast<float>(p.y_) * 43);
    }
    if (!floatPaths.empty())
    {
        floatPaths.pop_front();
    }
    return floatPaths;
}

std::list<Vector2> Enemy::EnemyHelper::FindToPlayerPath(const Vector2 originPos)
{
    return FindPath(originPos, Player::PlayerAvatar::Model().Transform()->position_);
}
