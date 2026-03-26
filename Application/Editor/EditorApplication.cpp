#include "EditorApplication.h"
#include "DxLib.h"
#include "../ApplicationParameter.h"
#include "../../Libs/ImGuiWrapper.h"
#include "../../Libs/ImGui/imgui.h"
#include "../../Render/Render.h"

void EditorApplication::Init()
{
    IApplication::Init();
    DxLib_Init();

    SetGraphMode(WINDOW_WIDTH_SCALE, WINDOW_HEIGHT_SCALE, GAME_WINDOW_COLOR_SCALE);
    ChangeWindowMode(TRUE);
    SetDrawScreen(DX_SCREEN_BACK);
    SetMouseDispFlag(true);

    ImGuiWrapper::CreateInstance();
    resourceManageContainerGroup_ = std::make_unique<ResourceManageContainerGroup>();
}

void EditorApplication::OnStartGameRoopAsync()
{
    while (CheckContinueGameRoop())
    {
        fps_.IsSkipDrawScene();
        OnUpdateGameRoop();
        fps_.OnTryWaitUntilTargetFrame();
    }
}

void EditorApplication::OnUpdateGameRoop()
{
    ClearDrawScreen();
    OnUpdateLifeCycle();

    RenderVertex();
    ImGuiWrapper::Instance().Draw();
    ScreenFlip();
}

void EditorApplication::OnUpdateLifeCycle()
{
    ImGuiWrapper::Instance().Update();

    ImGui::Begin("FPS");
    ImGui::Text(std::to_string(GetFPS()).c_str());
    ImGui::End();

    OnDrawChangeDebugModeWindow();

    if (!isPlayMode_)
    {
        sceneManager_.OnUpdate();
        onAwakeEntityContainer_.OnUpdateForGameRoop();
        entityContainer_.OnUpdateBeginPhysics();
        physics_.OnUpdateWorld();
        entityContainer_.OnUpdateEndPhysics();
        entityContainer_.OnUpdateForGameRoop();
        // onAwakeEntityContainer_.OnUpdateForGameRoop();
        physics_.OnUpdateContacts();
    }
    else
    {
        onAwakeEntityContainer_.OnUpdateForGameRoop();
        entityContainer_.OnEditorUpdate();
        camera_.OnUpdate();
    }
    entityContainer_.OnUpdateDraw();
    Render::OnDrawAllRender();
    onDespawnEntityContainer_.OnUpdateForGameRoop(entityContainer_, resourceManageContainerGroup_.get());
    entityContainer_.OnUpdateContentLifeCycle();
    resourceManageContainerGroup_->OnDrawDebugWindow();

    ImGui::EndFrame();
}

void EditorApplication::OnDrawChangeDebugModeWindow()
{
    ImGui::Begin("PlayMode");
    if (ImGui::Button("isPlayMode"))
    {
        isPlayMode_ = !isPlayMode_;
    }
    ImGui::End();
}

void EditorApplication::OnExit()
{
    
}

bool EditorApplication::CheckContinueGameRoop()
{
    return ProcessMessage() >= 0 && !CheckHitKey(KEY_INPUT_ESCAPE);
}
