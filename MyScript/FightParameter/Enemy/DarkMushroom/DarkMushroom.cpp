#include "DarkMushroom.h"

#include "../../../../Component/Content/Basically/Renderer/AnimationRenderer/AnimationRenderer.h"
#include "../../../../Component/Content/Basically/Transform/Transform.hpp"
#include "../../../../Entity/Entity.hpp"
#include "../../../../Helper/ImGui/ImGuiHelper.h"
#include "../../../AI/BehaviourTree/DSL/BehaviourTreeDSL.h"
#include "../../../Sound/HandleContainer/HandleContainer.h"
#include "../Behaviour/Action/CreateDeathParticle/CreateDeathParticle.h"
#include "../Behaviour/Action/OnDamage/OnDamage.h"
#include "../Behaviour/Action/OnDespawnEntity/OnDespawnEntity.h"
#include "../Behaviour/Action/OnDropMadnessEnergy/OnDropMadnessEnergy.h"
#include "../Behaviour/Action/PlayAnimation/PlayAnimation.h"
#include "../Behaviour/Action/PlaySE/PlaySE.h"
#include "../Behaviour/Condition/IsDeath.h"
#include "../Behaviour/Condition/IsDamaged/IsDamaged.h"

void Enemy::DarkMushroom::Awake()
{
    EntityRef().GetComponent<AnimationRenderer>()->SetAnimation(idleAnimation_);

    behaviour_ = Bt::CreateBehaviour(
        Bt::PromptSelector(
            //ダメージを受けた
            Bt::Sequence(
                Bt::When<Condition::IsDamaged   >(onDamaged_),
                Bt::Then<Action::PlaySe         >(Sound::Skeleton::OnHurt()),
                Bt::Then<Action::PlayAnimation  >(EntityRef(), hurtAnimation_),
                Bt::CreateNode<Ai::ActionNode   >([this]()
                {
                    health_ -= Health(1);
                    std::queue<std::shared_ptr<DamageContext::IDamageContext>> empty;
                    std::swap(onDamaged_, empty);
                    return Ai::INode::Status::Success;
                }),
                Bt::Then<Action::OnDropMadnessEnergy>(EntityRef(), onDamageDropEnergyCount_, onDamageDropEnergy_),
                Bt::Then<Action::PlayAnimation      >(EntityRef(), idleAnimation_),
                //死亡
                Bt::Sequence(
                    Bt::When<Condition::IsDeath     >(health_),
                    Bt::Then<Action::PlaySe         >(Sound::Skeleton::OnDeath()),
                    Bt::Then<Action::PlayAnimation  >(EntityRef(), deathAnimation_),
                    Bt::Wait(70),
                    Bt::Then<Action::OnDespawnEntity    >(EntityRef()),
                    Bt::Then<Action::CreateDeathParticle>(EntityRef())
                )
            )
        )
    );
}

void Enemy::DarkMushroom::OnUpdate()
{
    behaviour_->OnUpdate();
}

void Enemy::DarkMushroom::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("health"                  , health_                   );
    ImGuiHelper::OnDrawInputField("onDamageDropEnergyCount" , onDamageDropEnergyCount_  );
    ImGuiHelper::OnDrawInputField("onDamageDropEnergy"      , onDamageDropEnergy_       );

    ImGuiHelper::OnDrawInputField("idleAnimation"   , idleAnimation_    );
    ImGuiHelper::OnDrawInputField("hurtAnimation"   , hurtAnimation_    );
    ImGuiHelper::OnDrawInputField("deathAnimation"  , deathAnimation_   );
}

void Enemy::DarkMushroom::OnDamage(const std::shared_ptr<DamageContext::IDamageContext> damageContext)
{
    onDamaged_.push(damageContext);
}

Vector2 Enemy::DarkMushroom::Position() const
{
    return EntityRef().GetComponent<Transform>()->position_;
}
