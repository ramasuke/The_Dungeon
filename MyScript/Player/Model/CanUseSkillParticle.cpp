#include "CanUseSkillParticle.h"

#include "../../../Entity/Entity.hpp"
#include "../../../Libs/ImGui/imgui.h"

void Player::CanUseSkillParticle::OnUpdate()
{
    if (followTransform_ == nullptr)
        return;

    EntityRef().GetComponent<Transform>()->position_ = followTransform_->position_ + followOffsetPos_;
}

void Player::CanUseSkillParticle::OnDrawInspector()
{
    if (ImGui::TreeNode("offset"))
    {
        followOffsetPos_.OnDrawDebug();
        ImGui::TreePop();
        ImGui::Spacing();
    }
}

void Player::CanUseSkillParticle::SetFollowTarget(Transform* followTransform)
{
    followTransform_ = followTransform;
}
