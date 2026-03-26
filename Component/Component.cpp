#include "Component.hpp"

#include "../Entity/Entity.hpp"

void Component::SetEntityRef(Entity& entity)
{
    entity_ = &entity;
}

Entity& Component::EntityRef() const
{
    return *entity_;
}

void Component::Init()
{
}

void Component::Awake()
{
}

void Component::Despawned()
{
}

void Component::OnBeginUpdatePhysics()
{
}

void Component::OnUpdate()
{
}

void Component::OnEndUpdatePhysics()
{
}

void Component::OnDraw()
{
}

void Component::OnEditorUpdate()
{
}

void Component::OnDrawInspector()
{
}

const rxcpp::composite_subscription& Component::OnDespawnSubscription() const
{
    return entity_->OnDespawnSubscription();
}

// rxcpp::composite_subscription& Component::OnDespawnCancellationToken()
// {
//     return onDespawnCancellationToken_;
// }
