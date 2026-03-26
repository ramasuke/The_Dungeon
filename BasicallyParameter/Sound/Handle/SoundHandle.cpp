#include "SoundHandle.h"

#include <DxLib.h>

#include "../../../Helper/ImGui/ImGuiHelper.h"
#include "../../../Libs/ImGui/imgui.h"

Sound::SoundHandle::SoundHandle()
= default;

Sound::SoundHandle::SoundHandle(std::string resourceFilePath, const int volume, const bool isLoadSoundMem)
    : resourceFilePath_(std::move(resourceFilePath)), volume_(volume)
{
    if (!isLoadSoundMem)
        return;

    OnUpdateSoundHandle();
}

Sound::SoundHandle::~SoundHandle()
{
    if (handle_ == -1)
        return;

    DeleteSoundMem(handle_);
}

void Sound::SoundHandle::Init()
{
    OnUpdateSoundHandle();
}

void Sound::SoundHandle::OnDrawInspector()
{
    char nameBuffer[256];
    strncpy_s(nameBuffer, resourceFilePath_.c_str(), sizeof(nameBuffer));
    ImGui::InputText("resourceFilePath: ", nameBuffer, sizeof(nameBuffer));
    resourceFilePath_ = nameBuffer;

    ImGui::InputInt("volume", &volume_);

    ImGui::Text(std::to_string(handle_).c_str());
    if (ImGui::Button("OnUpdateHandle"))
    {
        OnUpdateSoundHandle();
    }
}

int Sound::SoundHandle::Handle() const
{
    return handle_;
}

void Sound::SoundHandle::OnUpdateSoundHandle()
{
    handle_ = LoadSoundMem(resourceFilePath_.c_str());
    ChangeVolumeSoundMem(volume_, handle_);
}
