#include "SetIsReverse.h"

#include "../AnimationRenderer.h"
#include "../../../../../../Entity/Entity.hpp"

void SetIsReverse::Init()
{
    EntityRef().GetComponent<AnimationRenderer>()->isReverseX_ = isReverseX_;
}

void SetIsReverse::OnDrawInspector()
{
    ImGui::Checkbox("isReverseX", &isReverseX_);
}
