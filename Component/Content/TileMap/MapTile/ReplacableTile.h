#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../TileMap.h"
#include "../../../Component.hpp"
#include "../../Basically/Transform/Transform.hpp"

class ReplacableTile final : public virtual Component
{
public:
    template <typename Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::base_class<Component>(this),
            cereal::make_nvp("gridCellSize", gridCellSize_),
            cereal::make_nvp("enableClickDuration", enableClickDuration_)
        );
    }

    void SetParameter(TileMap* tileMap, float cellSize);

private:
    void Init() override;
    void OnUpdate() override;
    void OnEditorUpdate() override;
    void OnDrawInspector() override;

    TileMap* tileMapRef_ = nullptr;
    Transform* transform_ = nullptr;
    float gridCellSize_ = 0;
    int enableClickDuring_ = 0;
    int enableClickDuration_ = 20;
};

CEREAL_REGISTER_TYPE(ReplacableTile)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, ReplacableTile)
