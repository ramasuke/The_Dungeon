#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../../Component/Component.hpp"
#include "../../../../../Component/Content/Basically/Renderer/AnimationRenderer/Animation/Animation.h"
#include "../../../../FightParameter/Health/Health.h"
#include "../../../../FightParameter/MadnessEnergy/MadnessEnergy.h"

namespace GamePlayScene
{
    namespace PlayerParamView
    {
        class MadnessBar final : public virtual Component
        {
        public:
            template <class Archive>
            void serialize(Archive& archive)
            {
                archive(
                    cereal::base_class<Component>(this),
                    cereal::make_nvp("barAnimation", barAnimation_)
                );
            }
            void OnUpdateView(MadnessEnergy madnessEnergy) const;
            
        private:
            void Init() override;
            void OnDrawInspector() override;
            

            std::shared_ptr<Animation> barAnimation_ = std::make_shared<Animation>();
        };
    }
}

CEREAL_REGISTER_TYPE(GamePlayScene::PlayerParamView::MadnessBar)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, GamePlayScene::PlayerParamView::MadnessBar)
