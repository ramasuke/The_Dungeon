#include "SummonBossCircle.h"

#include "../../../../Component/Content/Basically/Renderer/AnimationRenderer/AnimationRenderer.h"
#include "../../../../Entity/Entity.hpp"
#include "../../../../Helper/ImGui/ImGuiHelper.h"

void Enemy::SummonBossCircle::SetSummonModel(const SpawnEnemyModel& summonModel,
                                             const std::function<void()>& onDeathBossCallback)
{
    spawnEnemyModel_        = summonModel;
    onDeathBossCallback_    = onDeathBossCallback;   
}

void Enemy::SummonBossCircle::Init()
{
    EntityRef().GetComponent<AnimationRenderer>()->SetAnimation(animation_);
}

void Enemy::SummonBossCircle::OnUpdate()
{
    onSummonDuring_++;

    if (onSummonDuring_ <= onSummonDuration_)
        return;

    OnSpawnEnemy();
    EntityRef().OnDespawn();
}

void Enemy::SummonBossCircle::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("animation"           , animation_        );
    ImGuiHelper::OnDrawInputField("onDestroyDuration"   , onSummonDuration_ );
    ImGuiHelper::OnDrawInputField("onDestroyDuring"     , onSummonDuring_   );
}

void Enemy::SummonBossCircle::OnSpawnEnemy() const
{
    const auto& boss = Entity::Spawn(spawnEnemyModel_.PrefabPath(), spawnEnemyModel_.Position());
    auto callbackCopy = onDeathBossCallback_;
    boss.OnDespawnSubscription().add([callbackCopy] {
            callbackCopy();
    });
}
