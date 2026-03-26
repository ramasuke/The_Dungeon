#pragma once
#include <vector>
#include <memory>
#include <string>
#include <tuple>
#include "../../Helper/FolderLoader.h"
#include "../../Libs/ImGui/imgui.h"
#include "../IResource/IResource.h"

template <typename T, typename RemoveT, typename = std::enable_if_t<std::is_base_of_v<IResource, T>>>
class ResourceManageContainerBase
{
public:
    virtual ~ResourceManageContainerBase() = default;
    explicit ResourceManageContainerBase(const std::string& resourceFolderPath);
    void OnSaveResources();
    void OnDrawDebug();
    virtual void OnUpdate() = 0;
    virtual bool OnTryRemoveContent(RemoveT* resource) = 0;
    
    std::vector<std::tuple<bool, std::unique_ptr<T>, std::string>> contents_;

private:
    std::string folderPath_ = "Resource/";
};

template <typename T, typename RemoveT, typename T0>
::ResourceManageContainerBase<T, RemoveT, T0>::ResourceManageContainerBase(const std::string& resourceFolderPath)
    : folderPath_(resourceFolderPath)
{
    for (const auto& filePath : FolderLoader::OnCatchAllFile(folderPath_))
    {
        auto resource = std::make_unique<T>();
        resource->OnDeserialize(filePath);
        contents_.push_back(std::make_tuple(false, std::move(resource), filePath));
    }
}

template <typename T, typename RemoveT, typename T0>
void ::ResourceManageContainerBase<T, RemoveT, T0>::OnSaveResources()
{
    for (auto& content : contents_)
    {
        std::get<1>(content)->OnSerialize(std::get<2>(content));
    }
}

template <typename T, typename RemoveT, typename T0>
void ::ResourceManageContainerBase<T, RemoveT, T0>::OnDrawDebug()
{
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();

    ImGui::SeparatorText(folderPath_.c_str());
    for (auto& content : contents_)
    {
        if (ImGui::Button(std::get<2>(content).c_str()))
        {
            content = std::make_tuple(!std::get<0>(content), std::move(std::get<1>(content)), std::get<2>(content));
        }
    }

    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();
    const auto newButtonString = "New " + folderPath_;
    if (ImGui::Button(newButtonString.c_str()))
    {
        const auto fullPath = folderPath_ + "/Empty" + std::to_string(contents_.size()) + ".json";
        auto resource = std::make_unique<T>();
        resource->OnSerialize(fullPath);
        contents_.emplace_back(false, std::move(resource), fullPath);
        OnSaveResources();
    }

    ImGui::Begin(folderPath_.c_str());
    for (auto& content : contents_)
    {
        if (!std::get<0>(content))
            continue;

        static std::string newName = "";
        char nameBuffer[256];
        strncpy_s(nameBuffer, newName.c_str(), sizeof(nameBuffer));
        ImGui::InputText("newDirName: ", nameBuffer, sizeof(nameBuffer));
        newName = nameBuffer;
        if (ImGui::Button("UpdateDirName"))
        {
            auto a = std::get<2>(content);
            if (remove(a.c_str()) == 0)
            {
                std::get<1>(content)->OnSerialize(folderPath_ + '/' + newName + ".json");
                content = std::make_tuple(std::get<0>(content), std::move(std::get<1>(content)),
                                          folderPath_ + '/' + newName + ".json");
            }
        }
        std::get<1>(content)->OnDrawDebug();
    }
    ImGui::End();
}