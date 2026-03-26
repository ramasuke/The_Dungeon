#include "Raycast.h"

#include "../../Libs/Box2D/include/src/box2d/box2d.h"
#include "../../MyScript/Player/PlayerAvatar.h"
#include <DxLib.h>

#include "../../Application/IApplication/IApplication.hpp"

bool Raycast::CheckHit(const Vector2 origin) const
{
    b2RayCastInput input = {};
    input.origin = b2Vec2{origin.x_, origin.y_};
    input.translation = b2Vec2{direction_.x_, direction_.y_};
    input.maxFraction = 1;

    const auto playerBodyId = Player::PlayerAvatar::Model().Collider()->GetBodyId();
    const int shapeCount = b2Body_GetShapeCount(playerBodyId);
    std::vector<b2ShapeId> shapes(shapeCount);
    b2Body_GetShapes(playerBodyId, shapes.data(), shapeCount);

    const b2Transform transform = b2Body_GetTransform(playerBodyId);
    input.origin = b2InvTransformPoint(transform, input.origin);
    input.translation = b2InvRotateVector(transform.q, input.translation);

    bool hit = false;
    b2Vec2 hitPoint = b2Vec2{0, 0};

    b2ShapeId hitShapeId = b2_nullShapeId;

    for (int i = 0; i < shapeCount; ++i)
    {
        if (b2Shape_GetType(shapes[i]) == b2_polygonShape)
        {
            const b2Polygon polygon = b2Shape_GetPolygon(shapes[i]);
            const b2CastOutput result = b2RayCastPolygon(&input, &polygon);
            if (result.hit)
            {
                hit = true;
                hitShapeId = shapes[i];
                hitPoint = b2TransformPoint(transform, input.origin + result.fraction * input.translation);
                break;
            }
        }
    }

    return hit;
}

bool Raycast::CheckHit(const Vector2 origin, const b2BodyId colliderId) const
{
    return IApplication::GetInstance().Physics().CheckHitRaycast(origin, direction_, colliderId);
}

void Raycast::OnDrawInspector(const Vector2 origin)
{
    if (ImGui::TreeNode("direction"))
    {
        direction_.OnDrawDebug();
        ImGui::TreePop();
        ImGui::Spacing();
    }

    OnDrawDebug(origin);
}

void Raycast::OnDrawDebug(const Vector2 origin) const
{
    b2RayCastInput input = {};
    input.origin = b2Vec2{origin.x_, origin.y_};
    input.translation = b2Vec2{direction_.x_, direction_.y_};
    input.maxFraction = 1;

    const auto playerBodyId = Player::PlayerAvatar::Model().Collider()->GetBodyId();
    const int shapeCount = b2Body_GetShapeCount(playerBodyId);
    std::vector<b2ShapeId> shapes(shapeCount);
    b2Body_GetShapes(playerBodyId, shapes.data(), shapeCount);

    const b2Transform transform = b2Body_GetTransform(playerBodyId);
    input.origin = b2InvTransformPoint(transform, input.origin);
    input.translation = b2InvRotateVector(transform.q, input.translation);

    bool hit = false;
    auto hitPoint = b2Vec2{0, 0};

    b2ShapeId hitShapeId = b2_nullShapeId;

    for (int i = 0; i < shapeCount; ++i)
    {
        if (b2Shape_GetType(shapes[i]) == b2_polygonShape)
        {
            const b2Polygon polygon = b2Shape_GetPolygon(shapes[i]);
            const b2CastOutput result = b2RayCastPolygon(&input, &polygon);
            if (result.hit)
            {
                hit = true;
                hitShapeId = shapes[i]; // ← ここでヒットしたShapeIdを記録
                hitPoint = b2TransformPoint(transform, input.origin + result.fraction * input.translation);
                break;
            }
        }
    }

    /*if (hit && B2_IS_NON_NULL(hitShapeId)) {
        auto* obj = static_cast<Entity*>(b2Shape_GetUserData(hitShapeId))->GetComponent<T>;
    }*/

    // ワールド空間での描画
    const b2Vec2 worldStart = b2TransformPoint(transform, input.origin);
    const b2Vec2 worldEnd = b2TransformPoint(transform, input.origin + input.translation);

    if (hit)
    {
        const auto cameraPosition = IApplication::GetInstance().Camera().position_;
        DrawLine(cameraPosition.x_ + worldStart.x,
                 cameraPosition.y_ + worldStart.y,
                 cameraPosition.x_ + hitPoint.x,
                 cameraPosition.y_ + hitPoint.y,
                 GetColor(255, 0, 0));

        DrawCircle(cameraPosition.x_ + hitPoint.x,
                   cameraPosition.y_ + hitPoint.y,
                   5.0f, GetColor(255, 255, 0), TRUE);
    }
    else
    {
        const auto cameraPosition = IApplication::GetInstance().Camera().position_;
        DrawLine(cameraPosition.x_ + worldStart.x,
                 cameraPosition.y_ + worldStart.y,
                 cameraPosition.x_ + hitPoint.x,
                 cameraPosition.y_ + hitPoint.y,
                 GetColor(0, 255, 0));
    }
}
