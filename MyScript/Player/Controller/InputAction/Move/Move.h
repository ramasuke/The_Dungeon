#pragma once
#include "../InputAction.h"
#include "../../../../../BasicallyParameter/Vector2/Vector2.hpp"

namespace Player
{
    namespace InputActionContent
    {
        class Move final : public virtual InputAction<Vector2>
        {
        public:
            void OnUpdateForGameRoop();
            void SetActive(bool active);

        private:
            bool        IsPressed()         const override;
            bool        IsUpdatePressed()   const override;
            bool        IsReleased()        const override;
            Vector2     ReadValue()         const override;
            static bool CheckOnInputKey();

            bool previewIsPress_ = false;
            bool isActive_ = true;
        };
    }
}
