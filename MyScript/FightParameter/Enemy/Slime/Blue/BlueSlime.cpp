#include "BlueSlime.h"

#include "../../../../../Application/IApplication/IApplication.hpp"
#include "../../../../../Entity/Entity.hpp"
#include "../../../../../Helper/Random/Random.h"
#include "../../../../../Libs/ImGui/imgui.h"
#include "../../../../AI/BehaviourTree/DSL/BehaviourTreeDSL.h"
#include "../../../../DamageNotation/Physics/DamageNotation.h"
#include "../../../../Sound/HandleContainer/HandleContainer.h"
#include "../../../MadnessEnergy/MadnessEnergyObject/MadnessEnergyObject.h"
#include "../../Behaviour/Action/ChaseToPlayer/ChasePlayer.h"
#include "../../Behaviour/Action/ChaseToPlayerForFindPath/ChasePlayerForFindPath.h"
#include "../../Behaviour/Action/CopyableChasePlayerForFindPath/CopyableChasePlayerForFindPath.h"
#include "../../Behaviour/Action/CreateDeathParticle/CreateDeathParticle.h"
#include "../../Behaviour/Action/OnDamage/OnDamage.h"
#include "../../Behaviour/Action/OnDespawnEntity/OnDespawnEntity.h"
#include "../../Behaviour/Action/OnDropMadnessEnergy/OnDropMadnessEnergy.h"
#include "../../Behaviour/Action/PlayAnimation/PlayAnimation.h"
#include "../../Behaviour/Action/PlaySE/PlaySE.h"
#include "../../Behaviour/Action/SurprisedSign/SurprisedSign.h"
#include "../../Behaviour/Action/SuspiciousSign/SuspiciousSign.h"
#include "../../Behaviour/Action/Wander/Wander.h"
#include "../../Behaviour/Condition/IsDeath.h"
#include "../../Behaviour/Condition/DistanceToPlayer/DistanceToPlayer.h"
#include "../../Behaviour/Condition/IsDamaged/IsDamaged.h"
#include "../../Behaviour/Condition/RaycastToPlayer/RaycastToPlayer.h"
#include "../../Helper/EnemyHelper.h"

void Enemy::BlueSlime::Init()
{
    transform_ = EntityRef().GetComponent<Transform>();
    collider_ = EntityRef().GetComponent<BoxCollider>();
    animation_->Init();
    EntityRef().GetComponent<AnimationRenderer>()->SetAnimation(animation_);
    // onDeathSound_.Init();
}

void Enemy::BlueSlime::Awake()
{
    collider_->SetLayer(EnemyHelper::CollisionableFilter());

    behaviour_ = Bt::CreateBehaviour(
        Bt::PromptSelector(
            //被ダメージ時
            Bt::Sequence(
                Bt::When<Condition::IsDamaged   >(onDamaged_),
                Bt::Then<Action::OnDamage       >(EntityRef(), health_, onDamaged_),
                //死亡
                Bt::Sequence(
                    Bt::When<Condition::IsDeath         >(health_),
                    Bt::Then<Action::PlayAnimation      >(EntityRef(), animation_),
                    Bt::Then<Action::OnDropMadnessEnergy>(EntityRef(), dropComboCount_, dropComboEnergy_),
                    Bt::Then<Action::OnDespawnEntity    >(EntityRef()),
                    Bt::Then<Action::CreateDeathParticle>(EntityRef()),
                    Bt::Then<Action::PlaySe             >(Sound::BlueSlime::OnDeathSound())
                )
            ),
            Bt::Selector(
                //Playerを見つけた
                Bt::Sequence(
                    Bt::When<Condition::RaycastToPlayer >(EntityRef(), 10.0f),
                    Bt::Then<Action::PlayAnimation      >(EntityRef(), animation_),
                    Bt::Then<Action::SurprisedSign      >(EntityRef(), -50.0f),
                    Bt::Then<Action::PlaySe             >(Sound::OnSurprise()),
                    Bt::Wait(30),
                    Bt::While(
                        Bt::When<Condition::RaycastToPlayer >(EntityRef(), 10.0f),
                        Bt::Then<Action::ChasePlayer        >(EntityRef(), 0.016f)
                    )
                ),
                //怪しむ
                Bt::Sequence(
                    Bt::When<Condition::DistanceToPlayer>(EntityRef(), 300.0f),
                    Bt::Then<Action::SuspiciousSign     >(EntityRef(), -50.0f),
                    Bt::Wait(30),
                    //Playerを感じる間
                    Bt::While(
                        Bt::Selector(
                            Bt::Sequence(
                                //Playerを見つけた
                                Bt::When<Condition::RaycastToPlayer>(EntityRef(), 10.0f),
                                Bt::Abort()
                            ),
                            Bt::Sequence(
                                //経路を沿って歩く
                                Bt::When<Condition::DistanceToPlayer>(EntityRef(), 300.0f),
                                Bt::Then<Action::CopyableChasePlayerForFindPath>(EntityRef(), 0.007f)
                            )
                        )
                    )
                ),
                //通常
                Bt::Sequence(
                    Bt::Then<Action::PlayAnimation>(EntityRef(), animation_),
                    Bt::Then<Action::Wander>(EntityRef(), 0.005f, Random::Context<int>(100, 250)),
                    Bt::Wait(Random::Range(25, 60))
                )
            )
        )
    );
}

void Enemy::BlueSlime::OnUpdate()
{
    behaviour_->OnUpdate();
}

void Enemy::BlueSlime::OnBeginContact(b2ContactBeginTouchEvent*, IReceivableEnemyAttack* contact)
{
    contact->OnDamage(std::make_shared<DamageContext::PhysicsDamageContext>(EntityRef(), physicsPower_));
}

void Enemy::BlueSlime::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("health"          , health_           );
    ImGuiHelper::OnDrawInputField("physicsPower"    , physicsPower_     );
    ImGuiHelper::OnDrawInputField("dropComboCount"  , dropComboCount_   );
    ImGuiHelper::OnDrawInputField("dropComboEnergy" , dropComboEnergy_  );
    ImGuiHelper::OnDrawInputField("animation"       , animation_        );
    ImGuiHelper::OnDrawInputField("onDeathSound"    , onDeathSound_     );
}

void Enemy::BlueSlime::OnDamage(const std::shared_ptr<DamageContext::IDamageContext> damage)
{
    onDamaged_.push(damage);
}

Vector2 Enemy::BlueSlime::Position() const
{
    return EntityRef().GetComponent<Transform>()->position_;
}

