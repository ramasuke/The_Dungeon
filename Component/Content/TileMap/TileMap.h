#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../Component.hpp"
#include "../../../BasicallyParameter/Vector2Int/Vector2Int.h"
#include "../../../Entity/Entity.hpp"
#include "TilePreset/TilePreset.h"
#include "TilePreset/Container/TilePresetContainer.h"
#include "TilePreset/RLE/TilePresetRLE.h"

///NOTE: このコンポーネントはちょっと複雑なのでリファクタリングしていません。
class TileMap final : public virtual Component
{
public:
    TileMap();
    ~TileMap() override;

    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(cereal::base_class<Component>(this));

        dispatchImpl(archive);
    }

    template <class Archive>
    typename std::enable_if<Archive::is_saving::value>::type
    dispatchImpl(Archive& archive)
    {
        auto allRleTile = CompressToRle(allTileId_);
        archive(
            cereal::make_nvp("allRleTileId"         , allRleTile),
            cereal::make_nvp("replaceTilePresetId"  , placeTilePresetId_),
            cereal::make_nvp("gridCellSize"         , gridCellSize_),
            cereal::make_nvp("isPathFindingMap"     , isPathFindingMap_)
        );
    }

    template <class Archive>
    typename std::enable_if<Archive::is_loading::value>::type
    dispatchImpl(Archive& archive)
    {
        
        std::vector<std::vector<Tile::TilePresetRle>> allRleTileId;
        archive(
            cereal::make_nvp("allRleTileId"         , allRleTileId),
            cereal::make_nvp("replaceTilePresetId"  , placeTilePresetId_),
            cereal::make_nvp("gridCellSize"         , gridCellSize_),
            cereal::make_nvp("isPathFindingMap"     , isPathFindingMap_)
        );
        allTileId_ = ExpandFromRle(allRleTileId);
    }


    void OnReplaceTile(const Entity* replaceEntity);

private:
    void Init() override;
    void OnDrawInspector() override;
    void OnEnableEditMode();
    void OnDisableEditMode() const;
    void SetDisablePathFindingPath() const;
    static std::vector<std::vector<Tile::TilePresetRle>> CompressToRle(
        const std::vector<std::vector<int>>& presetIdRows);
    static std::vector<std::vector<int>> ExpandFromRle(const std::vector<std::vector<Tile::TilePresetRle>>& rleMap);
    static Tile::TilePresetContainer& TilePresets();

    std::vector<std::vector<Entity*>> allTile_;
    std::vector<std::vector<int>> allTileId_;

    int placeTilePresetId_ = -1;
    float gridCellSize_ = 43;
    float replaceCellSize_ = 20.0f;
    bool isEraseMode_ = false;
    bool isPathFindingMap_ = false;
};

CEREAL_REGISTER_TYPE(TileMap)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, TileMap)
