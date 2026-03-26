#include "OnDamage.h"


#include "../../../../../DamageNotation/Physics/DamageNotation.h"
#include "../../../../IReceivablePlayerAttack/IReceivablePlayerAttack.h"

Enemy::Behaviour::Action::OnDamage::OnDamage(Entity& entity, Health& healthRef,
                                             std::queue<std::shared_ptr<DamageContext::IDamageContext>>& onDamages)
    : entity_(entity), healthRef_(healthRef), onDamagesRef_(onDamages)
{
}

Ai::INode::Status Enemy::Behaviour::Action::OnDamage::operator()()
{
    while (!onDamagesRef_.empty())
    {
        auto damageContext = onDamagesRef_.front();
        if (damageContext != nullptr)
        {
            damageContext->OnStartEffect(entity_, healthRef_);
            Entity::Spawn<DamageNotation>(DAMAGE_NOTATION_PREFAB_PATH, entity_.GetComponent<Transform>()->position_)->
                SetNotation(damageContext->GetParam().ToString(), damageContext->GetParam().Color());
            damageEffectings_.push_back(damageContext);
        }
        onDamagesRef_.pop();
    }

    bool isRunning = false;
    for (auto it = damageEffectings_.begin(); it != damageEffectings_.end();)
    {
        if (!(*it)->CheckUpdateCondition(entity_, healthRef_))
        {
            it->get()->OnExitEffect(entity_, healthRef_);
            it = damageEffectings_.erase(it);
        }
        else
        {
            isRunning = true;
            Health prevHealth = healthRef_;
            it->get()->OnUpdateEffect(entity_, healthRef_);
            Health damageCount = prevHealth - healthRef_;
            if (damageCount != Health(0))
            {
                Entity::Spawn<DamageNotation>(DAMAGE_NOTATION_PREFAB_PATH,
                                              entity_.GetComponent<Transform>()->position_)->
                    SetNotation(damageCount.ToString(), it->get()->GetParam().Color());
            }
            ++it;
        }
    }

    if (isRunning)
    {
        return Ai::INode::Status::Running;
    }

    return Ai::INode::Status::Success;
}
