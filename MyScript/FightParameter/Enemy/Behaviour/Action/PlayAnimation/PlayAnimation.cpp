#include "PlayAnimation.h"

#include "../../../../../../Component/Content/Basically/Renderer/AnimationRenderer/AnimationRenderer.h"

Enemy::Behaviour::Action::PlayAnimation::PlayAnimation(Entity& self, const std::shared_ptr<Animation>& animation)
    : self_(self), animation_(animation)
{
}

Ai::INode::Status Enemy::Behaviour::Action::PlayAnimation::operator()() const
{
    self_.GetComponent<AnimationRenderer>()->SetAnimation(animation_);
    return Ai::INode::Status::Success;
}
