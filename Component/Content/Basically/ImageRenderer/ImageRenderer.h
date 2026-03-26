#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../Component.hpp"
#include "../Transform/Transform.hpp"

class ImageRenderer final : public virtual Component
{
public:
    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::base_class<Component>(this),
            cereal::make_nvp("renderSpriteFilePath" , renderSpriteFilePath_ ),
            cereal::make_nvp("renderOrder"          , renderOrder_          )
        );
    }

    bool isReverseX_    = false;
    int renderHandleId_ = -1;

private:
    void Init()             override;
    void OnDraw()           override;
    void OnDrawInspector()  override;

    Transform*  transformRef_           = nullptr;
    std::string renderSpriteFilePath_   = "Resource/Sprite/";
    int         renderOrder_            = 1000;
};

CEREAL_REGISTER_TYPE(ImageRenderer)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, ImageRenderer)
