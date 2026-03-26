#pragma once

namespace Player
{
    template <typename T>
    class InputAction
    {
    public:
        virtual ~InputAction() = default;
        virtual bool    IsPressed()         const = 0;
        virtual bool    IsUpdatePressed()   const = 0;
        virtual bool    IsReleased()        const = 0;
        virtual T       ReadValue()         const = 0;
    };
}
