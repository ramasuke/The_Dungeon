#include "WhiteSkeleton.h"

#include "../../../../../Component/Content/Basically/Renderer/AnimationRenderer/AnimationRenderer.h"
#include "../../../../../Helper/ImGui/ImGuiHelper.h"
#include "../../../../AI/BehaviourTree/DSL/BehaviourTreeDSL.h"
#include "../../../../Sound/HandleContainer/HandleContainer.h"
#include "../../Behaviour/Action/ChaseToPlayerForFindPath/ChasePlayerForFindPath.h"
#include "../../Behaviour/Action/CopyableChasePlayerForFindPath/CopyableChasePlayerForFindPath.h"
#include "../../Behaviour/Action/CreateDeathParticle/CreateDeathParticle.h"
#include "../../Behaviour/Action/OnDamage/OnDamage.h"
#include "../../Behaviour/Action/OnDespawnEntity/OnDespawnEntity.h"
#include "../../Behaviour/Action/OnDropMadnessEnergy/OnDropMadnessEnergy.h"
#include "../../Behaviour/Action/OnLookPlayer/OnLookPlayer.h"
#include "../../Behaviour/Action/PlayAnimation/PlayAnimation.h"
#include "../../Behaviour/Action/PlaySE/PlaySE.h"
#include "../../Behaviour/Action/SpawnAttackArea/SpawnBoxAttackArea.h"
#include "../../Behaviour/Action/SurprisedSign/SurprisedSign.h"
#include "../../Behaviour/Action/SuspiciousSign/SuspiciousSign.h"
#include "../../Behaviour/Action/Wander/Wander.h"
#include "../../Behaviour/Condition/IsDeath.h"
#include "../../Behaviour/Condition/DistanceToPlayer/DistanceToPlayer.h"
#include "../../Behaviour/Condition/IsDamaged/IsDamaged.h"
#include "../../Behaviour/Condition/IsInPlayer/IsInPlayer.h"
#include "../../Helper/EnemyHelper.h"

void Enemy::WhiteSkeleton::Init()
{
    EntityRef().GetComponent<AnimationRenderer>()->SetAnimation(idleAnimation_);
}

void Enemy::WhiteSkeleton::Awake()
{
    EntityRef().GetComponent<Collider>()->SetLayer(EnemyHelper::CollisionableFilter());

    behaviour_ = Bt::CreateBehaviour(
        Bt::PromptSelector(
            //ダメージを受けた
            Bt::Sequence(
                Bt::When<Condition::IsDamaged   >(onDamaged_),
                Bt::Then<Action::PlaySe         >(Sound::Skeleton::OnHurt()),
                Bt::Then<Action::PlayAnimation  >(EntityRef(), hurtAnimation_),
                Bt::Then<Action::OnDamage       >(EntityRef(), health_, onDamaged_),
                Bt::Then<Action::PlayAnimation  >(EntityRef(), walkAnimation_),
                //死亡
                Bt::Sequence(
                    Bt::When<Condition::IsDeath     >(health_),
                    Bt::Then<Action::PlaySe         >(Sound::Skeleton::OnDeath()),
                    Bt::Then<Action::PlayAnimation  >(EntityRef(), deathAnimation_),
                    Bt::Wait(70),
                    Bt::Then<Action::OnDropMadnessEnergy>(EntityRef(), dropComboCount_, dropComboEnergy_),
                    Bt::Then<Action::OnDespawnEntity    >(EntityRef()),
                    Bt::Then<Action::CreateDeathParticle>(EntityRef())
                )
            ),
            Bt::Selector(
                //Playerを見つけた
                Bt::Sequence(
                    Bt::When<Condition::RaycastToPlayer >(EntityRef(), 10.0f),
                    Bt::Then<Action::PlayAnimation      >(EntityRef(), idleAnimation_),
                    Bt::Then<Action::OnLookPlayer       >(EntityRef()),
                    Bt::Then<Action::SurprisedSign      >(EntityRef(), -50.0f),
                    Bt::Then<Action::PlaySe             >(Sound::OnSurprise()),
                    Bt::Wait(30),
                    Bt::Then<Action::PlayAnimation>(EntityRef(), walkAnimation_),
                    //Playerを見つけている間
                    Bt::While(
                        //Playerに向かって歩く
                        Bt::When<Condition::RaycastToPlayer >(EntityRef(), 10.0f),
                        Bt::Then<Action::OnLookPlayer       >(EntityRef()),
                        Bt::Then<Action::ChasePlayer        >(EntityRef(), 0.011f),
                        //攻撃
                        Bt::Transform(
                            std::unordered_map<Ai::INode::Status, Ai::INode::Status>{
                                {Ai::INode::Status::Failure, Ai::INode::Status::Success},
                                {Ai::INode::Status::Running, Ai::INode::Status::Running},
                                {Ai::INode::Status::Abort, Ai::INode::Status::Abort}
                            },
                            Bt::Sequence(
                                Bt::When<Condition::RaycastToPlayer >(EntityRef(), 0.7f),
                                Bt::When<Condition::IsInPlayer      >(EntityRef(), startAttackMotionArea_),
                                Bt::RandomSelect(
                                    //攻撃1
                                    Bt::Sequence(
                                        Bt::Then<Action::PlayAnimation      >(EntityRef(), attackAnimation1_),
                                        Bt::Wait(16),
                                        Bt::Then<Action::SpawnBoxAttackArea >(
                                            EntityRef(),
                                            std::make_shared<DamageContext::PhysicsDamageContext>(
                                                EntityRef(), physicsPower_), attack1AreaModel_),
                                        Bt::Wait(30),
                                        Bt::Then<Action::PlayAnimation      >(EntityRef(), walkAnimation_)
                                    ),
                                    //攻撃2
                                    Bt::Sequence(
                                        Bt::Then<Action::PlayAnimation      >(EntityRef(), attackAnimation2_),
                                        Bt::Wait(20),
                                        Bt::Then<Action::SpawnBoxAttackArea >(
                                            EntityRef(),
                                            std::make_shared<DamageContext::PhysicsDamageContext>(
                                                EntityRef(), physicsPower_), attack2AreaModel_),
                                        Bt::Wait(26),
                                        Bt::Then<Action::PlayAnimation      >(EntityRef(), walkAnimation_)
                                    )
                                )
                            )
                        )
                    )
                ),
                //怪しむ
                Bt::Sequence(
                    Bt::When<Condition::DistanceToPlayer>(EntityRef(), 300.0f),
                    Bt::Then<Action::PlayAnimation      >(EntityRef(), walkAnimation_),
                    Bt::Then<Action::SuspiciousSign     >(EntityRef(), -50.0f),
                    Bt::Wait(30),
                    //Playerを感じる間
                    Bt::While(
                        Bt::Selector(
                            Bt::Sequence(
                                //Playerを見つけた
                                Bt::When<Condition::RaycastToPlayer             >(EntityRef(), 10.0f),
                                Bt::Abort()
                            ),
                            Bt::Sequence(
                                //経路を沿って歩く
                                Bt::When<Condition::DistanceToPlayer            >(EntityRef(), 300.0f),
                                Bt::Then<Action::CopyableChasePlayerForFindPath >(EntityRef(), 0.007f)
                            )
                        )
                    )
                ),
                //通常
                Bt::Sequence(
                    Bt::Then<Action::PlayAnimation  >(EntityRef(), walkAnimation_),
                    Bt::Then<Action::Wander         >(EntityRef(), 0.005f, Random::Context<int>(100, 120)),
                    Bt::Wait(Random::Range(25, 60)
                    )
                )
            )
        )
    );
}

