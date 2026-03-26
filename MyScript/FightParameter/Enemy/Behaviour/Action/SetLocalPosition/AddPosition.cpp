#include "AddPosition.h"


Action::AddPosition::AddPosition(Entity& entity, Vector2 addPos)
    : entity_(entity), addPos_(addPos)
{
}

Ai::INode::Status Action::AddPosition::operator()() const
{
    entity_.GetComponent<Transform>()->position_ += addPos_;
    return Ai::INode::Status::Success;
}
