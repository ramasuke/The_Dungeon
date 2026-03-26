#pragma once

#include "../../../../../../Component/Content/Basically/Collider/Collider.h"
#include "../../../../../../Helper/Random/Random.h"
#include "../../../../../AI/BehaviourTree/Node/Action/ActionNode.h"

namespace Enemy
{
    namespace Behaviour
    {
        namespace Action
        {
            class Wander final
            {
            public:
                Wander(Entity& self, float moveSpeed, Random::Context<int> totalFramesToSuccessContext);

                Ai::INode::Status operator()();

            private:
                Collider& collider_;
                float moveSpeed_;

                int totalFramesToSuccess_ = 0;
                Random::Context<int> totalFramesToSuccessContext_;
                mutable int direction_ = 1;
                mutable int elapsedFrame_ = 0;
            };
        }
    }
}
