#include "Transform.hpp"

#include "../../../../Helper/MyCalculator/MyCalculator.h"
#include "../../../../Libs/ImGui/imgui.h"

void Transform::Init()
{
}

void Transform::Awake()
{
}

void Transform::OnUpdate()
{
}

void Transform::OnDraw()
{
}

void Transform::OnDrawInspector()
{
    if (ImGui::TreeNode("Position"))
    {
        position_.OnDrawDebug();
        ImGui::TreePop();
        ImGui::Spacing();
    }
    if (ImGui::TreeNode("Rotation"))
    {
        ImGui::InputFloat("z", &rotation_);
        ImGui::TreePop();
        ImGui::Spacing();
    }
    if (ImGui::TreeNode("Scale"))
    {
        ImGui::InputFloat("scale", &scale_);
        ImGui::TreePop();
        ImGui::Spacing();
    }
}
