#pragma once
#include "../../Camera/Base/CameraBase.hpp"

constexpr auto EDITOR_CAMERA_MOVE_SPEED = 0.4f;

class EditorCamera final : public virtual CameraBase
{
public:
    void OnUpdate();

private:
    Vector2 previewMousePos_;
};
