#pragma once
#include "../../../../../AI/BehaviourTree/DSL/BehaviourTreeDSL.h"
namespace Enemy
{
    namespace Behaviour
    {
        namespace Action
        {
            class OnLookPlayer final
            {
            public:
                explicit OnLookPlayer(Entity& self);

                Ai::INode::Status operator()() const;
                
            private:
                Entity& self_;
            };
        }
    }
}
