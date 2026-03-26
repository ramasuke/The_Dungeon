#include "SmallFireBall.h"

#include "../../../../Entity/Entity.hpp"
#include "../../../../Helper/MyCalculator/MyCalculator.h"
#include "../../../../Libs/Box2D/include/src/box2d/box2d.h"
#include "../../../Player/PlayerAvatar.h"
#include "../../Enemy/BoxAttackArea/EnemyBoxAttackArea.h"

void Projectile::SmallFireBall::Init()
{
    EntityRef().GetComponent<AnimationRenderer>()->SetAnimation(shootAnimation_);
}

void Projectile::SmallFireBall::OnUpdate()
{
    auto a = MyCalculator::GetDirection(EntityRef().GetComponent<Transform>()->rotation_).ToB2Vec2();
    b2Body_SetLinearVelocity(EntityRef().GetComponent<Collider>()->GetBodyId(), (MyCalculator::GetDirection(EntityRef().GetComponent<Transform>()->rotation_) * speed_).ToB2Vec2());
}

void Projectile::SmallFireBall::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("shootAnimation", shootAnimation_);
    ImGuiHelper::OnDrawInputField("speed", speed_);
}

void Projectile::SmallFireBall::OnBeginSensor(b2SensorBeginTouchEvent*, Transform* target)
{
    EntityRef().OnDespawn();
}
