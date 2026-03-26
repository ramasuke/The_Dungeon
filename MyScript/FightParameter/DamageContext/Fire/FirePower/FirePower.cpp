#include "FirePower.h"

#include "../../../../../Helper/ImGui/ImGuiHelper.h"

void FirePower::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("hitDamage", hitDamage_);
    ImGuiHelper::OnDrawInputField("burnDamage", burnDamage_);
    ImGuiHelper::OnDrawInputField("burnDuration", burnDuration_);
}

std::string FirePower::ToString() const
{
    return std::to_string(hitDamage_);
}

Color FirePower::Color() const
{
    return ::Color(255, 0, 0);
}
