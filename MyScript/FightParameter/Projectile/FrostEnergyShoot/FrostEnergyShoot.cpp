#include "FrostEnergyShoot.h"

#include "../../../../Entity/Entity.hpp"
#include "../../Enemy/Behaviour/Action/SpawnAttackArea/SpawnBoxAttackArea.h"
#include "../../Enemy/BoxAttackArea/EnemyBoxAttackArea.h"

void Projectile::FrostEnergyShoot::OnUpdate()
{
    summonAttackAreaDuring_++;

    if (summonAttackAreaDuration_ == summonAttackAreaDuring_)
    {
        const auto collider = Entity::Spawn<Enemy::EnemyBoxAttackArea>(ENEMY_BOX_ATTACK_AREA_PREFAB_PATH,
                                                                       EntityRef().GetComponent<Transform>()->
                                                                       position_);

        const auto summonAttackAreaPos = Vector2(
            EntityRef().GetComponent<AnimationRenderer>()->ToTurnDirction().x_ * summonAttackAreaModel_.Offset().x_,
            summonAttackAreaModel_.Offset().y_);

        const auto summonAttackAreaModel = SpawnAttackAreaModel(summonAttackAreaPos, summonAttackAreaModel_.AreaSize(),
                                                                summonAttackAreaModel_.DespawnDuration());

        collider->InitArea(std::make_shared<DamageContext::PhysicsDamageContext>(EntityRef(), damage_),
                           summonAttackAreaModel);
    }
}

void Projectile::FrostEnergyShoot::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("damage", damage_);

    if (ImGui::TreeNode("summonAttackAreaModel"))
    {
        summonAttackAreaModel_.OnDrawInspector(EntityRef());
        ImGui::TreePop();
        ImGui::Spacing();
    }

    ImGuiHelper::OnDrawInputField("summonAttackAreaDuration", summonAttackAreaDuration_);
}
