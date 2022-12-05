#include "RunGame.h"

static float timerGrowBar;
static float timerDwarfBall;
float screenWidth;
float screenHeight;
void RunGame(MenuOptions& menuOptions, bool p2Active)
{
    const float initialBallSpeed = 300.0f;
    const float barSpeed = 700.0f;
    screenWidth = static_cast<float>(GetScreenWidth());
    screenHeight = static_cast<float>(GetScreenHeight());

    float auxSpeed = initialBallSpeed;
    float ballSpeedX;
    float ballSpeedY;

    int score[2] = {0, 0};

    static Rectangle growBar;
    static Rectangle dwarfBall;
    Rectangle bar1;
    Rectangle bar2;
    Rectangle ball = InitBall();

    ResetBars(bar1, bar2);
    HidePowerUps(growBar, dwarfBall);
    SpawnBall(ball, ballSpeedX, ballSpeedY, auxSpeed, initialBallSpeed);

    timerGrowBar = 8.0f;
    timerDwarfBall = 10.0f;

    while (menuOptions == play)
    {
        timerGrowBar -= GetFrameTime();
        timerDwarfBall -= GetFrameTime();

        if (timerGrowBar < 0)
        {
            ResetGrowBar(growBar);
            bar1.height = static_cast<float>(screenHeight) / 7.0f;
            bar2.height = static_cast<float>(screenHeight) / 7.0f;
            timerGrowBar = 8.0f;
        }
        if (timerDwarfBall < 0)
        {
            ResetDwarfBall(dwarfBall);
            ball.width = (static_cast<float>(screenHeight) / 7.0f) / 10.0f;
            timerDwarfBall = 8.0f;
        }
        CheckBallCollision(ball, bar1, bar2, ballSpeedX, ballSpeedY, auxSpeed, score, initialBallSpeed);

        MoveBall(ball, ballSpeedX, ballSpeedY);

        if (!p2Active) BotIA(bar2, ball, barSpeed);

        PlayerActions(bar1, bar2, barSpeed, p2Active);

        CheckWin(score, ballSpeedX, ballSpeedY, menuOptions);

        DrawGame(ball, bar1, bar2, growBar, dwarfBall, score);
        PowerUp(ball, bar1, bar2, growBar, dwarfBall, ballSpeedX);
        if (IsKeyReleased(KEY_X)) menuOptions = menu;
        if (WindowShouldClose()) CloseWindow();
    }
    menuOptions = MenuOptions::menu;
}

void DrawGame(Rectangle ball, Rectangle bar1, Rectangle bar2, Rectangle growBar, Rectangle dwarfBall, int score[])
{
    const float screenHeight2 = screenHeight / 30.0f;
    const int widthAux = static_cast<int>(screenWidth) / 15;
    const float halfScreen = screenWidth / 2.0f;

    BeginDrawing();

    for (int i = 0; i < screenHeight; i += static_cast<int>(screenHeight2) * 2)
    {
        DrawRectangle(static_cast<int>(halfScreen + bar1.width * 0.5f), i, static_cast<int>(bar1.width / 1.3f), static_cast<int>(screenHeight2), WHITE);
    }

    for (int i = 0; i < 2; ++i)
    {
        DrawText(TextFormat("%i", score[i]), static_cast<int>(halfScreen - widthAux + widthAux * 2.0f * i), static_cast<int>(screenHeight) / 40,
                 widthAux,WHITE);
    }

    ClearBackground(BLACK);
    DrawBall(ball);
    DrawPad(bar1, bar2);
    DrawPowerUp(growBar, dwarfBall);
    EndDrawing();
}

void BotIA(Rectangle& bar, Rectangle ball, float barSpeed)
{
    if (ball.y <= bar.y + bar.height * 0.3f && bar.y > 0)
        bar.y -= (barSpeed * GetFrameTime()) * 0.58f;
    if (ball.y >= bar.y + bar.height * 0.7f && bar.y < screenHeight - bar.height)
        bar.y += (barSpeed * GetFrameTime()) * 0.58f;
}

