#pragma once
#include "../../../../../AI/BehaviourTree/DSL/BehaviourTreeDSL.h"

namespace Enemy
{
    namespace Behaviour
    {
        namespace Action
        {
            class AddPosForTurnDirection final
            {
            public:
                explicit AddPosForTurnDirection(Entity& entity, Vector2 addPos);

                Ai::INode::Status operator()() const;

            private:
                Entity& entity_;
                const Vector2 addPos_;
            };
        }
    }
}