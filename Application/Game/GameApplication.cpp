#include "GameApplication.h"
#include "DxLib.h"
#include "../ApplicationParameter.h"
#include "../../Libs/ImGuiWrapper.h"
#include "../../Libs/ImGui/imgui.h"
#include "../../Render/Render.h"

void GameApplication::Init()
{
    IApplication::Init();
    DxLib_Init();

    SetGraphMode(WINDOW_WIDTH_SCALE, WINDOW_HEIGHT_SCALE, GAME_WINDOW_COLOR_SCALE);
    // ChangeWindowMode(TRUE);
    SetDrawScreen(DX_SCREEN_BACK);
    SetMouseDispFlag(false);
    
    ImGuiWrapper::CreateInstance();
    //sceneManager_.OnLoadSceneAsync("Resource/Scene/GameClearScene.json");
    sceneManager_.OnLoadSceneAsync("Resource/Scene/SelectStageScene.json");
    sceneManager_.OnLoadSceneAsync("Resource/Scene/MoveControllExplainUiScene.json");
    sceneManager_.OnLoadSceneAsync("Resource/Scene/PlayerParamScene.json");
}

void GameApplication::OnStartGameRoopAsync()
{
    while (CheckContinueGameRoop())
    {
        fps_.IsSkipDrawScene();
        OnUpdateGameRoop();
        fps_.OnTryWaitUntilTargetFrame();
    }
}

void GameApplication::OnUpdateGameRoop()
{
    ClearDrawScreen();
    OnUpdateLifeCycle();

    RenderVertex();
    ScreenFlip();
}

void GameApplication::OnUpdateLifeCycle()
{
    sceneManager_.OnUpdate();
    onAwakeEntityContainer_.OnUpdateForGameRoop();
    entityContainer_.OnUpdateBeginPhysics();
    physics_.OnUpdateWorld();
    entityContainer_.OnUpdateEndPhysics();
    entityContainer_.OnUpdateForGameRoop();
    // onAwakeEntityContainer_.OnUpdateForGameRoop();
    physics_.OnUpdateContacts();

    entityContainer_.OnUpdateDraw();
    Render::OnDrawAllRender();
    onDespawnEntityContainer_.OnUpdateForGameRoop(entityContainer_, nullptr);
    entityContainer_.OnUpdateContentLifeCycle();
}

void GameApplication::OnExit()
{
}

bool GameApplication::CheckContinueGameRoop()
{
    return ProcessMessage() >= 0;
}
