#pragma once
#include <cereal/cereal.hpp>

//NOTE: 値オブジェクト推奨
struct Color final
{
    explicit Color(const int r = 255, const int g = 255, const int b = 255)
        : r_(r),
          g_(g),
          b_(b)
    {
    }

    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::make_nvp("r", r_),
            cereal::make_nvp("g", g_),
            cereal::make_nvp("b", b_)
        );
    }

    int ToColorId() const;
    void OnDrawInspector();

private:
    int r_;
    int g_;
    int b_;
};
