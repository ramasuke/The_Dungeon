#pragma once
#include "../../../../FightParameter/DamageContext/Physics/PhysicsPower/PhysicsPower.h"
#include "../../../../Player/PlayerAvatar.h"
#include "../Base/PowerUpItemBase.h"

namespace Player
{
    class PhysicsPowerUpItem final : public virtual PowerUpItemBase
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
        
        PhysicsPower value_ = PhysicsPower(1);
        int despawnDuration_ = 30;
        int despawnDuring_ = 0;
    };
}

CEREAL_REGISTER_TYPE(Player::PhysicsPowerUpItem)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Player::PhysicsPowerUpItem)