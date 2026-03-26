// #pragma once
// #include <cereal/types/polymorphic.hpp>
//
// #include "../../../../Component/Component.hpp"
// #include "../../../../Component/Content/Basically/Renderer/AnimationRenderer/Animation/Animation.h"
// #include "../../../AI/BehaviourTree/BehaviourTree.h"
// #include "../../DamageContext/Interface/IDamageContext.h"
// #include "../../DamageContext/Physics/PhysicsPower/PhysicsPower.h"
// #include "../../IReceivablePlayerAttack/IReceivablePlayerAttack.h"
// #include "../../MadnessEnergy/MadnessEnergy.h"
//
// namespace Enemy
// {
//     class DarkSamurai final : public virtual Component,
//                               public virtual IReceivablePlayerAttack
//     {
//     public:
//         template <class Archive>
//         void serialize(Archive& archive)
//         {
//             archive(
//                 cereal::base_class<Component>(this),
//                 cereal::make_nvp("health"               , health_               ),
//                 cereal::make_nvp("physicsPower"         , physicsPower_         ),
//                 cereal::make_nvp("dropComboCount"       , dropComboCount_       ),
//                 cereal::make_nvp("dropComboEnergy"      , dropComboEnergy_      ),
//                 
//                 cereal::make_nvp("idleAnimation"        , idleAnimation_        ),
//                 cereal::make_nvp("jumpAnimation"        , jumpAnimation_        ),
//                 cereal::make_nvp("firstAttackAnimation" , firstAttackAnimation_ ),
//                 cereal::make_nvp("secondAttackAnimation", secondAttackAnimation_),
//                 cereal::make_nvp("hurtAnimation"        , hurtAnimation_        ),
//                 cereal::make_nvp("deathAnimation"       , deathAnimation_       )
//             );
//         }
//
//     private:
//         void Init()             override;
//         void Awake()            override;
//         void OnUpdate()         override;
//         void OnDrawInspector()  override;
//         void OnDamage(std::shared_ptr<DamageContext::IDamageContext> damageContext) override;
//         Vector2 Position() const override;
//         
//         Health health_;
//         PhysicsPower physicsPower_;
//         int dropComboCount_ = 0;
//         MadnessEnergy dropComboEnergy_;
//         std::queue<std::shared_ptr<DamageContext::IDamageContext>> onDamaged_;
//         std::unique_ptr<Ai::BehaviourTree> behaviour_;
//         
//         std::shared_ptr<Animation> idleAnimation_;
//         std::shared_ptr<Animation> jumpAnimation_;
//         std::shared_ptr<Animation> firstAttackAnimation_;
//         std::shared_ptr<Animation> secondAttackAnimation_;
//         std::shared_ptr<Animation> hurtAnimation_;
//         std::shared_ptr<Animation> deathAnimation_;
//     };
// }
//
// CEREAL_REGISTER_TYPE(Enemy::DarkSamurai)
//
// CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Enemy::DarkSamurai)