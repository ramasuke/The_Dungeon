#pragma once
#include <vector>

#include "../TilePreset.h"

namespace Tile
{
    class TilePresetContainer final
    {
    public:
        explicit TilePresetContainer();


        TilePreset EmptyTilePreset()                const { return emptyTilePreset_; }
        TilePreset CatchTilePreset(int presetId)    const;

    private:
        const TilePreset emptyTilePreset_ = TilePreset(-1, 1.0f, false, Vector2(1, 1), 0, -10, -1);
        std::vector<TilePreset> contents_;
    };
}
