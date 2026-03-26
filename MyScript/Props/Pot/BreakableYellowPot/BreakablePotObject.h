#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../Component/Component.hpp"
#include "../../../FightParameter/IReceivablePlayerAttack/IReceivablePlayerAttack.h"

namespace Prop
{
    class BreakablePotObject final : public virtual Component,
                                     public virtual IReceivablePlayerAttack
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
        void OnDamage(std::shared_ptr<DamageContext::IDamageContext> damage) override;
        void OnBreakPot() const;
        Vector2 Position() const override;

        const std::string breakingPotPrefabPath_ = "Resource/Prefab/BreakingYellowPot.json";
    };
}

CEREAL_REGISTER_TYPE(Prop::BreakablePotObject)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Prop::BreakablePotObject)
