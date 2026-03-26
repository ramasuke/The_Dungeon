#pragma once
#include "../../../BasicallyParameter/Sound/Handle/SoundHandle.h"

namespace Sound
{
    namespace BlueSlime
    {
        static const SoundHandle& OnDeathSound()
        {
            static auto onDeathSound = SoundHandle("Resource/Sound/SE/BlueSlime/OnDeath.mp3", 255, true);
            return onDeathSound;
        }    
    }
    
    static const SoundHandle& OnDeathSound()
    {
        static auto onDeathSound = SoundHandle("Resource/Sound/SE/InputWaterOnBath.mp3", 255, true);
        return onDeathSound;
    }
    static const SoundHandle& OnSurprise()
    {
        static auto onSurpriseSound = SoundHandle("Resource/Sound/SE/Surprise.mp3", 200, true);
        return onSurpriseSound;
    }
    
    namespace Skeleton
    {

        static const SoundHandle& OnHurt()
        {
            static auto hurtSound = SoundHandle("Resource/Sound/SE/Skeleton/Hurt.mp3", 255, true);
            return hurtSound;
        }

        static const SoundHandle& OnDeath()
        {
            static auto deathSound = SoundHandle("Resource/Sound/SE/Skeleton/Death.mp3", 255, true);
            return deathSound;
        }
    }
    
    namespace FlyingFox
    {
        static const SoundHandle& OnAttack()
        {
            static auto hurtSound = SoundHandle("Resource/Sound/SE/Skeleton/Hurt.mp3", 255, true);
            return hurtSound;
        }
        
        static const SoundHandle& OnHurt()
        {
            static auto hurtSound = SoundHandle("Resource/Sound/SE/Skeleton/Hurt.mp3", 255, true);
            return hurtSound;
        }

        static const SoundHandle& OnDeath()
        {
            static auto deathSound = SoundHandle("Resource/Sound/SE/Skeleton/Death.mp3", 255, true);
            return deathSound;
        }
    }
    
    namespace GhostWizard
    {
        static const SoundHandle& OnAttack()
        {
            static auto attackSound = SoundHandle("Resource/Sound/SE/GhostWizard/Attack.mp3", 255, true);
            return attackSound;
        }

        static const SoundHandle& OnHurt()
        {
            static auto hurtSound = SoundHandle("Resource/Sound/SE/GhostWizard/Hurt.mp3", 255, true);
            return hurtSound;
        }

        static const SoundHandle& OnDeath()
        {
            static auto deathSound = SoundHandle("Resource/Sound/SE/GhostWizard/Death.mp3", 255, true);
            return deathSound;
        }
    }

    static const SoundHandle& OnCollectMadnessEnergy()
    {
        static auto sound = SoundHandle("Resource/Sound/SE/Pap.mp3", 160, true);
        return sound;
    }

    namespace SmallOrc
    {
        static const SoundHandle& OnHurt()
        {
            static auto hurtSound = SoundHandle("Resource/Sound/SE/Skeleton/Hurt.mp3", 255, true);
            return hurtSound;
        }

        static const SoundHandle& OnDeath()
        {
            static auto deathSound = SoundHandle("Resource/Sound/SE/Skeleton/Death.mp3", 255, true);
            return deathSound;
        }
    }

    namespace DarkSamurai
    {
        static const SoundHandle& OnHurt()
        {
            static auto hurtSound = SoundHandle("Resource/Sound/SE/Skeleton/Hurt.mp3", 255, true);
            return hurtSound;
        }

        static const SoundHandle& OnDeath()
        {
            static auto deathSound = SoundHandle("Resource/Sound/SE/Skeleton/Death.mp3", 255, true);
            return deathSound;
        }
    }

    namespace Gimmick
    {
        static const SoundHandle& OnThunder()
        {
            static auto deathSound = SoundHandle("Resource/Sound/SE/OnThunderGimmick.mp3", 230, true);
            return deathSound;
        }
    }

    namespace GameClear
    {
        static const SoundHandle& OnSurpriseClear()
        {
            static auto clearSound = SoundHandle("Resource/Sound/SE/Yeahhhhhhhhh.mp3", 230, true);
            return clearSound;
        }
    }

    namespace StageSelect
    {
        static const SoundHandle& OpenBook()
        {
            static auto clearSound = SoundHandle("Resource/Sound/SE/Page.mp3", 255, true);
            return clearSound;   
        }
    }
}
