#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../../Component.hpp"

class SetIsReverse final : public virtual Component
{
public:
    template <typename Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::base_class<Component>(this),
            cereal::make_nvp("isReverseX", isReverseX_)
        );
    }

private:
    void Init() override;
    void OnDrawInspector() override;
    
    bool isReverseX_ = false;
};

CEREAL_REGISTER_TYPE(SetIsReverse)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, SetIsReverse)