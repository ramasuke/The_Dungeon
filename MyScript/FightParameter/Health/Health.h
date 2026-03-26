#pragma once
#include <cereal/cereal.hpp>

constexpr auto HEALTH_DEATH_VALUE = 0;

//NOTE: 値オブジェクト
struct Health final
{
    template <typename Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::make_nvp("value", value_)
        );
    }

    explicit Health(const int value = 0) : value_(value)
    {
    }

    Health(const Health&) = default;

    bool operator==(const Health& other) const { return value_ == other.value_; }
    bool operator!=(const Health& other) const { return !(*this == other); }
    Health operator+(const Health& other) const { return Health(value_ + other.value_); }
    Health operator-(const Health& other) const { return Health(value_ - other.value_); }
    Health operator*(const double scale) const { return Health(static_cast<int>(value_ * scale)); }
    Health operator/(const double divisor) const {return divisor != 0.0 ? Health(static_cast<int>(value_ / divisor)) : *this;}
    bool operator<(const Health& other) const { return value_ < other.value_; }
    bool operator<=(const Health& other) const { return value_ <= other.value_; }
    bool operator>(const Health& other) const { return value_ > other.value_; }
    bool operator>=(const Health& other) const { return value_ >= other.value_;}
    Health& operator+=(const Health& other) {
        value_ += other.value_;
        return *this;
    }

    Health& operator-=(const Health& other) {
        value_ -= other.value_;
        return *this;
    }

    int Value() const { return value_; }
    void OnDrawInspector();
    bool IsDeath() const;
    std::string ToString() const { return std::to_string(value_); }

private:
    int value_;
};
