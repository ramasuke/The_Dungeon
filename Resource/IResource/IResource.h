#pragma once
#include <string>

class IResource
{
public:
    virtual ~IResource() = default;
    virtual void OnSerialize(const std::string& filePath) = 0;
    virtual void OnDeserialize(const std::string& filePath) = 0;
    virtual void OnDrawDebug() = 0;
};