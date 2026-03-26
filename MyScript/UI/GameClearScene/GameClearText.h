#pragma once
#include "../../../BasicallyParameter/SerializeComponentRef/ComponentRef.h"
#include "../../../Component/Component.hpp"
#include "cereal/types/polymorphic.hpp"

namespace GameClearScene
{
    class GameClearText final : public Component
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this),    
                cereal::make_nvp("gameClearParticlePrefabFilePath_", gameClearParticlePrefabFilePath_)
            );
        }

    private:
        void Init() override;
        void OnUpdate() override;
        void OnDrawInspector() override;
        
        std::string gameClearParticlePrefabFilePath_;
        const int returnTitleDuration_ = 300;
        int returnTitleDuring_ = 0;
    };
}

CEREAL_REGISTER_TYPE(GameClearScene::GameClearText)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, GameClearScene::GameClearText)
