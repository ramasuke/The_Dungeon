#pragma once
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/memory.hpp>
#include "../../../../BasicallyParameter/Vector2/Vector2.hpp"
#include "../../../Component.hpp"

class Transform final : public virtual Component
{
public:
    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::base_class<Component>(this),
            cereal::make_nvp("position", position_),
            cereal::make_nvp("rotation", rotation_),
            cereal::make_nvp("scale", scale_)
        );
    }

    Vector2 position_;
    float rotation_ = 0;
    float scale_ = 1;

private:
    void Init() override;
    void Awake() override;
    void OnUpdate() override;
    void OnDraw() override;
    void OnDrawInspector() override;
};

CEREAL_REGISTER_TYPE(Transform)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Transform)
