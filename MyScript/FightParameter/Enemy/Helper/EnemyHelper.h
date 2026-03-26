#pragma once
#include "../../../../BasicallyParameter/Vector2/Vector2.hpp"
#include "../../../../Libs/Box2D/include/src/box2d/types.h"

class Collider;

namespace Enemy
{
    class EnemyHelper final
    {
        EnemyHelper() = delete;

    public:
        static [[nodiscard]] bool CheckRaycast(Vector2 origin, const Collider& collider, float distanceCoefficient = 100, b2QueryFilter filter = b2QueryFilter());
        static [[nodiscard]] bool FindPlayerForRaycast(Vector2 origin, float distanceCoefficient = 100);
        static b2Filter CollisionableFilter();
        static b2Filter EnemyAttackAreaFilter();
        static std::list<Vector2> FindPath(Vector2 originPos,Vector2 endPos);
        static std::list<Vector2> FindToPlayerPath(Vector2 originPos);
    };
}
