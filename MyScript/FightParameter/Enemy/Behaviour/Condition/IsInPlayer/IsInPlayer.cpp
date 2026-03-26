#include "IsInPlayer.h"

#include "../../../../../../Component/Content/Basically/Transform/Transform.hpp"
#include "../../../../../../Entity/Entity.hpp"
#include "../../../../../Player/PlayerAvatar.h"

Enemy::Behaviour::Condition::IsInPlayer::IsInPlayer(Entity& entity, const StartMotionArea startMotionArea)
    : startMotionArea_(startMotionArea), origin_(*entity.GetComponent<Transform>())
{
}

bool Enemy::Behaviour::Condition::IsInPlayer::operator()() const
{
    return
        origin_.position_.x_ + startMotionArea_.Offset().x_ +  startMotionArea_.Size().x_ > Player::PlayerAvatar::Model().Transform()->position_.x_ &&
        origin_.position_.x_ + startMotionArea_.Offset().x_ -  startMotionArea_.Size().x_ < Player::PlayerAvatar::Model().Transform()->position_.x_ &&
        origin_.position_.y_ + startMotionArea_.Offset().y_ -  startMotionArea_.Size().y_ < Player::PlayerAvatar::Model().Transform()->position_.y_ &&
        origin_.position_.y_ + startMotionArea_.Offset().y_ +  startMotionArea_.Size().y_ > Player::PlayerAvatar::Model().Transform()->position_.y_;
}
