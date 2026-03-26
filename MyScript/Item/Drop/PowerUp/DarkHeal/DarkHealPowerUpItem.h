#pragma once
#include "../../../../Player/PlayerAvatar.h"
#include "../Base/PowerUpItemBase.h"

namespace Player
{
    class DarkHealPowerUpItem final : public virtual PowerUpItemBase
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this),
                cereal::make_nvp("value", value_),
                cereal::make_nvp("despawnDuration", despawnDuration_)
            );
        }

    private:
        void OnUpdate() override;
        void OnDrawInspector() override;
        
        Health value_ = Health(1);
        int despawnDuration_ = 30;
        int despawnDuring_ = 0;
    };
}

CEREAL_REGISTER_TYPE(Player::DarkHealPowerUpItem)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Player::DarkHealPowerUpItem)