#pragma once
#include "../../IState/IPlayerState.hpp"

namespace Player
{
    namespace DarkForm
    {
        class DarkFormAttackState final : public virtual IPlayerState
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
            Entity* SpawnAttackArea(BasicParam& basicParam, const Transform& transform, bool isReverseX) const;

            const std::string attackAreaPrefabPath_ = "Resource/Prefab/Player-DarkAttack-Collider.json";
            Entity* attackArea_ = nullptr;
            float nextStateDuring_ = 0;
        };
    }
}
