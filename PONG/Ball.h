#pragma once
#include <raylib.h>

void DrawBall(Rectangle ball);
void MoveBall(Rectangle& ball, float ballSpeedX, float ballSpeedY);
Rectangle InitBall();
