#pragma once
#include <string>
#include <cereal/cereal.hpp>

#include "../../Libs/Box2D/include/src/box2d/math_functions.h"

struct Vector2
{
    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(CEREAL_NVP(x_), CEREAL_NVP(y_));
    }

    explicit Vector2(const float x = 0.0, const float y = 0.0) : x_(x), y_(y)
    {
    }

    float       Dot             (const Vector2& other   )   const;
    float       Magnitude       (                       )   const;
    Vector2     Normalize       (                       )   const;
    float       SqrtMagnitude   (                       )   const;
    std::string ToString        (                       )   const;
    b2Vec2      ToB2Vec2        (                       )   const;
    float       ToRadian        (                       )   const { return atan2(y_, x_); }
    float       ToDegree        (                       )   const { return ToRadian() * 180.0f / 3.14159265359f; }
    
    void OnDrawDebug();

    static Vector2 Zero ()  { return Vector2(0, 0);     }
    static Vector2 One  ()  { return Vector2(1, 1);     }
    static Vector2 Right()  { return Vector2(1, 0);     }
    static Vector2 Left ()  { return Vector2(-1, 0);    }
    static Vector2 Down ()  { return Vector2(0, 1);     }
    static Vector2 Up   ()  { return Vector2(0, -1);    }
    
    Vector2     operator+   (const Vector2& other   )  const;
    Vector2     operator-   (const Vector2& other   )  const;
    Vector2     operator*   (float scalar           )  const;
    Vector2     operator/   (float scalar           )  const;
    Vector2&    operator+=  (const Vector2& other   );
    Vector2&    operator-=  (const Vector2& other   );
    Vector2&    operator*=  (float scalar           );
    bool        operator==  (const Vector2& other   )   const { return x_ == other.x_ && y_ == other.y_; }
    bool        operator!=  (const Vector2& other   )   const { return !(*this == other);                }
    
    float x_;
    float y_;
};
