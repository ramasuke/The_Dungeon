#include "SkillSlotView.h"

void GamePlayScene::PlayerParamView::SkillSlotView::OnUpdateView(const std::shared_ptr<Skill::SkillBase>& skill) const
{
    if (skill == nullptr)
        return;
    
    EntityRef().GetComponent<ImageRenderer>()->renderHandleId_ = skill->GetSpriteHandle();
}
