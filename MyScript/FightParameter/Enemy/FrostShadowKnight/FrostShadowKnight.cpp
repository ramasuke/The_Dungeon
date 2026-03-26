#include "FrostShadowKnight.h"

#include "../../../../../Component/Content/Basically/Renderer/AnimationRenderer/AnimationRenderer.h"
#include "../../../../../Helper/ImGui/ImGuiHelper.h"
#include "../../../AI/BehaviourTree/DSL/BehaviourTreeDSL.h"
#include "../../../Sound/HandleContainer/HandleContainer.h"
#include "../Behaviour/Action/AddPosForTurnDirection/AddPosForTurnDirection.h"
#include "../Behaviour/Action/ChaseToPlayerForFindPath/ChasePlayerForFindPath.h"
#include "../Behaviour/Action/CopyableChasePlayerForFindPath/CopyableChasePlayerForFindPath.h"
#include "../Behaviour/Action/CreateDeathParticle/CreateDeathParticle.h"
#include "../Behaviour/Action/OnDamage/OnDamage.h"
#include "../Behaviour/Action/OnDespawnEntity/OnDespawnEntity.h"
#include "../Behaviour/Action/OnDropMadnessEnergy/OnDropMadnessEnergy.h"
#include "../Behaviour/Action/OnLookPlayer/OnLookPlayer.h"
#include "../Behaviour/Action/PlayAnimation/PlayAnimation.h"
#include "../Behaviour/Action/PlaySE/PlaySE.h"
#include "../Behaviour/Action/SetLinearVelocity/SetLinearVelocity.h"
#include "../Behaviour/Action/SpawnAttackArea/SpawnBoxAttackArea.h"
#include "../Behaviour/Action/SurprisedSign/SurprisedSign.h"
#include "../Behaviour/Action/SuspiciousSign/SuspiciousSign.h"
#include "../Behaviour/Action/Wander/Wander.h"
#include "../Behaviour/Condition/IsDeath.h"
#include "../Behaviour/Condition/DistanceToPlayer/DistanceToPlayer.h"
#include "../Behaviour/Condition/IsDamaged/IsDamaged.h"
#include "../Behaviour/Condition/IsInPlayer/IsInPlayer.h"
#include "../Helper/EnemyHelper.h"
#include "Behaviour/SummonFrostEnergyShoot/SummonFrostEnergyShoot.h"

void Enemy::FrostShadowKnight::Init()
{
    EntityRef().GetComponent<AnimationRenderer>()->SetAnimation(idleAnimation_);
}

void Enemy::FrostShadowKnight::Awake()
{
    EntityRef().GetComponent<Collider>()->SetLayer(EnemyHelper::CollisionableFilter());

    behaviour_ = ActionBehaviour();
}

void Enemy::FrostShadowKnight::OnUpdate()
{
    behaviour_->OnUpdate();
}

