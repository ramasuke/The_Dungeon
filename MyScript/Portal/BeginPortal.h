#pragma once
#include "../../BasicallyParameter/SerializeComponentRef/ComponentRef.h"
#include "../../Component/Component.hpp"
#include "../../Physics/Sensor/Begin/IBeginSensorable.h"
#include "../Player/PlayerAvatar.h"
#include "cereal/types/base_class.hpp"
#include "cereal/types/polymorphic.hpp"

namespace Portal
{
    class BeginPortal final : public virtual Component,
                              public virtual IBeginSensorable<Player::PlayerAvatar>
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this)
            );
        }

    private:
        void OnBeginSensor(b2SensorBeginTouchEvent*, Player::PlayerAvatar*) override;
    };
}

CEREAL_REGISTER_TYPE(Portal::BeginPortal)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Portal::BeginPortal)
