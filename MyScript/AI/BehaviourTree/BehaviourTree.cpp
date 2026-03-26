#include "BehaviourTree.h"

Ai::BehaviourTree::BehaviourTree(std::unique_ptr<INode> node)
{
    behaviourNode_ = std::move(node);
}

void Ai::BehaviourTree::OnUpdate() const
{
    behaviourNode_->Tick();
}
