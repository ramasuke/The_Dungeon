#include "AddPosForTurnDirection.h"

#include "../../../../../../Component/Content/Basically/Renderer/AnimationRenderer/AnimationRenderer.h"

Action::AddPosForTurnDirection::AddPosForTurnDirection(Entity& entity, const Vector2 addPos)
    : entity_(entity), addPos_(addPos)
{
}

Ai::INode::Status Action::AddPosForTurnDirection::operator()() const
{
    entity_.GetComponent<Transform>()->position_ += Vector2(entity_.GetComponent<AnimationRenderer>()->ToTurnDirction().x_ * addPos_.x_, addPos_.y_); 
    return Ai::INode::Status::Success;
}
