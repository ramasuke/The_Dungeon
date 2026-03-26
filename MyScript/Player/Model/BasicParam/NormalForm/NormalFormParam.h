#pragma once
#include <stack>

#include "../../../../../BasicallyParameter/SerializableSubject/Subject.h"
#include "../../../../../BasicallyParameter/SerializableSubject/unit/unit.h"
#include "../../../../../BasicallyParameter/Sound/Handle/SoundHandle.h"
#include "../../../../FightParameter/Health/Health.h"
#include "../../../../FightParameter/MadnessEnergy/MadnessEnergy.h"
#include "../../../../FightParameter/DamageContext/Physics/PhysicsDamageContext.h"
#include "../../../../FightParameter/DamageContext/Physics/PhysicsPower/PhysicsPower.h"
#include "../FormParamBase/FormParamBase.h"
#include "Animation/NormalFormAnimation.h"
#include "Sound/NormalFormSound.h"

class Transform;

namespace Player
{
    class CanUseSkillParticle;
}

namespace Player
{
    namespace NormalForm
    {
        class NormalFormParam final : public virtual FormParamBase
        {
        public:
            template <typename Archive>
            void serialize(Archive& archive)
            {
                archive(cereal::make_nvp("subject_maxHealth"                        , maxHealth_),
                        cereal::make_nvp("subject_health"                           , health_),
                        cereal::make_nvp("subject_physicsAttackPower"               , physicsAttackPower_),
                        cereal::make_nvp("subject_walkSpeed"                        , walkSpeed_),
                        cereal::make_nvp("subject_attackStateDuration"              , attackStateDuration_),
                        cereal::make_nvp("subject_attackStateOnAttackDamageDuration", attackStateOnAttackDamageDuration_),
                        cereal::make_nvp("subject_attackDistance"                   , attackDistance_),
                        cereal::make_nvp("subject_goInsaneDuration"                 , goInsaneDuration_),
                        cereal::make_nvp("subject_onDarkHealStateDuration"          , onDarkHealStateDuration_),
                        cereal::make_nvp("subject_onDamageStateDuration"            , onDamageStateDuration_),
                        cereal::make_nvp("subject_maxCollectMadness"                , maxCollectMadness_),
                        cereal::make_nvp("subject_skillEffectNeedMadness"           , useSkillNeedMadness_),
                        cereal::make_nvp("subject_darkHealNeedMadness"              , darkHealNeedMadness_),
                        cereal::make_nvp("subject_darkHealNeedDuration"             , darkHealNeedDuration_),
                        cereal::make_nvp("subject_darkHealCount"                    , darkHealCount_),
                        cereal::make_nvp("subject_toDarkFormNeedMadness"            , toDarkFormNeedMadness_),
                        cereal::make_nvp("subject_toDarkFormNeedDuration"           , toDarkFormNeedDuration_),
                        cereal::make_nvp("subject_currentMadness"                   , currentMadness_),
                        cereal::make_nvp("animation"                                , animation_),
                        cereal::make_nvp("sound"                                    , sound_)
                );
            }

            void Init();
            ReadOnlyReactiveContext<Health>         Health()                            const { return health_.AsReadOnly(); }
            ReadOnlyReactiveContext<PhysicsPower>   PhysicsAttackPower()                const { return physicsAttackPower_.AsReadOnly(); }
            ReadOnlyReactiveContext<float>          WalkSpeed()                         const { return walkSpeed_.AsReadOnly(); }
            ReadOnlyReactiveContext<int>            AttackStateDuration()               const { return attackStateDuration_.AsReadOnly(); }
            ReadOnlyReactiveContext<int>            AttackStateOnAttackDamageDuration() const { return attackStateOnAttackDamageDuration_.AsReadOnly(); }
            ReadOnlyReactiveContext<float>          AttackDistance()                    const { return attackDistance_.AsReadOnly(); }
            ReadOnlyReactiveContext<MadnessEnergy>  CurrentMadness()                    const { return currentMadness_.AsReadOnly(); }
            ReadOnlyReactiveContext<int>            GoInsaneDuration()                  const { return goInsaneDuration_.AsReadOnly(); }
            ReadOnlyReactiveContext<int>            OnDarkHealStateDuration()           const { return onDarkHealStateDuration_.AsReadOnly(); }
            ReadOnlyReactiveContext<int>            OnDamageStateDuration()             const { return onDamageStateDuration_.AsReadOnly(); }
            ReadOnlyReactiveContext<int>            OnDeathStateDuration()              const { return onDeathStateDuration_.AsReadOnly(); }
            ReadOnlyReactiveContext<MadnessEnergy>  UseSkillNeedMadness()               const { return useSkillNeedMadness_.AsReadOnly(); }
            ReadOnlyReactiveContext<MadnessEnergy>  DarkHealNeedMadness()               const { return darkHealNeedMadness_.AsReadOnly(); }
            ReadOnlyReactiveContext<int>            DarkHealNeedDuration()              const { return toDarkFormNeedDuration_.AsReadOnly(); }
            ReadOnlyReactiveContext<MadnessEnergy>  ToGoInsaneNeedMadness()             const { return toDarkFormNeedMadness_.AsReadOnly(); }
            ReadOnlyReactiveContext<int>            ToDarkFormNeedDuration()            const { return toDarkFormNeedDuration_.AsReadOnly(); }
            rxcpp::observable<unit>                 OnDeathObservable()                 const { return onDeath_.get_observable(); }
            const NormalFormAnimation&              Animation()                         const { return animation_; }
            const NormalFormSound&                  Sound()                             const { return sound_; }
            
