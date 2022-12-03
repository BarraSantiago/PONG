#pragma once
#include <raylib.h>
#include <algorithm>
#include <iostream>



enum MenuOptions
{
	menu,
	play,
	options,
	rules,
	credits,
	exitGame
};

struct MenuUI
{
	int fontSize;
	float xPosition;
	float yPosition;
	float xRepos;
	float yRepos;
};

void Menu();
void MainMenu(MenuOptions& menuOptions);
void DrawMainMenu(MenuUI menuUI, Rectangle menuRectangles[]);
void OptionsMenu(MenuOptions& menuOptios, int& screenWidth, int& screenHeight, bool& p2Active);
void DrawOptions(Rectangle backBackRec, Rectangle screenSizeA, Rectangle screenSizeB, Rectangle onePlayer, Rectangle twoPlayers);
void RulesMenu(MenuOptions& menuOptions);
void DrawRules(Rectangle backRulesRec);
void CreditsMenu(MenuOptions& menuOptions);
void DrawCredits(Rectangle backCreditsRec);
MenuUI InitMenuUI();