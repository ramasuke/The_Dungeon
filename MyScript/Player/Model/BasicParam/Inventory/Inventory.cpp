#include "Inventory.h"

void Player::Inventory::SetSkill(const std::shared_ptr<Skill::SkillBase>& skill)
{
    skill_.OnNext(skill);
}

void Player::Inventory::OnDrawInspector() const
{
    if (skill_.get() != nullptr)
    {
        skill_.get()->OnDrawInspector();
    }
}