void Enemy::FrostShadowKnight::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("health"          , health_           );
    ImGuiHelper::OnDrawInputField("physicsPower"    , physicsPower_     );
    ImGuiHelper::OnDrawInputField("dropComboCount"  , dropComboCount_   );
    ImGuiHelper::OnDrawInputField("dropComboEnergy" , dropComboEnergy_  );

    if (ImGui::TreeNode("AttackArea"))
    {
        if (ImGui::TreeNode("singleAttackMotionArea"))
        {
            singleAttackMotionArea_.OnDrawInspector(EntityRef().GetComponent<Transform>()->position_);
            ImGui::TreePop();
            ImGui::Spacing();
        }
        if (ImGui::TreeNode("doubleAttackMotionArea"))
        {
            doubleAttackMotionArea_.OnDrawInspector(EntityRef().GetComponent<Transform>()->position_);
            ImGui::TreePop();
            ImGui::Spacing();
        }

        if (ImGui::TreeNode("singleAttackArea"))
        {
            singleAttackAreaModel_.OnDrawInspector(EntityRef());
            ImGui::TreePop();
            ImGui::Spacing();
        }
        if (ImGui::TreeNode("doubleAttackArea"))
        {
            doubleAttackAreaModel_.OnDrawInspector(EntityRef());
            ImGui::TreePop();
            ImGui::Spacing();
        }
        ImGui::TreePop();
        ImGui::Spacing();
    }

    if (ImGui::TreeNode("frostEnergyShootOffset"))
    {
        frostEnergyShootOffset_.OnDrawDebug();
        ImGui::TreePop();
        ImGui::Spacing();
    }
    ImGuiHelper::OnDrawInputField("frostEnergyShootPrefabPath", frostEnergyShootPrefabPath_);

    if (ImGui::TreeNode("Animation"))
    {
        ImGuiHelper::OnDrawInputField("idleAnimation"           , idleAnimation_        );
        ImGuiHelper::OnDrawInputField("walkAnimation"           , walkAnimation_        );
        ImGuiHelper::OnDrawInputField("singleAttackAnimation"   , singleAttackAnimation_);
        ImGuiHelper::OnDrawInputField("doubleAttackAnimation"   , doubleAttackAnimation_);
        ImGuiHelper::OnDrawInputField("defenseAnimation"        , defenseAnimation_     );
        ImGuiHelper::OnDrawInputField("hurtAnimation"           , hurtAnimation_        );
        ImGuiHelper::OnDrawInputField("deathAnimation"          , deathAnimation_       );
        ImGui::TreePop();
        ImGui::Spacing();
    }
}

Ai::INode::Status Enemy::FrostShadowKnight::AddTiredCount()
{
    tiredingCount_++;
    return Ai::INode::Status::Success;
}

Ai::INode::Status Enemy::FrostShadowKnight::ResetTiredCount()
{
    tiredingCount_ = 0;
    return Ai::INode::Status::Success;
}

void Enemy::FrostShadowKnight::OnDamage(const std::shared_ptr<DamageContext::IDamageContext> damageContext)
{
    onDamaged_.push(damageContext);
}

Vector2 Enemy::FrostShadowKnight::Position() const
{
    return EntityRef().GetComponent<Transform>()->position_;
}

