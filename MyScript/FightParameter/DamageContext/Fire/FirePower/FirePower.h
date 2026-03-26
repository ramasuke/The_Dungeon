#pragma once
#include <cereal/cereal.hpp>

#include "../../../IDamageParam/IDamageParam.h"

// Note: 値オブジェクト
struct FirePower final : virtual IDamageParam
{
    template <typename Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::make_nvp("hitDamage", hitDamage_),
            cereal::make_nvp("burnDamage", burnDamage_),
            cereal::make_nvp("burnDuration", burnDuration_)
        );
    }

    explicit FirePower(const int value = 0) : hitDamage_(value)
    {
    }

    FirePower(const FirePower&) = default;
    bool operator==(const FirePower& other) const { return hitDamage_ == other.hitDamage_; }
    bool operator!=(const FirePower& other) const { return !(*this == other); }
    FirePower operator+(const FirePower& other) const { return FirePower(hitDamage_ + other.hitDamage_); }
    FirePower operator-(const FirePower& other) const { return FirePower(hitDamage_ - other.hitDamage_); }
    FirePower operator*(const double scale) const { return FirePower(static_cast<int>(hitDamage_ * scale)); }

    FirePower operator/(const double divisor) const
    {
        return divisor != 0.0 ? FirePower(static_cast<int>(hitDamage_ / divisor)) : *this;
    }

    int HitDamage() const override { return hitDamage_; }
    int BurnDamage() const { return burnDamage_; }
    int BurnDuration() const { return burnDuration_; }
    void OnDrawInspector();
    std::string ToString() const override;
    ::Color Color() const override;

private:
    int hitDamage_ = 1;
    int burnDamage_ = 1;
    int burnDuration_ = 5;
};