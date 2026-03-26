#pragma once
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/memory.hpp>

#include "../../Component/Component.hpp"
#include "EntranceArea/EntranceArea.h"
#include "EntranceArea/SpawnModel/SpawnEntranceModel.h"
#include "EntranceEvent/IEntranceEvent.h"
#include "EntranceEvent/SpawnEnemy/SpawnEntity.h"
#include "EntranceEvent/OnPlaySound/OnPlaySoundEffect.h"
#include "EntranceEvent/BossFight/BossFight.h"
#include "EntranceEvent/LoadScene/LoadSceneEvent.h"

namespace Map
{
    namespace Room
    {
        constexpr auto ENTRANCE_PREFAB_PATH = "Resource/Prefab/RoomEntranceArea.json";

        class DungeonRoom final : public virtual Component
        {
        public:
            template <class Archive>
            void serialize(Archive& archive)
            {
                archive(
                    cereal::base_class<Component>(this),
                    cereal::make_nvp("spawnEntranceModels"  , spawnEntranceModels_),
                    cereal::make_nvp("onEnterPlayerEvent"   , onEnterPlayerEvent_)
                );
            }

        private:
            void Init()             override;
            void OnDrawInspector()  override;
            void OnDrawDebug()      const;
            void Despawned()        override;
            void OnDrawAddEntranceButton();
            void OnDrawAddOnEnterPlayerEventButton();
            void OnSpawnEntrance(SpawnEntranceModel spawnEntranceModel);

            rxcpp::subscription                                 onEnterPlayerSubscription_;
            std::vector<EntranceArea*>                          entranceAreas_;
            std::vector<SpawnEntranceModel>                     spawnEntranceModels_;
            std::vector<std::unique_ptr<Event::IEntranceEvent>> onEnterPlayerEvent_;
        };
    }
}

CEREAL_REGISTER_TYPE(Map::Room::DungeonRoom)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Map::Room::DungeonRoom)
