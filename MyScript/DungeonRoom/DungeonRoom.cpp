#include "DungeonRoom.h"

#include "../../Application/Screen/ScreenHelper.h"
#include "../../Component/Content/Basically/Collider/Box/BoxCollider.h"
#include "../../Entity/Entity.hpp"
#include "../../Helper/ImGui/ImGuiHelper.h"
#include "EntranceArea/EntranceArea.h"
#include "EntranceEvent/OnPlaySound/OnPlaySoundEffect.h"
#include "EntranceEvent/SpawnEnemy/SpawnEntity.h"

void Map::Room::DungeonRoom::Init()
{
    for (const auto spawnEntranceModel : spawnEntranceModels_)
    {
        OnSpawnEntrance(spawnEntranceModel);
    }
    
    for (const auto& onEnterPlayerEvent : onEnterPlayerEvent_)
    {
        onEnterPlayerEvent->Init();
    }
}

void Map::Room::DungeonRoom::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("spawnEntranceModels_",
                                  spawnEntranceModels_,
                                  [this]() { OnDrawAddEntranceButton(); });
    ImGuiHelper::OnDrawInputField("OnEnterPlayerEvent",
                                  onEnterPlayerEvent_,
                                  [this]() { OnDrawAddOnEnterPlayerEventButton(); });

    OnDrawDebug();
}

void Map::Room::DungeonRoom::OnDrawDebug() const
{
    for (auto& spawnEntranceModel : spawnEntranceModels_)
    {
        spawnEntranceModel.OnDrawDebug();
    }
    for (auto& onEnterPlayerEvent : onEnterPlayerEvent_)
    {
        onEnterPlayerEvent->OnDrawDebug();
    }
}

void Map::Room::DungeonRoom::Despawned()
{
    for (const auto& entrance : entranceAreas_)
    {
        entrance->EntityRef().OnDespawn();
    }
    
    onEnterPlayerSubscription_.unsubscribe();
    entranceAreas_.clear();
}

void Map::Room::DungeonRoom::OnDrawAddEntranceButton()
{
    if (ImGui::Button("add"))
    {
        spawnEntranceModels_.emplace_back(Screen::CameraCenterWorldPos(), Vector2(50.0f, 50.0f));
    }
}

void Map::Room::DungeonRoom::OnDrawAddOnEnterPlayerEventButton()
{
    if (ImGui::TreeNode("add"))
    {
        if (ImGui::Button("SpawnEnemy"))
        {
            onEnterPlayerEvent_.push_back(std::make_unique<Event::SpawnEntity>());
        }
        if (ImGui::Button("OnPlaySoundEffect"))
        {
            onEnterPlayerEvent_.push_back(std::make_unique<Event::OnPlaySoundEffect>());
        }
        if (ImGui::Button("BossFight"))
        {
            onEnterPlayerEvent_.push_back(std::make_unique<Event::BossFight>());
        }
        if (ImGui::Button("LoadScene"))
        {
            onEnterPlayerEvent_.push_back(std::make_unique<Event::LoadSceneEvent>());
        }
        ImGui::TreePop();
        ImGui::Spacing();
    }
}

void Map::Room::DungeonRoom::OnSpawnEntrance(const SpawnEntranceModel spawnEntranceModel)
{
    auto& entrance = Entity::Spawn(ENTRANCE_PREFAB_PATH, spawnEntranceModel.Position());
    auto& entranceCollider = *entrance.GetComponent<BoxCollider>();
    entranceCollider.SetSize(spawnEntranceModel.AreaSize());

    const auto entranceArea = entrance.GetComponent<EntranceArea>();
    entranceAreas_.push_back(entranceArea);

    entranceArea->OnEnterPlayer()
                .subscribe(
                    [&](auto)
                    {
                        for (auto& entrance : entranceAreas_)
                        {
                            entrance->EntityRef().OnDespawn();
                        }
                        for (const auto& enterEvent : onEnterPlayerEvent_)
                        {
                            enterEvent->Execute();
                        }
                        onEnterPlayerSubscription_.unsubscribe();
                        entranceAreas_.clear();
                    },
                    [&](std::exception_ptr e)
                    {
                    },
                    [&]()
                    {
                    }
                ).add(onEnterPlayerSubscription_);
}
