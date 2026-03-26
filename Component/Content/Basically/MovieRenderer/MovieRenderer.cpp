#include "MovieRenderer.h"
#include <DxLib.h>

#include "../../../../Application/ApplicationParameter.h"
#include "../../../../Entity/Entity.hpp"
#include "../../../../Helper/ImGui/ImGuiHelper.h"
#include "../../../../Render/Render.h"
#include "../Transform/Transform.hpp"

MovieRenderer::~MovieRenderer()
{
    DeleteGraph(movieHandle_);
}

void MovieRenderer::SetResourceFilePath(const std::string& resourceFilePath)
{
    movieHandle_    = LoadGraph(resourceFilePath.c_str());
}

void MovieRenderer::Init()
{
    
    movieHandle_    = LoadGraph(resourceFilePath_.c_str());
    screenHandle_   = MakeScreen(WINDOW_WIDTH_SCALE, WINDOW_HEIGHT_SCALE, TRUE);
}

void MovieRenderer::OnDraw()
{
    screenHandle_   = MakeScreen(WINDOW_WIDTH_SCALE, WINDOW_HEIGHT_SCALE, TRUE);
    const auto transform = EntityRef().GetComponent<Transform>();

    //スクリーンハンドルに動画を描画する
    if (isLoop_)
    {
        PlayMovieToGraph(movieHandle_, DX_PLAYTYPE_LOOP);
    }
    else
    {
        PlayMovieToGraph(movieHandle_);
    }
    Render::DrawRotaGraphF(transform->position_, transform->rotation_, transform->scale_, renderOrder_, movieHandle_,
                           false, screenHandle_);

    if (isFilter_)
    {
        //スクリーンハンドルを画像として透過してから描画
        Render::DrawFilter(screenHandle_, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_GREATER, 128, transparentColor_, 0,
                           renderOrder_ + 1);
    }
    // DrawExtendGraph(position.x, position.y, position.x + movieWidth, position.y + movieHeight, screenHandle, TRUE);
    Render::DrawRotaGraphF(transform->position_, transform->rotation_, transform->scale_, renderOrder_ + 2,
                           screenHandle_, false);
    DeleteGraph(screenHandle_);
}

void MovieRenderer::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("resourceFilePath", resourceFilePath_);
    ImGuiHelper::OnDrawInputField("transparentColor", transparentColor_);
    ImGuiHelper::OnDrawInputField("movieHandle"     , movieHandle_);
    ImGuiHelper::OnDrawInputField("renderOrder"     , renderOrder_);
    ImGui::Checkbox("isLoop", &isLoop_);
    ImGui::Checkbox("isFilter", &isFilter_);
    
    if (ImGui::Button("onUpdateMovieHandle"))
    {
        movieHandle_ = LoadGraph(resourceFilePath_.c_str());
    }
    ImGui::Text(std::to_string(GetMovieStateToGraph(movieHandle_)).c_str());
}
