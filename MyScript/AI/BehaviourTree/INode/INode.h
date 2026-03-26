#pragma once

namespace Ai
{
    class INode
    {
    public:
        enum class Status { Failure, Running, Success, Abort};

        virtual ~INode() = default;
        virtual Status Tick() = 0;
    };
    
    inline bool operator==(INode::Status lhs, INode::Status rhs)
    {
        return static_cast<int>(lhs) == static_cast<int>(rhs);
    }

    inline bool operator!=(const INode::Status lhs, const INode::Status rhs)
    {
        return !(lhs == rhs);
    }
}
