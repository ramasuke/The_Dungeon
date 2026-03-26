#include "PhysicsPower.h"

#include "../../../../../Libs/ImGui/imgui.h"

void PhysicsPower::OnDrawInspector()
{
    ImGui::InputInt("value", &value_);
}

std::string PhysicsPower::ToString() const
{
    return std::to_string(value_);
}

Color PhysicsPower::Color() const
{
    return ::Color(139, 0, 0);
}
