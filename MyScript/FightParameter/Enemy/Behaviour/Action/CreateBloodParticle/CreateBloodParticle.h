#pragma once
#include "../../../../../../Entity/Entity.hpp"
#include "../../../../../AI/BehaviourTree/Node/Abort/AbortNode.h"

namespace Enemy
{
    namespace Behaviour
    {
        namespace Action
        {
            class CreateBloodParticle final
            {
            public:
                explicit CreateBloodParticle(Entity& self);
                
                Ai::INode::Status operator()() const;
                
            private:
                Entity& self_;
                const std::string BloodParticlePrefabPath = "Resource/Prefab/BloodParticle.json";
            };
        }
    }
}
