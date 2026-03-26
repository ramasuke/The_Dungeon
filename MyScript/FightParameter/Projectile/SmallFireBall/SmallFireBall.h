#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../Component/Component.hpp"
#include "../../../../Component/Content/Basically/Renderer/AnimationRenderer/Animation/Animation.h"
#include "../../../../Component/Content/Basically/Transform/Transform.hpp"
#include "../../../../Physics/Sensor/Begin/IBeginSensorable.h"

namespace Projectile
{
    class SmallFireBall final : public virtual Component,
                                public virtual IBeginSensorable<Transform>
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this),
                cereal::make_nvp("shootAnimation", shootAnimation_),
                cereal::make_nvp("speed", speed_)
            );
        }

    private:
        void Init() override;
        void OnUpdate() override;
        void OnDrawInspector() override;
        void OnBeginSensor(b2SensorBeginTouchEvent*, Transform*) override;

        std::shared_ptr<Animation> shootAnimation_ = std::make_shared<Animation>();
        float speed_ = 0.03f;
    };
}

CEREAL_REGISTER_TYPE(Projectile::SmallFireBall)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Projectile::SmallFireBall)
