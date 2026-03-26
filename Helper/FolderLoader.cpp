#include "FolderLoader.h"
#include <iostream>
#include <DxLib.h>
#include <vector>
#include <string>
#include <Windows.h>

std::vector<std::string> FolderLoader::OnCatchAllFile(const std::string& folderPath)
{
    WIN32_FIND_DATA win32Fd;
    std::vector<std::string> file_names;

    const std::string search_name = folderPath + "\\*";

    const HANDLE fHandle = FindFirstFile(search_name.c_str(), &win32Fd);

    if (fHandle == INVALID_HANDLE_VALUE)
    {
        // "'GetLastError() == 3' is 'file not found'"
        return file_names;
    }

    do
    {
        if (win32Fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            //ディレクトリである

            //そのディレクトリそのものを表す場合は処理しない
            if (win32Fd.cFileName[0] == '.') continue;

            std::string fullpath = folderPath + "\\" + win32Fd.cFileName;

            //再帰的にファイルを検索
            std::vector<std::string> files = OnCatchAllFile(folderPath);

            file_names.insert(file_names.end(), files.begin(), files.end());
        }
        else
        {
            //ファイルである
            std::string fullpath = folderPath + "\\" + win32Fd.cFileName;
            file_names.emplace_back(fullpath);
        }
    }
    while (FindNextFile(fHandle, &win32Fd));

    FindClose(fHandle);

    return file_names;
}