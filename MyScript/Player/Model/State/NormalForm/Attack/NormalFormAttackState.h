#pragma once
#include "../../IState/IPlayerState.hpp"

namespace Player
{
    namespace NormalForm
    {
        class NormalFormAttackState final : public virtual IPlayerState
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
            
            void SpawnAttackArea(BasicParam& basicParam, const Transform& transform, bool isReverseX);

            const std::string attackAreaPrefabPath_ = "Resource/Prefab/Player-NormalAttack-Area.json";
            Entity* attackArea_ = nullptr;
            float nextStateDuring_ = 0;
        };
    }
}
