#pragma once
#include "../../IState/IPlayerState.hpp"

namespace Player
{
    namespace NormalForm
    {
        class NormalFormWalkState final : public virtual IPlayerState
        {
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
            
            void UpdateWalkSound(BasicParam& basicParam);

            const int walkSoundDuration_ = 19;
            int walkSoundDuring_ = 0;
        };
    }
}
