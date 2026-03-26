#include "SpawnAttackAreaModel.h"


#include "../../../Component/Content/Basically/Transform/Transform.hpp"
#include <DxLib.h>

#include "../../../Application/IApplication/IApplication.hpp"
#include "../../../Entity/Entity.hpp"

SpawnAttackAreaModel::SpawnAttackAreaModel(const Vector2 offset, const Vector2 size, const int despawnDuration)
    : offset_(offset), size_(size), despawnDuration_(despawnDuration)
{
}

void SpawnAttackAreaModel::OnDrawInspector(Entity& spawnOffset)
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
    ImGui::InputInt("despawnDuration", &despawnDuration_);
    OnDrawDebug(spawnOffset);
}

void SpawnAttackAreaModel::OnDrawDebug(Entity& spawnOffset) const
{
    const auto spawnOffsetPos = spawnOffset.GetComponent<Transform>()->position_;
    DrawBox(IApplication::GetInstance().Camera().position_.x_ + spawnOffsetPos.x_ + offset_.x_ - size_.x_,
            IApplication::GetInstance().Camera().position_.y_ + spawnOffsetPos.y_ + offset_.y_ - size_.y_,
            IApplication::GetInstance().Camera().position_.x_ + spawnOffsetPos.x_ + offset_.x_ + size_.x_,
            IApplication::GetInstance().Camera().position_.y_ + spawnOffsetPos.y_ + offset_.y_ + size_.y_,
            GetColor(0, 255, 0),
            false);
}
