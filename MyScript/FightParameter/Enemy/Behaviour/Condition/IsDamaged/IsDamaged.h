#pragma once
#include <queue>

#include "../../../../DamageContext/Physics/PhysicsDamageContext.h"

namespace Enemy
{
    namespace Behaviour
    {
        namespace Condition
        {
            class IsDamaged final
            {
            public:
                explicit IsDamaged(std::queue<std::shared_ptr<DamageContext::IDamageContext>>& onDamages);

                bool operator()() const;

            private:
                std::queue<std::shared_ptr<DamageContext::IDamageContext>>& onDamagesRef_;
            };
        }
    }
}
