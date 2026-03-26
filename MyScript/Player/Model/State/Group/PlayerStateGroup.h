#pragma once
#include "../NormalForm/Attack/NormalFormAttackState.h"
#include "../NormalForm/Idle/NormalFormIdleState.h"
#include "../NormalForm/Walk/NormalFormWalkState.h"
#include "../NormalForm/GoInsane/GoInsaneState.h"
#include "../DarkForm/Attack/DarkFormAttackState.h"
#include "../DarkForm/Idle/DarkFormIdleState.h"
#include "../DarkForm/Walk/DarkFormWalkState.h"
#include "../DarkForm/OnDamage/DarkFormOnDamageState.h"
#include "../DarkForm/OnReleaseForm/DarkFormOnReleaseFormState.h"
#include "../NormalForm/ConsumptionMadness/NormalFormConsumptionMadnessState.h"
#include "../NormalForm/OnDamage/NormalFormOnDamageState.h"
#include "../NormalForm/OnDarkHeal/NormalFormOnDarkHealState.h"
#include "../NormalForm/OnDeath/NormalFormOnDeathState.h"

namespace Player
{
    class PlayerStateGroup final
    {
    public:
        const std::shared_ptr<NormalForm::NormalFormIdleState>&                 NormalFormIdleState()               const { return normalFormIdleState_;                } 
        const std::shared_ptr<NormalForm::NormalFormWalkState>&                 NormalFormWalkState()               const { return normalFormWalkState_;                } 
        const std::shared_ptr<NormalForm::NormalFormAttackState>&               NormalFormAttackState()             const { return normalFormAttackState_;              } 
        const std::shared_ptr<NormalForm::NormalFormOnDamageState>&             NormalFormOnDamageState()           const { return normalFormOnDamageState_;            } 
        const std::shared_ptr<NormalForm::NormalFormOnDarkHealState>&           NormalFormOnDarkHealState()         const { return normalFormOnDarkHealState_;          } 
        const std::shared_ptr<NormalForm::NormalFormOnDeathState>&              NormalFormOnDeathState()            const { return normalFormOnDeathState_;             } 
        const std::shared_ptr<NormalForm::NormalFormConsumptionMadnessState>&   NormalFormConsumptionMadnessState() const { return normalFormConsumptionMadnessState_;  } 
         
        const std::shared_ptr<NormalForm::GoInsaneState>&               GoInsaneState()                 const { return goInsaneState_;              } 
        const std::shared_ptr<DarkForm::DarkFormIdleState>&             DarkFormIdleState()             const { return darkFormIdleState_;          } 
        const std::shared_ptr<DarkForm::DarkFormWalkState>&             DarkFormWalkState()             const { return darkFormWalkState_;          } 
        const std::shared_ptr<DarkForm::DarkFormAttackState>&           DarkFormAttackState()           const { return darkFormAttackState_;        } 
        const std::shared_ptr<DarkForm::DarkFormOnDamageState>&         DarkFormOnDamageState()         const { return darkFormOnDamageState_;      } 
        const std::shared_ptr<DarkForm::DarkFormOnReleaseFormState>&    DarkFormOnReleaseFormState()    const { return darkFormOnReleaseFormState_; } 

    private:
        std::shared_ptr<NormalForm::NormalFormIdleState>                normalFormIdleState_                = std::make_shared<NormalForm::NormalFormIdleState>();
        std::shared_ptr<NormalForm::NormalFormWalkState>                normalFormWalkState_                = std::make_shared<NormalForm::NormalFormWalkState>();
        std::shared_ptr<NormalForm::NormalFormAttackState>              normalFormAttackState_              = std::make_shared<NormalForm::NormalFormAttackState>();
        std::shared_ptr<NormalForm::NormalFormOnDeathState>             normalFormOnDeathState_             = std::make_shared<NormalForm::NormalFormOnDeathState>();
        std::shared_ptr<NormalForm::NormalFormOnDamageState>            normalFormOnDamageState_            = std::make_shared<NormalForm::NormalFormOnDamageState>();
        std::shared_ptr<NormalForm::NormalFormOnDarkHealState>          normalFormOnDarkHealState_          = std::make_shared<NormalForm::NormalFormOnDarkHealState>();
        std::shared_ptr<NormalForm::NormalFormConsumptionMadnessState>  normalFormConsumptionMadnessState_  = std::make_shared<NormalForm::NormalFormConsumptionMadnessState>();
        
        
        std::shared_ptr<NormalForm::GoInsaneState>              goInsaneState_              = std::make_shared<NormalForm::GoInsaneState>();
        std::shared_ptr<DarkForm::DarkFormIdleState>            darkFormIdleState_          = std::make_shared<DarkForm::DarkFormIdleState>();
        std::shared_ptr<DarkForm::DarkFormWalkState>            darkFormWalkState_          = std::make_shared<DarkForm::DarkFormWalkState>();
        std::shared_ptr<DarkForm::DarkFormAttackState>          darkFormAttackState_        = std::make_shared<DarkForm::DarkFormAttackState>();
        std::shared_ptr<DarkForm::DarkFormOnDamageState>        darkFormOnDamageState_      = std::make_shared<DarkForm::DarkFormOnDamageState>();
        std::shared_ptr<DarkForm::DarkFormOnReleaseFormState>   darkFormOnReleaseFormState_ = std::make_shared<DarkForm::DarkFormOnReleaseFormState>();
    };
}
