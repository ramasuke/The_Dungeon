#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../Component/Component.hpp"
#include "../../Physics/Sensor/Begin/IBeginSensorable.h"
#include "../Player/PlayerAvatar.h"

namespace Portal
{
    class Portal final : public virtual Component,
                         public virtual IBeginSensorable<Player::PlayerAvatar>
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this),
                cereal::make_nvp("animation", animation_),
                cereal::make_nvp("unloadSceneFilePath", unloadSceneFilePaths_),
                cereal::make_nvp("nextSceneFilePath", nextSceneFilePaths_)
            );
        }

    private:
        void Init() override;
        void OnDrawInspector() override;
        static void OnDrawAddButton(std::vector<std::string>&);
        void OnBeginSensor(b2SensorBeginTouchEvent*, Player::PlayerAvatar*) override;

        std::vector<std::string> unloadSceneFilePaths_
        {
            "Resource/Scene/TutorialScene.json"
        };
        std::vector<std::string> nextSceneFilePaths_
        {
            "Resource/Scene/TutorialScene.json"
        };
        std::shared_ptr<Animation> animation_ = std::make_shared<Animation>();
    };
}

CEREAL_REGISTER_TYPE(Portal::Portal)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Portal::Portal)
