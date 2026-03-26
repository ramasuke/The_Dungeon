#pragma once
#include "../../../../../../Entity/Entity.hpp"
#include "../../../../../AI/BehaviourTree/Node/Abort/AbortNode.h"
#include "../../../../Health/Health.h"
#include "../../../../DamageContext/Physics/PhysicsDamageContext.h"

namespace Enemy
{
    namespace Behaviour
    {
        namespace Action
        {
            class OnDamage final
            {
            public:
                explicit OnDamage(Entity& entity, Health& healthRef, std::queue<std::shared_ptr<DamageContext::IDamageContext>>& onDamages);
                
                Ai::INode::Status operator()();

            private:
                Entity& entity_;
                Health& healthRef_;
                std::queue<std::shared_ptr<DamageContext::IDamageContext>>& onDamagesRef_;
                std::vector<std::shared_ptr<DamageContext::IDamageContext>> damageEffectings_;
            };
        }
    }
}
