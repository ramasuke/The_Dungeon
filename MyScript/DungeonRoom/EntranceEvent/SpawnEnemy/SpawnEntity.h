#pragma once
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/vector.hpp>

#include "../IEntranceEvent.h"
#include "../../../FightParameter/Enemy/SpawnModel/SpawnEnemyModel.h"

namespace Map
{
    namespace Room
    {
        namespace Event
        {
            class SpawnEntity final : public virtual IEntranceEvent
            {
            public:
                template <class Archive>
                void serialize(Archive& archive)
                {
                    archive(
                        cereal::base_class<IEntranceEvent>(this),
                        cereal::make_nvp("spawnEnemyModels", spawnEnemyModels_)
                    );
                }

            private:
                void Execute() override;
                void OnDrawInspector() override;
                void OnDrawDebug() const override;

                void OnDrawAddEnemyModelButton();

                const std::string summonEnemyParticlePrefabPath_ = "Resource/Prefab/SummonEnemyCircle.json";
                std::vector<SpawnEnemyModel> spawnEnemyModels_;
            };
        }
    }
}

CEREAL_REGISTER_TYPE(Map::Room::Event::SpawnEntity)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Map::Room::Event::IEntranceEvent, Map::Room::Event::SpawnEntity)
