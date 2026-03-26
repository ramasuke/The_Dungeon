#pragma once
#include <string>

#include "../../../Player/Controller/PlayerController.h"

// #include "../../Player/Model/PlayerModel.h"


class AnimationRenderer;

namespace Player
{
    class PlayerModel;
}

namespace Skill
{
    class SkillBase
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
        }

        virtual ~SkillBase() = default;
        virtual std::string Name() = 0;
        virtual int GetSpriteHandle() = 0;
        virtual void Init() = 0;
        virtual void OnExecuteNormalForm(Player::PlayerModel&, Player::PlayerController&, AnimationRenderer&) = 0;
        virtual void OnExecuteDarkForm(Player::PlayerModel&, Player::PlayerController&, AnimationRenderer&) = 0;
        virtual void OnDrawInspector() = 0;
    };
}
