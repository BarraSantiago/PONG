#include "Ball.h"

void DrawBall(Rectangle ball)
{
    DrawCircle(ball.x, ball.y, ball.width, WHITE);
}

void MoveBall(Rectangle& ball, float ballSpeedX, float ballSpeedY)
{
    ball.y += ballSpeedY * GetFrameTime();
    ball.x += ballSpeedX * GetFrameTime();
    
}

Rectangle InitBall()
{
    const float barHeight = static_cast<float>(GetScreenHeight()) / 7.0f;
    const float ballSize = barHeight / 10.0f;
    const float halfScreenY = GetScreenHeight() / 2.0f;
    return {GetScreenWidth() / 2.0f, halfScreenY, ballSize, ballSize};
}