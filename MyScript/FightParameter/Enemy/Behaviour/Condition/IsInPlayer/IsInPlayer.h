#pragma once
#include "../../../StartAttackArea/StartMotionArea.h"

class Transform;
class Entity;

namespace Enemy
{
    namespace Behaviour
    {
        namespace Condition
        {
            class IsInPlayer
            {
            public:
                explicit IsInPlayer(Entity& entity, StartMotionArea startMotionArea);

                bool operator()() const;

            private:
                const StartMotionArea startMotionArea_;
                
                Transform& origin_;
            };
        }
    }
}
