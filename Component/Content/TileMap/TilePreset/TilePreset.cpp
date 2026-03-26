#include "TilePreset.h"

#include <DxLib.h>


Tile::TilePreset::TilePreset(
    const int id,
    const float cellTransformScale,
    const bool enableAttachCollider,
    const Vector2& cellColliderScale,
    const int colliderBodyTypeId,
    const int renderOrder,
    const int renderHandleId)
    : id_(id),
      cellTransformScale_(cellTransformScale),
      enableAttachCollider_(enableAttachCollider),
      cellColliderScale_(cellColliderScale),
      colliderBodyTypeId_(colliderBodyTypeId),
      renderOrder_(renderOrder),
      renderHandleId_(renderHandleId)
{
    
}
