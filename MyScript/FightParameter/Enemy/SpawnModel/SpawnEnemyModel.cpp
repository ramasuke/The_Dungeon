#include "SpawnEnemyModel.h"

#include <DxLib.h>

#include "../../../../Application/IApplication/IApplication.hpp"
#include "../../../../Libs/ImGui/imgui.h"

void SpawnEnemyModel::OnDrawInspector()
{
    if (ImGui::TreeNode("onSpawnEnemyPos"))
    {
        onSpawnEnemyPos_.OnDrawDebug();
        ImGui::TreePop();
        ImGui::Spacing();
    }
    char nameBuffer[256];
    strncpy_s(nameBuffer, spawnEnemyPrefabPath_.c_str(), sizeof(nameBuffer));
    ImGui::InputText("spawnEnemyPrefabPath: ", nameBuffer, sizeof(nameBuffer));
    spawnEnemyPrefabPath_ = nameBuffer;
    OnDrawDebug();
}

void SpawnEnemyModel::OnDrawDebug() const
{
    DrawCircle(
        static_cast<int>(onSpawnEnemyPos_.x_ + IApplication::GetInstance().Camera().position_.
            x_),
        static_cast<int>(onSpawnEnemyPos_.y_ + IApplication::GetInstance().Camera().position_.
            y_),
        4, GetColor(255, 255, 0), 1);
}

Vector2 SpawnEnemyModel::Position() const
{
    return onSpawnEnemyPos_;
}

std::string SpawnEnemyModel::PrefabPath() const
{
    return spawnEnemyPrefabPath_;
}
