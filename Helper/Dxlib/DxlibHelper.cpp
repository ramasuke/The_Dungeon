#include "DxlibHelper.h"

#include <DxLib.h>

#include "../../Application/IApplication/IApplication.hpp"

Vector2 DxlibHelper::GetMousePosition()
{
    int mousePosX = 0;
    int mousePosY = 0;
    GetMousePoint(&mousePosX, &mousePosY);
    return Vector2(mousePosX, mousePosY);
}

Vector2 DxlibHelper::GetWorldMousePosition()
{
    int mousePosX = 0;
    int mousePosY = 0;
    GetMousePoint(&mousePosX, &mousePosY);
    return Vector2(mousePosX , mousePosY) + IApplication::GetInstance().Camera().position_;
}
