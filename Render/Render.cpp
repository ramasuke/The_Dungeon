#include "Render.h"

#include <vector>
#include <algorithm>

#include "../Helper/MyCalculator/MyCalculator.h"
#include "RenderContent/Filter/RenderFilterContent.h"
#include "RenderContent/Graph/RenderGraphContent.h"
#include "RenderContent/Text/RenderTextContent.h"

static std::vector<std::unique_ptr<RenderContent>> renders;

void Render::OnDrawAllRender()
{
    std::sort(renders.begin(), renders.end(),
              [](const std::unique_ptr<RenderContent>& a, const std::unique_ptr<RenderContent>& b)
              {
                  return a->RenderOrder() < b->RenderOrder();
              });

    for (const auto& render : renders)
    {
        render->OnDraw();
    }

    renders.clear();
}

void Render::DrawRotaGraphF(const Vector2 position,
                            const float rotation,
                            const float scale,
                            const int renderOrder,
                            const int handleId,
                            const bool isReverseX,
                            const int screenHandle)
{
    renders.push_back(
        std::make_unique<RenderGraphContent>(position, renderOrder, rotation, scale, handleId, isReverseX,
                                             screenHandle));
}

void Render::DrawTextF(const std::string& text,
                       const Vector2 position,
                       const float rotation,
                       const float scale,
                       const int renderOrder,
                       const int color,
                       const int fondHandle)
{
    renders.push_back(
        std::make_unique<RenderTextContent>(text, position, renderOrder, rotation, scale, color, fondHandle));
}

void Render::DrawFilter(int screenHandle, int filterType, int filterParam, int filterBrightness, Color transParentColor,
                        int alpha, int renderOrder)
{
    renders.push_back(
        std::make_unique<RenderFilterContent>(screenHandle, filterType, filterParam, filterBrightness, transParentColor,
                                              alpha, renderOrder));
}
