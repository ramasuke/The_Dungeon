#pragma once
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/memory.hpp>
#include "../../../../../Component/Component.hpp"
#include "../../../../FightParameter/DamageContext/Thunder/ThunderPower/ThunderPower.h"

class Thunder0Object final : public virtual Component
{
public:
    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::base_class<Component>(this),
            cereal::make_nvp("onSpawnAttackAreaCooldownDuration", onSpawnAttackAreaCooldownDuration_),
            cereal::make_nvp("onDespawnDuration", onDespawnDuration_)
        );
    }

    void SetThunderPower(const ThunderPower&);

private:
    void OnUpdate() override;
    void OnDrawInspector() override;

    ThunderPower thunderPower_;
    const std::string attackAreaPrefabPath_ = "Resource/Prefab/Thunder0-AttackArea.json";
    int onSpawnAttackAreaCooldownDuration_ = 30;
    int onDespawnDuration_ = 100;
    int aliveDuring_ = 0;
    Entity* attackArea_ = nullptr;
};

CEREAL_REGISTER_TYPE(Thunder0Object)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Thunder0Object)
