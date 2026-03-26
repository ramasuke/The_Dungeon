#pragma once
#include <type_traits>
#include <string>
#include "../../Libs/ImGui/imgui.h"
#include <functional>

namespace ImGuiHelper
{
    template <typename T>
    static typename std::enable_if<std::is_same<T, int>::value>::type
    OnDrawInputField(const std::string& label, T& value)
    {
        ImGui::InputInt(label.c_str(), &value);
    }

    template <typename T>
    static typename std::enable_if<std::is_same<T, float>::value>::type
    OnDrawInputField(const std::string& label, T& value)
    {
        ImGui::InputFloat(label.c_str(), &value);
    }

    template <typename T>
    static typename std::enable_if<std::is_same<T, double>::value>::type
    OnDrawInputField(const std::string& label, T& value)
    {
        ImGui::InputDouble(label.c_str(), &value);
    }

    template <typename T>
    static typename std::enable_if<std::is_same<T, std::string>::value>::type
    OnDrawInputField(const std::string& label, T& value)
    {
        char buffer[256];
        strncpy_s(buffer, value.c_str(), sizeof(buffer));
        buffer[sizeof(buffer) - 1] = '\0';
        if (ImGui::InputText(label.c_str(), buffer, sizeof(buffer)))
        {
            value = buffer;
        }
    }

    //NOTE: 自作クラス用：OnDrawInspector() を持つ型
    template <typename T>
    static typename std::enable_if<
        std::is_same<decltype(std::declval<T&>().OnDrawInspector()), void>::value
    >::type
    OnDrawInputField(const std::string& label, T& value)
    {
        if (ImGui::TreeNode(label.c_str()))
        {
            value.OnDrawInspector();
            ImGui::TreePop();
            ImGui::Spacing();
        }
    }

    //NOTE: 未対応型：OnDrawInspector() を持たない型
    template <typename T>
    static typename std::enable_if<
        !std::is_same<decltype(std::declval<T&>().OnDrawInspector()), void>::value
    >::type
    OnDrawInputField(const std::string&, T&)
    {
        static_assert(sizeof(T) == 0, "Unsupported type for ImGuiHelper::OnDrawInputField");
    }

    template <typename PtrType>
    static typename std::enable_if<
        std::is_pointer<typename PtrType::element_type*>::value
    >::type
    OnDrawInputField(const std::string& label, PtrType& ptr)
    {
        if (ptr)
        {
            OnDrawInputField(label, *ptr);
        }
        else
        {
            ImGui::Text("%s: nullptr", label.c_str());
        }
    }

    //NOTE: 自作クラス用：OnDrawInspector() を持つ型
    template <typename T>
    static typename std::enable_if<
        std::is_same<decltype(std::declval<T&>().OnDrawInspector()), void>::value
    >::type
    OnDrawTreeInspector(const std::string& label, T& value)
    {
        if (ImGui::TreeNode(label.c_str()))
        {
            value.OnDrawInspector();
            ImGui::TreePop();
            ImGui::Spacing();
        }
    }

    template <typename Container>
    static typename std::enable_if<
        !std::is_same<typename Container::value_type, void>::value
    >::type
    OnDrawInputField(const std::string& label, Container& container, const std::function<void()> drawAddButton)
    {
        if (ImGui::TreeNode(label.c_str()))
        {
            int index = 0;
            for (auto& element : container)
            {
                std::string itemLabel = "Element " + std::to_string(index++);
                OnDrawInputField(itemLabel, element); // 再帰的に呼び出して各型に応じて描画
            }
            drawAddButton();
            static int deleteIndex = 0;
            ImGui::InputInt("Delete Index", &deleteIndex);
            if (ImGui::Button("Delete") && deleteIndex >= 0 && deleteIndex < static_cast<int>(container.size()))
            {
                container.erase(container.begin() + deleteIndex);
                deleteIndex = 0;
            }

            ImGui::TreePop();
            ImGui::Spacing();
        }
    }
};
