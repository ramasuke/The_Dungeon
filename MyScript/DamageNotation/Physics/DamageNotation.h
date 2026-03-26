#pragma once

#include "../../../BasicallyParameter/Vector2/Vector2.hpp"
#include <cereal/types/polymorphic.hpp>

#include "../../../Component/Content/Basically/Renderer/TextRenderer/TextRenderer.h"
#include "../../FightParameter/DamageContext/Physics/PhysicsDamageContext.h"
#include "../../FightParameter/DamageContext/Thunder/ThunderPower/ThunderPower.h"

struct PhysicsPower;
class Transform;

class DamageNotation final : public virtual Component
{
public:
    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::base_class<Component>(this),
            cereal::make_nvp("moveTweenDirection", moveTweenDirection_),
            cereal::make_nvp("despawnDuration", despawnDuration_)
        );
    }

    void SetNotation(std::string damageText, Color color) const;
    
private:
    void Init() override;
    void OnUpdate() override;
    void OnDrawInspector() override;
    
    TextRenderer* textRenderer_ = nullptr;
    Transform* transform_ = nullptr;
    Vector2 moveTweenDirection_;
    int despawnDuration_ = 30;
    int despawnDuring_ = 0;
};

CEREAL_REGISTER_TYPE(DamageNotation)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, DamageNotation)
