#include "GameClearText.h"

#include "../../../BasicallyParameter/Sound/Play/SoundPlay.h"
#include "../../../Component/Content/Basically/Transform/Transform.hpp"
#include "../../Player/PlayerAvatar.h"
#include "../../Sound/HandleContainer/HandleContainer.h"

void GameClearScene::GameClearText::Init()
{
    if (gameClearParticlePrefabFilePath_.empty())
        return;

    Entity::Spawn(gameClearParticlePrefabFilePath_, Player::PlayerAvatar::Model().Transform()->position_);
    Sound::PlaySe(Sound::GameClear::OnSurpriseClear());
}

void GameClearScene::GameClearText::OnUpdate()
{
    returnTitleDuring_++;

    if (returnTitleDuration_ == returnTitleDuring_)
    {
        IApplication::GetInstance().SceneManager().OnUnloadScene("Resource/Scene/GameClearScene.json");
        IApplication::GetInstance().SceneManager().OnUnloadScene("Resource/Scene/Dungeon1-4.json");
        IApplication::GetInstance().SceneManager().OnLoadSceneAsync("Resource/Scene/SelectStageScene.json");
    }
}

void GameClearScene::GameClearText::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("gameClearParticlePrefabFilePath_", gameClearParticlePrefabFilePath_);
    
    if(ImGui::Button("generate gameClearParticle"))
    {
        Entity::Spawn(gameClearParticlePrefabFilePath_, EntityRef().GetComponent<Transform>()->position_);
    }
}
