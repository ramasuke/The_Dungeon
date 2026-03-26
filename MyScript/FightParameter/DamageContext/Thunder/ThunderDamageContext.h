#pragma once
#include "ThunderPower/ThunderPower.h"
#include "../Interface/IDamageContext.h"

namespace DamageContext
{
    struct ThunderDamageContext final : virtual IDamageContext
    {
        explicit ThunderDamageContext   (Entity& fromEntity , const ThunderPower& damage    );
        void OnStartEffect              (Entity& target     , Health& healthRef             )   override;
        void OnUpdateEffect             (Entity& target     , Health& health                )   override;
        bool CheckUpdateCondition       (Entity& target     , const Health& health          )   override;
        void OnExitEffect               (Entity& target     , Health& health                )   override;
        
        const IDamageParam& GetParam    (                                                   )   override;
        Vector2 FromPos                 (                                                   )   const override { return fromPos_; }

    private:
        const Vector2 fromPos_;
        ThunderPower damage_;
        int numbDuring_ = 0;
    };
}
