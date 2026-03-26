#pragma once
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/memory.hpp>

#include "../../../../Component.hpp"
#include "../../Transform/Transform.hpp"
#include "Animation/Animation.h"

class AnimationRenderer final : public virtual Component
{
public:
    template <typename Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::base_class<Component>(this),
            cereal::make_nvp("renderOrder", renderOrder_)
        );
    }

    bool    isReverseX_ = false;
    Vector2 offsetPos_ = Vector2(0, 0);
    
    void    SetAnimation(const std::shared_ptr<Animation>& animation);
    bool    IsPlayingAnim()     const;
    Vector2 ToTurnDirction()    const { return isReverseX_ ? Vector2::Left() : Vector2::Right(); }
    
private:
    void Init()             override;
    void OnUpdate()         override;
    void OnDraw()           override;
    void OnDrawInspector()  override;
    void OnRestaratAnimation();

    Transform* transformRef_ = nullptr;
    std::shared_ptr<Animation> animation_ = std::make_shared<Animation>();
    int renderOrder_ = 0;
    int effectDuringFrame_ = 0;
    int currentHandleIndex_ = 0;
};

CEREAL_REGISTER_TYPE(AnimationRenderer)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, AnimationRenderer)
