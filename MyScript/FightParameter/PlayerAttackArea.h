#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../Component/Component.hpp"
#include "../../Physics/Sensor/Begin/IBeginSensorable.h"
#include "IReceivablePlayerAttack/IReceivablePlayerAttack.h"
#include "DamageContext/Physics/PhysicsPower/PhysicsPower.h"

class PlayerAttackArea final : public virtual Component, public virtual IBeginSensorable<IReceivablePlayerAttack>
{
public:
    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::base_class<Component>(this)
        );
    }
    void SetDamage(const std::shared_ptr<DamageContext::IDamageContext>& damage);

private:
    void Awake() override;
    void OnBeginSensor(b2SensorBeginTouchEvent*, IReceivablePlayerAttack*) override;

    std::shared_ptr<DamageContext::IDamageContext> damage_;
};

CEREAL_REGISTER_TYPE(PlayerAttackArea)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, PlayerAttackArea)