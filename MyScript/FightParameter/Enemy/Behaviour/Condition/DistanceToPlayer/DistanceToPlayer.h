#pragma once
#include "../../../../../../Entity/Entity.hpp"

namespace Enemy
{
    namespace Behaviour
    {
        namespace Condition
        {
            class DistanceToPlayer final
            {
            public:
                explicit DistanceToPlayer(Entity& self, float range);

                bool operator()() const;

            private:
                Entity& self_;
                float range_;   
            };
        }
    }
}