            void OnDrawInspector();
            void OnCollectMadness(MadnessEnergy onCollectMadness);
            void OnDamage(std::stack<std::shared_ptr<DamageContext::IDamageContext>>& damageStack, Entity& entityRef);
            void OnCostMadness(const MadnessEnergy decrease) { currentMadness_.OnNext(currentMadness_.get() - decrease); }
            void OnUseSkill();
            bool CanEnableUseSkill()    const { return  currentMadness_.get() >= useSkillNeedMadness_.get(); }
            bool IsUseSkill()           const { return isUseSkill_.get(); }
            bool CanDarkHeal()          const { return currentMadness_.get() >= darkHealNeedMadness_.get(); }
            ::Health DarkHealCount()    const { return darkHealCount_.get(); }
            bool CanChangeDarkForm()    const { return currentMadness_.get() >= toDarkFormNeedMadness_.get(); }
            bool IsDeath()              const { return health_.get() <= minDeathHealth_; }
            void OnDeath() const;
            void OnEnableUseSkill(Transform& playerTransform);
            void OnDarkHeal(::Health healCount);
            
            void ReinforcementDarkHeal          (const ::Health reinforceValue)      { darkHealCount_.OnNext(reinforceValue + darkHealCount_.get()); }
            void ReinforcementPhysicsAttackPower(const PhysicsPower& reinforceValue) { physicsAttackPower_.OnNext(reinforceValue + physicsAttackPower_.get()); }
            void ReinforceCollectMadness        (const MadnessEnergy reinforceValue) { reinforcingCollectMadness_.OnNext(reinforceValue + reinforcingCollectMadness_.get()); }

        private:
            Subject<bool> isUseSkill_ = Subject<bool>(false);
            
            const ::Health minDeathHealth_      = ::Health(0);
            Subject<::Health> maxHealth_        = Subject<::Health>(::Health(8));
            Subject<::Health> health_;
            Subject<PhysicsPower> physicsAttackPower_;
            Subject<float> walkSpeed_                       = Subject<float>(1);
            Subject<int> attackStateDuration_               = Subject<int>(35);
            Subject<int> attackStateOnAttackDamageDuration_ = Subject<int>(10);
            Subject<float> attackDistance_                  = Subject<float>(0);
            Subject<int> goInsaneDuration_                  = Subject<int>(30);
            Subject<int> onDarkHealStateDuration_           = Subject<int>(30); 
            Subject<int> onDamageStateDuration_             = Subject<int>(30);
            Subject<int> onDeathStateDuration_              = Subject<int>(80);
            Subject<MadnessEnergy> maxCollectMadness_       = Subject<MadnessEnergy>(MadnessEnergy(100));
            Subject<MadnessEnergy> useSkillNeedMadness_     = Subject<MadnessEnergy>(MadnessEnergy(100));
            Subject<MadnessEnergy> darkHealNeedMadness_     = Subject<MadnessEnergy>(MadnessEnergy(100));
            Subject<int> darkHealNeedDuration_              = Subject<int>(30);
            Subject<::Health> darkHealCount_                = Subject<::Health>(::Health(1)); 
            Subject<MadnessEnergy> toDarkFormNeedMadness_   = Subject<MadnessEnergy>(MadnessEnergy(100));
            Subject<int> toDarkFormNeedDuration_            = Subject<int>(30);
            Subject<MadnessEnergy> currentMadness_;
            rxcpp::subjects::subject<unit> onDeath_;
            
            NormalFormAnimation animation_;
            NormalFormSound sound_;
            
            Subject<MadnessEnergy> reinforcingCollectMadness_ = Subject<MadnessEnergy>(MadnessEnergy(0));
            
            const std::string       canUseSkillParticlePrefabPath_  = "Resource/Prefab/CanUsingSkillParticle.json";
            const std::string       splatterBloodPrefabPath_        = "Resource/Prefab/SplatterBlood.json";
            CanUseSkillParticle*    canUseSkillParticle_            = nullptr;
            rxcpp::composite_subscription onDeathSubscription_;
        };
    }
}
