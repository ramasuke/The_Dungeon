#pragma once
#include <vector>
#include <string>
#include <memory>
#include "../BasicallyParameter/Guid/Guid.h"
#include "../BasicallyParameter/Vector2/Vector2.hpp"
#include "../Component/Component.hpp"
#include "../Libs/ImGui/imgui.h"
#include "../Resource/IResource/IResource.h"

class Entity final : public virtual IResource
{
public:
    ~Entity() override;

    //XXX: Scene上のEntityはInit()よりも先に必ずこの関数を呼び出してください。
    void InitSceneEntity();

    void Init();
    void InitComponents() const;
    void OnAwakeComponents() const;
    static Entity& Spawn(const std::string& filePath, Vector2 position);
    template <class T>
    static [[nodiscard]] T* Spawn(const std::string& filePath, Vector2 position);
    void OnDespawn();
    template <class T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
    T& AddComponent();
    template <class T>
    void RemoveComponent();
    template <class T>
    [[nodiscard]] T* GetComponent();
    [[nodiscard]] Guid& GetGuid();
    void OnUpdateBeginPhysics() const;
    void OnUpdateForGameRoop() const;
    void OnUpdateDraw() const;
    void OnUpdateEndPhysics() const;
    void OnEditorUpdate() const;
    void OnDrawDebug() override;
    void OnSerialize(const std::string& filePath) override;
    void OnDeserialize(const std::string& filePath) override;
    const std::string& Name() const { return name_; }
    const rxcpp::composite_subscription& OnDespawnSubscription() const;

    template <typename Archive>
    void serialize(Archive& archive);

private:
    template <class T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
    void DrawAddComponentButton();

    Guid guid_;
    std::string name_ = "Empty";
    std::vector<std::unique_ptr<Component>> components_;
    rxcpp::composite_subscription onDespawnSubscription_;
};

template <class T>
T* Entity::Spawn(const std::string& filePath, const Vector2 position)
{
    return Spawn(filePath, position).GetComponent<T>();
}

template <class T, typename>
T& Entity::AddComponent()
{
    auto component = std::make_unique<T>();
    auto& componentRef = *component;
    components_.push_back(std::move(component));
    auto* addedComponent = components_.empty() ? nullptr : components_.back().get();
    addedComponent->SetEntityRef(*this);
    addedComponent->Init();
    addedComponent->Awake();
    return componentRef;
}

template <class T>
void Entity::RemoveComponent()
{
    auto it = std::remove_if(components_.begin(), components_.end(),
                             [](const std::unique_ptr<Component>& component)
                             {
                                 return dynamic_cast<T*>(component.get()) != nullptr;
                             });

    components_.erase(it, components_.end());
}

template <class T>
T* Entity::GetComponent()
{
    for (const auto& component : components_)
    {
        T* casted = dynamic_cast<T*>(component.get());

        if (casted != nullptr)
        {
            return casted;
        }
    }
    return nullptr;
}

template <typename Archive>
void Entity::serialize(Archive& archive)
{
    archive(guid_, name_, components_);
}

template <class T, typename>
void Entity::DrawAddComponentButton()
{
    if (ImGui::Button(typeid(T).name()))
    {
        AddComponent<T>();
    }
}
