#include "TileMap.h"

#include "../../../Application/IApplication/IApplication.hpp"
#include "../../../MyScript/ApplicationExtension/ApplicationExtension.h"
#include "../Basically/Collider/Box/BoxCollider.h"
#include "../Basically/Renderer/SpriteRenderer/SpriteRenderer.h"
#include "MapTile/ReplacableTile.h"

constexpr auto TILE_OPTIOMATION = true;

TileMap::TileMap()
{
    // 外側のベクトルを初期化
    allTile_.resize(GAME_MAP_SIZE_Y);

    for (size_t y = 0; y < GAME_MAP_SIZE_Y; ++y)
    {
        // 各行のベクトルを初期化
        allTile_[y].resize(GAME_MAP_SIZE_X);

        for (size_t x = 0; x < GAME_MAP_SIZE_X; ++x)
        {
            allTile_[y][x] = new Entity();
            allTile_[y][x]->AddComponent<Transform>();
            allTile_[y][x]->GetComponent<Transform>()->position_ = Vector2(x, y) * gridCellSize_;
            allTile_[y][x]->GetComponent<Transform>()->scale_ = 1;
        }
    }

    // 外側のベクトルを初期化
    allTileId_.resize(GAME_MAP_SIZE_Y);

    for (size_t y = 0; y < GAME_MAP_SIZE_Y; ++y)
    {
        // 各行のベクトルを初期化
        allTileId_[y].resize(GAME_MAP_SIZE_X);

        for (size_t x = 0; x < GAME_MAP_SIZE_X; ++x)
        {
            allTileId_[y][x] = TilePresets().EmptyTilePreset().id_;
        }
    }
}

TileMap::~TileMap()
{
    for (int y = 0; y < allTile_.size(); y++)
    {
        for (int x = 0; x < allTile_[y].size(); x++)
        {
            //TODO: 空のマップの時に軽量化のためにTileそのものの削除
            //NOTE: 軽量化
            //WARNING: TileMap削除処理時にTileの削除処理を2重に行わないように注意。
            if (TILE_OPTIOMATION)
            {
                if (allTileId_[y][x] != TilePresets().EmptyTilePreset().id_)
                {
                    allTile_[y][x]->OnDespawn();
                    continue;
                }
            }
            else
            {
                allTile_[y][x]->OnDespawn();
            }
        }
    }
}

void TileMap::OnReplaceTile(const Entity* replaceEntity)
{
    if (!replaceEntity)
        return;

    const auto placeTilePreset = TilePresets().CatchTilePreset(placeTilePresetId_);

    for (int y = 0; y < allTile_.size(); y++)
    {
        for (int x = 0; x < allTile_[y].size(); x++)
        {
            if (!allTile_[y][x] || allTile_[y][x] != replaceEntity)
                continue;

            allTile_[y][x]->OnDespawn();
            allTile_[y][x] = new Entity();
            if (isEraseMode_)
            {
                allTile_[y][x]->AddComponent<Transform>();
                allTile_[y][x]->Init();
                allTile_[y][x]->GetComponent<Transform>()->position_ = Vector2(x, y) * gridCellSize_;
                allTile_[y][x]->GetComponent<Transform>()->scale_ = placeTilePreset.cellTransformScale_;
                allTileId_[y][x] = -1;
                continue;
            }

            allTile_[y][x]->AddComponent<Transform>();
            allTile_[y][x]->AddComponent<SpriteRenderer>();
            if (placeTilePreset.enableAttachCollider_)
            {
                auto& boxCollider = allTile_[y][x]->AddComponent<BoxCollider>();
                boxCollider.SetSize(placeTilePreset.cellColliderScale_);
                boxCollider.SetBodyType(placeTilePreset.colliderBodyTypeId_);
                boxCollider.SetEnableContactEvent(true);
                boxCollider.SetEnableHitEvent(true);
                boxCollider.OnDestroyBody();
            }
            allTile_[y][x]->AddComponent<ReplacableTile>().SetParameter(this, replaceCellSize_);
            allTile_[y][x]->GetComponent<SpriteRenderer>()->SetRenderOrder(placeTilePreset.renderOrder_);
            allTile_[y][x]->Init();
            allTile_[y][x]->GetComponent<SpriteRenderer>()->SetRenderHandleId(placeTilePreset.RenderHandleId());
            allTile_[y][x]->GetComponent<Transform>()->position_ = Vector2(x, y) * gridCellSize_;
            allTile_[y][x]->GetComponent<Transform>()->scale_ = placeTilePreset.cellTransformScale_;
            allTileId_[y][x] = placeTilePreset.id_;
        }
    }
}

