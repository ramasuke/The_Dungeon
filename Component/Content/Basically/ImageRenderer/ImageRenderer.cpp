#include "ImageRenderer.h"

#include <DxLib.h>

#include "../../../../Entity/Entity.hpp"
#include "../../../../Helper/ImGui/ImGuiHelper.h"
#include "../../../../Render/Render.h"

void ImageRenderer::Init()
{
    transformRef_   = EntityRef().GetComponent<Transform>();
    renderHandleId_ = LoadGraph(renderSpriteFilePath_.c_str());
}

void ImageRenderer::OnDraw()
{
    if (!transformRef_)
        return;

    Render::DrawRotaGraphF(transformRef_->position_,
                           transformRef_->rotation_,
                           transformRef_->scale_,
                           renderOrder_,
                           renderHandleId_,
                           isReverseX_);
}

void ImageRenderer::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("renderSpriteFilePath", renderSpriteFilePath_ );
    ImGuiHelper::OnDrawInputField("renderOrder"         , renderOrder_          );
    ImGui::Text(std::to_string(renderHandleId_).c_str());
    if (ImGui::Button("OnUpdateRenderId"))
    {
        renderHandleId_ = LoadGraph(renderSpriteFilePath_.c_str());
    }
    ImGui::Checkbox("isReverseX", &isReverseX_);
}