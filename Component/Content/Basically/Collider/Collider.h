#pragma once
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

#include "../../../Component.hpp"
#include "../../../../BasicallyParameter/Vector2/Vector2.hpp"
#include "../../../../Libs/Box2D/include/src/box2d/id.h"
#include "../../../../Libs/Box2D/include/src/box2d/types.h"

class Collider : public virtual Component
{
public:
    template <typename Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::base_class<Component>(this)
        );
    }

    virtual ~Collider() = default;
    virtual b2BodyId GetBodyId() const = 0;
    virtual void SetOffsetPos(Vector2 pos) = 0;
    virtual void SetLayer(b2Filter) = 0;
};

CEREAL_REGISTER_TYPE(Collider)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Collider)
