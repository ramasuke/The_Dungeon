#pragma once
#include <type_traits>

#include "../Entity/Entity.hpp"
#include "../Libs/Box2D/include/src/box2d/box2d.h"
#include "Contact/Begin/IBeginContactable.h"
#include "Sensor/Begin/IBeginSensorable.h"

constexpr float TIME_STEP = 60;
constexpr int SUB_STEP_COUNT = 3;

enum Layer
{
    EnemyLayer = 0x0002,
    PlayerAttackAreaLayer = 0x0010,
    MadnessEnergyLayer = 0x0020,
    EnemyAttackAreaLayer   = 0x0040     
};

class Entity;

class Physics final
{
public:
    Physics();
    void OnUpdateWorld() const;
    void OnUpdateContacts();

    b2BodyId CreateCollider(b2Vec2 position,
                            b2BodyType bodyType,
                            const b2Polygon& polygon,
                            const b2ShapeDef& shapeDef) const;
    static b2Polygon CreateBoxPolygon(Vector2 size);
    static void OnDestroyBody(b2BodyId targetId);

    bool CheckHitRaycast(Vector2 origin, Vector2 direction, b2BodyId checkBody, b2QueryFilter filter = b2DefaultQueryFilter()) const;

private:
    b2BodyId CreateBody(b2Vec2 position, b2BodyType bodyType) const;
    template <typename A, typename B,
              typename = std::enable_if_t<std::is_base_of_v<IBeginContactable<B>, A>>>
    void TryOnBeginContactEvent(b2ContactBeginTouchEvent* contactEvent);
    template <typename A, typename B,
              typename = std::enable_if_t<std::is_base_of_v<IBeginSensorable<B>, A>>>
    void TryOnBeginSensorEvent(b2SensorBeginTouchEvent* sensorEvent);
    // template <typename A, typename B,
    //           typename = std::enable_if_t<std::is_base_of_v<IEndContactable, A>>>
    // void TryOnEndContactEvent(b2ContactEndTouchEvent* contactEvent);
    // template <typename A, typename B,
    //           typename = std::enable_if_t<std::is_base_of_v<IHitContactable, A>>>
    // void TryOnHitContactEvent(b2ContactHitEvent* contactEvent);

    b2WorldDef worldDef_;
    b2WorldId worldId_;
};

template <typename A, typename B, typename>
void Physics::TryOnBeginContactEvent(b2ContactBeginTouchEvent* contactEvent)
{
    auto a = static_cast<Entity*>(b2Shape_GetUserData(contactEvent->shapeIdA));
    
    auto* componentA = static_cast<Entity*>(b2Shape_GetUserData(contactEvent->shapeIdA))->GetComponent<A>();
    auto* componentB = static_cast<Entity*>(b2Shape_GetUserData(contactEvent->shapeIdB))->GetComponent<B>();

    //NOTE: AABBがどの順番でshapId B, Aに登録されているのかわからないので、AABBとBBAAのどちらも検証
    if (componentA == nullptr)
    {
        componentA = static_cast<Entity*>(b2Shape_GetUserData(contactEvent->shapeIdB))->GetComponent<A>();
        componentB = static_cast<Entity*>(b2Shape_GetUserData(contactEvent->shapeIdA))->GetComponent<B>();
    }

    if (componentA != nullptr && componentB != nullptr)
    {
        dynamic_cast<IBeginContactable<B>*>(componentA)->OnBeginContact(contactEvent, componentB);
    }
}

template <typename A, typename B, typename>
void Physics::TryOnBeginSensorEvent(b2SensorBeginTouchEvent* sensorEvent)
{
    auto* componentA = static_cast<Entity*>(b2Shape_GetUserData(sensorEvent->sensorShapeId))->GetComponent<A>();
    auto* componentB = static_cast<Entity*>(b2Shape_GetUserData(sensorEvent->visitorShapeId))->GetComponent<B>();

    //NOTE: AABBがどの順番でshapId B, Aに登録されているのかわからないので、AABBとBBAAのどちらも検証
    if (componentA == nullptr)
    {
        componentA = static_cast<Entity*>(b2Shape_GetUserData(sensorEvent->visitorShapeId))->GetComponent<A>();
        componentB = static_cast<Entity*>(b2Shape_GetUserData(sensorEvent->sensorShapeId))->GetComponent<B>();
    }

    if (componentA != nullptr && componentB != nullptr)
    {
        dynamic_cast<IBeginSensorable<B>*>(componentA)->OnBeginSensor(sensorEvent, componentB);
    }
}

// template <typename A, typename B, typename>
// void Physics::TryOnEndContactEvent(b2ContactEndTouchEvent* contactEvent)
// {
//     auto* componentA = static_cast<Entity*>(b2Shape_GetUserData(contactEvent->shapeIdA))->GetComponent<A>();
//     auto* componentB = static_cast<Entity*>(b2Shape_GetUserData(contactEvent->shapeIdB))->GetComponent<B>();
//
//     if (componentA != nullptr && componentB != nullptr)
//     {
//         dynamic_cast<IBeginContactable<B>*>(componentA)->OnEndContact(contactEvent, componentB);
//     }
// }
//
// template <typename A, typename B, typename>
// void Physics::TryOnHitContactEvent(b2ContactHitEvent* contactEvent)
// {
//     auto* componentA = static_cast<Entity*>(b2Shape_GetUserData(contactEvent->shapeIdA))->GetComponent<A>();
//     auto* componentB = static_cast<Entity*>(b2Shape_GetUserData(contactEvent->shapeIdB))->GetComponent<B>();
//
//     if (componentA != nullptr && componentB != nullptr)
//     {
//         dynamic_cast<IBeginContactable<B>*>(componentA)->OnHitContact(contactEvent, componentB);
//     }
// }
