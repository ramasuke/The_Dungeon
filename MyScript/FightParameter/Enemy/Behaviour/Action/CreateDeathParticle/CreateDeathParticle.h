#pragma once

#include "../../../../../../Component/Content/Basically/Transform/Transform.hpp"
#include "../../../../../../Entity/Entity.hpp"
#include "../../../../../AI/BehaviourTree/INode/INode.h"

namespace Enemy
{
    namespace Behaviour
    {
        namespace Action
        {
            class CreateDeathParticle final
            {
            public:
                explicit CreateDeathParticle(Entity& entity);

                Ai::INode::Status operator()() const;

            private:
                Transform* transform_;
                constexpr static auto PREFAB_PATH = "Resource/Prefab/OnDeathEnemyParticle.json";
            };
        }
    }
}
