#include "ReplacableTile.h"

#include <DxLib.h>

#include "../../../../Application/IApplication/IApplication.hpp"

void ReplacableTile::SetParameter(TileMap* tileMap, const float cellSize)
{
    tileMapRef_ = tileMap;
    gridCellSize_ = cellSize;
}

void ReplacableTile::Init()
{
    transform_ = EntityRef().GetComponent<Transform>();
}

void ReplacableTile::OnUpdate()
{
    
}

void ReplacableTile::OnEditorUpdate()
{
    enableClickDuring_++;

    if (enableClickDuration_ > enableClickDuring_)
        return;
    
    switch (GetMouseInput())
    {
    case MOUSE_INPUT_LEFT:
        int clickPosX;
        int clickPosY;
        GetMousePoint(&clickPosX, &clickPosY);

        if (IApplication::GetInstance().Camera().position_.x_ + transform_->position_.x_ - gridCellSize_ < clickPosX &&
            IApplication::GetInstance().Camera().position_.x_ + transform_->position_.x_ + gridCellSize_ > clickPosX &&
            IApplication::GetInstance().Camera().position_.y_ + transform_->position_.y_ - gridCellSize_ < clickPosY &&
            IApplication::GetInstance().Camera().position_.y_ + transform_->position_.y_ + gridCellSize_ > clickPosY)
        {
            tileMapRef_->OnReplaceTile(&EntityRef());
        }
    default:
        break;
    }
}

void ReplacableTile::OnDrawInspector()
{
    
}
