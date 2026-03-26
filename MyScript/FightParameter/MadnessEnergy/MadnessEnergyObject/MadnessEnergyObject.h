#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../MadnessEnergy.h"
#include "../../../../BasicallyParameter/Vector2/Vector2.hpp"
#include "../../../../Component/Component.hpp"
#include "../../../../Physics/Sensor/Begin/IBeginSensorable.h"
#include "../IReceivableMadnessEnergy/IReceivableMadnessEnergy.h"

constexpr auto MADNESS_ENERGY_OBJECT_PREFAB_PATH = "Resource/Prefab/MadnessEnergy.json";

class Transform;

class MadnessEnergyObject final : public virtual Component,
                                  public virtual IBeginSensorable<IReceivableMadnessEnergy>
{
public:
    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::base_class<Component>(this),
            cereal::make_nvp("diffusionMoveDuration", diffusionMoveDuration_),
            cereal::make_nvp("onDiffusionMoveSpeed", onDiffusionMoveSpeed_),
            cereal::make_nvp("toPlayerMoveSpeed", toPlayerMoveSpeed_)
        );
    }

    static void Spawn(Vector2 position, MadnessEnergy dropEnergy);
    static void Spawn(Vector2 position, int count, MadnessEnergy dropEnergy);
    void SetEnergy(MadnessEnergy comboEnergy);

private:
    void Init() override;
    void Awake() override;
    void OnBeginSensor(b2SensorBeginTouchEvent*, IReceivableMadnessEnergy*) override;
    void OnUpdate() override;
    void OnDiffusionMove() const;
    void OnToPlayerMove() const;
    void OnDrawInspector() override;

    MadnessEnergy energy_;
    Vector2 diffusionDirection_ = Vector2();
    int diffusionMoveDuration_ = 100;
    int diffusionMoveDuring_ = 0;
    float onDiffusionMoveSpeed_ = 10.0f;

    float toPlayerMoveSpeed_ = 1.0f;
    Transform* transform_ = nullptr;
};

CEREAL_REGISTER_TYPE(MadnessEnergyObject)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, MadnessEnergyObject)
