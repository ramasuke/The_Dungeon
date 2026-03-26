#include "Particle.h"

#include "../../../../Entity/Entity.hpp"

void Particle::Init()
{
    animationRenderer_ = EntityRef().GetComponent<AnimationRenderer>();
    if (animationRenderer_ == nullptr)
    {
        animationRenderer_ = &EntityRef().AddComponent<AnimationRenderer>();
    }
    animation_->Init();
    animationRenderer_->SetAnimation(animation_);
}

void Particle::OnUpdate()
{
    onDestroyParticleDuring_++;

    if (onDestroyParticleDuring_ <= onDestroyParticleDuration_)
        return;

    EntityRef().OnDespawn();
}

void Particle::OnDrawInspector()
{
    ImGui::InputInt("onDestroyParticleDuration", &onDestroyParticleDuration_);
    if (ImGui::TreeNode("AnimationModel"))
    {
        animation_->OnDrawInspector();
        ImGui::TreePop();
        ImGui::Spacing();
    }
    if (ImGui::Button("OnUpdateParticle"))
    {
        animationRenderer_->SetAnimation(animation_);
    }
}
