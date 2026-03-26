#include "SpawnBoxAttackArea.h"

#include "../../../../../../Component/Content/Basically/Collider/Collider.h"
#include "../../../../../../Component/Content/Basically/Transform/Transform.hpp"
#include "../../../../../../Physics/Physics.h"
#include "../../../../DamageContext/Interface/IDamageContext.h"
#include "../../../BoxAttackArea/EnemyBoxAttackArea.h"

Enemy::Behaviour::Action::SpawnBoxAttackArea::SpawnBoxAttackArea(Entity& self,
                                                                 const std::shared_ptr<DamageContext::IDamageContext>&
                                                                 damage,
                                                                 const SpawnAttackAreaModel& attackAreaParam)
    : self_(self), damage_(damage), attackAreaParam_(attackAreaParam)
{
}

Ai::INode::Status Enemy::Behaviour::Action::SpawnBoxAttackArea::operator()() const
{
    const auto collider = Entity::Spawn<EnemyBoxAttackArea>(ENEMY_BOX_ATTACK_AREA_PREFAB_PATH,
                                                            self_.GetComponent<Transform>()->position_);
    collider->InitArea(damage_, attackAreaParam_);

    return Ai::INode::Status::Success;
}
