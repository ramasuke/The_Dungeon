#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../IEntranceEvent.h"
#include "../../../../BasicallyParameter/Sound/Handle/SoundHandle.h"
#include "../../../FightParameter/Enemy/SpawnModel/SpawnEnemyModel.h"

namespace Map
{
    namespace Room
    {
        namespace Event
        {
            class BossFight final : public virtual IEntranceEvent
            {
            public:
                template <class Archive>
                void serialize(Archive& archive)
                {
                    archive(
                        cereal::base_class<IEntranceEvent>(this),
                        cereal::make_nvp("spawnBoss"                , spawnBoss_                ),
                        cereal::make_nvp("spawnBossSound"           , spawnBossSound_           ),
                        cereal::make_nvp("bossBgm"                  , bossBgm_                  ),
                        cereal::make_nvp("onDeathBossSummonModels"  , onDeathBossSummonModels_  )
                    );
                }

            private:
                void Init()             override;
                void Execute()          override;
                void OnDrawInspector()  override;
                void OnDrawDebug()      const override;
                void OnDeathBossEvent() const;

                const std::string               summonBossEnemyParticlePrefabPath_ = "Resource/Prefab/SummonBossCircle.json";
                SpawnEnemyModel                 spawnBoss_;
                Sound::SoundHandle              spawnBossSound_;
                Sound::SoundHandle              bossBgm_;
                std::vector<SpawnEnemyModel>    onDeathBossSummonModels_;
            };
        }
    }
}

CEREAL_REGISTER_TYPE(Map::Room::Event::BossFight)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Map::Room::Event::IEntranceEvent, Map::Room::Event::BossFight)
