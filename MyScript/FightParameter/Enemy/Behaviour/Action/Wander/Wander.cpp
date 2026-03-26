#include "Wander.h"

#include "../../../../../../Component/Content/Basically/Renderer/AnimationRenderer/AnimationRenderer.h"
#include "../../../../../../Entity/Entity.hpp"
#include "../../../../../../Libs/Box2D/include/src/box2d/box2d.h"

Enemy::Behaviour::Action::Wander::Wander(Entity& self, const float moveSpeed,
                                         const Random::Context<int> totalFramesToSuccessContext)
    : collider_(*self.GetComponent<Collider>()),
      moveSpeed_(moveSpeed),
      totalFramesToSuccessContext_(totalFramesToSuccessContext)
{
    if (rand() % 2 == 0)
        direction_ = -1;
    else
        direction_ = 1;

    totalFramesToSuccess_ = Random::Range(totalFramesToSuccessContext.min_, totalFramesToSuccessContext.max_);
    elapsedFrame_ = 0;
}

Ai::INode::Status Enemy::Behaviour::Action::Wander::operator()()
{
    if (elapsedFrame_ >= totalFramesToSuccess_) {
        elapsedFrame_ = 0;
        totalFramesToSuccess_ = Random::Range(totalFramesToSuccessContext_.min_, totalFramesToSuccessContext_.max_);
        
        if (rand() % 2 == 0)
            direction_ = -1;
        else
            direction_ = 1;
        return Ai::INode::Status::Success;
    }

    ++elapsedFrame_;

    const Vector2 moveVec = Vector2(static_cast<float>(direction_), 0.0f) * moveSpeed_;
    b2Body_SetLinearVelocity(collider_.GetBodyId(), moveVec.ToB2Vec2());
    collider_.EntityRef().GetComponent<AnimationRenderer>()->isReverseX_ = moveVec.x_ < 0.0f;
    return Ai::INode::Status::Running;
}