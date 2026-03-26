#pragma once
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include "../../Skill/SummonFireBall/SummonFireBallSkill.h"

#include "../../../../Component/Component.hpp"
#include "../../Skill/Base/SkillBase.h"


class SkillBookDropItemObject final : public virtual Component
{
public:
    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::base_class<Component>(this),
            cereal::make_nvp("skillItem", skillItem_)
        );
    }

    void SetSkillItem(std::shared_ptr<Skill::SkillBase>);
    std::shared_ptr<Skill::SkillBase> OnPickUp() const;
    void OnDrawInspector() override;

private:
    void Init() override;
    
    std::shared_ptr<Skill::SkillBase> skillItem_ = nullptr;
};

CEREAL_REGISTER_TYPE(SkillBookDropItemObject)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, SkillBookDropItemObject)