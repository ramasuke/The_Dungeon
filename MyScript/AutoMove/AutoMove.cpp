#include "AutoMove.h"

#include "../../Component/Content/Basically/Transform/Transform.hpp"
#include "../../Entity/Entity.hpp"
#include "../../Helper/ImGui/ImGuiHelper.h"
#include "../../Libs/ImGui/imgui.h"

void AutoMove::OnUpdate()
{
    if (moveDuration_ < moveDuring_)
        return;
    
    moveDuring_++;

    EntityRef().GetComponent<Transform>()->position_ += move_; 
}

void AutoMove::OnDrawInspector()
{
    if (ImGui::TreeNode("move"))
    {
        move_.OnDrawDebug();
        ImGui::TreePop();
        ImGui::Spacing();
    }
    ImGuiHelper::OnDrawInputField("moveDuration", moveDuration_ );
    ImGuiHelper::OnDrawInputField("moveDuring"  , moveDuring_   );
}
