#pragma once
#include "../MadnessEnergy.h"

class IReceivableMadnessEnergy
{
public:
    virtual ~IReceivableMadnessEnergy() = default;
    virtual void OnContactComboEnergy(MadnessEnergy combo) = 0;
};