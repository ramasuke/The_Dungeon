#pragma once
#include <string>

class Guid final
{
    std::string value_;

public:
    Guid();
    void OnDrawInspector();

    template <typename Archive>
    void serialize(Archive& archive)
    {
        archive(value_);
    }

    std::string Value() const;

    bool operator==(const Guid& other) const
    {
        return value_ == other.value_;
    }
};

struct GuidHash final
{
    std::size_t operator()(const Guid& guid) const
    {
        return std::hash<std::string>()(guid.Value());
    }
};
