#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../Component/Component.hpp"

namespace GameOverScene
{
    class StartOverButton final : public virtual Component
    {
    public:
        template <typename Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this)
            );
        }
        
    private:
        void Init() override;
        void Awake() override;
        static void OnClickEvent();
    };
}

CEREAL_REGISTER_TYPE(GameOverScene::StartOverButton)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, GameOverScene::StartOverButton)
