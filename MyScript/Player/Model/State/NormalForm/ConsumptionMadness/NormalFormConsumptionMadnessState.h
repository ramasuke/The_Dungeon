#pragma once
#include "../../IState/IPlayerState.hpp"

namespace Player
{
    namespace NormalForm
    {
        class NormalFormConsumptionMadnessState final : public virtual IPlayerState
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

            void OnExit(Collider&       collider,
                        PlayerModel&    playerModel) override;

            void OnUpdateConsumptionParticle(PlayerModel&      playerModel,
                                                  BasicParam&       basicParam,
                                                  const PlayerController& controller) const;
            
            static void OnConsumptionMadnessAction(const PlayerModel&         playerModel,
                                                   const PlayerController&    controller,
                                                   BasicParam&          basicParam,
                                                   const PlayerStateGroup&    stateGroup,
                                                   const std::function<void(const std::shared_ptr<IPlayerState>&)>&
                                                   onChangeState);
            
            void OnPlayPromptConsumptionParticle(const PlayerModel& playerModel) const; 

            static constexpr int ClampToNOrMore(const int value, const int n) {
                return (value < n) ? n : value;
            }


            int                 stateDuring_                            = 0;
            Entity*             particle_                               = nullptr;
            const float         particleScaleCoefficient_               = 0.015f;
            const std::string   consumptioningParticlePrefabPath_       = "Resource/Prefab/ConsumptioningMadnessParticle.json";
            const std::string   promptConsumptionParticlePrefabPath_    = "Resource/Prefab/PromptConsumptioningMadnessParticle.json";
            const Vector2       particleOffsetPos_                      = Vector2(0.0f, -100.0f);
        };
    }
}
