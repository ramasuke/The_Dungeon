#pragma once
#include "../../../Component/Content/Basically/Renderer/AnimationRenderer/AnimationRenderer.h"
#include "../../../Component/Content/Basically/Collider/Collider.h"
#include "../Controller/PlayerController.h"
#include "BasicParam/BasicParam.h"
#include "State/Group/PlayerStateGroup.h"

namespace Player
{
    class PlayerModel final
    {
    public:
        PlayerModel();
        void Init           (AnimationRenderer* , Transform*, Collider*, PlayerController&);
        void OnUpdate       (AnimationRenderer& , PlayerController&);
        void OnChangeState  (PlayerController&  , AnimationRenderer&, const std::shared_ptr<IPlayerState>&);
        void OnDrawInspector(AnimationRenderer& , PlayerController&);
        void OnReset();
        
        const std::shared_ptr<IPlayerState>& CurrentState() const { return currentState_; }
        BasicParam& BasicParam()                            const { return *basicParam_; }
        Transform*  Transform()                             const { return transform_; }
        Collider*   Collider()                              const;

    private:
        std::shared_ptr<Player::BasicParam> basicParam_ = nullptr;

        //Model State
        ::Transform*                    transform_ = nullptr;
        ::Collider*                     collider_   = nullptr;
        PlayerStateGroup                stateGroup_;
        std::shared_ptr<IPlayerState>   currentState_;
    };
}
