#include "SpawnEntranceModel.h"

#include <DxLib.h>

#include "../../../../Application/IApplication/IApplication.hpp"
#include "../../../../Helper/ImGui/ImGuiHelper.h"

SpawnEntranceModel::SpawnEntranceModel(const Vector2 position, const Vector2 areaSize): position_(position),
    areaSize_(areaSize)
{
}

void SpawnEntranceModel::OnDrawInspector()
{
    if (ImGui::TreeNode("position"))
    {
        position_.OnDrawDebug();
        ImGui::TreePop();
        ImGui::Spacing();
    }
    if (ImGui::TreeNode("areaSize"))
    {
        areaSize_.OnDrawDebug();
        ImGui::TreePop();
        ImGui::Spacing();
    }
    OnDrawDebug();
}

void SpawnEntranceModel::OnDrawDebug() const
{
    DrawBox(IApplication::GetInstance().Camera().position_.x_ + position_.x_ - areaSize_.x_,
            IApplication::GetInstance().Camera().position_.y_ + position_.y_ - areaSize_.y_,
            IApplication::GetInstance().Camera().position_.x_ + position_.x_ + areaSize_.x_,
            IApplication::GetInstance().Camera().position_.y_ + position_.y_ + areaSize_.y_,
            GetColor(0, 255, 0),
            false);
}
