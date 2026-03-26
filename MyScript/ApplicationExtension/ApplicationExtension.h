#pragma once
#include "../PathFinding/AStar/AStar.h"
#include "../Player/Model/BasicParam/BasicParam.h"
constexpr int GAME_MAP_SIZE_X = 130;
constexpr int GAME_MAP_SIZE_Y = 130;

class Transform;

class ApplicationExtension final
{
public:
    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::make_nvp("playerParam", playerParam_)
        );
    }

    std::shared_ptr<Player::BasicParam> PlayerParam() { return playerParam_; }
    PathFinding::AStar& AStar() { return aStar_; }

private:
    std::shared_ptr<Player::BasicParam> playerParam_ = std::make_shared<Player::BasicParam>();
    PathFinding::AStar aStar_;
};
