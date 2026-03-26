#pragma once
#include <cereal/cereal.hpp>

#include "../../../IDamageParam/IDamageParam.h"

//NOTE: 値オブジェクト
struct PhysicsPower final : virtual IDamageParam
{
    template <typename Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::make_nvp("value", value_)
        );
    }

    explicit PhysicsPower(const int value = 0) : value_(value)
    {
    }

    bool            operator==  (const PhysicsPower&    other   )   const { return value_ == other.value_; }
    bool            operator!=  (const PhysicsPower&    other   )   const { return !(*this == other); }
    PhysicsPower    operator+   (const PhysicsPower&    other   )   const { return PhysicsPower(value_ + other.value_); }
    PhysicsPower    operator-   (const PhysicsPower&    other   )   const { return PhysicsPower(value_ - other.value_); }
    PhysicsPower    operator*   (const double           scale   )   const { return PhysicsPower(static_cast<int>(value_ * scale)); }
    PhysicsPower    operator/   (const double           divisor )   const { return divisor != 0.0 ? PhysicsPower(static_cast<int>(value_ / divisor)) : *this; }

    int             HitDamage() const override { return value_; }
    
    void            OnDrawInspector ();
    std::string     ToString        () const override;
    ::Color         Color           () const override;

private:
    int value_;
};
