#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../Component/Component.hpp"
#include "../../../Component/Content/Basically/Renderer/AnimationRenderer/Animation/Animation.h"
#include "../../FightParameter/MadnessEnergy/MadnessEnergy.h"
#include "../../FightParameter/IReceivablePlayerAttack/IReceivablePlayerAttack.h"

class TorchObject final : public virtual Component,
                          public virtual IReceivablePlayerAttack
{
public:
    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::base_class<Component>(this),
            cereal::make_nvp("animationModel", animation_),
            cereal::make_nvp("dropComboEnergy", dropComboEnergy_)
        );
    }

private:
    void Init() override;
    void OnDrawInspector() override;
    void OnDamage(std::shared_ptr<DamageContext::IDamageContext> damage) override;
    Vector2 Position() const override;

    const std::string onDestroyParticlePrefabPath_ = "Resource/Prefab/OnDestroyTorchParticle.json";
    const Vector2 onDestroyParticleOffset_ = Vector2(0,-17);
    std::shared_ptr<Animation> animation_ = std::make_shared<Animation>();
    MadnessEnergy dropComboEnergy_;
};

CEREAL_REGISTER_TYPE(TorchObject)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, TorchObject)
