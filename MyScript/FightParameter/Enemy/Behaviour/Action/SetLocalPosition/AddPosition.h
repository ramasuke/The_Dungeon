#pragma once
#include "../../../../../../Entity/Entity.hpp"
#include "../../../../../AI/BehaviourTree/DSL/BehaviourTreeDSL.h"

namespace Enemy
{
    namespace Behaviour
    {
        namespace Action
        {
            class AddPosition final
            {
            public:
                explicit AddPosition(Entity& entity, Vector2 addPos);

                Ai::INode::Status operator()() const;

            private:
                Entity& entity_;
                const Vector2 addPos_;
            };
        }
    }
}
