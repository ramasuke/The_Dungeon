#include "StartMotionArea.h"

#include <DxLib.h>

#include "../../../../Application/IApplication/IApplication.hpp"
#include "../../../../Helper/ImGui/ImGuiHelper.h"

StartMotionArea::StartMotionArea(const Vector2 offset, const Vector2 size)
    : offset_(offset), size_(size)
{
}

void StartMotionArea::OnDrawInspector(const Vector2 origin)
{
    if (ImGui::TreeNode("offset"))
    {
        offset_.OnDrawDebug();
        ImGui::TreePop();
        ImGui::Spacing();
    }
    if (ImGui::TreeNode("size"))
    {
        size_.OnDrawDebug();
        ImGui::TreePop();
        ImGui::Spacing();
    }

    OnDrawDebug(origin);
}

void StartMotionArea::OnDrawDebug(const Vector2 origin) const
{
    DrawBox(IApplication::GetInstance().Camera().position_.x_ + origin.x_ + offset_.x_ - size_.x_,
            IApplication::GetInstance().Camera().position_.y_ + origin.y_ + offset_.y_ - size_.y_,
            IApplication::GetInstance().Camera().position_.x_ + origin.x_ + offset_.x_ + size_.x_,
            IApplication::GetInstance().Camera().position_.y_ + origin.y_ + offset_.y_ + size_.y_,
            GetColor(0, 255, 0),
            false);
}
