#pragma once
#include "../../../../BasicallyParameter/Vector2/Vector2.hpp"
#include "PhysicsPower/PhysicsPower.h"
#include "../Interface/IDamageContext.h"

namespace DamageContext
{
    constexpr auto KNOCK_BACK_FORCE = 0.2f;
    constexpr auto KNOCK_BACK_DURATION = 1;

    ///NOTE: 値オブジェクト推奨
    struct PhysicsDamageContext final : IDamageContext
    {
        explicit PhysicsDamageContext   (Entity& fromEntity , const PhysicsPower& damage);
        void OnUpdateEffect             (Entity& target     , Health& health            ) override;
        void OnStartEffect              (Entity& target     , Health& health            ) override;
        bool CheckUpdateCondition       (Entity& target     , const Health& health      ) override;
        void OnExitEffect               (Entity& target     , Health& health            ) override;
        
        const IDamageParam& GetParam    (                                               ) override;
        Vector2 FromPos                 (                                               ) const override { return fromPos_; }

    private:
        Vector2         fromPos_;
        PhysicsPower    damage_;
        float           knockBackDuring_ = 0;
    };
}
