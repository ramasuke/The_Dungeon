#pragma once
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/memory.hpp>

#include "../../Component/Component.hpp"
#include "../../Component/Content/Basically/Renderer/AnimationRenderer/AnimationRenderer.h"
#include "../../Component/Content/Basically/Collider/Box/BoxCollider.h"
#include "../../Physics/Sensor/Begin/IBeginSensorable.h"
#include "../FightParameter/MadnessEnergy/IReceivableMadnessEnergy/IReceivableMadnessEnergy.h"
#include "../FightParameter/IReceivableEnemyAttack/IReceivableEnemyAttack.h"
#include "../Item/Drop/SkillBookItem/SkillBookDropItemObject.h"
#include "Controller/PlayerController.h"
#include "Model/PlayerModel.h"
#include "Model/State/Group/PlayerStateGroup.h"

namespace Player
{
    class PlayerAvatar final : public virtual Component,
                               public virtual IReceivableEnemyAttack,
                               public virtual IBeginSensorable<SkillBookDropItemObject>,
                               public virtual IReceivableMadnessEnergy
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this)
            );
        }

        ~PlayerAvatar() override;
        static PlayerModel& Model()
        {
            static PlayerModel model;
            return model;
        }
        PlayerController& Controller() { return controller_; }
    
    private:
        void Init()             override;
        void OnUpdate()         override;
        void OnDrawInspector()  override;
        void OnDamage(std::shared_ptr<DamageContext::IDamageContext> damage) override;
        void OnBeginSensor(b2SensorBeginTouchEvent*, SkillBookDropItemObject*) override;
        void OnContactComboEnergy(MadnessEnergy madness) override;
    
        PlayerController controller_;
        AnimationRenderer* animationRenderer_ = nullptr;
    };
}

CEREAL_REGISTER_TYPE(Player::PlayerAvatar)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Player::PlayerAvatar)
