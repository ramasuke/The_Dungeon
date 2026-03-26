#pragma once
#include <cereal/types/base_class.hpp>
#include <cereal/types/polymorphic.hpp>

#include "../../../../Component/Component.hpp"
#include "../../../../Component/Content/Basically/Renderer/AnimationRenderer/Animation/Animation.h"
#include "../../../AI/BehaviourTree/BehaviourTree.h"
#include "../../DamageContext/Fire/FirePower/FirePower.h"
#include "../../DamageContext/Interface/IDamageContext.h"
#include "../../Health/Health.h"
#include "../../IReceivablePlayerAttack/IReceivablePlayerAttack.h"
#include "../../MadnessEnergy/MadnessEnergy.h"

namespace Enemy
{
    class GhostWizard final : public virtual Component,
                              public virtual IReceivablePlayerAttack
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this),
                cereal::make_nvp("health"           , health_           ),
                cereal::make_nvp("firePower"        , firePower_        ),
                cereal::make_nvp("dropComboCount"   , dropComboCount_   ),
                cereal::make_nvp("dropComboEnergy"  , dropComboEnergy_  ),
                cereal::make_nvp("idleAnimation"    , idleAnimation_    ),
                cereal::make_nvp("avoidAnimatoin"   , avoidAnimatoin_   ),
                cereal::make_nvp("deathAnimation"   , deathAnimation_   )
            );
        }

    private:
        void Init()             override;
        void Awake()            override;
        void OnUpdate()         override;
        void OnDrawInspector()  override;
        void OnDamage(std::shared_ptr<DamageContext::IDamageContext> damageContext) override;
        Vector2 Position() const override;

        std::shared_ptr<Animation> idleAnimation_ = std::make_shared<Animation>();
        std::shared_ptr<Animation> avoidAnimatoin_ = std::make_shared<Animation>();
        std::shared_ptr<Animation> deathAnimation_ = std::make_shared<Animation>();


        Health health_ = Health(4);
        int dropComboCount_ = 6;
        FirePower firePower_ = FirePower(1);
        MadnessEnergy dropComboEnergy_ = MadnessEnergy(1);

        std::string smallFireBallPrefabPath_ = "Resource/Prefab/SmallFireBall.json";

        std::unique_ptr<Ai::BehaviourTree> behaviour_;
        std::queue<std::shared_ptr<DamageContext::IDamageContext>> onDamaged_;
    };
}

CEREAL_REGISTER_TYPE(Enemy::GhostWizard)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Enemy::GhostWizard)
