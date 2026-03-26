#pragma once
#include <DxLib.h>

#include "../RenderContent.h"
#include "../../../BasicallyParameter/Vector2/Vector2.hpp"

class RenderGraphContent final : public RenderContent
{
public:
    RenderGraphContent(const Vector2& position,
                       int renderOrder,
                       float rotation,
                       float scale,
                       int handleId,
                       bool isReverseX,
                       int screenHandle = DX_SCREEN_BACK);

private:
    void    OnDraw()        const override;
    int     RenderOrder()   const override { return renderOrder_; }

    Vector2 position_;
    int     renderOrder_;
    float   rotation_;
    float   scale_;
    int     handleId_;
    bool    isReverseX_;
    int     screenHandle_ = -1;
};
