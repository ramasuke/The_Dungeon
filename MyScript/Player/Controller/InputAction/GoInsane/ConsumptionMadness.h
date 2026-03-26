#pragma once
#include "../InputAction.h"

namespace Player
{
    namespace InputActionContent
    {
        class ConsumptionMadness final : public virtual InputAction<int>
        {
        public:
            void OnUpdateForGameRoop();
            void SetActive(bool active);

        private:
            bool    IsPressed()        const override;
            bool    IsUpdatePressed()  const override;
            bool    IsReleased()       const override;
            int     ReadValue()        const override;
            static bool CheckOnInputKey();

            int pressDuring_ = 0;
            bool previewIsPress_ = false;
            bool isActive_ = true;    
        };
    }
}