void PlayerActions(Rectangle& bar1, Rectangle& bar2, float barSpeed, bool p2Active)
{
    if (p2Active)
    {
        if (IsKeyDown(KEY_UP) && bar2.y > 0)
            bar2.y -= barSpeed * GetFrameTime();
        if (IsKeyDown(KEY_DOWN) && bar2.y < screenHeight - bar2.height)
            bar2.y += barSpeed * GetFrameTime();
    }

    if (IsKeyDown('W') && bar1.y > 0)
        bar1.y -= barSpeed * GetFrameTime();
    if (IsKeyDown('S') && bar1.y < screenHeight - bar1.height)
        bar1.y += barSpeed * GetFrameTime();
}


void CheckBallCollision(Rectangle& ball, Rectangle bar1, Rectangle bar2, float& ballSpeedX, float& ballSpeedY,
                        float& auxSpeed, int score[], float initialBallSpeed)
{
    if (CheckBarCollision(ball, bar1, bar2))
    {
        ball.x = ball.x < screenWidth / 2.0f
                     ? bar1.x + ball.width + bar1.width
                     : screenWidth - (bar1.x + ball.width + bar1.width + 1); //REPOSICIONA BALL AFUERA DE LA BARRA

        if (abs(ballSpeedX) == initialBallSpeed)
            ballSpeedX += ballSpeedX < 0 ? -initialBallSpeed / 3 : initialBallSpeed / 3;
        else
            ballSpeedX += ballSpeedX > 0 ? initialBallSpeed / 3 : -initialBallSpeed / 3;
        ballSpeedX *= -1.0f;
        BallDirection(ball, bar1, bar2, ballSpeedY, auxSpeed, initialBallSpeed);
    }

    ballSpeedY *= CheckYBorderCollision(ball) ? -1.0f : 1.0f;

    if (CheckXBorderCollision(ball))
    {
        score[ball.x > screenWidth / 2 ? 0 : 1]++;
        SpawnBall(ball, ballSpeedX, ballSpeedY, auxSpeed, initialBallSpeed);
    }
}

void BallDirection(Rectangle ball, Rectangle bar1, Rectangle bar2, float& ballSpeedY, float& auxSpeed,
                   float initialBallSpeed)
{
    if (ball.x < screenWidth / 2.0f)
        SetBallVelocity(ball, bar1, ballSpeedY, auxSpeed, initialBallSpeed);
    else
        SetBallVelocity(ball, bar2, ballSpeedY, auxSpeed, initialBallSpeed);
}

void SetBallVelocity(Rectangle ball, Rectangle bar, float& ballSpeedY, float& auxSpeed, float initialSpeed)
{
    if (ball.y <= bar.y + bar.height * 0.4f)
        ballSpeedY = -abs(auxSpeed + initialSpeed / 2.2f);
    else if (ball.y <= bar.y + bar.height * 0.6f)
    {
        auxSpeed = ballSpeedY < auxSpeed ? auxSpeed : ballSpeedY;
        ballSpeedY = 0.2f * ballSpeedY + ballSpeedY / 5;
    }
    else if (ball.y >= bar.y + bar.height * 0.6f)
        ballSpeedY = abs(auxSpeed + initialSpeed / 2.2f);
}

//COLLISION SOURCE http://www.jeffreythompson.org/
static bool CheckRecRecCollision(Rectangle rec1, Rectangle rec2)
{
    if (rec1.x + rec1.width >= rec2.x && // r1 right edge past r2 left
        rec1.x <= rec2.x + rec2.width && // r1 left edge past r2 right
        rec1.y + rec1.height >= rec2.y && // r1 top edge past r2 bottom
        rec1.y <= rec2.y + rec2.height) // r1 bottom edge past r2 top
        return true;

    return false;
}

bool CheckXBorderCollision(Rectangle ball)
{
    return ball.x <= 0 || ball.x >= screenWidth;
}

bool CheckYBorderCollision(Rectangle ball)
{
    return ball.y - ball.height / 2 <= 0 || ball.y + ball.height / 2 >= screenHeight;
}

bool CheckBarCollision(Rectangle ball, Rectangle bar1, Rectangle bar2)
{
    return CheckRecRecCollision(bar1, ball) || CheckRecRecCollision(bar2, ball);
}

