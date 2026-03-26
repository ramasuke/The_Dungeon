#include "OnLookPlayer.h"

#include "../../../../../../Component/Content/Basically/Renderer/AnimationRenderer/AnimationRenderer.h"
#include "../../../../../Player/PlayerAvatar.h"

Action::OnLookPlayer::OnLookPlayer(Entity& self)
    : self_(self)
{
}

Ai::INode::Status Action::OnLookPlayer::operator()() const
{
    self_.GetComponent<AnimationRenderer>()->isReverseX_ = self_.GetComponent<Transform>()->position_.x_ > Player::PlayerAvatar::Model().Transform()->position_.x_;
    return Ai::INode::Status::Success;
}
