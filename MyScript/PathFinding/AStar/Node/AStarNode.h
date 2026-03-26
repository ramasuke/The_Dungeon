#pragma once

// ノード構造体の定義
struct AStarNode {
    short cost_;
    short score_;
    char state_;
    char direction_;
};
