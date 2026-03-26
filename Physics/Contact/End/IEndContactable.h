#pragma once

class IEndContactable
{
public:
    virtual ~IEndContactable() = default;
    virtual void OnEndContact() = 0;
};
