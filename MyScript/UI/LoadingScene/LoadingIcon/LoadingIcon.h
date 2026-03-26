#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../Component/Component.hpp"
#include "../../../../Component/Content/Basically/ImageRenderer/ImageRenderer.h"
#include "../../../../Component/Content/Basically/Renderer/AnimationRenderer/Animation/Animation.h"

namespace LoadingScene
{
    class LoadingIcon final : public virtual Component
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
        void OnUpdate() override;
        void OnDrawInspector() override;

        ImageRenderer* imageRenderer_ = nullptr;
        std::shared_ptr<Animation> animation_ = std::make_shared<Animation>();
        
        int effectDuringFrame_ = 0;
        int currentHandleIndex_ = 0;
    };
}

CEREAL_REGISTER_TYPE(LoadingScene::LoadingIcon)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, LoadingScene::LoadingIcon)
