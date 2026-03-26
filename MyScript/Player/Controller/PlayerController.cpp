#include "PlayerController.h"

void Player::PlayerController::OnUpdate()
{
    attackAction_.OnUpdateForGameRoop();
    moveAction_.OnUpdateForGameRoop();
    consumptionMadnessAction_.OnUpdateForGameRoop();
    dashAttackAction_.OnUpdateForGameRoop();
}

void Player::PlayerController::SetActive(const bool active)
{
    attackAction_.SetActive(active);
    moveAction_.SetActive(active);
    consumptionMadnessAction_.SetActive(active);
    dashAttackAction_.SetActive(active);
}
