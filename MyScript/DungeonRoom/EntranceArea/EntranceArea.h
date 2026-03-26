#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../BasicallyParameter/SerializableSubject/unit/unit.h"
#include "../../../BasicallyParameter/Vector2/Vector2.hpp"
#include "../../../Component/Component.hpp"
#include "../../../Physics/Sensor/Begin/IBeginSensorable.h"
#include "../../Player/PlayerAvatar.h"

namespace Map
{
    namespace Room
    {
        class EntranceArea final : public virtual Component,
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

            rxcpp::observable<unit> OnEnterPlayer() const { return onEnterPlayer_.get_observable(); }

        private:
            void OnBeginSensor(b2SensorBeginTouchEvent*, Player::PlayerAvatar*) override;
            void OnDrawInspector() override;
            // void OnDrawAddEnemyModelButton();

            rxcpp::subjects::subject<unit> onEnterPlayer_;
        };
    }
}

CEREAL_REGISTER_TYPE(Map::Room::EntranceArea)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Map::Room::EntranceArea)
