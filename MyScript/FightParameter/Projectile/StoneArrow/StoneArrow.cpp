#include "StoneArrow.h"

#include "../../../../Component/Content/Basically/Collider/Collider.h"
#include "../../../../Entity/Entity.hpp"
#include "../../../../Helper/ImGui/ImGuiHelper.h"
#include "../../../../Helper/MyCalculator/MyCalculator.h"
#include "../../../../Libs/Box2D/include/src/box2d/box2d.h"
#include "../../Enemy/BoxAttackArea/EnemyBoxAttackArea.h"

void Projectile::StoneArrow::Init()
{
    EntityRef().GetComponent<Enemy::EnemyBoxAttackArea>()->InitDamage(std::make_shared<DamageContext::PhysicsDamageContext>(EntityRef(), damage_), 10000000);
}

void Projectile::StoneArrow::OnUpdate()
{
    b2Body_SetLinearVelocity(EntityRef().GetComponent<Collider>()->GetBodyId(),
                             (MyCalculator::GetDirection(EntityRef().GetComponent<Transform>()->rotation_) * speed_).
                             ToB2Vec2());
}
void Projectile::StoneArrow::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("speed", speed_);
    ImGuiHelper::OnDrawInputField("damage", damage_);
}

void Projectile::StoneArrow::OnBeginSensor(b2SensorBeginTouchEvent*, Transform*)
{
    EntityRef().OnDespawn();
}
