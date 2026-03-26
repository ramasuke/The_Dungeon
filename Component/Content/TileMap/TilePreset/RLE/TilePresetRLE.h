#pragma once
#include <cereal/cereal.hpp>

namespace Tile
{
    ///NOTE: 値オブジェクト推奨
    struct TilePresetRle final
    {
        TilePresetRle(const int presetId = -1, const int runLength = 0)
            : presetId_(presetId),
              runLength_(runLength)
        {
        }

        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::make_nvp("presetId", presetId_),
                cereal::make_nvp("runLength", runLength_)
            );
        }

        int PresetId() const { return presetId_; }
        int RunLength() const { return runLength_; }

    private:
        int presetId_ = 0;
        int runLength_ = 0;
    };
}
