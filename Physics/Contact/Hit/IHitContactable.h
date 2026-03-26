#pragma once

class IHitContactable
{
public:
    virtual ~IHitContactable() = default;
    virtual void OnHitContact() = 0;
};
