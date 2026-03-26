#pragma once
#include <cereal/types/polymorphic.hpp>
#include "../../../../../Component/Component.hpp"
#include "../../../../../Physics/Sensor/Begin/IBeginSensorable.h"
#include "../../../../FightParameter/IReceivablePlayerAttack/IReceivablePlayerAttack.h"
#include "../../../../FightParameter/DamageContext/Thunder/ThunderPower/ThunderPower.h"

class Thunder0ObjectAttackArea final : public virtual Component, public virtual IBeginSensorable<IReceivablePlayerAttack>
{
public:
    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::base_class<Component>(this),
            cereal::make_nvp("hitThunderParticlePrefabPath", hitThunderParticlePrefabPath_)
        );
    }

    
    void SetThunderPower(const ThunderPower& thunderPower);

private:
    void Awake() override;
    void OnBeginSensor(b2SensorBeginTouchEvent*, IReceivablePlayerAttack*) override;
    void OnDrawInspector() override;
    
    
    ThunderPower thunderPower_;
    std::string hitThunderParticlePrefabPath_ = "Resource/Prefab/HitThunderParticle.json";
};

CEREAL_REGISTER_TYPE(Thunder0ObjectAttackArea)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Thunder0ObjectAttackArea)