void TileMap::Init()
{
    for (int y = 0; y < allTile_.size(); y++)
    {
        for (int x = 0; x < allTile_[y].size(); x++)
        {
            //TODO: 空のマップの時に軽量化のためにTileそのものの削除
            //NOTE: 軽量化
            //WARNING: TileMap削除処理時にTileの削除処理を2重に行わないように注意。
            if (TILE_OPTIOMATION)
            {
                if (allTileId_[y][x] == TilePresets().EmptyTilePreset().id_)
                {
                    allTile_[y][x]->OnDespawn();
                    continue;
                }                
            }

            const auto placeTilePreset = TilePresets().CatchTilePreset(allTileId_[y][x]);

            if (placeTilePreset.enableAttachCollider_)
            {
                auto& boxCollider = allTile_[y][x]->AddComponent<BoxCollider>();
                boxCollider.SetSize(placeTilePreset.cellColliderScale_);
                boxCollider.SetBodyType(placeTilePreset.colliderBodyTypeId_);
                boxCollider.SetEnableContactEvent(true);
                boxCollider.SetEnableHitEvent(true);
                boxCollider.OnDestroyBody();
            }
            if (placeTilePreset.RenderHandleId() != -1)
            {
                allTile_[y][x]->AddComponent<SpriteRenderer>();
                allTile_[y][x]->GetComponent<SpriteRenderer>()->SetRenderOrder(placeTilePreset.renderOrder_);
            }
            allTile_[y][x]->Init();
            if (allTile_[y][x]->GetComponent<SpriteRenderer>() != nullptr)
            {
                allTile_[y][x]->GetComponent<SpriteRenderer>()->SetRenderHandleId(placeTilePreset.RenderHandleId());
            }
            allTile_[y][x]->GetComponent<Transform>()->position_ = Vector2(x, y) * gridCellSize_;
            allTile_[y][x]->GetComponent<Transform>()->scale_ = placeTilePreset.cellTransformScale_;
        }
    }

    if (isPathFindingMap_)
    {
        SetDisablePathFindingPath();
    }
}

void TileMap::OnDrawInspector()
{
    ImGui::InputInt("placeTilePresetId", &placeTilePresetId_);
    ImGui::Checkbox("isEraseMode", &isEraseMode_);
    ImGui::Checkbox("isPathFindingMap", &isPathFindingMap_);
    if (ImGui::Button("OnEnableEditMode"))
    {
        OnEnableEditMode();
    }

    if (ImGui::Button("OnDisableEditMode"))
    {
        OnDisableEditMode();
    }
}

void TileMap::OnEnableEditMode()
{
    for (auto& y : allTile_)
    {
        for (const auto& entity : y)
        {
            entity->AddComponent<ReplacableTile>().SetParameter(this, replaceCellSize_);
        }
    }
}

void TileMap::OnDisableEditMode() const
{
    for (auto& y : allTile_)
    {
        for (const auto& entity : y)
        {
            entity->RemoveComponent<ReplacableTile>();
        }
    }
}

void TileMap::SetDisablePathFindingPath() const
{
    std::vector<std::vector<bool>> map;
    map.resize(allTile_.size());

    for (int y = 0; y < allTile_.size(); y++)
    {
        map[y].resize(allTile_[y].size());
        for (int x = 0; x < allTile_[y].size(); x++)
        {
            map[y][x] = allTile_[y][x]->GetComponent<Collider>() != nullptr;
        }
    }

    IApplication::GetInstance().Extension().AStar().SetMap(map);
}

std::vector<std::vector<Tile::TilePresetRle>> TileMap::CompressToRle(const std::vector<std::vector<int>>& presetIdRows)
{
    std::vector<std::vector<Tile::TilePresetRle>> compressed;

    for (const auto& row : presetIdRows)
    {
        std::vector<Tile::TilePresetRle> rleRow;
        if (row.empty())
        {
            compressed.emplace_back();
            continue;
        }

        int currentId = row[0];
        int count = 1;

        for (size_t i = 1; i < row.size(); ++i)
        {
            if (row[i] == currentId)
            {
                ++count;
            }
            else
            {
                rleRow.emplace_back(currentId, count);
                currentId = row[i];
                count = 1;
            }
        }

        rleRow.emplace_back(currentId, count);
        compressed.push_back(std::move(rleRow));
    }

    return compressed;
}

std::vector<std::vector<int>> TileMap::ExpandFromRle(const std::vector<std::vector<Tile::TilePresetRle>>& rleMap)
{
    std::vector<std::vector<int>> expanded;

    for (const auto& rleRow : rleMap)
    {
        std::vector<int> row;

        for (const auto& rle : rleRow)
        {
            row.insert(row.end(), rle.RunLength(), rle.PresetId());
        }

        expanded.push_back(std::move(row));
    }

    return expanded;
}

Tile::TilePresetContainer& TileMap::TilePresets()
{
    static Tile::TilePresetContainer tilePresets;
    return tilePresets;
}