///RANDOMIZA LA DIRECCION PRINCIPAL DE LA PELOTA  
void SpawnBall(Rectangle& ball, float& ballSpeedX, float& ballSpeedY, float& auxSpeed, float initialBallSpeed)
{
    ballSpeedX = initialBallSpeed * (rand() % 2 == 0 ? -1.0f : 1.0f);
    ballSpeedY = initialBallSpeed * (rand() % 2 == 0 ? -1.0f : 1.0f) * 1.35F;
    auxSpeed = initialBallSpeed;
    ball.x = screenWidth / 2.0f;
    ball.y = screenHeight / 2.0f;
}

void CheckWin(int score[], float& ballSpeedX, float& ballSpeedY, MenuOptions& menuOptions)
{
    const Color NEONCYAN = CLITERAL(Color){4, 217, 255, 255};
    string pressEsc = "Presione ESC para volver al menu.";
    if (score[0] == 7)
    {
        ballSpeedY = 0;
        ballSpeedX = 0;
        string pla2Win = "Gano Player 2!";

        DrawText(pla2Win.c_str(), static_cast<int>(screenWidth) / 2 - MeasureText(pla2Win.c_str(), static_cast<int>(screenHeight) / 10) / 2,
                 static_cast<int>(screenHeight) / 2, static_cast<int>(screenHeight) / 10, NEONCYAN);
        DrawText(pressEsc.c_str(), static_cast<int>(screenWidth) / 2 - MeasureText(pressEsc.c_str(), static_cast<int>(screenHeight) / 23) / 2,
                 static_cast<int>(screenHeight / 1.7f), static_cast<int>(screenHeight) / 23, NEONCYAN);
        menuOptions = MenuOptions::menu;
    }
    else if (score[1] == 7)
    {
        ballSpeedY = 0;
        ballSpeedX = 0;
        string pla1Win = "Gano Player 1!";
        DrawText(pla1Win.c_str(), static_cast<int>(screenWidth / 2 - MeasureText(pla1Win.c_str(), static_cast<int>(screenHeight) / 10) / 2),
                 static_cast<int>(screenHeight) / 2, static_cast<int>(screenHeight) / 10, NEONCYAN);
        DrawText(pressEsc.c_str(), static_cast<int>(screenWidth) / 2 - MeasureText(pressEsc.c_str(), static_cast<int>(screenHeight) / 23) / 2,
                 static_cast<int>(screenHeight / 1.7f), static_cast<int>(screenHeight) / 23, NEONCYAN);

        menuOptions = MenuOptions::menu;
    }
}

void PowerUp(Rectangle& ball, Rectangle& bar1, Rectangle& bar2, Rectangle& growBar, Rectangle& dwarfBall,
             float ballSpeedX)
{
    if (CheckRecRecCollision(growBar, ball))
    {
        if (ballSpeedX < 0)
        {
            bar2.height *= 1.6f;
            growBar.x *= 500;
        }
        else
        {
            bar1.height *= 1.6f;
            growBar.x *= 500;
        }
        timerGrowBar = 7.0f;
    }

    if (CheckRecRecCollision(dwarfBall, ball))
    {
        ball.width *= 0.5f;
        dwarfBall.x *= 500;
        timerDwarfBall = 6.f;
    }
}

void DrawPowerUp(Rectangle growBar, Rectangle dwarfBall)
{
    DrawRectangleRec(growBar, DARKGRAY);
    DrawRectangleRec(dwarfBall, RED);
}

void ResetBars(Rectangle& bar1, Rectangle& bar2)
{
    bar1 = InitBar1();
    bar2 = InitBar2();
}

void HidePowerUps(Rectangle& growBar, Rectangle& dwarfBall)
{
    growBar.x = 3000;
    dwarfBall.x = 3000;
}

void ResetGrowBar(Rectangle& growBar)
{
    float rand1 = rand() % static_cast<int>(screenWidth) / 3.0f + screenWidth / 4.0f;
    float rand2 = rand() % static_cast<int>(screenHeight) / 3.0f + screenHeight / 4.0f;
    growBar = {rand1, rand2, screenWidth / 10.0f, screenHeight / 8.0f};
}

void ResetDwarfBall(Rectangle& dwarfBall)
{
    float rand3 = rand() % static_cast<int>(screenWidth) / 3.0f + screenWidth / 4.0f;
    float rand4 = rand() % static_cast<int>(screenHeight) / 3.0f + screenHeight / 4.0f;
    dwarfBall = {rand3, rand4, screenWidth / 13.0f, screenHeight / 8.0f};
}
