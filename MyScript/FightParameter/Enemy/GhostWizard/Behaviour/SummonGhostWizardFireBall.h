#pragma once
#include "../../../../../Entity/Entity.hpp"
#include "../../../../AI/BehaviourTree/Node/Abort/AbortNode.h"
#include "../../../DamageContext/Fire/FirePower/FirePower.h"

namespace Enemy
{
    namespace Behaviour
    {
        namespace Action
        {
            class SummonGhostWizardFireBall
            {
            public:
                SummonGhostWizardFireBall(Entity& self, float offsetDistance, const FirePower& firePower);

                Ai::INode::Status operator()() const;

            private:
                Entity& self_;
                FirePower firePower_;
                float offsetDistance_;
                const std::string summonFireBallPrefabPath_ = "Resource/Prefab/Projectile-Enemy-SmallFireBall.json";
                const int despawnFireBallDuration_ = 1000;
            };
        }
    }
}
