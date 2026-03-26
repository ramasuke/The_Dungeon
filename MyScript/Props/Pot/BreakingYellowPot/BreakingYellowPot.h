#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../Component/Component.hpp"
#include "../../../../Component/Content/Basically/Renderer/AnimationRenderer/Animation/Animation.h"

namespace Prop
{
    class BreakingYellowPot final : public virtual Component
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this),
                cereal::make_nvp("animation", animation_)
            );
        }

    private:
        void Init() override;
        void OnDrawInspector() override;

        std::shared_ptr<Animation> animation_ = std::make_shared<Animation>();
    };
}

CEREAL_REGISTER_TYPE(Prop::BreakingYellowPot)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Prop::BreakingYellowPot)
