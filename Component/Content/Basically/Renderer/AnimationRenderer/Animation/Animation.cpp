#include "Animation.h"

#include <DxLib.h>

#include "../../../../../../Helper/ImGui/ImGuiHelper.h"
#include "../../../../../Libs/ImGui/imgui.h"

void Animation::Init()
{
    OnLoadAnimation();
}

void Animation::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("resourcePath", resourcePath_ );
    ImGuiHelper::OnDrawInputField("splitCount"  , splitCount_   );
    if (ImGui::TreeNode("SplitNum"))
    {
        splitNum_.OnDrawDebug();
        ImGui::TreePop();
        ImGui::Spacing();
    }
    if (ImGui::TreeNode("SplitSize"))
    {
        splitSize_.OnDrawDebug();
        ImGui::TreePop();
        ImGui::Spacing();
    }
    ImGuiHelper::OnDrawInputField("effectDuration_frame", effectDuration_frame_);
    ImGui::Checkbox("isRoop", &isRoop_);

    if (ImGui::Button("OnUpdateHandle"))
    {
        OnLoadAnimation();
    }

    if (ImGui::TreeNode("LoadedHandles"))
    {
        for (const auto handle : handles_)
        {
            ImGui::Text(std::to_string(handle).c_str());
        }
        ImGui::TreePop();
        ImGui::Spacing();
    }
}

void Animation::OnLoadAnimation()
{
    std::unique_ptr<int[]> handles;
    handles = std::make_unique<int[]>(splitCount_);

    LoadDivGraph(resourcePath_.c_str(),
                 splitCount_,
                 splitNum_.x_,
                 splitNum_.y_,
                 splitSize_.x_,
                 splitSize_.y_,
                 handles.get()
    );

    handles_.assign(handles.get(), handles.get() + splitCount_);
}
