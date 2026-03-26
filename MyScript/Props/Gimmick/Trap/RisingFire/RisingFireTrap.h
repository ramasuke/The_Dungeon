#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../../BasicallyParameter/Vector2/Vector2.hpp"
#include "../../../../../Component/Component.hpp"
#include "../../../../../Component/Content/Basically/Renderer/AnimationRenderer/Animation/Animation.h"
#include "../../../../FightParameter/Enemy/BoxAttackArea/EnemyBoxAttackArea.h"

namespace Prop
{
    namespace Trap
    {
        class RisingFireTrap final : public virtual Component
        {
        public:
            template <class Archive>
            void serialize(Archive& archive)
            {
                archive(
                    cereal::base_class<Component>(this),
                    cereal::make_nvp("animation"            , animation_            ),
                    cereal::make_nvp("damage"               , damage_               ),
                    cereal::make_nvp("trapBootDuration"     , trapBootDuration_     ),
                    cereal::make_nvp("trapBootDuring"       , trapBootDuring_       ),
                    cereal::make_nvp("boxAttackAreaModel"   , boxAttackAreaModel_   )
                );
            }

        private:
            void Init()             override;
            void OnUpdate()         override;
            void OnDrawInspector()  override;

            std::shared_ptr<Animation> animation_ = std::make_shared<Animation>();
            SpawnAttackAreaModel boxAttackAreaModel_;
            PhysicsPower damage_;
            int trapBootDuration_   = 30;
            int trapBootDuring_     = 0;
            static constexpr auto ENEMY_BOX_ATTACK_AREA_PREFAB_PATH = "Resource/Prefab/Enemy-BoxAttackArea.json";
        };
    }
}

CEREAL_REGISTER_TYPE(Prop::Trap::RisingFireTrap)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Prop::Trap::RisingFireTrap)