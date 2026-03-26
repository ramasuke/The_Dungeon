#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../Component/Component.hpp"
#include "../../../../Component/Content/Basically/Renderer/AnimationRenderer/Animation/Animation.h"
#include "../../../AI/BehaviourTree/BehaviourTree.h"
#include "../../../AI/BehaviourTree/Node/Action/ActionNode.h"
#include "../../IReceivablePlayerAttack/IReceivablePlayerAttack.h"
#include "../../MadnessEnergy/MadnessEnergy.h"

namespace Enemy
{
    class DarkMushroom final : public virtual Component,
                               public virtual IReceivablePlayerAttack
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this),
                cereal::make_nvp("health"                   , health_                   ),
                cereal::make_nvp("onDamageDropEnergyCount"  , onDamageDropEnergyCount_  ),
                cereal::make_nvp("onDamageDropEnergy"       , onDamageDropEnergy_       ),
                cereal::make_nvp("idleAnimation"            , idleAnimation_            ),
                cereal::make_nvp("hurtAnimation"            , hurtAnimation_            ),
                cereal::make_nvp("deathAnimation"           , deathAnimation_           )
            );
        }

    private:
        void Awake()            override;
        void OnUpdate()         override;
        void OnDrawInspector()  override;
        void OnDamage(std::shared_ptr<DamageContext::IDamageContext> damageContext) override;
        Vector2 Position() const override;
        
        
        Health health_      = Health(35);
        int onDamageDropEnergyCount_        = 1;
        MadnessEnergy onDamageDropEnergy_   = MadnessEnergy(1);

        std::shared_ptr<Animation> idleAnimation_   = std::make_shared<Animation>();
        std::shared_ptr<Animation> hurtAnimation_   = std::make_shared<Animation>();
        std::shared_ptr<Animation> deathAnimation_  = std::make_shared<Animation>();
        
        std::unique_ptr<Ai::BehaviourTree> behaviour_;
        std::queue<std::shared_ptr<DamageContext::IDamageContext>> onDamaged_;
    };
}

CEREAL_REGISTER_TYPE(Enemy::DarkMushroom)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Enemy::DarkMushroom)
