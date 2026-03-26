#pragma once
#include "../../../../../Component/Component.hpp"

namespace Player
{
    constexpr int ON_PICKUP_DURATION = 10;
    constexpr float ON_UPDATE_UP_MOVE_SPEED = -1.0f;
    
    class PowerUpItemBase : public virtual Component
    {
    public:
        explicit PowerUpItemBase() = default;
        virtual ~PowerUpItemBase() = default;
    };
}
