#pragma once
#include <iostream>
#include <raylib.h>
#include <string>
#include "Ball.h"
#include "menu.h"
#include "Pad.h"

using namespace std;

void RunGame(MenuOptions& menuOptionsbool, bool p2Active);
void DrawGame(Rectangle ball, Rectangle bar1, Rectangle bar2, Rectangle growBar, Rectangle dwarfBall, int score[]);
void BotIA(Rectangle& bar, Rectangle ball, float barSpeed);
void PlayerActions(Rectangle& bar1, Rectangle& bar2, float barSpeed, bool p2Active);
void SpawnBall(Rectangle& ball, float& ballSpeedX, float& ballSpeedY, float& auxSpeed, float initialBallSpeed);
void CheckBallCollision(Rectangle& ball, Rectangle bar1, Rectangle bar2, float& ballSpeedX, float& ballSpeedY, float& auxSpeed, int score[], float initialBallSpeed);
bool CheckXBorderCollision(Rectangle ball);
bool CheckBarCollision(Rectangle ball, Rectangle bar1, Rectangle bar2);
bool CheckYBorderCollision(Rectangle ball);
void BallDirection(Rectangle ball, Rectangle bar1, Rectangle bar2, float& ballSpeedY, float& auxSpeed, float initialBallSpeed);
void SetBallVelocity(Rectangle ball, Rectangle bar, float& ballSpeedY, float& auxSpeed, float initialBallSpeed);
void CheckWin(int score[], float& ballSpeedX, float& ballSpeedY, MenuOptions& menuOptions);
void DrawPowerUp(Rectangle growBar, Rectangle dwarfBall);
void PowerUp(Rectangle& ball, Rectangle& bar1, Rectangle& bar2, Rectangle& growBar, Rectangle& dwarfBall, float ballSpeedX);
void ResetBars(Rectangle& bar1,Rectangle& bar2);
void ResetGrowBar( Rectangle& growBar);
void ResetDwarfBall(Rectangle& dwarfBall);
void HidePowerUps(Rectangle& growBar,Rectangle& dwarfBall);