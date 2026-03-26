#include "AbortNode.h"

Ai::INode::Status Ai::AbortNode::Tick()
{
    return Status::Abort;
}
