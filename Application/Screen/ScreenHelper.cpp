#include "ScreenHelper.h"

#include "../ApplicationParameter.h"
#include "../IApplication/IApplication.hpp"

Vector2 Screen::CameraCenterWorldPos()
{
    return IApplication::GetInstance().Camera().position_ * -1 + Vector2(WINDOW_WIDTH_SCALE, WINDOW_HEIGHT_SCALE) /
        2;
}
