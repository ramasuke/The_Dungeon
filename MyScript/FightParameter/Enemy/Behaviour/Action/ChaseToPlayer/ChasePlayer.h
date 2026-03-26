#pragma once
#include "../../../../../Component/Content/Basically/Collider/Box/BoxCollider.h"
#include "../../../../../AI/BehaviourTree/BehaviourTree.h"

namespace Enemy
{
    namespace Behaviour
    {
        namespace Action
        {
            class ChasePlayer final
            {
            public:
                ChasePlayer(Entity& self, float speed);

                Ai::INode::Status operator()() const;

            private:
                Entity& self_;
                float speed_;
            };
        }
    }
}
