#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../BasicallyParameter/SerializeComponentRef/ComponentRef.h"
#include "../../../Component/Component.hpp"
#include "../../../Component/Content/Basically/MovieRenderer/MovieRenderer.h"
#include "../../../Component/Content/Basically/Ui/Button/Button.h"

namespace StageSelectScene
{
    class SelectStageNumber final : public virtual Component
    {
    public:
        template <typename Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this),
                cereal::make_nvp("stageNames_", stageNames_),
                cereal::make_nvp("onNextStageSelect_", onNextStageSelect_),
                cereal::make_nvp("onMinusStageSelect_", onMinusStageSelect_),
                cereal::make_nvp("stageMovieRenderer_", stageMovieRenderer_)
            );
        }
        [[nodiscard]] int CurrentStageNumber() const { return currentSelectStageNumber_; }
        
    private:
        void Awake() override;
        void OnUpdate() override;
        void OnDrawInspector() override;

        
        const std::vector<std::string> stageMovieResourcePaths_ =
        {
            "Resource/Movie/Tutorial.mp4",
            "Resource/Movie/Dungeon1-1.mp4",
            "Resource/Movie/Dungeon1-2.mp4",
            "Resource/Movie/Dungeon1-3.mp4",
            "Resource/Movie/Dungeon1-4.mp4",
        };
        std::vector<std::string> stageNames_; 
        int currentSelectStageNumber_ = 0;
        ComponentRef<Ui::Button> onNextStageSelect_;
        ComponentRef<Ui::Button> onMinusStageSelect_;
        ComponentRef<MovieRenderer> stageMovieRenderer_;
    };
}

CEREAL_REGISTER_TYPE(StageSelectScene::SelectStageNumber)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, StageSelectScene::SelectStageNumber)
