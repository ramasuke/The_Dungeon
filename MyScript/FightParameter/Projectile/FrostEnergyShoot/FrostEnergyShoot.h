#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../Component/Component.hpp"
#include "../../../../Component/Content/Basically/Renderer/AnimationRenderer/Animation/Animation.h"
#include "../../DamageContext/Physics/PhysicsPower/PhysicsPower.h"
#include "../../SpawnAttackAreaModel/SpawnAttackAreaModel.h"

namespace Projectile
{
    class FrostEnergyShoot final : public virtual Component
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this),
                cereal::make_nvp("damage"                       , damage_                       ),
                cereal::make_nvp("summonAttackAreaModel"        , summonAttackAreaModel_        ),
                cereal::make_nvp("summonAttackAreaDuration"     , summonAttackAreaDuration_     )
                
            );
        }

    private:
        void OnUpdate()         override;
        void OnDrawInspector()  override;

        PhysicsPower            damage_     = PhysicsPower(1);
        SpawnAttackAreaModel    summonAttackAreaModel_;
        int                     summonAttackAreaDuration_ = 100;
        int                     summonAttackAreaDuring_ = 0;
        static constexpr auto   ENEMY_BOX_ATTACK_AREA_PREFAB_PATH = "Resource/Prefab/Enemy-BoxAttackArea.json";
    };
}
    
CEREAL_REGISTER_TYPE(Projectile::FrostEnergyShoot)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Projectile::FrostEnergyShoot)