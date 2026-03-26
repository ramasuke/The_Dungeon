#pragma once
#include <type_traits>

#include "../../IDamageParam/IDamageParam.h"

template<typename T, typename = std::enable_if_t<std::is_base_of_v<IDamageParam, T>>>
class IReceivableDamage
{
public:
    virtual ~IReceivableDamage() = default;
    virtual void OnTypeDamage(const T& damage) = 0;
};
