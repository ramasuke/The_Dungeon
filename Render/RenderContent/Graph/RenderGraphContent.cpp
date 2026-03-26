#include "RenderGraphContent.h"

#include <DxLib.h>

#include "../../../Helper/MyCalculator/MyCalculator.h"

RenderGraphContent::RenderGraphContent(const Vector2& position,
                                       const int renderOrder,
                                       const float rotation,
                                       const float scale,
                                       const int handleId,
                                       const bool isReverseX,
                                       const int screenHandle)
    : position_(position),
      renderOrder_(renderOrder),
      rotation_(rotation),
      scale_(scale),
      handleId_(handleId),
      isReverseX_(isReverseX),
      screenHandle_(screenHandle)
{
}

void RenderGraphContent::OnDraw() const
{
    if (screenHandle_ == DX_SCREEN_BACK)
    {
        DrawRotaGraphF(position_.x_,
                       position_.y_,
                       scale_,
                       MyCalculator::DegToRadF(rotation_),
                       handleId_,
                       true,
                       isReverseX_);
    }
    else
    {
        SetDrawScreen(screenHandle_);
        
        DrawRotaGraphF(position_.x_,
                          position_.y_,
                          scale_,
                          MyCalculator::DegToRadF(rotation_),
                          handleId_,
                          true,
                          isReverseX_);

        SetDrawScreen(DX_SCREEN_BACK);
    }
}
