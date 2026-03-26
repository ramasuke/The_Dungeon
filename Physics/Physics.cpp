#include "Physics.h"

#include <algorithm>

#include "../Component/Content/Basically/Collider/Box/BoxCollider.h"
#include "../MyScript/FightParameter/MadnessEnergy/MadnessEnergyObject/MadnessEnergyObject.h"
#include "../MyScript/FightParameter/MadnessEnergy/IReceivableMadnessEnergy/IReceivableMadnessEnergy.h"
#include "../MyScript/FightParameter/IReceivableEnemyAttack/IReceivableEnemyAttack.h"
#include "../MyScript/FightParameter/IReceivablePlayerAttack/IReceivablePlayerAttack.h"
#include "../MyScript/Player/PlayerAvatar.h"
#include "../MyScript/Portal/Portal.h"
#include "Sensor/Begin/IBeginSensorable.h"

Physics::Physics()
{
    worldDef_ = b2DefaultWorldDef();
    worldDef_.gravity = b2Vec2{0.0f, 0.0f};
    worldId_ = b2CreateWorld(&worldDef_);
}

void Physics::OnUpdateWorld() const
{
    b2World_Step(worldId_, TIME_STEP, SUB_STEP_COUNT);
}

void Physics::OnUpdateContacts()
{
    const b2ContactEvents contactEvents = b2World_GetContactEvents(worldId_);
    for (int i = 0; i < contactEvents.beginCount; i++)
    {
        TryOnBeginContactEvent<IBeginContactable<IReceivableEnemyAttack>, IReceivableEnemyAttack>(
            contactEvents.beginEvents + i);
    }

    const b2SensorEvents sensorEvents = b2World_GetSensorEvents(worldId_);
    for (int i = 0; i < sensorEvents.beginCount; i++)
    {
        TryOnBeginSensorEvent<IBeginSensorable<IReceivablePlayerAttack>, IReceivablePlayerAttack>(
            sensorEvents.beginEvents + i);
        TryOnBeginSensorEvent<IBeginSensorable<IReceivableEnemyAttack>, IReceivableEnemyAttack>(
            sensorEvents.beginEvents + i);
        TryOnBeginSensorEvent<Player::PlayerAvatar, SkillBookDropItemObject>(sensorEvents.beginEvents + i);
        TryOnBeginSensorEvent<IBeginSensorable<IReceivableMadnessEnergy>, IReceivableMadnessEnergy>(
            sensorEvents.beginEvents + i);
        TryOnBeginSensorEvent<IBeginSensorable<Player::PlayerAvatar>, Player::PlayerAvatar>(
            sensorEvents.beginEvents + i);
        TryOnBeginSensorEvent<IBeginSensorable<Transform>, Transform>(
            sensorEvents.beginEvents + i);
    }
}

b2Polygon Physics::CreateBoxPolygon(const Vector2 size)
{
    return b2MakeBox(size.x_, size.y_);
}

b2BodyId Physics::CreateCollider(
    const b2Vec2 position,
    const b2BodyType bodyType,
    const b2Polygon& polygon,
    const b2ShapeDef& shapeDef) const
{
    const auto bodyId = CreateBody(position, bodyType);
    b2CreatePolygonShape(bodyId, &shapeDef, &polygon);
    return bodyId;
}

b2BodyId Physics::CreateBody(const b2Vec2 position,
                             const b2BodyType bodyType) const
{
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = bodyType;
    bodyDef.position = position;
    return b2CreateBody(worldId_, &bodyDef);
}

void Physics::OnDestroyBody(const b2BodyId targetId)
{
    b2DestroyBody(targetId);
}

bool Physics::CheckHitRaycast(const Vector2 origin, const Vector2 direction, const b2BodyId checkBody,
                              const b2QueryFilter filter) const
{
    // 最も近いヒットを取得
    const b2RayResult result = b2World_CastRayClosest(worldId_, origin.ToB2Vec2(), direction.ToB2Vec2(), filter);

    // ヒットしていなければ false
    if (!result.hit)
        return false;

    // ヒットしたシェイプのボディIDを取得
    const b2BodyId hitBody = b2Shape_GetBody(result.shapeId);

    // 指定されたボディと一致するかどうかを比較
    return hitBody.index1 == checkBody.index1 &&
        hitBody.world0 == checkBody.world0 &&
        hitBody.generation == checkBody.generation;
}
