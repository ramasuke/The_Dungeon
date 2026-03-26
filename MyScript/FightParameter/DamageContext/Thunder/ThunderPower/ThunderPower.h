#pragma once
#include <cereal/cereal.hpp>

#include "../../../IDamageParam/IDamageParam.h"

//Note: 値オブジェクト
struct ThunderPower final : virtual IDamageParam
{
    template <typename Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::make_nvp("value", value_),
            cereal::make_nvp("numbDuration", numbDuration_)
        );
    }

    explicit ThunderPower(const int value = 0) : value_(value)
    {
    }

    ThunderPower(const ThunderPower&) = default;
    bool operator==(const ThunderPower& other) const { return value_ == other.value_; }
    bool operator!=(const ThunderPower& other) const { return !(*this == other); }
    ThunderPower operator+(const ThunderPower& other) const { return ThunderPower(value_ + other.value_); }
    ThunderPower operator-(const ThunderPower& other) const { return ThunderPower(value_ - other.value_); }
    ThunderPower operator*(const double scale) const { return ThunderPower(static_cast<int>(value_ * scale)); }

    ThunderPower operator/(const double divisor) const
    {
        return divisor != 0.0 ? ThunderPower(static_cast<int>(value_ / divisor)) : *this;
    }

    int HitDamage() const override { return value_; }
    int NumbDuration() const { return numbDuration_; }
    void OnDrawInspector();
    std::string ToString() const override;
    ::Color Color() const override;

private:
    int value_;
    int numbDuration_ = 30;
};
