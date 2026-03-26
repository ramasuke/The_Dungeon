#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../Component/Component.hpp"

namespace LoadingScene
{
    class UnLoadLoadingSceneComponent final : public virtual Component
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this)
            );
        }
        
    private:
        void Awake() override;
    };
}

CEREAL_REGISTER_TYPE(LoadingScene::UnLoadLoadingSceneComponent)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, LoadingScene::UnLoadLoadingSceneComponent)
