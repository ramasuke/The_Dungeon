#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../Component/Component.hpp"
#include "../../../../Physics/Sensor/Begin/IBeginSensorable.h"
#include "../../../Player/PlayerAvatar.h"
#include "../../SpawnAttackAreaModel/SpawnAttackAreaModel.h"

namespace Enemy
{
    class EnemyBoxAttackArea final : public virtual Component,
                                     public virtual IBeginSensorable<IReceivableEnemyAttack>
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this)
            );
        }

        void InitDamage(const std::shared_ptr<DamageContext::IDamageContext>& damage, int despawnDuration);
        void InitArea(const std::shared_ptr<DamageContext::IDamageContext>& damage,
                      const SpawnAttackAreaModel& attackAreaModel);
        void SetDespawnDuration(const int duration) { despawnDuration_ = duration; }

    private:
        void Awake() override;
        void OnUpdate() override;
        void OnBeginSensor(b2SensorBeginTouchEvent*, IReceivableEnemyAttack*) override;

        int despawnDuration_ = 0;
        int despawnDuring_ = 0;
        std::shared_ptr<DamageContext::IDamageContext> damage_;
    };
}

CEREAL_REGISTER_TYPE(Enemy::EnemyBoxAttackArea)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Enemy::EnemyBoxAttackArea)
