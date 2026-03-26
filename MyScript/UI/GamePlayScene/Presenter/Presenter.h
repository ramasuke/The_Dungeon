#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../Component/Component.hpp"
#include "../PlayerParamView/PlayerParamView.h"

namespace GamePlayScene
{
    class Presenter final : public virtual Component
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this),
                cereal::make_nvp("playerParamView", playerParamView_)
            );
        }

    private:
        void Awake() override;
        void OnDrawInspector() override;
        
        void SubscribeModelEventToView();


        // void SubscribeViewEventToModel();

        PlayerParamView::PlayerParamView playerParamView_;
    };
}

CEREAL_REGISTER_TYPE(GamePlayScene::Presenter)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, GamePlayScene::Presenter)