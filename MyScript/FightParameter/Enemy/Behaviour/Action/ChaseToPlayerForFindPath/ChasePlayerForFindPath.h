#pragma once

#include <thread>
#include <list>
#include <atomic>
#include <mutex>

#include "../../../../../../Entity/Entity.hpp"
#include "../../../../../AI/BehaviourTree/INode/INode.h"

namespace Enemy
{
    namespace Behaviour
    {
        namespace Action
        {
            class ChasePlayerForFindPath final
            {
            public:
                ChasePlayerForFindPath(Entity& self, float moveSpeed, int maxPathDistance = 10);
                Ai::INode::Status operator()() const;

            private:
                Entity& self_;
                float moveSpeed_;
                int maxPathDistance_;

                mutable std::atomic_bool isSearching_{false};
                mutable std::atomic_bool isReady_{false};
                mutable std::list<Vector2> cachedPath_;
                mutable std::mutex mutex_;
                mutable std::thread pathThread_;
            };
        }
    }
}
