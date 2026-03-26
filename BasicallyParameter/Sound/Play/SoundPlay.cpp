#include "SoundPlay.h"

#include <DxLib.h>

void Sound::PlayBgm(const SoundHandle& handle)
{
    PlaySoundMem(handle.Handle(), DX_PLAYTYPE_LOOP);
}

void Sound::PlaySe(const SoundHandle& handle)
{
    PlaySoundMem(handle.Handle(), DX_PLAYTYPE_BACK);
}

void Sound::StopBgm(const SoundHandle& handle)
{
    StopSoundMem(handle.Handle());
}
