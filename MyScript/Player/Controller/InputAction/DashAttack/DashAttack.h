#pragma once
#include "../InputAction.h"

namespace Player
{
    namespace InputActionContent
    {
        class DashAttack final : public virtual InputAction<void>
        {
        public:
            void OnUpdateForGameRoop();
            void SetActive(bool active);

        private:
            bool IsPressed()        const override;
            bool IsUpdatePressed()  const override;
            bool IsReleased()       const override;
            void ReadValue()        const override;
            static bool CheckOnInputKey();

            bool previewIsPress_ = false;
            bool isActive_ = true;
        };
    }
}
