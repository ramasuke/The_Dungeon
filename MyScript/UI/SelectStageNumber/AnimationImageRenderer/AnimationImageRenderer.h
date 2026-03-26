#pragma once
#include <memory>
#include <cereal/types/polymorphic.hpp>

#include "../../../../Component/Component.hpp"
#include "../../../../Component/Content/Basically/Renderer/AnimationRenderer/Animation/Animation.h"
#include "../../../../Component/Content/Basically/Transform/Transform.hpp"

class AnimationImageRenderer final : public virtual Component
{
public:
    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::base_class<Component>(this),
            cereal::make_nvp("animation_", animation_),
            cereal::make_nvp("renderOrder", renderOrder_),
            cereal::make_nvp("offsetPos", offsetPos_),
            cereal::make_nvp("isReverseX", isReverseX_)
        );
    }

    void SetAnimation(const std::shared_ptr<Animation>& animation);
    bool IsPlayingAnim() const;

private:
    void Init()             override;
    void OnUpdate()         override;
    void OnDraw()           override;
    void OnDrawInspector()  override;

    void RestartAnimation();

    Transform* transformRef_ = nullptr;

    std::shared_ptr<Animation> animation_ = std::make_shared<Animation>();

    bool    isReverseX_ = false;
    Vector2 offsetPos_  = Vector2(0, 0);

    int renderOrder_ = 0;

    int effectDuringFrame_   = 0;
    int currentHandleIndex_  = 0;
};

CEREAL_REGISTER_TYPE(AnimationImageRenderer)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, AnimationImageRenderer)
