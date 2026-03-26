#pragma once
#include "../RenderContent.h"
#include "../../../BasicallyParameter/Vector2/Vector2.hpp"

class RenderTextContent final : public RenderContent
{
public:
    RenderTextContent(const std::string& text, const Vector2& position, int renderOrder, float rotation, float scale, int textColor,
                      int fondHandle);

private:
    void OnDraw() const override;
    int RenderOrder() const override;

    std::string text_;
    Vector2 position_;
    int renderOrder_;
    float rotation_;
    float scale_;
    int color_;
    int fontHandle_;
};
