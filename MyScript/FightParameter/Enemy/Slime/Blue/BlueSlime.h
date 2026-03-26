#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../../BasicallyParameter/SerializableSubject/Subject.h"
#include "../../../../../BasicallyParameter/Sound/Handle/SoundHandle.h"
#include "../../../../../Component/Component.hpp"
#include "../../../../../Component/Content/Basically/Collider/Box/BoxCollider.h"
#include "../../../../../Component/Content/Basically/Renderer/AnimationRenderer/AnimationRenderer.h"
#include "../../../../../Physics/Contact/Begin/IBeginContactable.h"
#include "../../../../../Physics/Raycast/Raycast.h"
#include "../../../../AI/BehaviourTree/BehaviourTree.h"
#include "../../../../AI/BehaviourTree/Node/Action/ActionNode.h"
#include "../../../../AI/BehaviourTree/Node/PersistentSelector/PersistentSelectorNode.h"
#include "../../../MadnessEnergy/MadnessEnergy.h"
#include "../../../Health/Health.h"
#include "../../../IReceivableEnemyAttack/IReceivableEnemyAttack.h"
#include "../../../IReceivablePlayerAttack/IReceivablePlayerAttack.h"
#include "../../../DamageContext/Physics/PhysicsPower/PhysicsPower.h"

class Transform;

namespace Enemy
{
    class BlueSlime final : public virtual Component,
                            public virtual IBeginContactable<IReceivableEnemyAttack>,
                            public virtual IReceivablePlayerAttack
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this),
                cereal::make_nvp("animationModel"   , animation_        ),
                cereal::make_nvp("health"           , health_           ),
                cereal::make_nvp("physicsPower"     , physicsPower_     ),
                cereal::make_nvp("dropComboCount"   , dropComboCount_   ),
                cereal::make_nvp("dropComboEnergy"  , dropComboEnergy_  ),
                cereal::make_nvp("onDeathSound"     , onDeathSound_     )
            );
        }

    private:
        void Init()     override;
        void Awake()    override;
        void OnUpdate() override;
        void OnBeginContact(b2ContactBeginTouchEvent*, IReceivableEnemyAttack*) override;
        void OnDrawInspector() override;
        void OnDamage(std::shared_ptr<DamageContext::IDamageContext> damage) override;
        Vector2 Position() const override;

        Transform* transform_ = nullptr;
        BoxCollider* collider_ = nullptr;
        std::shared_ptr<Animation> animation_ = std::make_shared<Animation>();

        Health health_;
        PhysicsPower physicsPower_;
        int dropComboCount_ = 0;
        MadnessEnergy dropComboEnergy_;

        std::queue<std::shared_ptr<DamageContext::IDamageContext>> onDamaged_;
        std::unique_ptr<Ai::BehaviourTree> behaviour_;
        Sound::SoundHandle onDeathSound_;
    };
}

CEREAL_REGISTER_TYPE(Enemy::BlueSlime)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Enemy::BlueSlime)
