#pragma once
#include "../../../Health/Health.h"

namespace Enemy
{
    namespace Behaviour
    {
        namespace Condition
        {
            class IsDeath final
            {
            public:
                explicit IsDeath(Health& hp);

                bool operator()() const;
                
            private:
                Health& hp_;
            };
        }
    }
}
