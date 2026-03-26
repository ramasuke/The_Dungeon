#include "SetPosition.h"

Action::SetPosition::SetPosition(Entity& entity, const Vector2 position)
    :entity_(entity), setPos_(position)
{
}

Ai::INode::Status Action::SetPosition::operator()() const
{
    entity_.GetComponent<Transform>()->position_ = setPos_;
    return Ai::INode::Status::Success;
}
