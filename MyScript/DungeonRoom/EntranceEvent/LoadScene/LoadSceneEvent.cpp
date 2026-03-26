#include "LoadSceneEvent.h"

#include "../../../../Application/IApplication/IApplication.hpp"
#include "../../../../Helper/ImGui/ImGuiHelper.h"

void Map::Room::Event::LoadSceneEvent::Execute()
{
    IApplication::GetInstance().SceneManager().OnLoadSceneAsync(sceneFilePath_);
}

void Map::Room::Event::LoadSceneEvent::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("sceneFilePath", sceneFilePath_);
}

void Map::Room::Event::LoadSceneEvent::OnDrawDebug() const
{
    
}
