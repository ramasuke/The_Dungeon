#pragma once
#include "../../../../../../Component/Content/Basically/Renderer/AnimationRenderer/Animation/Animation.h"
#include "../../../../../../Entity/Entity.hpp"
#include "../../../../../AI/BehaviourTree/Node/Action/ActionNode.h"

namespace Enemy
{
    namespace Behaviour
    {
        namespace Action
        {
            class PlayAnimation final
            {
            public:
                PlayAnimation(Entity& self, const std::shared_ptr<Animation>& animation);

                Ai::INode::Status operator()() const;

            private:
                Entity& self_;
                std::shared_ptr<Animation> animation_;
            };
        }
    }
}
