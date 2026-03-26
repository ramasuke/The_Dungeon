#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../../Component/Component.hpp"
#include "../../../../../Component/Content/Basically/Renderer/AnimationRenderer/AnimationRenderer.h"
#include "../../Interface/IGimmick.h"

namespace Prop
{
    class CopperFence final : public virtual Component,
                             public virtual Gimmick::IGimmick
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this),
                cereal::make_nvp("idleFenceAnimation", idleFenceAnimation_),
                cereal::make_nvp("downFenceAnimation", downFenceAnimation_)
            );
        }

    private:
        void Init() override;
        void Awake() override;
        void OnUpdate() override;
        void OnDrawInspector() override;
        void OnStartGimmick() override;

        bool isGimmicked_ = false;
        std::shared_ptr<Animation> idleFenceAnimation_ = std::make_shared<Animation>();
        std::shared_ptr<Animation> downFenceAnimation_ = std::make_shared<Animation>();
    };
}

CEREAL_REGISTER_TYPE(Prop::CopperFence)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Prop::CopperFence)