void Enemy::WhiteSkeleton::OnUpdate()
{
    behaviour_->OnUpdate();
}

void Enemy::WhiteSkeleton::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("health"          , health_           );
    ImGuiHelper::OnDrawInputField("physicsPower"    , physicsPower_     );
    ImGuiHelper::OnDrawInputField("dropComboCount"  , dropComboCount_   );
    ImGuiHelper::OnDrawInputField("dropComboEnergy" , dropComboEnergy_  );

    if (ImGui::TreeNode("AttackArea"))
    {
        if (ImGui::TreeNode("startAttackMotionArea"))
        {
            startAttackMotionArea_.OnDrawInspector(EntityRef().GetComponent<Transform>()->position_);
            ImGui::TreePop();
            ImGui::Spacing();
        }

        if (ImGui::TreeNode("attack1Area"))
        {
            attack1AreaModel_.OnDrawInspector(EntityRef());
            ImGui::TreePop();
            ImGui::Spacing();
        }
        if (ImGui::TreeNode("attack2Area"))
        {
            attack2AreaModel_.OnDrawInspector(EntityRef());
            ImGui::TreePop();
            ImGui::Spacing();
        }
        ImGui::TreePop();
        ImGui::Spacing();
    }

    if (ImGui::TreeNode("Animation"))
    {
        ImGuiHelper::OnDrawInputField("idleAnimation"   , idleAnimation_    );
        ImGuiHelper::OnDrawInputField("walkAnimation"   , walkAnimation_    );
        ImGuiHelper::OnDrawInputField("attackAnimation1", attackAnimation1_ );
        ImGuiHelper::OnDrawInputField("attackAnimation2", attackAnimation2_ );
        ImGuiHelper::OnDrawInputField("hurtAnimation"   , hurtAnimation_    );
        ImGuiHelper::OnDrawInputField("deathAnimation"  , deathAnimation_   );
        ImGui::TreePop();
        ImGui::Spacing();
    }
}

void Enemy::WhiteSkeleton::OnDamage(const std::shared_ptr<DamageContext::IDamageContext> damageContext)
{
    onDamaged_.push(damageContext);
}

Vector2 Enemy::WhiteSkeleton::Position() const
{
    return EntityRef().GetComponent<Transform>()->position_;
}
