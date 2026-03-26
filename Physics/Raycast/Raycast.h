#pragma once
#include "../../BasicallyParameter/Vector2/Vector2.hpp"
#include "../../Libs/Box2D/include/src/box2d/id.h"

class Raycast final
{
public:
    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(direction_);
    }

    [[nodiscard]] bool CheckHit(Vector2 origin) const;
    [[nodiscard]] bool CheckHit(Vector2 origin, b2BodyId) const;
    void OnDrawInspector(Vector2 origin);
    void OnDrawDebug(Vector2 origin) const;

private:
    Vector2 direction_;
};
