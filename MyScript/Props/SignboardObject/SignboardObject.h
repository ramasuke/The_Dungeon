#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../Component/Component.hpp"
#include "../../FightParameter/IReceivablePlayerAttack/IReceivablePlayerAttack.h"

namespace Prop
{
    class SignboardObject final : public virtual Component,
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
        void OnDrawInspector() override;
        void OnDamage(std::shared_ptr<DamageContext::IDamageContext> damage) override;
        Vector2 Position() const override;
    };
}

CEREAL_REGISTER_TYPE(Prop::SignboardObject)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Prop::SignboardObject)