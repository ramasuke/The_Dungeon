#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../BasicallyParameter/SerializeComponentRef/ComponentRef.h"
#include "../../../Component/Component.hpp"
#include "../../../Component/Content/Basically/ImageRenderer/ImageRenderer.h"
#include "../../UI/SelectStageNumber/SelectStageNumber.h"

namespace Player
{
    class PlayerAvatar;
}

namespace PauseScene
{
    class GameStartButton final : public virtual Component
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this),
                cereal::make_nvp("gameStartText", gameStartText_),
                cereal::make_nvp("sceneNames_", sceneNames_),
                cereal::make_nvp("selectStageNumber_", selectStageNumber_)
            );
        }

    private:
        void Init() override;
        void Awake() override;
        void OnDrawInspector() override;
        void OnReleaseButton();

        const std::string buttonParticlePrefabPath_ = "Resource/Prefab/ButtonParticle.json";
        std::vector<std::string> sceneNames_;
        
        ComponentRef<ImageRenderer> gameStartText_;
        ComponentRef<StageSelectScene::SelectStageNumber> selectStageNumber_;
    };
}

CEREAL_REGISTER_TYPE(PauseScene::GameStartButton)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, PauseScene::GameStartButton)
