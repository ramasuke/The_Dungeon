#pragma once
#include "../../IState/IPlayerState.hpp"

namespace Player
{
    namespace NormalForm
    {
        class NormalFormOnDarkHealState final : public virtual IPlayerState
        {
        public:
            void OnEnter(BasicParam& basicParam,
                         Transform& transform,
                         Collider& collider,
                         PlayerController& controller,
                         AnimationRenderer& playerAnimRender,
                         PlayerModel& playerModel) override;

            void OnUpdateForGameRoop(BasicParam& basicParam,
                                     Transform& transform,
                                     Collider& collider,
                                     PlayerController& controller,
                                     PlayerStateGroup& stateGroup,
                                     AnimationRenderer& animRender,
                                     PlayerModel& playerModel,
                                     std::function<void(const std::shared_ptr<IPlayerState>&)> onChangeState) override;

            void OnExit(Collider& collider,
                        PlayerModel& playerModel) override;

        private:
            const std::string particlePrefabPath_ = "Resource/Prefab/Player-DarkHeal-Particle.json";
            float nextStateDuring_ = 0;
        };
    }
}
