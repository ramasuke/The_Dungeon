#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../Component/Component.hpp"

namespace Enemy
{
    class WizardGhost final : public virtual Component
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this)
                // cereal::make_nvp("animationModel", animation_),
                // cereal::make_nvp("health", health_),
                // cereal::make_nvp("physicsPower", physicsPower_),
                // cereal::make_nvp("dropComboCount", dropComboCount_),
                // cereal::make_nvp("dropComboEnergy", dropComboEnergy_),
                // cereal::make_nvp("onDeathSound", onDeathSound_)
            );
        }

    private:
    };
}

CEREAL_REGISTER_TYPE(Enemy::WizardGhost)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Enemy::WizardGhost)
