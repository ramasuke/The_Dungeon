#pragma once
#include <stack>
#include <cereal/cereal.hpp>

#include "../../../FightParameter/DamageContext/Physics/PhysicsDamageContext.h"
#include "Inventory/Inventory.h"
#include "NormalForm/NormalFormParam.h"
#include "DarkForm/DarkFormParam.h"

namespace Player
{
    class BasicParam final
    {
    public:
        template <typename Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::make_nvp("normalFormParam"  , normalFormParam_  ),
                cereal::make_nvp("darkFormParam"    , darkFormParam_    ),
                cereal::make_nvp("inventory"        , inventory_        )
            );
        }

        void Init();
        NormalForm::NormalFormParam&    NormalFormParam()   { return normalFormParam_; }
        DarkForm::DarkFormParam&        DarkFormParam()     { return darkFormParam_; }
        Inventory& Inventory();
        void OnDrawInspector();
        void OnHitDamage(const std::shared_ptr<DamageContext::IDamageContext>& damage);
        bool IsHitDamaged() const;
        std::stack<std::shared_ptr<DamageContext::IDamageContext>>& CurrentDamageStack() { return currentDamageStack_; }

    private:
        NormalForm::NormalFormParam normalFormParam_;
        DarkForm::DarkFormParam darkFormParam_;
        Player::Inventory inventory_;
        std::stack<std::shared_ptr<DamageContext::IDamageContext>> currentDamageStack_;
    };
}
