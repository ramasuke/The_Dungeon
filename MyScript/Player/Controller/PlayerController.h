#pragma once

#include "InputAction/Move/Move.h"
#include "InputAction/Attack/Attack.h"
#include "InputAction/GoInsane/ConsumptionMadness.h"
#include "InputAction/DashAttack/DashAttack.h"

namespace Player
{
    class PlayerController final
    {
    public:
        const InputAction<Vector2>& Move()                      const { return moveAction_; }
        const InputAction<void>&    Attack()                    const { return attackAction_; }
        const InputAction<int>&     ConsumptionMadnessAction()  const { return consumptionMadnessAction_; }
        const InputAction<void>&    DashAttackAction()          const { return dashAttackAction_; }
        void SetActive(bool active);
        void OnUpdate();

    private:
        InputActionContent::Attack              attackAction_;
        InputActionContent::Move                moveAction_;
        InputActionContent::ConsumptionMadness  consumptionMadnessAction_;
        InputActionContent::DashAttack          dashAttackAction_;
    };
}
