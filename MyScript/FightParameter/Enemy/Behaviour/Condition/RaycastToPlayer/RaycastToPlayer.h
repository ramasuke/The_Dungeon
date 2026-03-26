#pragma once
#include "../../../../../../Entity/Entity.hpp"

namespace Enemy
{
    namespace Behaviour
    {
        namespace Condition
        {
            class RaycastToPlayer final
            {
            public:
                explicit RaycastToPlayer(Entity& self, float raycastRangeCoefficient = 100);

                bool operator()() const;

            private:
                Entity& self_;
                float raycastRangeCoefficient_;
            };
        }
    }
}
