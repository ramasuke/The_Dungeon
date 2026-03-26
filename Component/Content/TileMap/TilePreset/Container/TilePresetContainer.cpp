#include "TilePresetContainer.h"

Tile::TilePresetContainer::TilePresetContainer()
{
    // RedDungeon
    contents_.emplace_back(100, 2.71f, false, Vector2(21.5, 21.5), 0, -10,
                           LoadGraph("Resource/Sprite/Tile/RedDungeon/EmptyFloor.png"));
    contents_.emplace_back(101, 2.71f, false, Vector2(21.5, 21.5), 0, -10,
                           LoadGraph("Resource/Sprite/Tile/RedDungeon/UpLeftFloor.png"));
    contents_.emplace_back(102, 2.71f, false, Vector2(21.5, 21.5), 0, -10,
                           LoadGraph("Resource/Sprite/Tile/RedDungeon/UpCenterFloor.png"));
    contents_.emplace_back(103, 2.71f, false, Vector2(21.5, 21.5), 0, -10,
                           LoadGraph("Resource/Sprite/Tile/RedDungeon/UpRightFloor.png"));
    contents_.emplace_back(104, 2.71f, false, Vector2(21.5, 21.5), 0, -10,
                           LoadGraph("Resource/Sprite/Tile/RedDungeon/LeftFloor.png"));
    contents_.emplace_back(105, 2.71f, false, Vector2(21.5, 21.5), 0, -10,
                           LoadGraph("Resource/Sprite/Tile/RedDungeon/CenterFloor.png"));
    contents_.emplace_back(106, 2.71f, false, Vector2(21.5, 21.5), 0, -10,
                           LoadGraph("Resource/Sprite/Tile/RedDungeon/RightFloor.png"));
    contents_.emplace_back(107, 2.71f, false, Vector2(21.5, 21.5), 0, -10,
                           LoadGraph("Resource/Sprite/Tile/RedDungeon/DownLeftFloor.png"));
    contents_.emplace_back(108, 2.71f, false, Vector2(21.5, 21.5), 0, -10,
                           LoadGraph("Resource/Sprite/Tile/RedDungeon/DownFloor.png"));
    contents_.emplace_back(109, 2.71f, false, Vector2(21.5, 21.5), 0, -10,
                           LoadGraph("Resource/Sprite/Tile/RedDungeon/DownRightFloor.png"));

    contents_.emplace_back(110, 2.71f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/RedDungeon/LeftWall.png"));
    contents_.emplace_back(111, 2.71f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/RedDungeon/RightWall.png"));
    contents_.emplace_back(112, 2.71f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/RedDungeon/UpWall.png"));
    contents_.emplace_back(113, 2.71f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/RedDungeon/DownWall.png"));
    contents_.emplace_back(114, 2.71f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/RedDungeon/DownLeftWall.png"));
    contents_.emplace_back(115, 2.71f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/RedDungeon/DownRightWall.png"));

    contents_.emplace_back(121, 2.71f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/RedDungeon/UpLeftEdge.png"));
    contents_.emplace_back(122, 2.71f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/RedDungeon/UpRightEdge.png"));
    contents_.emplace_back(123, 2.71f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/RedDungeon/DownLeftEdge.png"));
    contents_.emplace_back(124, 2.71f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/RedDungeon/DownRightEdge.png"));

    contents_.emplace_back(140, 2.71f, false, Vector2(21.5, 21.5), 0, -10,
                           LoadGraph("Resource/Sprite/Tile/RedDungeon/DesignedFloor.png"));
    contents_.emplace_back(141, 2.71f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/RedDungeon/UpWallBanner.png"));
    contents_.emplace_back(142, 2.71f, false, Vector2(21.5, 21.5), 0, -10,
                           LoadGraph("Resource/Sprite/Tile/RedDungeon/CenterSkullFloor.png"));

    // SandStone
    contents_.emplace_back(201, 1.355f, false, Vector2(21.5, 21.5), 0, -10,
                           LoadGraph("Resource/Sprite/Tile/SandStone/Floor.png"));

    contents_.emplace_back(221, 1.355f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/SandStone/LeftWall.png"));
    contents_.emplace_back(222, 1.355f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/SandStone/UpWall.png"));
    contents_.emplace_back(223, 1.355f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/SandStone/RightWall.png"));
    contents_.emplace_back(224, 1.355f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/SandStone/DownLeftWall.png"));
    contents_.emplace_back(225, 1.355f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/SandStone/DownWall.png"));
    contents_.emplace_back(226, 1.355f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/SandStone/DownRightWall.png"));

    contents_.emplace_back(231, 1.355f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/SandStone/UpLeftEdge.png"));
    contents_.emplace_back(232, 1.355f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/SandStone/UpRightEdge.png"));

    // WhiteGrayDungeon
    contents_.emplace_back(300, 2.71f, false, Vector2(21.5, 21.5), 0, -10,
                           LoadGraph("Resource/Sprite/Tile/WhiteGrayDungeon/EmptyFloor.png"));
    contents_.emplace_back(301, 2.71f, false, Vector2(21.5, 21.5), 0, -10,
                           LoadGraph("Resource/Sprite/Tile/WhiteGrayDungeon/Floor.png"));
    contents_.emplace_back(302, 2.71f, false, Vector2(21.5, 21.5), 0, -10,
                           LoadGraph("Resource/Sprite/Tile/WhiteGrayDungeon/DesignedFloor.png"));
    contents_.emplace_back(311, 2.71f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/WhiteGrayDungeon/LeftUpWall.png"));
    contents_.emplace_back(312, 2.71f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/WhiteGrayDungeon/CenterUpWall.png"));

    contents_.emplace_back(313, 2.71f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/WhiteGrayDungeon/RightUpWall.png"));
    contents_.emplace_back(314, 2.71f, true, Vector2(21.5, 21.5), 0, 10,
                       LoadGraph("Resource/Sprite/Tile/WhiteGrayDungeon/LeftWall.png"));
    contents_.emplace_back(315, 2.71f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/WhiteGrayDungeon/RightWall.png"));
    contents_.emplace_back(316, 2.71f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/WhiteGrayDungeon/LeftDownWall.png"));
    contents_.emplace_back(317, 2.71f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/WhiteGrayDungeon/DownCenterWall.png"));
    contents_.emplace_back(318, 2.71f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/WhiteGrayDungeon/RightDownWall.png"));
    contents_.emplace_back(319, 2.71f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/WhiteGrayDungeon/LeftUpEdge.png"));
    contents_.emplace_back(320, 2.71f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/WhiteGrayDungeon/RightUpEdge.png"));
    contents_.emplace_back(321, 2.71f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/WhiteGrayDungeon/DownLeftEdge.png"));
    contents_.emplace_back(322, 2.71f, true, Vector2(21.5, 21.5), 0, 10,
                           LoadGraph("Resource/Sprite/Tile/WhiteGrayDungeon/DownRightEdge.png"));
}

Tile::TilePreset Tile::TilePresetContainer::CatchTilePreset(const int presetId) const
{
    const auto it = std::find_if(contents_.begin(), contents_.end(), [&](const Tile::TilePreset& preset)
    {
        return preset.id_ == presetId;
    });

    if (it != contents_.end())
    {
        return *it;
    }

    return emptyTilePreset_;
}
