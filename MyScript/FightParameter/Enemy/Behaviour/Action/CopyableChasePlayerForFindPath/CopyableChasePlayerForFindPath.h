#pragma once
#include <memory>

#include "../ChaseToPlayerForFindPath/ChasePlayerForFindPath.h"

namespace Enemy
{
    namespace Behaviour
    {
        namespace Action
        {
            struct CopyableChasePlayerForFindPath
            {
                CopyableChasePlayerForFindPath(Entity& self, float mv);

                Ai::INode::Status operator()() const;

            private:
                std::shared_ptr<Enemy::Behaviour::Action::ChasePlayerForFindPath> impl_;
            };

        }
    }
}