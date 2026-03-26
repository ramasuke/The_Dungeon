#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../BasicallyParameter/Vector2/Vector2.hpp"
#include "../../../FightParameter/DamageContext/Fire/FirePower/FirePower.h"
#include "../Base/SkillBase.h"

namespace Skill
{
    class SummonFireBallSkill final : public virtual SkillBase
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::make_nvp("name"                     , name_),
                cereal::make_nvp("summonFireBallPrefabPath" , summonFireBallPrefabPath_),
                cereal::make_nvp("spriteResourceFilePath"   , spriteResourceFilePath_),
                cereal::make_nvp("firePower"                , firePower_),
                cereal::make_nvp("summonDistance"           , summonDistance_),
                cereal::make_nvp("summonAmount"             , summonAmount_),
                cereal::make_nvp("startAngle"               , startAngle_),
                cereal::make_nvp("endAngle"                 , endAngle_)
            );
        }

        std::string Name() override { return name_; }
        int GetSpriteHandle() override { return spriteHandle_; }
        void Init() override;
        void OnExecuteNormalForm(Player::PlayerModel&, Player::PlayerController&, AnimationRenderer&) override;
        void OnExecuteDarkForm(Player::PlayerModel&, Player::PlayerController&, AnimationRenderer&) override;
        void OnDrawInspector() override;

    private:
        void SummmonFireBalls(const Player::PlayerModel& playerModel, const Player::PlayerController& controller);

        std::string name_ = "SummonLightningSkill";
        std::string summonFireBallPrefabPath_;
        std::string spriteResourceFilePath_;
        int spriteHandle_ = -1;
        FirePower firePower_;
        float summonDistance_ = 100;
        int summonAmount_ = 3;
        float startAngle_ = 0;
        float endAngle_ = 0;
    };
}

CEREAL_REGISTER_TYPE(Skill::SummonFireBallSkill)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Skill::SkillBase, Skill::SummonFireBallSkill)
