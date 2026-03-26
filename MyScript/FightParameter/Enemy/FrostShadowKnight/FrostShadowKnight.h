#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../Component/Component.hpp"

#include "../../../../../Component/Content/Basically/Renderer/AnimationRenderer/Animation/Animation.h"
#include "../../../AI/BehaviourTree/BehaviourTree.h"
#include "../../../AI/BehaviourTree/Node/Action/ActionNode.h"
#include "../../Health/Health.h"
#include "../../MadnessEnergy/MadnessEnergy.h"
#include "../../DamageContext/Physics/PhysicsPower/PhysicsPower.h"
#include "../../IReceivablePlayerAttack/IReceivablePlayerAttack.h"
#include "../../SpawnAttackAreaModel/SpawnAttackAreaModel.h"
#include "../StartAttackArea/StartMotionArea.h"

namespace Enemy
{
    class FrostShadowKnight final : public virtual Component,
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
            cereal::make_nvp("singleAttackAnimation"        , singleAttackAnimation_        ),
            cereal::make_nvp("doubleAttackAnimation"        , doubleAttackAnimation_        ),
            cereal::make_nvp("defenseAnimation"             , defenseAnimation_             ),
            cereal::make_nvp("hurtAnimation"                , hurtAnimation_                ),
            cereal::make_nvp("deathAnimation"               , deathAnimation_               ),
            cereal::make_nvp("health"                       , health_                       ),
            cereal::make_nvp("physicsPower"                 , physicsPower_                 ),
            cereal::make_nvp("dropComboCount"               , dropComboCount_               ),
            cereal::make_nvp("dropComboEnergy"              , dropComboEnergy_              ),
            cereal::make_nvp("singleAttackMotionArea"       , singleAttackMotionArea_       ),
            cereal::make_nvp("doubleAttackMotionArea"       , doubleAttackMotionArea_       ),
            cereal::make_nvp("singleAttackAreaModel"        , singleAttackAreaModel_        ),
            cereal::make_nvp("frostEnergyShootOffset"       , frostEnergyShootOffset_       ),
            cereal::make_nvp("frostEnergyShootPrefabPath"   , frostEnergyShootPrefabPath_   ),
            cereal::make_nvp("doubleAttackAreaModel"        , doubleAttackAreaModel_        )
            );
        }
        
    private:
        void Init()             override;
        void Awake()            override;
        void OnUpdate()         override;
        void OnDrawInspector()  override;
        Ai::INode::Status AddTiredCount();
        Ai::INode::Status ResetTiredCount();
        void OnDamage(std::shared_ptr<DamageContext::IDamageContext> damageContext) override;
        Vector2 Position() const override;
        std::unique_ptr<Ai::BehaviourTree> ActionBehaviour();


        std::shared_ptr<Animation> idleAnimation_           = std::make_shared<Animation>();
        std::shared_ptr<Animation> walkAnimation_           = std::make_shared<Animation>();
        std::shared_ptr<Animation> singleAttackAnimation_   = std::make_shared<Animation>();
        std::shared_ptr<Animation> doubleAttackAnimation_   = std::make_shared<Animation>();
        std::shared_ptr<Animation> defenseAnimation_        = std::make_shared<Animation>();
        std::shared_ptr<Animation> hurtAnimation_           = std::make_shared<Animation>();
        std::shared_ptr<Animation> deathAnimation_          = std::make_shared<Animation>();

        Health          health_;
        PhysicsPower    physicsPower_;
        int             dropComboCount_ = 0;
        MadnessEnergy   dropComboEnergy_;

        StartMotionArea         singleAttackMotionArea_;
        StartMotionArea         doubleAttackMotionArea_;
        SpawnAttackAreaModel    singleAttackAreaModel_;
        SpawnAttackAreaModel    doubleAttackAreaModel_;

        Vector2     frostEnergyShootOffset_;
        std::string frostEnergyShootPrefabPath_ = "Resource/Prefab/"; 
        
        std::unique_ptr<Ai::BehaviourTree> behaviour_;
        std::queue<std::shared_ptr<DamageContext::IDamageContext>> onDamaged_;
        int tiredingCount_ = 0;
        int tiredCount_ = 3;
    };
}

CEREAL_REGISTER_TYPE(Enemy::FrostShadowKnight)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Enemy::FrostShadowKnight)