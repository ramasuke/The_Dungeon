#pragma once
#include "../../../../BasicallyParameter/Vector2/Vector2.hpp"

///NOTE: 値オブジェクト推奨
struct SpawnEntranceModel final
{
    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::make_nvp("position", position_),
            cereal::make_nvp("areaSize", areaSize_)
        );
    }

    explicit SpawnEntranceModel(Vector2 position = Vector2(), Vector2 areaSize = Vector2());

    void OnDrawInspector();
    Vector2 Position() const { return position_; }
    Vector2 AreaSize() const { return areaSize_; }
    void OnDrawDebug() const;

private:
    Vector2 position_;
    Vector2 areaSize_;
};
