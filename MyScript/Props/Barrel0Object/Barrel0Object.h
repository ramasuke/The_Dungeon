#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../Component/Component.hpp"
#include "../../../Component/Content/Basically/Renderer/AnimationRenderer/Animation/Animation.h"
#include "../../FightParameter/MadnessEnergy/MadnessEnergy.h"
#include "../../FightParameter/IReceivablePlayerAttack/IReceivablePlayerAttack.h"

namespace Prop
{
    class Barrel0Object final : public virtual Component,
                                public virtual IReceivablePlayerAttack
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this),
                cereal::make_nvp("dropComboEnergy", dropComboEnergy_)
            );
        }
        
    private:
        void OnDrawInspector() override;
        void OnDamage(std::shared_ptr<DamageContext::IDamageContext> damage) override;
        Vector2 Position() const override;

        MadnessEnergy dropComboEnergy_;
    };
}

CEREAL_REGISTER_TYPE(Prop::Barrel0Object)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Prop::Barrel0Object)
