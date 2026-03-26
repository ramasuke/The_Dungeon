#include "GhostWizard.h"

#include "../../../../Component/Content/Basically/Collider/Collider.h"
#include "../../../../Component/Content/Basically/Renderer/AnimationRenderer/AnimationRenderer.h"
#include "../../../../Entity/Entity.hpp"
#include "../../../../Helper/ImGui/ImGuiHelper.h"
#include "../../../Sound/HandleContainer/HandleContainer.h"
#include "../Helper/EnemyHelper.h"

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
#include "Behaviour/SummonGhostWizardFireBall.h"

void Enemy::GhostWizard::Init()
{
    EntityRef().GetComponent<AnimationRenderer>()->SetAnimation(idleAnimation_);
}

void Enemy::GhostWizard::Awake()
{
    EntityRef().GetComponent<Collider>()->SetLayer(EnemyHelper::CollisionableFilter());

    behaviour_ = Bt::CreateBehaviour(
        Bt::PromptSelector(
            //ダメージを受けた
            Bt::Sequence(
                Bt::When<Condition::IsDamaged>(onDamaged_),
                Bt::Then<Action::PlaySe>(Sound::GhostWizard::OnHurt()),
                Bt::Then<Action::OnDamage>(EntityRef(), health_, onDamaged_),
                //死亡
                Bt::Sequence(
                    Bt::When<Condition::IsDeath>(health_),
                    Bt::Then<Action::PlaySe>(Sound::GhostWizard::OnDeath()),
                    Bt::Then<Action::PlayAnimation>(EntityRef(), deathAnimation_),
                    Bt::Wait(20),
                    Bt::Then<Action::OnDropMadnessEnergy>(EntityRef(), dropComboCount_, dropComboEnergy_),
                    Bt::Then<Action::OnDespawnEntity>(EntityRef()),
                    Bt::Then<Action::CreateDeathParticle>(EntityRef())
                )
            ),
            Bt::Selector(
                Bt::Sequence(
                    //攻撃
                    Bt::When<Condition::RaycastToPlayer>(EntityRef(), 100.0f),
                    Bt::Then<Action::PlayAnimation>(EntityRef(), idleAnimation_),
                    Bt::Then<Action::SummonGhostWizardFireBall>(EntityRef(), 80.0f, firePower_),
                    Bt::Wait(100),
                    Bt::Then<Action::SetLinearVelocity>(EntityRef(), Vector2(0, 0))
                )
            )
        )
    );
}

void Enemy::GhostWizard::OnUpdate()
{
    behaviour_->OnUpdate();
}

void Enemy::GhostWizard::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("health", health_);
    ImGuiHelper::OnDrawInputField("firePower", firePower_);
    ImGuiHelper::OnDrawInputField("dropComboCount", dropComboCount_);
    ImGuiHelper::OnDrawInputField("dropComboEnergy", dropComboEnergy_);

    if (ImGui::TreeNode("Animation"))
    {
        ImGuiHelper::OnDrawInputField("idleAnimation", idleAnimation_);
        ImGuiHelper::OnDrawInputField("avoidAnimatoin", avoidAnimatoin_);
        ImGuiHelper::OnDrawInputField("deathAnimation", deathAnimation_);
        ImGui::TreePop();
        ImGui::Spacing();
    }
}

void Enemy::GhostWizard::OnDamage(const std::shared_ptr<DamageContext::IDamageContext> damageContext)
{
    onDamaged_.push(damageContext);
}

Vector2 Enemy::GhostWizard::Position() const
{
    return EntityRef().GetComponent<Transform>()->position_;
}
