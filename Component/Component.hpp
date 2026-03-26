#pragma once
#include "../Libs/rxcpp/operators/rx-all.hpp"
// #include "../Libs/rxcpp/rx-subscription.hpp"

class Entity;

class Component
{
public:
    template <typename Archive>
    void serialize(Archive&)
    {
    }
    
    virtual ~Component() = default;
    void SetEntityRef(Entity& entity);
    Entity& EntityRef() const;
    
    virtual void Init();
    virtual void Awake();
    virtual void Despawned();
    virtual void OnBeginUpdatePhysics();
    virtual void OnUpdate();
    virtual void OnEndUpdatePhysics();
    virtual void OnDraw();
    virtual void OnEditorUpdate();
    virtual void OnDrawInspector();
    const rxcpp::composite_subscription& OnDespawnSubscription() const;

private:
    Entity* entity_ = nullptr;
};
