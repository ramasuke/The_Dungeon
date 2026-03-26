#include "RenderFilterContent.h"

#include "../Graph/RenderGraphContent.h"

RenderFilterContent::RenderFilterContent(
    const int   screenHandle,
    const int   filterType,
    const int   filterParam,
    const int   filterBrightness,
    const Color transParentColor,
    const int   alpha,
    const int   renderOrder)
    : screenHandle_(screenHandle),
      filterType_(filterType),
      filterParam_(filterParam),
      filterBrihtness(filterBrightness),
      transParentColor_(transParentColor),
      alpha_(alpha),
      renderOrder_(renderOrder)
{
}

void RenderFilterContent::OnDraw() const
{
    GraphFilter(screenHandle_, filterType_, filterParam_, filterBrihtness, TRUE, transParentColor_.ToColorId(), 0);
}

int RenderFilterContent::RenderOrder() const
{
    return renderOrder_;
}
