#include "MadnessEnergyObject.h"

#include "../../../../Component/Content/Basically/Transform/Transform.hpp"
#include "../../../../Entity/Entity.hpp"
#include "../../../../Helper/Random/Random.h"
#include "../../../../Physics/Physics.h"
#include "../../../Player/PlayerAvatar.h"

void MadnessEnergyObject::Spawn(const Vector2 position, const MadnessEnergy dropEnergy)
{
    auto& comboEnergyObject = Entity::Spawn(MADNESS_ENERGY_OBJECT_PREFAB_PATH, position);
    comboEnergyObject.GetComponent<MadnessEnergyObject>()->SetEnergy(dropEnergy);
}

void MadnessEnergyObject::Spawn(const Vector2 position, int count, const MadnessEnergy dropEnergy)
{
    for (int i = 0; i < count; i++)
    {
        auto& comboEnergyObject = Entity::Spawn(MADNESS_ENERGY_OBJECT_PREFAB_PATH, position);
        comboEnergyObject.GetComponent<MadnessEnergyObject>()->SetEnergy(dropEnergy);
    }
}

void MadnessEnergyObject::SetEnergy(const MadnessEnergy comboEnergy)
{
    energy_ = comboEnergy;
}

void MadnessEnergyObject::Init()
{
    transform_ = EntityRef().GetComponent<Transform>();
}

void MadnessEnergyObject::Awake()
{
    diffusionDirection_ = Vector2(Random::Range(-1, 1), Random::Range(-1, 1));

    EntityRef().GetComponent<Collider>()->SetLayer(b2Filter{MadnessEnergyLayer, 0xFFFF, 0});
}

void MadnessEnergyObject::OnBeginSensor(b2SensorBeginTouchEvent*, IReceivableMadnessEnergy* contact)
{
    contact->OnContactComboEnergy(energy_);
    EntityRef().OnDespawn();
}

void MadnessEnergyObject::OnUpdate()
{
    if (diffusionMoveDuration_ > diffusionMoveDuring_)
    {
        diffusionMoveDuring_++;
        OnDiffusionMove();
    }
    else
    {
        OnToPlayerMove();
    }
}

void MadnessEnergyObject::OnDiffusionMove() const
{
    transform_->position_ += diffusionDirection_ * onDiffusionMoveSpeed_;
}

void MadnessEnergyObject::OnToPlayerMove() const
{
    transform_->position_ += (Player::PlayerAvatar::Model().Transform()->position_ - transform_->position_).
        Normalize() * toPlayerMoveSpeed_;
}

void MadnessEnergyObject::OnDrawInspector()
{
    ImGui::InputInt("diffusionMoveDuration", &diffusionMoveDuration_);
    ImGui::InputInt("diffusionMoveDuring", &diffusionMoveDuring_);
    ImGui::InputFloat("onDiffusionMoveSpeed", &onDiffusionMoveSpeed_);
    ImGui::InputFloat("toPlayerMoveSpeed", &toPlayerMoveSpeed_);
}
