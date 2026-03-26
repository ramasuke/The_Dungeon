#pragma once
#include "../../../../../../BasicallyParameter/Sound/Handle/SoundHandle.h"

namespace Player
{
    namespace NormalForm
    {
        class NormalFormSound
        {
        public:
            template <typename Archive>
            void serialize(Archive& archive)
            {
                archive(cereal::make_nvp("walkSound"            , walkSound_        ),
                        cereal::make_nvp("onAttackSound"        , onAttackSound_    ),
                        cereal::make_nvp("onDamageSound"        , onDamageSound_    ),
                        cereal::make_nvp("onDarkHealSound"      , onDarkHealSound_  ),
                        cereal::make_nvp("onDeathSound"         , onDeathSound_     )
                );
            }

            void Init();
            void OnDrawInspector();
            const Sound::SoundHandle& Walk()        const { return walkSound_;          }
            const Sound::SoundHandle& OnAttack()    const { return onAttackSound_;      }
            const Sound::SoundHandle& OnDamage()    const { return onDamageSound_;      }
            const Sound::SoundHandle& OnDarkHeal()  const { return onDarkHealSound_;    }
            const Sound::SoundHandle& OnDeath()     const { return onDeathSound_;       }

        private:
            Sound::SoundHandle walkSound_;
            Sound::SoundHandle onAttackSound_;
            Sound::SoundHandle onDamageSound_;
            Sound::SoundHandle onDarkHealSound_;
            Sound::SoundHandle onDeathSound_;
        };
    }
}
