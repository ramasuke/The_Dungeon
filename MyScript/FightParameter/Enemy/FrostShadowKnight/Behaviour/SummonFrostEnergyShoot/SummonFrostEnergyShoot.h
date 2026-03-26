#pragma once
#include "../../../../../../Entity/Entity.hpp"
#include "../../../../../AI/BehaviourTree/DSL/BehaviourTreeDSL.h"
#include "../../../../DamageContext/Physics/PhysicsPower/PhysicsPower.h"

namespace Enemy
{
    namespace Behaviour
    {
        namespace Action
        {
            class SummonFrostEnergyShoot final
            {
            public:
                SummonFrostEnergyShoot(Entity& self, Vector2 offsetDistance);

                Ai::INode::Status operator()() const;

            private:
                Entity& self_;
                Vector2 offsetDistance_;
                const std::string summonShootPrefabPath_ = "Resource/Prefab/Projectile-Enemy-FrostEnergyShoot.json";
                const int despawnDuration_ = 1000;
            };
        }
    }
}
