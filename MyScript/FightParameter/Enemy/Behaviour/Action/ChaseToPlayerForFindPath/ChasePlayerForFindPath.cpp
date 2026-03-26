#include "ChasePlayerForFindPath.h"

#include "../../../../../../Component/Content/Basically/Collider/Collider.h"
#include "../../../../../../Component/Content/Basically/Renderer/AnimationRenderer/AnimationRenderer.h"
#include "../../../../../../Component/Content/Basically/Transform/Transform.hpp"
#include "../../../../../../Libs/Box2D/include/src/box2d/box2d.h"
#include "../../../Helper/EnemyHelper.h"

Enemy::Behaviour::Action::ChasePlayerForFindPath::ChasePlayerForFindPath(Entity& self, const float moveSpeed, const int maxPathDistance)
    : self_(self), moveSpeed_(moveSpeed * 2), maxPathDistance_(maxPathDistance)
{
}

Ai::INode::Status Enemy::Behaviour::Action::ChasePlayerForFindPath::operator()() const
{
    const auto currentPos = self_.GetComponent<Transform>()->position_;

    // 探索が未開始ならスレッド起動
    if (!isSearching_)
    {
        isSearching_ = true;
        isReady_ = false;

        const auto pos = currentPos;
        pathThread_ = std::thread([this, pos]()
        {
            {
                auto path = EnemyHelper::FindToPlayerPath(pos);
                std::lock_guard<std::mutex> lock(mutex_);
                cachedPath_ = std::move(path);
            }

            isReady_ = true;
        });

        pathThread_.detach();
        return Ai::INode::Status::Running;
    }

    // 探索完了チェック
    if (!isReady_)
    {
        return Ai::INode::Status::Running;
    }

    // 探索済み状態をリセット
    isSearching_ = false;
    isReady_ = false;

    // 結果を使って移動処理
    std::list<Vector2> pathCopy;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        pathCopy = cachedPath_;
    }

    if (!pathCopy.empty())
    {
        const auto direction = (pathCopy.front() - currentPos).Normalize() * moveSpeed_;
        const auto body = self_.GetComponent<Collider>()->GetBodyId();
        b2Body_SetLinearVelocity(body, direction.ToB2Vec2());
        
        self_.GetComponent<AnimationRenderer>()->isReverseX_ = self_.GetComponent<Transform>()->position_.x_ > pathCopy.front().x_;
        
        return Ai::INode::Status::Success;
    }

    return Ai::INode::Status::Failure;
}
