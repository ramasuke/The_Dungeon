#include "SummonEnemyCircle.h"

#include "../Enemy.h"
#include "../../../../Component/Content/Basically/Renderer/AnimationRenderer/AnimationRenderer.h"
#include "../../../../Entity/Entity.hpp"
#include "../../../../Helper/ImGui/ImGuiHelper.h"

void Enemy::SummonEnemyCircle::Init()
{
    animation_->Init();
    EntityRef().GetComponent<AnimationRenderer>()->SetAnimation(animation_);
}

void Enemy::SummonEnemyCircle::OnUpdate()
{
    onSummonDuring_++;

    if (onSummonDuring_ <= onSummonDuration_)
        return;

    OnSpawnEnemy();
    EntityRef().OnDespawn();
}

void Enemy::SummonEnemyCircle::SetSummonModel(const SpawnEnemyModel& spawnModel)
{
    spawnEnemyModel_ = spawnModel;
}

void Enemy::SummonEnemyCircle::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("animation"           , animation_        );
    ImGuiHelper::OnDrawInputField("onDestroyDuration"   , onSummonDuration_ );
    ImGuiHelper::OnDrawInputField("onDestroyDuring"     , onSummonDuring_   );
}

void Enemy::SummonEnemyCircle::OnSpawnEnemy() const
{
    Entity::Spawn(spawnEnemyModel_.PrefabPath(), spawnEnemyModel_.Position());
}
