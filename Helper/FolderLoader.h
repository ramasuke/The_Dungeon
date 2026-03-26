#pragma once
#include <vector>
#include <string>

class FolderLoader final
{
public:
    static std::vector<std::string> OnCatchAllFile(const std::string& folderPath);
};
