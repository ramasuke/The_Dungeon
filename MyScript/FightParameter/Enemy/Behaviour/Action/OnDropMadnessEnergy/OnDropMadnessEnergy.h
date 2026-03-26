#pragma once

#include "../../../../../../Entity/Entity.hpp"
#include "../../../../../AI/BehaviourTree/BehaviourTree.h"
#include "../../../../MadnessEnergy/MadnessEnergy.h"

namespace Enemy
{
    namespace Behaviour
    {
        namespace Action
        {
            class OnDropMadnessEnergy final
            {
            public:
                OnDropMadnessEnergy(Entity& self, int comboCount, MadnessEnergy energy);

                Ai::INode::Status operator()() const;

            private:
                Entity& self_;
                int count_;
                MadnessEnergy energy_;
            };
        }
    }
}
