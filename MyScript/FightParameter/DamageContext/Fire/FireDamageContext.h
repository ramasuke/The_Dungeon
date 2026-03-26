#pragma once
#include "../Interface/IDamageContext.h"
#include "FirePower/FirePower.h"

struct FireDamageContext final : virtual DamageContext::IDamageContext
{
    explicit FireDamageContext  (Entity& fromEntity , const FirePower& damage   );
    void OnStartEffect          (Entity& target     , Health& healthRef         ) override;
    void OnUpdateEffect         (Entity& target     , Health& health            ) override;
    bool CheckUpdateCondition   (Entity& target     , const Health& health      ) override;
    void OnExitEffect           (Entity& target     , Health& health            ) override;
    
    const IDamageParam& GetParam(                                               ) override;
    Vector2 FromPos             (                                               ) const override { return fromPos_; }

private:
    Vector2     fromPos_; 
    FirePower   damage_;
    int         burnDuring_ = 0;
};
