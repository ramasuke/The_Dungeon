#include "Random.h"
#include <random>

namespace {
    static std::mt19937& Generator() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }
}

int Random::Range(const int min, const int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(Generator());
}

float Random::Range(const float min, const float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(Generator());
}