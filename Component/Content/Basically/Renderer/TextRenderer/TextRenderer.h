#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../Component.hpp"
#include "../../Color/Color.h"
#include "../../Transform/Transform.hpp"

class TextRenderer final : public virtual Component
{
public:
    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::base_class<Component>(this),    
            cereal::make_nvp("worldSpace", isWorldSpace_),
            cereal::make_nvp("text", text_),
            cereal::make_nvp("color", color_),
            cereal::make_nvp("fontFilePath", fontName_),
            cereal::make_nvp("renderOrder", renderOrder_)
        );
    }
    std::string text_;
    Color color_ = Color();

private:
    void Init() override;
    void OnDraw() override;
    void OnDrawInspector() override;

    bool isWorldSpace_ = true;
    std::string fontName_;
    int renderOrder_ = 0;
    int fontHandleId_ = -1;
    Transform* transformRef_ = nullptr;
};

CEREAL_REGISTER_TYPE(TextRenderer)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, TextRenderer)
