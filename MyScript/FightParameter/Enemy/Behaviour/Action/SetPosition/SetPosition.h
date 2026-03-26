#pragma once
#include "../../../../../../Entity/Entity.hpp"
#include "../../../../../AI/BehaviourTree/DSL/BehaviourTreeDSL.h"

namespace Enemy
{
    namespace Behaviour
    {
        namespace Action
        {
            class SetPosition final
            {
            public:
                explicit SetPosition(Entity& entity, Vector2 position);

                Ai::INode::Status operator()() const;

            private:
                Entity& entity_;
                const Vector2 setPos_;
            };
        }
    }
}