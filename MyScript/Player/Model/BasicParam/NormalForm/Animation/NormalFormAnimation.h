#pragma once
#include <memory>

#include "../../../../../../Component/Content/Basically/Renderer/AnimationRenderer/Animation/Animation.h"

namespace Player
{
    namespace NormalForm
    {
        class NormalFormAnimation final
        {
        public:
            template <typename Archive>
            void serialize(Archive& archive)
            {
                archive(cereal::make_nvp("idleAnimation", idleAnimation_),
                        cereal::make_nvp("walkAnimation", walkAnimation_),
                        cereal::make_nvp("attackAnimation", attackAnimation_),
                        cereal::make_nvp("goInsaneAnimation", goInsaneAnimation_),
                        cereal::make_nvp("consumptionMadnessAnimation", consumptionMadnessAnimation_),
                        cereal::make_nvp("onDamageAnimation", onDamageAnimation_),
                        cereal::make_nvp("onDeathAnimation", onDeathAnimation_)
                );
            }

            const std::shared_ptr<Animation>& Idle() const { return idleAnimation_; }
            const std::shared_ptr<Animation>& Walk() const { return walkAnimation_; }
            const std::shared_ptr<Animation>& Attack() const { return attackAnimation_; }
            const std::shared_ptr<Animation>& GoInsane() const { return goInsaneAnimation_; }
            const std::shared_ptr<Animation>& ConsumptionMadness() const { return consumptionMadnessAnimation_; }
            const std::shared_ptr<Animation>& OnDamage() const { return onDamageAnimation_; }
            const std::shared_ptr<Animation>& OnDeath() const { return onDeathAnimation_; }

            void Init() const;
            void OnDrawInspector() const;

        private:
            std::shared_ptr<Animation> idleAnimation_ = std::make_shared<Animation>();
            std::shared_ptr<Animation> walkAnimation_ = std::make_shared<Animation>();
            std::shared_ptr<Animation> attackAnimation_ = std::make_shared<Animation>();
            std::shared_ptr<Animation> consumptionMadnessAnimation_ = std::make_shared<Animation>();
            std::shared_ptr<Animation> goInsaneAnimation_ = std::make_shared<Animation>();
            std::shared_ptr<Animation> onDamageAnimation_ = std::make_shared<Animation>();
            std::shared_ptr<Animation> onDeathAnimation_ = std::make_shared<Animation>();
        };
    }
}
