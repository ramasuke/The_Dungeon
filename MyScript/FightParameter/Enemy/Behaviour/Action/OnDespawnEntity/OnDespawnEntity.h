#pragma once

#include "../../../../../../Entity/Entity.hpp"
#include "../../../../../AI/BehaviourTree/INode/INode.h"

namespace Enemy
{
    namespace Behaviour
    {
        namespace Action
        {
            class OnDespawnEntity final
            {
            public:
                explicit OnDespawnEntity(Entity& self);

                Ai::INode::Status operator()() const;

            private:
                Entity& self_;
            };
        }
    }
}
