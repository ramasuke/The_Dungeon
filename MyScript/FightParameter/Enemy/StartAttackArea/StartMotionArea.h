#pragma once
#include "../../../../BasicallyParameter/Vector2/Vector2.hpp"

///NOTE: 値オブジェクト推奨
struct StartMotionArea final
{
    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::make_nvp("offset", offset_),
            cereal::make_nvp("size", size_)
        );
    }

    explicit StartMotionArea(Vector2 offset = Vector2(), Vector2 size = Vector2(100, 100));
    
    void OnDrawInspector(Vector2 origin);
    void OnDrawDebug(Vector2 origin) const;
    Vector2 Offset() const { return offset_; }
    Vector2 Size() const { return size_; }

private:
    Vector2 offset_;
    Vector2 size_ = Vector2(100, 100);
};
