#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../Component/Component.hpp"
#include "../../../../Component/Content/Basically/Renderer/AnimationRenderer/Animation/Animation.h"
#include "../SpawnModel/SpawnEnemyModel.h"

namespace Enemy
{
    class SummonBossCircle final : public virtual Component
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this),
                cereal::make_nvp("animation"        , animation_        ),
                cereal::make_nvp("onSummonDuration" , onSummonDuration_ )
            );
        }

        void SetSummonModel(const SpawnEnemyModel&, const std::function<void()>& onDeathBossCallback);
        
    private:
        void Init() override;
        void OnUpdate() override;
        void OnDrawInspector() override;
        void OnSpawnEnemy() const;


        std::function<void()> onDeathBossCallback_;
        std::shared_ptr<Animation> animation_ = std::make_shared<Animation>();
        SpawnEnemyModel spawnEnemyModel_ = SpawnEnemyModel(Vector2(), "Resource/Prefab/BlueSlime.json");

        int onSummonDuration_ = 100;
        int onSummonDuring_ = 0;
    };
}

CEREAL_REGISTER_TYPE(Enemy::SummonBossCircle)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Enemy::SummonBossCircle)