#pragma once

template <class T>
class IContainer
{
public:
    virtual ~IContainer() = default;
    virtual void AddContent(T add) = 0;
    virtual void RemoveContent(T remove) = 0;
};
