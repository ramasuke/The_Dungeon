#pragma once
#include <memory>
#include <cereal/cereal.hpp>

#include "../../../../../BasicallyParameter/SerializableSubject/Subject.h"
#include "../../../../Item/Skill/Base/SkillBase.h"

namespace Player
{
    class Inventory final
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(cereal::make_nvp("skill", skill_));
        }

        ReadOnlyReactiveContext<std::shared_ptr<Skill::SkillBase>> Skill() const { return skill_.AsReadOnly(); }
        void SetSkill(const std::shared_ptr<Skill::SkillBase>& skill);
        void OnDrawInspector() const;

    private:
        Subject<std::shared_ptr<Skill::SkillBase>> skill_ = Subject<std::shared_ptr<Skill::SkillBase>>(nullptr);
    };
}
