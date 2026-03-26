#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../Component/Component.hpp"
#include "../../../FightParameter/DamageContext/Fire/FirePower/FirePower.h"
#include "../../../FightParameter/DamageContext/IReceivable/IReceivableDamage.h"
#include "../../../FightParameter/IReceivablePlayerAttack/IReceivablePlayerAttack.h"

namespace Prop
{
    namespace Gimmick
    {
        class GimmickStrangeGrass final : public virtual Component,
                                          public virtual IReceivablePlayerAttack,
                                          public virtual IReceivableDamage<FirePower>

        {
        public:
            template <class Archive>
            void serialize(Archive& archive)
            {
                archive(
                    cereal::base_class<Component>(this),
                    cereal::make_nvp("health", health_)
                );
            }

        private:
            void OnDrawInspector() override;
            void OnTypeDamage(const FirePower& damage) override;
            void OnDamage(std::shared_ptr<DamageContext::IDamageContext> damageContext) override;
            Vector2 Position() const override;

            Health health_;
        };
    }
}

CEREAL_REGISTER_TYPE(Prop::Gimmick::GimmickStrangeGrass)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Prop::Gimmick::GimmickStrangeGrass)
