#pragma once
#include "../../../../../../BasicallyParameter/Sound/Handle/SoundHandle.h"

namespace Player
{
    namespace DarkForm
    {
        class DarkFormSound final
        {
        public:
            template <typename Archive>
            void serialize(Archive& archive)
            {
                archive(cereal::make_nvp("walkSound"            , walkSound_),
                        cereal::make_nvp("onAttackSound"        , onAttackSound_),
                        cereal::make_nvp("onDamageSound"     , onDamageSound_),
                        cereal::make_nvp("onReleaseFormSound"   , onReleaseFormSound_)
                );
            }

            void Init();
            void OnDrawInspector();
            const Sound::SoundHandle& Walk()            const { return walkSound_; }
            const Sound::SoundHandle& OnAttack()        const { return onAttackSound_; }
            const Sound::SoundHandle& OnDamageSound()   const { return onDamageSound_; }
            const Sound::SoundHandle& OnReleaseForm()   const { return onReleaseFormSound_; }

        private:
            Sound::SoundHandle walkSound_;
            Sound::SoundHandle onAttackSound_;
            Sound::SoundHandle onDamageSound_;
            Sound::SoundHandle onReleaseFormSound_;
        };
    }
}
