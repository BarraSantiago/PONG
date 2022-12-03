#include "Pad.h"

void DrawPad(Rectangle bar1, Rectangle bar2)
{
    const Color NEONCYAN = CLITERAL(Color){4, 217, 255, 255};
    DrawRectangleRec(bar1, NEONCYAN);
    DrawRectangleRec(bar2, NEONCYAN);
}

Rectangle InitBar1()
{
    const float barHeight = static_cast<float>(GetScreenHeight()) / 7.0f;
    const float barWidth = static_cast<float>(GetScreenHeight()) / 50.0f;
    const float halfScreenY = GetScreenHeight() / 2.0f;
    
    return {GetScreenWidth() / 100.0f, halfScreenY - barHeight / 2.0f, barWidth, barHeight};
}

Rectangle InitBar2()
{
    const float barHeight = static_cast<float>(GetScreenHeight()) / 7.0f;
    const float barWidth = static_cast<float>(GetScreenHeight()) / 50.0f;
    const float halfScreenY = GetScreenHeight() / 2.0f;
    
    return {GetScreenWidth() - barWidth - GetScreenWidth() / 100.0f, halfScreenY - barHeight / 2.0f, barWidth, barHeight};
}