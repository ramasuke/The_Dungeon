#pragma once
#include "../../../../../../Entity/Entity.hpp"
#include "../../../../../AI/BehaviourTree/Node/Wait/WaitNode.h"

namespace Enemy
{
    namespace Behaviour
    {
        namespace Action
        {
            class SurprisedSign final
            {
            public:
                explicit SurprisedSign(Entity& self, float offsetPosY);

                Ai::INode::Status operator()() const;

            private:
                Entity& self_;
                float offsetPosY_;
                static constexpr auto SURPRISED_PREFAB_PATH = "Resource/Prefab/SurprisedSign.json";
            };
        }
    }
}
