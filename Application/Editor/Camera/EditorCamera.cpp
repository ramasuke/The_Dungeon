#include "EditorCamera.hpp"

#include <DxLib.h>

void EditorCamera::OnUpdate()
{
    if (GetMouseInput() == MOUSE_INPUT_MIDDLE)
    {
        int currentMousePosX = 0;
        int currentMousePosY = 0;
        GetMousePoint(&currentMousePosX, &currentMousePosY);
        position_ += (Vector2(currentMousePosX, currentMousePosY) - previewMousePos_) *
            EDITOR_CAMERA_MOVE_SPEED;
    }

    int previewMousePosX = 0;
    int previewMousePosY = 0;
    GetMousePoint(&previewMousePosX, &previewMousePosY);
    previewMousePos_ = Vector2(previewMousePosX, previewMousePosY);
}
