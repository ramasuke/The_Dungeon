#pragma once
#include <stack>

#include "../../../../../BasicallyParameter/SerializableSubject/Subject.h"
#include "../../../../../BasicallyParameter/Vector2/Vector2.hpp"
#include "../../../../../Component/Content/Basically/Renderer/AnimationRenderer/Animation/Animation.h"
#include "../../../../FightParameter/Health/Health.h"
#include "../../../../FightParameter/DamageContext/Physics/PhysicsDamageContext.h"
#include "../../../../FightParameter/DamageContext/Physics/PhysicsPower/PhysicsPower.h"
#include "../FormParamBase/FormParamBase.h"
#include "Animation/DarkFormAnimation.h"
#include "Sound/DarkFormSound.h"

namespace Player
{
    namespace DarkForm
    {
        class DarkFormParam final : public virtual FormParamBase
        {
        public:
            template <typename Archive>
            void serialize(Archive& archive)
            {
                archive(cereal::make_nvp("subject_health", health_),
                        cereal::make_nvp("subject_physicsAttackPower", physicsAttackPower_),
                        cereal::make_nvp("subject_walkSpeed", walkSpeed_),
                        cereal::make_nvp("subject_attackStateDuration", attackStateDuration_),
                        cereal::make_nvp("subject_attackStateOnAttackDamageDuration",
                                         attackStateOnAttackDamageDuration_),
                        cereal::make_nvp("subject_attackDistance", attackDistance_),
                        cereal::make_nvp("subject_dashAttackOffsetPosX", dashAttackOffsetPosX_),
                        cereal::make_nvp("subject_dashAttackEndOffsetPosX", dashAttackEndOffsetPosX_),
                        cereal::make_nvp("subject_dashAttackStateDuration", dashAttackStateDuration_),
                        cereal::make_nvp("subject_dashAttackStateOnAttackDamageDuration",
                                         dashAttackStateOnAttackDamageDuration_),
                        cereal::make_nvp("subject_dashAttackDistance", dashAttackDistance_),
                        cereal::make_nvp("subject_onDamageStateDuration", onDamageStateDuration_),
                        cereal::make_nvp("subject_onReleaseFormStateDuration", onReleaseFormStateDuration_),
                        cereal::make_nvp("animation", animation_),
                        cereal::make_nvp("sound", sound_)
                );
            }

            void Init();
            ReadOnlyReactiveContext<Health> Health() const { return health_.AsReadOnly(); }
            ReadOnlyReactiveContext<PhysicsPower> PhysicsAttackPower() const { return physicsAttackPower_.AsReadOnly(); }
            ReadOnlyReactiveContext<float> WalkSpeed() const { return walkSpeed_.AsReadOnly(); }
            ReadOnlyReactiveContext<int> AttackStateDuration() const { return attackStateDuration_.AsReadOnly(); }
            ReadOnlyReactiveContext<int> AttackStateOnAttackDamageDuration() const { return attackStateOnAttackDamageDuration_.AsReadOnly(); }
            ReadOnlyReactiveContext<float> AttackDistance() const { return attackDistance_.AsReadOnly(); }
            ReadOnlyReactiveContext<float> DashAttackOffsetPosX() const { return dashAttackOffsetPosX_.AsReadOnly(); }
            ReadOnlyReactiveContext<float> DashAttackEndOffsetPosX() const { return dashAttackEndOffsetPosX_.AsReadOnly(); }
            ReadOnlyReactiveContext<int> DashAttackStateDuration() const { return dashAttackStateDuration_.AsReadOnly(); }
            ReadOnlyReactiveContext<int> DashAttackStateOnAttackDamageDuration() const { return dashAttackStateOnAttackDamageDuration_.AsReadOnly(); }
            ReadOnlyReactiveContext<float> DashAttackDistance() const { return dashAttackDistance_.AsReadOnly(); }
            ReadOnlyReactiveContext<int> OnDamageStateDuration() const { return onDamageStateDuration_.AsReadOnly(); }
            ReadOnlyReactiveContext<int> OnReleaseFormStateDuration() const { return onReleaseFormStateDuration_.AsReadOnly(); }

            void OnDrawInspector();
            void OnDamage(std::stack<DamageContext::IDamageContext>& damageStack, Entity& entityRef);
            bool IsOnReleaseForm() const { return minOnReleaseFormHealth_.get() >= health_.get(); }
            const DarkFormAnimation& Animation() const { return animation_; }
            const DarkFormSound& Sound() const { return sound_; }

        private:
            const Subject<::Health> minOnReleaseFormHealth_;
            Subject<::Health> health_;
            Subject<PhysicsPower> physicsAttackPower_;
            Subject<float> walkSpeed_ = Subject<float>(1);
            Subject<int> attackStateDuration_ = Subject<int>(35);
            Subject<int> attackStateOnAttackDamageDuration_ = Subject<int>(10);
            Subject<float> attackDistance_ = Subject<float>(0);
            Subject<float> dashAttackOffsetPosX_ = Subject<float>(30);
            Subject<float> dashAttackEndOffsetPosX_ = Subject<float>(100);
            Subject<int> dashAttackStateDuration_ = Subject<int>(35);
            Subject<int> dashAttackStateOnAttackDamageDuration_ = Subject<int>(10);
            Subject<float> dashAttackDistance_ = Subject<float>(0);
            Subject<int> onDamageStateDuration_ = Subject<int>(30);
            Subject<int> onReleaseFormStateDuration_ = Subject<int>(80);
            
            DarkFormAnimation animation_;
            DarkFormSound sound_;
        };
    }
}
