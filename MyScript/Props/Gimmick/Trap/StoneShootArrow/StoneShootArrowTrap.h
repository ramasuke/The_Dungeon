#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../../BasicallyParameter/Vector2/Vector2.hpp"
#include "../../../../../Component/Component.hpp"
#include "../../../../../Component/Content/Basically/Renderer/AnimationRenderer/Animation/Animation.h"

namespace Prop
{
    namespace Trap
    {
        class StoneShootArrowTrap final : public virtual Component
        {
        public:
            template <class Archive>
            void serialize(Archive& archive)
            {
                archive(
                    cereal::base_class<Component>(this),
                    cereal::make_nvp("animation"            , animation_),
                    cereal::make_nvp("summonArrowDuring"    , summonArrowDuring_),
                    cereal::make_nvp("summonArrowDuration"  , summonArrowDuration_),
                    cereal::make_nvp("summonArrowOffset"    , summonArrowOffset_),
                    cereal::make_nvp("summonArrowVelocity"  , summonArrowVelocity_),
                    cereal::make_nvp("summonArrowPrefabPath", summonArrowPrefabPath_)
                );
            }

        private:
            void Init()             override;
            void OnUpdate()         override;
            void OnDrawInspector()  override;

            std::shared_ptr<Animation> animation_ = std::make_shared<Animation>();
            int summonArrowDuring_ = 0;
            int summonArrowDuration_ = 30;
            Vector2 summonArrowOffset_;
            Vector2 summonArrowVelocity_;
            std::string summonArrowPrefabPath_ = "Resource/Prefab/Projectile-Enemy-SummonArrow.json";
        };
    }
}

CEREAL_REGISTER_TYPE(Prop::Trap::StoneShootArrowTrap)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Prop::Trap::StoneShootArrowTrap)
