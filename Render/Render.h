#pragma once
#include <DxLib.h>

#include "../BasicallyParameter/Vector2/Vector2.hpp"
#include "../Component/Content/Basically/Color/Color.h"

class Render final
{
public:
    static void OnDrawAllRender();
    static void DrawRotaGraphF(Vector2 position, float rotation, float scale, int renderOrder, int handleId,
                               bool isReverseX, int screenHandle = DX_SCREEN_BACK);
    static void DrawTextF(const std::string& text, Vector2 position, float rotation, float scale, int renderOrder,
                          int color, int fondHandle);
    static void DrawFilter(int screenHandle, int filterType, int filterParam, int filterBrightness, Color transParentColor,
                        int alpha, int renderOrder);
};
