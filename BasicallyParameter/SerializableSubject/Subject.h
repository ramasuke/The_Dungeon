#pragma once
#include <cereal/cereal.hpp>

#include "../../Helper/ImGui/ImGuiHelper.h"
#include "../../Libs/rxcpp/operators/rx-all.hpp"
#include "../ReadOnlyReactiveContext/ReadOnlyReactiveContext.h"

template <typename T>
class Subject final
{
public:
    template <class Archive>
    void serialize(Archive& ar)
    {
        ar(cereal::make_nvp("value", value_));
    }

    explicit Subject(T value = T());
    void OnDrawInspector();
    const T& get() const { return value_; }
    void OnNext(T value);
    ///NOTE: 中身がshared_ptrなどで持っているので、参照ではなく実態を返しても変わらない。
    ReadOnlyReactiveContext<T> AsReadOnly() const;

private:
    rxcpp::subjects::subject<T> subject_;
    T value_;
};

template <typename T>
Subject<T>::Subject(T value)
    : subject_(), value_(value)
{
}

template <typename T>
void Subject<T>::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("value", value_);
    if (ImGui::Button("onNext"))
    {
        OnNext(value_);
    }
}

template <typename T>
void Subject<T>::OnNext(T value)
{
    value_ = value;
    subject_.get_subscriber().on_next(value);
}

template <typename T>
ReadOnlyReactiveContext<T> Subject<T>::AsReadOnly() const
{
    return ReadOnlyReactiveContext<T>(value_, subject_.get_observable());
}
