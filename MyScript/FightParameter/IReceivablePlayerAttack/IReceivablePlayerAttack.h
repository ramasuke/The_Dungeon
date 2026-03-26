#pragma once
#include "../../../BasicallyParameter/Vector2/Vector2.hpp"
#include "../DamageContext/Physics/PhysicsDamageContext.h"
constexpr auto DAMAGE_NOTATION_PREFAB_PATH = "Resource/Prefab/DamageNotation.json";
constexpr auto ON_DESTROY_OBJECT_PARTICLE0 = "Resource/Prefab/OnDestroyObjectParticle0.json";
constexpr auto ON_DESTROY_OBJECT_PARTICLE1 = "Resource/Prefab/OnDestroyObjectParticle1.json";

class IReceivablePlayerAttack
{
public:
    virtual ~IReceivablePlayerAttack() = default;
    virtual void OnDamage(std::shared_ptr<DamageContext::IDamageContext> damageContext) = 0;
    virtual Vector2 Position() const = 0;
};
