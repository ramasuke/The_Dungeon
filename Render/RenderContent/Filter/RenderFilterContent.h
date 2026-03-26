#pragma once
#include "../RenderContent.h"
#include "../../../Component/Content/Basically/Color/Color.h"

class RenderFilterContent final : public RenderContent
{
public:
    RenderFilterContent(int screenHandle,
                        int filterType,
                        int filterParam,
                        int filterBrightness,
                        Color transParentColor,
                        int alpha,
                        int renderOrder);

private:
    void OnDraw() const override;
    int RenderOrder() const override;
    
    const int     screenHandle_;
    const int     filterType_;
    const int     filterParam_;
    const int     filterBrihtness;
    const Color   transParentColor_;
    const int     alpha_;
    const int     renderOrder_;
};
