#pragma once
#include <string>
#include <cereal/cereal.hpp>

class Vector2Int final
{
public:
    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(CEREAL_NVP(x_), CEREAL_NVP(y_));
    }
    
    explicit Vector2Int(const int x = 0.0, const int y = 0.0) : x_(x), y_(y)
    {
    }

    bool        operator==  (const Vector2Int& other) const { return x_ == other.x_ && y_ == other.y_; }
    bool        operator!=  (const Vector2Int& other) const { return !(*this == other); }
    Vector2Int  operator+   (const Vector2Int& other) const;
    Vector2Int  operator-   (const Vector2Int& other) const;
    Vector2Int& operator+=  (const Vector2Int& other);
    Vector2Int& operator-=  (const Vector2Int& other);
    
    float       Dot         (const Vector2Int& other) const;
    float       Magnitude   (                       ) const;
    std::string ToString    (                       ) const;
    void        OnDrawDebug (                       );

    static Vector2Int One();
    
    int x_;
    int y_;
};
