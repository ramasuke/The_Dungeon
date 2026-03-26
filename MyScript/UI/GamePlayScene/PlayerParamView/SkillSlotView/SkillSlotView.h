#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../../BasicallyParameter/SerializeComponentRef/ComponentRef.h"
#include "../../../../../Component/Component.hpp"
#include "../../../../../Component/Content/Basically/ImageRenderer/ImageRenderer.h"
#include "../../../../Item/Skill/Base/SkillBase.h"


namespace GamePlayScene
{
    namespace PlayerParamView
    {
        class SkillSlotView final : public virtual Component
        {
        public:
            template <class Archive>
            void serialize(Archive& archive)
            {
                archive(
                    cereal::base_class<Component>(this)
                );
            }
            
            void OnUpdateView(const std::shared_ptr<Skill::SkillBase>& skill) const;
        };
    }
}

CEREAL_REGISTER_TYPE(GamePlayScene::PlayerParamView::SkillSlotView)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, GamePlayScene::PlayerParamView::SkillSlotView)