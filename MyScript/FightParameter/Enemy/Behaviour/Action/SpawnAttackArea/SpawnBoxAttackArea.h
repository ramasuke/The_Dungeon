#pragma once
#include "../../../../../../Component/Content/Basically/Renderer/AnimationRenderer/Animation/Animation.h"
#include "../../../../../../Entity/Entity.hpp"
#include "../../../../../AI/BehaviourTree/Node/Action/ActionNode.h"
#include "../../../../DamageContext/Interface/IDamageContext.h"
#include "../../../../SpawnAttackAreaModel/SpawnAttackAreaModel.h"

namespace Enemy
{
    namespace Behaviour
    {
        namespace Action
        {
            class SpawnBoxAttackArea final
            {
            public:
                SpawnBoxAttackArea(Entity& self, const std::shared_ptr<DamageContext::IDamageContext>& damage, const SpawnAttackAreaModel& attackAreaParam);

                Ai::INode::Status operator()() const;

            private:
                Entity& self_;
                const std::shared_ptr<DamageContext::IDamageContext> damage_;
                const SpawnAttackAreaModel attackAreaParam_;

                static constexpr auto ENEMY_BOX_ATTACK_AREA_PREFAB_PATH = "Resource/Prefab/Enemy-BoxAttackArea.json";
            };
        }
    }
}
