#include "ThunderPower.h"

#include "../../../../../Entity/Entity.hpp"
#include "../../../../../Libs/ImGui/imgui.h"

void ThunderPower::OnDrawInspector()
{
    ImGui::InputInt("value", &value_);
    ImGui::InputInt("numbDuration", &numbDuration_);
}

std::string ThunderPower::ToString() const
{
    return std::to_string(value_);
}

Color ThunderPower::Color() const
{
    return ::Color(255, 200, 0);
}
