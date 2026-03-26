#pragma once
#include <cereal/cereal.hpp>

#include "../../Application/IApplication/IApplication.hpp"
#include "../Guid/Guid.h"

template <typename T>
class ComponentRef final
{
public:
    ///WARNING: Awake時に呼び出してください。Initやコンストラクタで呼び出すと挙動がバグります。
    void Init();
    T* Value();
    void OnDrawInspector();

    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(cereal::make_nvp("entityGUID: ", entityGuid_));
    }

    Guid entityGuid_;

private:
    T* value_ = nullptr;
};

template <typename T>
T* ComponentRef<T>::Value()
{
    return value_;
}

template <typename T>
void ComponentRef<T>::OnDrawInspector()
{
    entityGuid_.OnDrawInspector();
}

template <typename T>
void ComponentRef<T>::Init()
{
    const auto entityRef = IApplication::GetInstance().EntityContainer().CatchEntity(entityGuid_);
    if (entityRef == nullptr)
        return;

    value_ = entityRef->GetComponent<T>();
}