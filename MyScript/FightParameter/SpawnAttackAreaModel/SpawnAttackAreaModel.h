#pragma once
#include <cereal/cereal.hpp>

#include "../../../BasicallyParameter/Vector2/Vector2.hpp"

class Entity;

///NOTE: 値オブジェクト推奨
struct SpawnAttackAreaModel final
{
    template <typename Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::make_nvp("offset"           , offset_           ),
            cereal::make_nvp("size"             , size_             ),
            cereal::make_nvp("despawnDuration"  , despawnDuration_  )
        );
    }

    explicit SpawnAttackAreaModel(Vector2 offset = Vector2(), Vector2 size = Vector2(10, 10), int despawnDuration = 0);

    void OnDrawInspector(Entity& spawnOffset);
    void OnDrawDebug    (Entity& spawnOffset) const;

    Vector2 Offset()        const { return offset_;             }
    Vector2 AreaSize()      const { return size_;               }
    int DespawnDuration()   const { return despawnDuration_;    }

private:
    Vector2 offset_;
    Vector2 size_;
    int     despawnDuration_;
};
