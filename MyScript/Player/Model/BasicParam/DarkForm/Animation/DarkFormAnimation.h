#pragma once
#include <memory>

#include "../../../../../../Component/Content/Basically/Renderer/AnimationRenderer/Animation/Animation.h"

namespace Player
{
    namespace DarkForm
    {
        class DarkFormAnimation final
        {
        public:
            template <typename Archive>
            void serialize(Archive& archive)
            {
                archive(cereal::make_nvp("idleAnimation", idleAnimation_),
                        cereal::make_nvp("walkAnimation", walkAnimation_),
                        cereal::make_nvp("attackAnimation", attackAnimation_),
                        cereal::make_nvp("dashAttackAnimation", dashAttackAnimation_),
                        cereal::make_nvp("onDamageAnimation", onDamageAnimation_),
                        cereal::make_nvp("onReleaseFormAnimation", onReleaseFormAnimation_)
                );
            }

            void Init() const;
            void OnDrawInspector() const;

            const std::shared_ptr<Animation>& Idle() const { return idleAnimation_; }
            const std::shared_ptr<Animation>& Walk() const { return walkAnimation_; }
            const std::shared_ptr<Animation>& Attack() const { return attackAnimation_; }
            const std::shared_ptr<Animation>& DashAttack() const { return dashAttackAnimation_; }
            const std::shared_ptr<Animation>& OnDamage() const { return onDamageAnimation_; }
            const std::shared_ptr<Animation>& OnReleaseForm() const { return onReleaseFormAnimation_; }

        private:
            std::shared_ptr<Animation> idleAnimation_ = std::make_shared<Animation>();
            std::shared_ptr<Animation> walkAnimation_ = std::make_shared<Animation>();
            std::shared_ptr<Animation> attackAnimation_ = std::make_shared<Animation>();
            std::shared_ptr<Animation> dashAttackAnimation_ = std::make_shared<Animation>();
            std::shared_ptr<Animation> onDamageAnimation_ = std::make_shared<Animation>();
            std::shared_ptr<Animation> onReleaseFormAnimation_ = std::make_shared<Animation>();
        };
    }
}
