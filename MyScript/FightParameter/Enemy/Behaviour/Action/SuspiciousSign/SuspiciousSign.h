#pragma once
#include "../../../../../../Entity/Entity.hpp"
#include "../../../../../AI/BehaviourTree/Node/Action/ActionNode.h"

namespace Enemy
{
    namespace Behaviour
    {
        namespace Action
        {
            class SuspiciousSign final
            {
            public:
                explicit SuspiciousSign(Entity& self, float offsetPosY);

                Ai::INode::Status operator()() const;

            private:
                Entity& self_;
                float offsetPosY_;
                static constexpr auto SUSPICIOUS_PREFAB_PATH = "Resource/Prefab/QuestionSign.json";
            };
        }
    }
}
