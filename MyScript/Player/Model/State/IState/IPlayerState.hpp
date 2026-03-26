#pragma once
#include <functional>
#include <memory>

#include "../../../../../Component/Content/Basically/Renderer/AnimationRenderer/AnimationRenderer.h"
#include "../../../../../Component/Content/Basically/Collider/Collider.h"
#include "../../../Controller/PlayerController.h"
#include "../../BasicParam/BasicParam.h"

namespace Player
{
    class PlayerStateGroup;

    class IPlayerState
    {
    public:
        virtual ~IPlayerState() = default;
        virtual void OnEnter(BasicParam& basicParam,
                             Transform& transform,
                             Collider& collider,
                             PlayerController& controller,
                             AnimationRenderer& playerAnimRender,
                             PlayerModel& playerModel) = 0;
        
        ///NOTE: OnEnterが呼び出された1フレーム後に呼び出される。
        virtual void OnUpdateForGameRoop(BasicParam& basicParam,
                                         Transform& transform,
                                         Collider& collider,
                                         PlayerController& controller,
                                         PlayerStateGroup& stateGroup,
                                         AnimationRenderer& animRender,
                                         PlayerModel& playerModel,
                                         std::function<void(const std::shared_ptr<IPlayerState>&)> onChangeState) = 0;
        
        virtual void OnExit(Collider& collider,
                            PlayerModel& playerModel) = 0;
    };
}
