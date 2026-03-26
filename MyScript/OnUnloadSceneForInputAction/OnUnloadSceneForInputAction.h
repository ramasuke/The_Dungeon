#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../Component/Component.hpp"

class OnUnloadSceneForInputAction final : public virtual Component
{
public:
    template <typename Archive>
        void serialize(Archive& archive)
    {
        archive(
            cereal::base_class<Component>(this),
            cereal::make_nvp("unloadSceneFilePath", unloadSceneFilePath_)
        );
    }

private:
    void OnUpdate() override;
    void OnDrawInspector() override;
    
    std::string unloadSceneFilePath_ = "Resource/Scene/";
};

CEREAL_REGISTER_TYPE(OnUnloadSceneForInputAction)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, OnUnloadSceneForInputAction)
