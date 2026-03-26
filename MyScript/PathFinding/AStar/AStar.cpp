#include "AStar.h"

#include "Node/AStarNode.h"

void PathFinding::AStar::SetMap(const std::vector<std::vector<bool>>& map)
{
    map_ = map;
}

std::list<Vector2Int> PathFinding::AStar::FindRoute(const Vector2Int start,
                                                    const Vector2Int goal,
                                                    const short maxPathDistance)
{
    const int height = static_cast<int>(map_.size());
    const int width = static_cast<int>(map_[0].size());

    std::vector<std::vector<AStarNode>> mapNode;
    mapNode.resize(height, std::vector<AStarNode>(width));
    std::list<Vector2Int> result;
    std::list<Vector2Int> openList = {start};
    mapNode[start.y_][start.x_].state_ = InOpenList;

    Vector2Int current;

    while (!openList.empty())
    {
        if (openList.front() == goal)
        {
            result.push_front(goal);
            for (current = openList.front(); current != start; result.push_front(current))
            {
                const AStarNode& currentNode = mapNode[current.y_][current.x_];
                current.x_ -= directionDelta_[currentNode.direction_][X_ELM];
                current.y_ -= directionDelta_[currentNode.direction_][Y_ELM];
            }
            break;
        }

        current = openList.front();
        AStarNode& currentNode = mapNode[current.y_][current.x_];

        // 最大距離制限
        if (currentNode.cost_ > maxPathDistance)
        {
            openList.remove(current);
            continue;
        }

        for (int i = 0; i < DIR_MAX; i++)
        {
            const int tmpX = current.x_ + directionDelta_[i][X_ELM];
            const int tmpY = current.y_ + directionDelta_[i][Y_ELM];
            if (tmpX < 0 || tmpX >= width || tmpY < 0 || tmpY >= height) continue;
            if (map_[tmpY][tmpX] == Wall) continue;

            AStarNode& nextNode = mapNode[tmpY][tmpX];
            if (nextNode.state_ != Unchecked) continue;

            const short cost = currentNode.cost_ + chipCost_[map_[tmpY][tmpX]];
            if (cost > maxPathDistance) continue; //ここでも距離制限

            int deltaX = std::abs(tmpX - goal.x_);
            int deltaY = std::abs(tmpY - goal.y_);
            const short heuristic = static_cast<short>(std::max(deltaX, deltaY));
            const short score = cost + heuristic;

            nextNode.cost_ = cost;
            nextNode.score_ = score;
            nextNode.direction_ = static_cast<char>(i);
            nextNode.state_ = InOpenList;

            auto iter = openList.begin();
            for (; iter != openList.end(); ++iter)
            {
                if (score <= mapNode[iter->y_][iter->x_].score_)
                {
                    openList.insert(iter, Vector2Int{tmpX, tmpY});
                    break;
                }
            }
            if (iter == openList.end())
            {
                openList.emplace_back(tmpX, tmpY);
            }
        }

        currentNode.state_ = InCloseList;
        openList.remove(current);
    }

    return result;
}
