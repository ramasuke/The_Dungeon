#include <memory>
#include "DxLib.h"
#include "Application/Editor/EditorApplication.h"
#include "Application/Game/GameApplication.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    const auto application = std::make_unique<GameApplication>();
    application->Init();

    //TODO: フォント読み込み場所が雑なので適切な場所に変更。
    const auto fontFilePath = "Resource/Font/DotGothic16-Regular.ttf";
    AddFontResourceEx(fontFilePath, FR_PRIVATE, nullptr);
    
    application->OnStartGameRoopAsync();
    application->OnExit();
}



