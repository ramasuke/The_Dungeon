#include "TextRenderer.h"

#include <DxLib.h>

#include "../../../../../Application/IApplication/IApplication.hpp"
#include "../../../../../Entity/Entity.hpp"
#include "../../../../../Libs/ImGui/imgui.h"
#include "../../../../../Render/Render.h"

void TextRenderer::Init()
{
    transformRef_ = EntityRef().GetComponent<Transform>();
}

void TextRenderer::OnDraw()
{
    if (transformRef_ == nullptr)
        return;

    if (isWorldSpace_)
    {
        Render::DrawTextF(text_,
                          transformRef_->position_,
                          transformRef_->rotation_,
                          transformRef_->scale_,
                          renderOrder_,
                          color_.ToColorId(),
                          fontHandleId_);
    }
    else
    {
        Render::DrawTextF(text_,
                          IApplication::GetInstance().Camera().position_ + transformRef_->position_,
                          transformRef_->rotation_,
                          transformRef_->scale_,
                          renderOrder_,
                          color_.ToColorId(),
                          fontHandleId_);
    }
}

void TextRenderer::OnDrawInspector()
{
    ImGui::Checkbox("worldSpace", &isWorldSpace_);
    char nameBuffer[256];
    strncpy_s(nameBuffer, text_.c_str(), sizeof(nameBuffer));
    ImGui::InputText("text", nameBuffer, sizeof(nameBuffer));
    text_ = nameBuffer;
    ImGui::InputInt("renderOrder", &renderOrder_);

    if (ImGui::TreeNode("color"))
    {
        color_.OnDrawInspector();
        ImGui::TreePop();
        ImGui::Spacing();
    }

    char nameBuffer1[256];
    strncpy_s(nameBuffer1, fontName_.c_str(), sizeof(nameBuffer1));
    ImGui::InputText("fontFilePath: ", nameBuffer1, sizeof(nameBuffer1));
    fontName_ = nameBuffer1;

    if (ImGui::Button("OnUpdateFont"))
    {
        fontHandleId_ = CreateFontToHandle("DotGothic16", 20, 1, DX_FONTTYPE_ANTIALIASING_8X8);
    }

    ImGui::Text(std::to_string(fontHandleId_).c_str());
}
