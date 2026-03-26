#include "OnPlaySoundEffect.h"

#include "../../../../BasicallyParameter/Sound/Play/SoundPlay.h"
#include "../../../../Helper/ImGui/ImGuiHelper.h"

void Map::Room::Event::OnPlaySoundEffect::Init()
{
    for (auto& sound : sounds_)
    {
        sound.Init();
    }
}

void Map::Room::Event::OnPlaySoundEffect::Execute()
{
    for (auto& sound : sounds_)
    {
        Sound::PlaySe(sound);
    }
}

void Map::Room::Event::OnPlaySoundEffect::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("sounds", sounds_, [this]()
    {
        OnDrawAddSoundButton();
    });
}

void Map::Room::Event::OnPlaySoundEffect::OnDrawDebug() const
{
}

void Map::Room::Event::OnPlaySoundEffect::OnDrawAddSoundButton()
{
    if (ImGui::Button("add"))
    {
        sounds_.emplace_back();
    }
}