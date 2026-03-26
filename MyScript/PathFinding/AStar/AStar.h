#pragma once
#include <list>
#include <vector>
#include "../../../BasicallyParameter/Vector2Int/Vector2Int.h"

namespace PathFinding
{
    enum ChipType { Plane, Wall };
    enum State { Unchecked = 0, InOpenList, InCloseList };

    class AStar final
    {
    public:
        std::list<Vector2Int> FindRoute(Vector2Int start, Vector2Int goal, short maxPathDistance = 13);
        void SetMap(const std::vector<std::vector<bool>>& map);

    private:
        static constexpr int DIR_MAX = 4;
        static constexpr int X_ELM = 0;
        static constexpr int Y_ELM = 1;
        
        int directionDelta_[DIR_MAX][2] = {
            { 0, -1 }, // 上
            { 0, +1 }, // 下
            { -1, 0 }, // 左
            { +1, 0 }, // 右
        };

        short chipCost_[2] = {1, 255};

        std::vector<std::vector<bool>> map_;
    };
}