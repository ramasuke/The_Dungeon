#include "NormalFormParam.h"

#include <stack>

#include "../../CanUseSkillParticle.h"
#include "../../../../../Application/IApplication/IApplication.hpp"
#include "../../../../../BasicallyParameter/Sound/Play/SoundPlay.h"
#include "../../../../../Component/Content/Basically/Renderer/AnimationRenderer/AnimationRenderer.h"
#include "../../../../../Component/Content/Basically/Transform/Transform.hpp"
#include "../../../../../Entity/Entity.hpp"
#include "../../../../Sound/HandleContainer/HandleContainer.h"

void Player::NormalForm::NormalFormParam::Init()
{
    onDeathSubscription_.unsubscribe();
    onDeathSubscription_ = rxcpp::composite_subscription();
    onDeath_.get_observable()
        .take(1)
        .subscribe([this](const unit&)
        {
            IApplication::GetInstance().SceneManager().OnLoadSceneAsync("Resource/Scene/GameOverScene.json");
            onDeathSubscription_.unsubscribe();
            onDeathSubscription_ = rxcpp::composite_subscription();
        }).add(static_cast<rxcpp::subscription>(onDeathSubscription_));
    
    animation_  .Init();
    sound_      .Init();
    
    health_.OnNext(maxHealth_.get());
}

void Player::NormalForm::NormalFormParam::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("maxHealth"                           , maxHealth_                        );
    ImGuiHelper::OnDrawInputField("health"                              , health_                           );
    ImGuiHelper::OnDrawInputField("physicsAttackPower"                  , physicsAttackPower_               );
    ImGuiHelper::OnDrawInputField("walkSpeed"                           , walkSpeed_                        );
    ImGuiHelper::OnDrawInputField("attackStateDuration"                 , attackStateDuration_              );
    ImGuiHelper::OnDrawInputField("attackStateOnAttackDamageDuration"   , attackStateOnAttackDamageDuration_);
    ImGuiHelper::OnDrawInputField("attackDistance"                      , attackDistance_                   );
    ImGuiHelper::OnDrawInputField("maxCollectMadness"                   , maxCollectMadness_                );
    ImGuiHelper::OnDrawInputField("useSkillNeedMadness"                 , useSkillNeedMadness_              );
    ImGuiHelper::OnDrawInputField("toDarkFormNeedMadness"               , toDarkFormNeedMadness_            );
    ImGuiHelper::OnDrawInputField("toDarkFormNeedDuration"              , toDarkFormNeedDuration_           );
    ImGuiHelper::OnDrawInputField("collectMadness"                      , currentMadness_                   );
    ImGuiHelper::OnDrawInputField("goInsaneDuration"                    , goInsaneDuration_                 );
    ImGuiHelper::OnDrawInputField("onDarkHealStateDuration"             , onDarkHealStateDuration_          );
    ImGuiHelper::OnDrawInputField("darkHealNeedMadness"                 , darkHealNeedMadness_              );
    ImGuiHelper::OnDrawInputField("onDarkHealCount"                     , darkHealCount_                    );
    ImGuiHelper::OnDrawInputField("onDamageStateDuration"               , onDamageStateDuration_            );
    ImGuiHelper::OnDrawInputField("animation"                           , animation_                        );
    ImGuiHelper::OnDrawInputField("sound"                               , sound_                            );
}

void Player::NormalForm::NormalFormParam::OnCollectMadness(const MadnessEnergy onCollectMadness)
{
    Sound::PlaySe(Sound::OnCollectMadnessEnergy());
    const auto nextCollectMadness = onCollectMadness + currentMadness_.get();
    if (nextCollectMadness > maxCollectMadness_.get())
        return;

    currentMadness_.OnNext(currentMadness_.get() + onCollectMadness);
}

void Player::NormalForm::NormalFormParam::OnDamage(
    std::stack<std::shared_ptr<DamageContext::IDamageContext>>& damageStack,
    Entity& entityRef)
{
        const auto& context = damageStack.top();
        auto health = health_.get();    
        context->OnStartEffect(entityRef, health);
        auto& splatterBlood = Entity::Spawn(splatterBloodPrefabPath_, entityRef.GetComponent<Transform>()->position_);
        const auto onDamageDirection = context->FromPos().x_ - splatterBlood.GetComponent<Transform>()->position_.x_;
        splatterBlood.GetComponent<AnimationRenderer>()->isReverseX_ = onDamageDirection >= 0;
        const auto splatterBloodOffsetPos = Vector2(30 * splatterBlood.GetComponent<AnimationRenderer>()->ToTurnDirction().x_, -16);
        splatterBlood.GetComponent<Transform>()->position_ += splatterBloodOffsetPos;
        
        if (health <= minDeathHealth_)
        {
            health = minDeathHealth_;
        }
        health_.OnNext(health);
    
    while (!damageStack.empty())
    {
        damageStack.pop();
    }
}

void Player::NormalForm::NormalFormParam::OnUseSkill()
{
    isUseSkill_.OnNext(false);
    canUseSkillParticle_->EntityRef().OnDespawn();
    canUseSkillParticle_ = nullptr;
}

void Player::NormalForm::NormalFormParam::OnDeath() const
{
    onDeath_.get_subscriber().on_next(unit{});
}

void Player::NormalForm::NormalFormParam::OnEnableUseSkill(Transform& playerTransform)
{
    canUseSkillParticle_ = Entity::Spawn<CanUseSkillParticle>(canUseSkillParticlePrefabPath_, playerTransform.position_);
    canUseSkillParticle_->SetFollowTarget(&playerTransform);
    
    currentMadness_.OnNext(currentMadness_.get() - useSkillNeedMadness_.get());
    isUseSkill_.OnNext(true);
}

void Player::NormalForm::NormalFormParam::OnDarkHeal(const ::Health healCount)
{
    currentMadness_.OnNext(currentMadness_.get() - darkHealNeedMadness_.get());
    const auto nextHealedHealth = health_.get() + healCount;
    if (nextHealedHealth > maxHealth_.get())
    {
        health_.OnNext(maxHealth_.get());
        return;
    }
    health_.OnNext(nextHealedHealth);
}
