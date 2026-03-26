#pragma once

class RenderContent
{
public:
    virtual ~RenderContent() = default;
    virtual int RenderOrder() const = 0;
    virtual void OnDraw() const = 0;
};
