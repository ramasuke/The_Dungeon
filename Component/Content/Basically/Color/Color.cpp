#include "Color.h"

#include <DxLib.h>

#include "../../../../Helper/ImGui/ImGuiHelper.h"

int Color::ToColorId() const
{
    return GetColor(r_, g_, b_);
}

void Color::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("r", r_);
    ImGuiHelper::OnDrawInputField("g", g_);
    ImGuiHelper::OnDrawInputField("b", b_);
}
