#include "MadnessEnergy.h"

#include "../../../Libs/ImGui/imgui.h"

MadnessEnergy& MadnessEnergy::operator+=(const MadnessEnergy& other)
{
    value_ += other.value_;
    return *this;
}

MadnessEnergy& MadnessEnergy::operator-=(const MadnessEnergy& other)
{
    value_ -= other.value_;
    return *this;
}

void MadnessEnergy::OnDrawInspector()
{
    ImGui::InputInt("value", &value_);
}
