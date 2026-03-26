#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../Component/Component.hpp"
#include "../../../Component/Content/Basically/Renderer/AnimationRenderer/AnimationRenderer.h"
#include "../../../Physics/Sensor/Begin/IBeginSensorable.h"
#include "../../Item/Drop/PowerUp/Physics/PhysicsPowerUpItem.h"
#include "../../Player/PlayerAvatar.h"

namespace Prop
{
    class WoodChest final : public virtual Component,
                            public virtual IBeginSensorable<Player::PlayerAvatar>
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this),
                cereal::make_nvp("powerUpItemPrefabPath"   , powerUpItemPrefabPath_   ),
                cereal::make_nvp("idleAnimation"        , idleAnimation_        ),
                cereal::make_nvp("openAnimation"        , openAnimation_        ),
                cereal::make_nvp("openDuration"         , openDuration_         )
            );
        }

    private:
        void Init() override;
        void OnUpdate() override;
        void OnDrawInspector() override;
        void OnBeginSensor(b2SensorBeginTouchEvent*, Player::PlayerAvatar*) override;


        bool isOpen_ = false;
        std::string powerUpItemPrefabPath_ = "Resource/Prefab/PowerUpItem.json";

        std::shared_ptr<Animation> idleAnimation_ = std::make_shared<Animation>();
        std::shared_ptr<Animation> openAnimation_ = std::make_shared<Animation>();
        int openDuration_ = 60;
        int openDuring_ = 0;
    };
}

CEREAL_REGISTER_TYPE(Prop::WoodChest)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Prop::WoodChest)
