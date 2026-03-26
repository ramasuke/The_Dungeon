#include "SceneBgmPlayer.h"

#include "../../../../BasicallyParameter/Sound/Play/SoundPlay.h"
#include "../../../../Helper/ImGui/ImGuiHelper.h"

void Sound::SceneBgmPlayer::Init()
{
    bgmHandle_.Init();
}

void Sound::SceneBgmPlayer::Awake()
{
    PlayBgm(bgmHandle_);
}

void Sound::SceneBgmPlayer::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("bgmHandle", bgmHandle_);
}

void Sound::SceneBgmPlayer::Despawned()
{
    StopBgm(bgmHandle_);
}
