#pragma once
#include "../../../../../../BasicallyParameter/Vector2/Vector2.hpp"
#include "../../../../../../Component/Content/Basically/Collider/Collider.h"
#include "../../../../../../Entity/Entity.hpp"
#include "../../../../../AI/BehaviourTree/Node/Abort/AbortNode.h"

namespace Enemy
{
    namespace Behaviour
    {
        namespace Action
        {
            class SetLinearVelocity final
            {
            public:
                explicit SetLinearVelocity(Entity& entity, Vector2 setVelocity);

                Ai::INode::Status operator()() const;

            private:
                Collider& entity_;
                const Vector2 setVelocity_;
            };
        }
    }
}
