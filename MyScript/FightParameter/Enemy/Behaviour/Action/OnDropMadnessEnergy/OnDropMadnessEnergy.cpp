#include "OnDropMadnessEnergy.h"

#include "../../../../../../Component/Content/Basically/Transform/Transform.hpp"
#include "../../../../MadnessEnergy/MadnessEnergyObject/MadnessEnergyObject.h"

Enemy::Behaviour::Action::OnDropMadnessEnergy::OnDropMadnessEnergy(Entity& self, const int comboCount,
                                                                   const MadnessEnergy energy)
    : self_(self), count_(comboCount), energy_(energy)
{
}

Ai::INode::Status Enemy::Behaviour::Action::OnDropMadnessEnergy::operator()() const
{
    const auto position = self_.GetComponent<Transform>()->position_;
    MadnessEnergyObject::Spawn(position, count_, energy_);
    return Ai::INode::Status::Success;
}
