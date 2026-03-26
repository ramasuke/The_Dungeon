#pragma once
#include "../../../../Component/Component.hpp"
#include "../../../../Component/Content/Basically/Transform/Transform.hpp"
#include "../../../../Physics/Sensor/Begin/IBeginSensorable.h"
#include "../../DamageContext/Physics/PhysicsPower/PhysicsPower.h"

namespace Projectile
{
    class StoneArrow final : public virtual Component,
                             public virtual IBeginSensorable<Transform>
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this),
                cereal::make_nvp("damage"   , damage_   ),
                cereal::make_nvp("speed"    , speed_    )
            );
        }

    private:
        void Init() override;
        void OnUpdate() override;
        void OnDrawInspector() override;
        void OnBeginSensor(b2SensorBeginTouchEvent*, Transform*) override;

        float           speed_      = 0.1f;
        PhysicsPower    damage_     = PhysicsPower(1);
    };
}

CEREAL_REGISTER_TYPE(Projectile::StoneArrow)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Projectile::StoneArrow)
