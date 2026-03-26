#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../BasicallyParameter/Vector2/Vector2.hpp"
#include "../../Component/Component.hpp"

class AutoMove final : public virtual Component
{
public:
    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::base_class<Component>(this),
            cereal::make_nvp("move"         , move_             ),
            cereal::make_nvp("moveDuration" , moveDuration_     )
        );
    }

private:
    void OnUpdate() override;
    void OnDrawInspector() override;
    
    Vector2 move_ = Vector2(-10, 0);
    int     moveDuration_ = 10;
    int     moveDuring_ = 0;
};

CEREAL_REGISTER_TYPE(AutoMove)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, AutoMove)