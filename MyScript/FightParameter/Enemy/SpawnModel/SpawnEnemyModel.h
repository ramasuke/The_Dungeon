#pragma once
#include <cereal/cereal.hpp>

#include "../../../../BasicallyParameter/Vector2/Vector2.hpp"

struct SpawnEnemyModel final
{
    explicit SpawnEnemyModel(const Vector2 onSpawnEnemyPos = Vector2(), std::string spawnEnemyPrefabPath = "Resource/Prefab/")
        : onSpawnEnemyPos_(onSpawnEnemyPos),
          spawnEnemyPrefabPath_(std::move(spawnEnemyPrefabPath))
    {
    }

    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::make_nvp("onSpawnEnemyPos"      , onSpawnEnemyPos_      ),
            cereal::make_nvp("spawnEnemyPrefabPath" , spawnEnemyPrefabPath_ )
        );
    }

    void OnDrawInspector();
    void OnDrawDebug() const;
    Vector2 Position() const;
    std::string PrefabPath() const;

private:
    Vector2 onSpawnEnemyPos_;
    std::string spawnEnemyPrefabPath_;
};
