#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../BasicallyParameter/Vector2/Vector2.hpp"
#include "../../../FightParameter/DamageContext/Thunder/ThunderPower/ThunderPower.h"
#include "../Base/SkillBase.h"


namespace Skill
{
    class SummonLightning final : public virtual SkillBase
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::make_nvp("name", name_),
                cereal::make_nvp("spriteResourceFilePath", spriteResourceFilePath_),
                cereal::make_nvp("summonLightningPrefabPath", summonLightningPrefabPath_),
                cereal::make_nvp("thunderPower", thunderPower_),
                cereal::make_nvp("summonThunderDistance", summonThunderDistance_),
                cereal::make_nvp("summonThunderOffset", summonThunderOffset_)
            );
        }

        std::string Name() override { return name_; }
        int GetSpriteHandle() override { return spriteHandle_; }
        void Init() override;
        void OnExecuteNormalForm(Player::PlayerModel&, Player::PlayerController&, AnimationRenderer&) override;
        void OnExecuteDarkForm(Player::PlayerModel&, Player::PlayerController&, AnimationRenderer&) override;
        void OnDrawInspector() override;

    private:
        std::string name_ = "SummonLightningSkill";
        std::string summonLightningPrefabPath_;
        std::string spriteResourceFilePath_;
        int spriteHandle_ = -1;
        ThunderPower thunderPower_;
        float summonThunderDistance_ = 100;
        Vector2 summonThunderOffset_ = Vector2();
    };
}

CEREAL_REGISTER_TYPE(Skill::SummonLightning)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Skill::SkillBase, Skill::SummonLightning)
