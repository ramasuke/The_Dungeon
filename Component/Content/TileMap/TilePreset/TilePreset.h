#pragma once
#include <DxLib.h>

#include "../../../../BasicallyParameter/Vector2/Vector2.hpp"

namespace Tile
{
    ///NOTE: 値オブジェクト推奨
    struct TilePreset final
    {
        TilePreset(int id,
                   float cellTransformScale,
                   bool enableAttachCollider,
                   const Vector2& cellColliderScale,
                   int colliderBodyTypeId,
                   int renderOrder,
                   int renderHandleId);

        int RenderHandleId() const { return renderHandleId_; }

        const int id_ = -1;
        const float cellTransformScale_ = 0;
        const bool enableAttachCollider_ = false;
        const Vector2 cellColliderScale_ = Vector2(1, 1);
        const int colliderBodyTypeId_ = 0;
        const int renderOrder_ = -10;

    private:
        int renderHandleId_ = -1;
    };
}
