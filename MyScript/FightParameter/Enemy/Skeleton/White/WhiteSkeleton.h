#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../../BasicallyParameter/Sound/Handle/SoundHandle.h"
#include "../../../../../Component/Component.hpp"
#include "../../../../../Component/Content/Basically/Renderer/AnimationRenderer/Animation/Animation.h"
#include "../../../../AI/BehaviourTree/BehaviourTree.h"
#include "../../../../AI/BehaviourTree/Node/Action/ActionNode.h"
#include "../../../Health/Health.h"
#include "../../../MadnessEnergy/MadnessEnergy.h"
#include "../../../DamageContext/Physics/PhysicsPower/PhysicsPower.h"
#include "../../../IReceivablePlayerAttack/IReceivablePlayerAttack.h"
#include "../../../SpawnAttackAreaModel/SpawnAttackAreaModel.h"
#include "../../StartAttackArea/StartMotionArea.h"

namespace Enemy
{
    class WhiteSkeleton final : public virtual Component,
                                public virtual IReceivablePlayerAttack
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this),
                cereal::make_nvp("idleAnimation"        , idleAnimation_        ),
                cereal::make_nvp("walkAnimation"        , walkAnimation_        ),
                cereal::make_nvp("attackAnimation1"     , attackAnimation1_     ),
                cereal::make_nvp("attackAnimation2"     , attackAnimation2_     ),
                cereal::make_nvp("hurtAnimation"        , hurtAnimation_        ),
                cereal::make_nvp("deathAnimation"       , deathAnimation_       ),
                cereal::make_nvp("health"               , health_               ),
                cereal::make_nvp("physicsPower"         , physicsPower_         ),
                cereal::make_nvp("dropComboCount"       , dropComboCount_       ),
                cereal::make_nvp("dropComboEnergy"      , dropComboEnergy_      ),
                cereal::make_nvp("startAttackMotionArea", startAttackMotionArea_),
                cereal::make_nvp("attack1AreaModel"     , attack1AreaModel_     ),
                cereal::make_nvp("attack2AreaModel"     , attack2AreaModel_     )
            );
        }

    private:
        void Init()             override;
        void Awake()            override;
        void OnUpdate()         override;
        void OnDrawInspector()  override;
        void OnDamage(std::shared_ptr<DamageContext::IDamageContext> damageContext) override;
        Vector2 Position() const override;


        std::shared_ptr<Animation> idleAnimation_       = std::make_shared<Animation>();
        std::shared_ptr<Animation> walkAnimation_       = std::make_shared<Animation>();
        std::shared_ptr<Animation> attackAnimation1_    = std::make_shared<Animation>();
        std::shared_ptr<Animation> attackAnimation2_    = std::make_shared<Animation>();
        std::shared_ptr<Animation> hurtAnimation_       = std::make_shared<Animation>();
        std::shared_ptr<Animation> deathAnimation_      = std::make_shared<Animation>();

        Health          health_;
        PhysicsPower    physicsPower_;
        int             dropComboCount_ = 0;
        MadnessEnergy   dropComboEnergy_;

        StartMotionArea         startAttackMotionArea_;
        SpawnAttackAreaModel    attack1AreaModel_;
        SpawnAttackAreaModel    attack2AreaModel_;

        std::unique_ptr<Ai::BehaviourTree> behaviour_;
        std::queue<std::shared_ptr<DamageContext::IDamageContext>> onDamaged_;
    };
}

CEREAL_REGISTER_TYPE(Enemy::WhiteSkeleton)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Enemy::WhiteSkeleton)
