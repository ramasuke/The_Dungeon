#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../BasicallyParameter/SerializeComponentRef/ComponentRef.h"
#include "../../../../Component/Component.hpp"
#include "../../../FightParameter/DamageContext/IReceivable/IReceivableDamage.h"
#include "../../../FightParameter/DamageContext/Thunder/ThunderPower/ThunderPower.h"
#include "../../../FightParameter/IReceivablePlayerAttack/IReceivablePlayerAttack.h"
#include "../Interface/IGimmick.h"

namespace Prop
{
    namespace Gimmick
    {
        class ReceiveThunderGimmick final : public virtual Component,
                                            public virtual IReceivablePlayerAttack,
                                            public virtual IReceivableDamage<ThunderPower>
        {
        public:
            template <class Archive>
            void serialize(Archive& archive)
            {
                archive(
                    cereal::base_class<Component>(this),
                    cereal::make_nvp("gimmickRefs", gimmickRefs_)
                );
            }

        private:
            void Awake() override;
            void OnDamage(std::shared_ptr<DamageContext::IDamageContext> damageContext) override;
            void OnTypeDamage(const ThunderPower& thunderPower) override;
            void OnDrawInspector() override;
            void OnDrawAddGimmickButton();
            Vector2 Position() const override;

            bool isGimmicked_ = false;
            std::vector<ComponentRef<IGimmick>> gimmickRefs_;
        };
    }
}

CEREAL_REGISTER_TYPE(Prop::Gimmick::ReceiveThunderGimmick)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Prop::Gimmick::ReceiveThunderGimmick)