std::unique_ptr<Ai::BehaviourTree> Enemy::FrostShadowKnight::ActionBehaviour()
{
    return Bt::CreateBehaviour(
        Bt::PromptSelector(
            //ダメージを受けた
            Bt::Sequence(
                Bt::When<Condition::IsDamaged   >(onDamaged_),
                Bt::Then<Action::PlaySe         >(Sound::Skeleton::OnHurt()),
                Bt::Then<Action::PlayAnimation  >(EntityRef(), hurtAnimation_),
                Bt::Then<Action::OnDamage       >(EntityRef(), health_, onDamaged_),
                Bt::Then<Action::PlayAnimation  >(EntityRef(), walkAnimation_),
                Bt::Transform(
                    std::unordered_map<Ai::INode::Status, Ai::INode::Status>{
                        {Ai::INode::Status::Failure , Ai::INode::Status::Success},
                        {Ai::INode::Status::Running , Ai::INode::Status::Running},
                        {Ai::INode::Status::Abort   , Ai::INode::Status::Abort  }
                    },
                    Bt::Sequence(
                        //疲労困憊
                        Bt::CreateNode<Ai::ConditionNode>([this]()
                        {
                            return tiredCount_ <= tiredingCount_;
                        }),
                        Bt::Then<Action::PlayAnimation  >(EntityRef(), defenseAnimation_)
                    ),
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
                )
            ),
            Bt::Selector(
                Bt::Sequence(
                    //Playerを見つけた
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
                                {Ai::INode::Status::Failure , Ai::INode::Status::Success},
                                {Ai::INode::Status::Running , Ai::INode::Status::Running},
                                {Ai::INode::Status::Abort   , Ai::INode::Status::Abort  }
                            },
                            Bt::Selector(
                                Bt::Sequence(
                                    //疲労困憊
                                    Bt::CreateNode<Ai::ConditionNode>([this]()
                                    {
                                        return tiredCount_ <= tiredingCount_;
                                    }),
                                    Bt::Then<Action::PlayAnimation  >(EntityRef(), defenseAnimation_),
                                    Bt::Wait(250),
                                    Bt::CreateNode<Ai::ActionNode   >([this]() { return ResetTiredCount();} ),
                                    Bt::Then<Action::PlayAnimation  >(EntityRef(), walkAnimation_)
                                ),
                                Bt::Sequence(
                                    //SingleAttack
                                    Bt::When<Condition::IsInPlayer      >(EntityRef(), singleAttackMotionArea_),
                                    Bt::Then<Action::PlayAnimation      >(EntityRef(), singleAttackAnimation_),
                                    Bt::Wait(22),
                                    Bt::Then<Action::SpawnBoxAttackArea >(EntityRef(), std::make_shared<DamageContext::PhysicsDamageContext>(EntityRef(), physicsPower_), singleAttackAreaModel_),
                                    Bt::Wait(24),
                                    Bt::Then<Action::PlayAnimation      >(EntityRef(), idleAnimation_),
                                    Bt::Then<Action::PlayAnimation      >(EntityRef(), walkAnimation_),
                                    Bt::CreateNode<Ai::ActionNode       >([this]() { return AddTiredCount();} )
                                ),
                                Bt::Sequence(
                                    //DoubleAttack
                                    Bt::When<Condition::IsInPlayer          >(EntityRef(), doubleAttackMotionArea_),
                                    Bt::Then<Action::AddPosForTurnDirection >(EntityRef(), Vector2(100, 0)),
                                    Bt::Then<Action::PlayAnimation          >(EntityRef(), doubleAttackAnimation_),
                                    Bt::Wait(20),
                                    Bt::Then<Action::SetLinearVelocity      >(EntityRef()   , Vector2(0, 0)),
                                    Bt::Then<Action::SpawnBoxAttackArea>(EntityRef(), std::make_shared<DamageContext::PhysicsDamageContext>(EntityRef(), physicsPower_), doubleAttackAreaModel_),
                                    Bt::Wait(50),
                                    Bt::Then<Action::AddPosForTurnDirection >(EntityRef(), Vector2(-100, 0)),
                                    Bt::Then<Action::PlayAnimation          >(EntityRef(), walkAnimation_),
                                    Bt::CreateNode<Ai::ActionNode           >([this]() { return AddTiredCount();} )
                                ),
                                Bt::Sequence(
                                    //MiddleRangeAttack
                                    Bt::When<Condition::IsInPlayer          >(EntityRef()   , StartMotionArea(Vector2(0, 0), Vector2(330, 20))),
                                    Bt::Then<Action::SetLinearVelocity      >(EntityRef()   , Vector2(0, 0)),
                                    Bt::Then<Action::PlayAnimation          >(EntityRef()   , idleAnimation_),
                                    Bt::Then<Action::SummonFrostEnergyShoot >(EntityRef()   , frostEnergyShootOffset_),
                                    Bt::Then<Action::SummonFrostEnergyShoot >(EntityRef()   , frostEnergyShootOffset_ + Vector2(0, 30)),
                                    Bt::Then<Action::SummonFrostEnergyShoot >(EntityRef()   , frostEnergyShootOffset_ + Vector2(0, -30)),
                                    Bt::Wait(80),
                                    Bt::Then<Action::PlayAnimation          >(EntityRef(), walkAnimation_)
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
                                Bt::When<Condition::RaycastToPlayer>(EntityRef(), 10.0f),
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
                    Bt::Then<Action::Wander         >(EntityRef(), 0.005f, Random::Context<int>(40, 60)),
                    Bt::Wait(Random::Range(25, 60))
                )
            )
        )
    );
}
