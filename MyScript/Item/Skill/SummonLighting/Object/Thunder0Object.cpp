#include "Thunder0Object.h"

#include "Thunder0ObjectAttackArea.h"
#include "../../../../../Component/Content/Basically/Collider/Collider.h"
#include "../../../../../Component/Content/Basically/Transform/Transform.hpp"
#include "../../../../../Entity/Entity.hpp"
#include "../../../../../Physics/Physics.h"

void Thunder0Object::SetThunderPower(const ThunderPower& thunderPower)
{
    thunderPower_ = thunderPower;
}

void Thunder0Object::OnUpdate()
{
    aliveDuring_++;
    if (onSpawnAttackAreaCooldownDuration_ == aliveDuring_)
    {
        attackArea_ = &Entity::Spawn(attackAreaPrefabPath_, EntityRef().GetComponent<Transform>()->position_);
        attackArea_->GetComponent<Thunder0ObjectAttackArea>()->SetThunderPower(thunderPower_);
    }

    if (onDespawnDuration_ < aliveDuring_)
    {
        EntityRef().OnDespawn();
        attackArea_->OnDespawn();
    }
}

void Thunder0Object::OnDrawInspector()
{
    ImGui::InputInt("onSpawnAttackAreaCooldownDuration", &onSpawnAttackAreaCooldownDuration_);
    ImGui::InputInt("onDespawnDuration", &onDespawnDuration_);
}
