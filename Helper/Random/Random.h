#pragma once

namespace Random
{
    int Range(int min, int max);
    float Range(float min, float max);

    ///値オブジェクト推奨
    template <typename T>
    struct Context final
    {
        Context(const T& min, const T& max)
            : min_(min),
              max_(max)
        {
        }

        const T min_;
        const T max_;
    };
};
