#include "SpriteRenderer.h"

#include <DxLib.h>

#include "../../../../../Application/IApplication/IApplication.hpp"
#include "../../../../../Helper/MyCalculator/MyCalculator.h"
#include "../../../../../Libs/ImGui/imgui.h"
#include "../../../../../Render/Render.h"

void SpriteRenderer::SetRenderResourcePath(const std::string& renderResourcePath)
{
    renderResourcePath_ = renderResourcePath;
}

void SpriteRenderer::SetRenderHandleId(const int renderHandleId)
{
    renderHandleId_ = renderHandleId;
}

void SpriteRenderer::SetRenderOrder(const int renderOrder)
{
    renderOrder_ = renderOrder;
}

void SpriteRenderer::Init()
{
    transformRef_ = EntityRef().GetComponent<Transform>();
    renderHandleId_ = LoadGraph(renderResourcePath_.c_str());
}

void SpriteRenderer::OnDraw()
{
    if (!transformRef_)
        return;

    Render::DrawRotaGraphF(IApplication::GetInstance().Camera().position_ + transformRef_->position_,
                           transformRef_->rotation_,
                           transformRef_->scale_,
                           renderOrder_,
                           renderHandleId_,
                           isReverseX_);
}

void SpriteRenderer::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("renderResourcePath"  , renderResourcePath_   );
    ImGuiHelper::OnDrawInputField("renderOrder"         , renderOrder_          );
    ImGui::Text(std::to_string(renderHandleId_).c_str());
    if (ImGui::Button("OnUpdateRenderId"))
    {
        renderHandleId_ = LoadGraph(renderResourcePath_.c_str());
    }
    ImGui::Checkbox("isReverseX", &isReverseX_);
}
