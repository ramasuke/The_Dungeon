#pragma once
#include <cereal/cereal.hpp>

// NOTE: 値オブジェクト
struct MadnessEnergy final
{
    template <typename Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::make_nvp("value", value_)
        );
    }

    explicit MadnessEnergy(const int count = 0) : value_(count)
    {
    }

    MadnessEnergy(const MadnessEnergy&) = default;

    bool operator==(const MadnessEnergy& other) const { return value_ == other.value_; }
    bool operator!=(const MadnessEnergy& other) const { return !(*this == other); }
    MadnessEnergy operator+(const MadnessEnergy& other) const { return MadnessEnergy(value_ + other.value_); }
    MadnessEnergy operator-(const MadnessEnergy& other) const { return MadnessEnergy(value_ - other.value_); }
    MadnessEnergy& operator+=(const MadnessEnergy& other);
    MadnessEnergy& operator-=(const MadnessEnergy& other);
    MadnessEnergy operator*(const double scale) const { return MadnessEnergy(static_cast<int>(value_ * scale)); }
    MadnessEnergy operator/(const double divisor) const{return divisor != 0.0 ? MadnessEnergy(static_cast<int>(value_ / divisor)) : *this;}
    bool operator<(const MadnessEnergy& other) const { return value_ < other.value_; }
    bool operator<=(const MadnessEnergy& other) const { return value_ <= other.value_; }
    bool operator>(const MadnessEnergy& other) const { return value_ > other.value_; }
    bool operator>=(const MadnessEnergy& other) const { return value_ >= other.value_; }

    int Value() const { return value_; }
    void OnDrawInspector();

private:
    int value_;
};
