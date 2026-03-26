#include "RenderTextContent.h"

#include <DxLib.h>

void RenderTextContent::OnDraw() const
{
    ChangeFont( "DotGothic16", DX_CHARSET_DEFAULT ) ;
    DrawExtendStringF(position_.x_, position_.y_, scale_, scale_, text_.c_str(), color_);
    // DrawExtendStringFToHandle(position_.x_, position_.y_, scale_, scale_, text_.c_str(), color_, fontHandle_);

    // DrawRotaStringFToHandle(position_.x_,
    //                         position_.y_,
    //                         scale_,
    //                         scale_,
    //                         position_.x_,
    //                         position_.y_,
    //                         rotation_,
    //                         color_,
    //                         fontHandle_,
    //                         color_,
    //                         false,
    //                         text_.c_str());
}

int RenderTextContent::RenderOrder() const
{
    return renderOrder_;
}

RenderTextContent::RenderTextContent(const std::string& text, const Vector2& position, const int renderOrder,
                                     const float rotation, const float scale,
                                     const int textColor, const int fondHandle)
    : text_(text), position_(position), renderOrder_(renderOrder), rotation_(rotation), scale_(scale),
      color_(textColor),
      fontHandle_(fondHandle)
{
}
