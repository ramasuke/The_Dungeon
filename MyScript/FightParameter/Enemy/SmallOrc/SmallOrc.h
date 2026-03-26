#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../Component/Component.hpp"
#include "../../../../Component/Content/Basically/Renderer/AnimationRenderer/Animation/Animation.h"
#include "../../../AI/BehaviourTree/BehaviourTree.h"
#include "../../DamageContext/Interface/IDamageContext.h"
#include "../../DamageContext/Physics/PhysicsPower/PhysicsPower.h"
#include "../../Health/Health.h"
#include "../../IReceivablePlayerAttack/IReceivablePlayerAttack.h"
#include "../../MadnessEnergy/MadnessEnergy.h"
#include "../../SpawnAttackAreaModel/SpawnAttackAreaModel.h"
#include "../StartAttackArea/StartMotionArea.h"

namespace Enemy
{
    class SmallOrc final : public virtual Component,
                           public virtual IReceivablePlayerAttack
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
            cereal::base_class<Component>(this),
            cereal::make_nvp("idleAnimation"                , idleAnimation_                ),
            cereal::make_nvp("walkAnimation"                , walkAnimation_                ),
            cereal::make_nvp("normalAttackAnimation"        , normalAttackAnimation_        ),
            cereal::make_nvp("chargeAttackAnimation"        , chargeAttackAnimation_        ),
            cereal::make_nvp("hurtAnimation"                , hurtAnimation_                ),
            cereal::make_nvp("deathAnimation"               , deathAnimation_               ),
            cereal::make_nvp("health"                       , health_                       ),
            cereal::make_nvp("physicsPower"                 , physicsPower_                 ),
            cereal::make_nvp("dropComboCount"               , dropComboCount_               ),
            cereal::make_nvp("dropComboEnergy"              , dropComboEnergy_              ),
            cereal::make_nvp("startAttackMotionArea"        , startNormalAttackMotionArea_  ),
            cereal::make_nvp("startChargeAttackMotionArea"  , startChargeAttackMotionArea_  ),
            cereal::make_nvp("normalAttackAreaModel"        , normalAttackAreaModel_        ),
            cereal::make_nvp("chargeAttackAreaModel"        , chargeAttackAreaModel_        )
            );
        }

    private:
        void Init()             override;
        void Awake()            override;
        void OnUpdate()         override;
        void OnDrawInspector()  override;
        void OnDamage(std::shared_ptr<DamageContext::IDamageContext> damageContext) override;
        Vector2 Position() const override;

        std::shared_ptr<Animation> idleAnimation_           = std::make_shared<Animation>();
        std::shared_ptr<Animation> walkAnimation_           = std::make_shared<Animation>();
        std::shared_ptr<Animation> normalAttackAnimation_   = std::make_shared<Animation>();
        std::shared_ptr<Animation> chargeAttackAnimation_   = std::make_shared<Animation>();
        std::shared_ptr<Animation> hurtAnimation_           = std::make_shared<Animation>();
        std::shared_ptr<Animation> deathAnimation_          = std::make_shared<Animation>();

        Health          health_;
        PhysicsPower    physicsPower_;
        int             dropComboCount_ = 0;
        MadnessEnergy   dropComboEnergy_;

        StartMotionArea         startNormalAttackMotionArea_;
        StartMotionArea         startChargeAttackMotionArea_;
        SpawnAttackAreaModel    normalAttackAreaModel_;
        SpawnAttackAreaModel    chargeAttackAreaModel_;

        std::unique_ptr<Ai::BehaviourTree> behaviour_;
        std::queue<std::shared_ptr<DamageContext::IDamageContext>> onDamaged_;
    };
}

CEREAL_REGISTER_TYPE(Enemy::SmallOrc)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Enemy::SmallOrc)
