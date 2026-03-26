#include "SkillBookDropItemObject.h"

#include <utility>

#include "../../../../Application/IApplication/IApplication.hpp"
#include "../../../../Libs/ImGui/imgui.h"
#include "../../Skill/SummonFireBall/SummonFireBallSkill.h"
#include "../../Skill/SummonLighting/SummonLightning.h"

void SkillBookDropItemObject::SetSkillItem(std::shared_ptr<Skill::SkillBase> skillItem)
{
    skillItem_ = std::move(skillItem);
}

std::shared_ptr<Skill::SkillBase> SkillBookDropItemObject::OnPickUp() const
{
    EntityRef().OnDespawn();
    return skillItem_;
}

void SkillBookDropItemObject::OnDrawInspector()
{
    if (ImGui::Button("SetSummonLightningSkill"))
    {
        skillItem_ = std::make_shared<Skill::SummonLightning>();
    }
    if (ImGui::Button("SetSummonFireBallSkill"))
    {
        skillItem_ = std::make_shared<Skill::SummonFireBallSkill>();
    }

    if (skillItem_ != nullptr)
    {
        if (ImGui::TreeNode(skillItem_->Name().c_str()))
        {
            skillItem_->OnDrawInspector();
            ImGui::TreePop();
            ImGui::Spacing();
        }
    }
    else
    {
        if (ImGui::TreeNode("skill is null"))
        {
            ImGui::TreePop();
            ImGui::Spacing();
        }
    }
}

void SkillBookDropItemObject::Init()
{
    if (skillItem_ != nullptr)
    {
        skillItem_->Init();
    }
}
