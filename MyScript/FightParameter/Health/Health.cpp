#include "Health.h"

#include "../../../Libs/ImGui/imgui.h"

void Health::OnDrawInspector()
{
    ImGui::InputInt("value", &value_);
}

bool Health::IsDeath() const
{
    return value_ <= HEALTH_DEATH_VALUE;
}
