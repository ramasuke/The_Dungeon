#pragma once
#include "../../../../BasicallyParameter/SerializeComponentRef/ComponentRef.h"
#include "HealthBar/HealthBar.h"
#include "MadnessBar/MadnessBar.h"
#include "SkillSlotView/SkillSlotView.h"

namespace GamePlayScene
{
    namespace PlayerParamView
    {
        class PlayerParamView final
        {
        public:
            template <class Archive>
            void serialize(Archive& archive)
            {
                archive(
                    cereal::make_nvp("healthBarRef" , healthBarRef_ ),
                    cereal::make_nvp("madnessBarRef", madnessBarRef_),
                    cereal::make_nvp("skillSlotRef" , skillSlotRef_ )
                );
            }

            void Init();
            void OnDrawInspector();
            ComponentRef<HealthBar>& HealthBar()        { return healthBarRef_;     }
            ComponentRef<MadnessBar>& MadnessBar()      { return madnessBarRef_;    }
            ComponentRef<SkillSlotView>& SkillSlot()    { return skillSlotRef_;     }

        private:
            ComponentRef<GamePlayScene::PlayerParamView::HealthBar      > healthBarRef_;
            ComponentRef<GamePlayScene::PlayerParamView::MadnessBar     > madnessBarRef_;
            ComponentRef<GamePlayScene::PlayerParamView::SkillSlotView  > skillSlotRef_;
        };
    }
}
