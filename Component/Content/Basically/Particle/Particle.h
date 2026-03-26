#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../Component.hpp"
#include "../Renderer/AnimationRenderer/AnimationRenderer.h"

class Particle final : public virtual Component
{
public:
    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::base_class<Component>(this),
            cereal::make_nvp("animationModel", animation_),
            cereal::make_nvp("onDestroyParticleDuration", onDestroyParticleDuration_)
        );
    }

    void Init() override;
    void OnUpdate() override;
    void OnDrawInspector() override;

private:
    AnimationRenderer* animationRenderer_ = nullptr;
    std::shared_ptr<Animation> animation_ = std::make_shared<Animation>();
    int onDestroyParticleDuration_ = 1000;
    int onDestroyParticleDuring_ = 0;
};

CEREAL_REGISTER_TYPE(Particle)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Particle)
