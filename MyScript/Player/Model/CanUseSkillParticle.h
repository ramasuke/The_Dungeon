#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../Component/Component.hpp"
#include "../../../Component/Content/Basically/Transform/Transform.hpp"

namespace Player
{
    class CanUseSkillParticle final : public virtual Component
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this),
                cereal::make_nvp("followOffsetPos", followOffsetPos_)
            );
        }

        
        void SetFollowTarget(Transform* followTransform);
        
    private:
        void OnUpdate() override;
        void OnDrawInspector() override;
        
        
        Transform* followTransform_ = nullptr;
        Vector2 followOffsetPos_;
    };
}

CEREAL_REGISTER_TYPE(Player::CanUseSkillParticle)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Player::CanUseSkillParticle)
