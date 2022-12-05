#include "menu.h"

#include "RunGame.h"


void Menu()
{
    int screenWidth = 1280;
    int screenHeight = 960;
    bool p2Active = true;
    char Title[] = "Pong";

    MenuOptions menuOptions = menu;

    InitWindow(screenWidth, screenHeight, Title);

    while (!WindowShouldClose() && menuOptions != exitGame)
    {
        switch (menuOptions)
        {
        case menu:
            MainMenu(menuOptions);
            break;
        case play:
            RunGame(menuOptions, p2Active);
            break;
        case options:
            OptionsMenu(menuOptions, screenWidth, screenHeight, p2Active);
            break;
        case rules:
            RulesMenu(menuOptions);
            break;
        case credits:
            CreditsMenu(menuOptions);
            break;
        case exitGame:
            break;
        default:
            break;
        }
    }
    CloseWindow();
}

MenuUI InitMenuUI()
{
    int fontSize = GetScreenHeight() / 9;
    float xPosition = static_cast<float>(GetScreenWidth()) / 25;
    float yPosition = static_cast<float>(fontSize);
    float xRepos = xPosition - xPosition / 5;
    float yRepos = yPosition / 20;
    return {fontSize, xPosition, yPosition, xRepos, yRepos};
}

void MainMenu(MenuOptions& menuOptions)
{
    Rectangle menuRectangles[6];

    MenuUI menuUI = InitMenuUI();

    for (int i = static_cast<int>(exitGame); i != static_cast<int>(menu); --i)
    {
        menuRectangles[i] = {
            menuUI.xRepos,
            GetScreenHeight() - menuUI.yPosition * (static_cast<int>(exitGame) - static_cast<float>(i) + 1.45f)
            + menuUI.yRepos,
            menuUI.fontSize * 3.9f, static_cast<float>(menuUI.fontSize)
        };
    }

    Vector2 mousePos = GetMousePosition();

    DrawMainMenu(menuUI, menuRectangles);

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(mousePos, menuRectangles[static_cast<int>(play)]))
            menuOptions = play;

        else if (CheckCollisionPointRec(mousePos, menuRectangles[static_cast<int>(options)]))
            menuOptions = options;

        else if (CheckCollisionPointRec(mousePos, menuRectangles[static_cast<int>(rules)]))
            menuOptions = rules;

        else if (CheckCollisionPointRec(mousePos, menuRectangles[static_cast<int>(credits)]))
            menuOptions = credits;

        else if (CheckCollisionPointRec(mousePos, menuRectangles[static_cast<int>(exitGame)]))
            menuOptions = exitGame;
    }
}

void DrawMainMenu(MenuUI menuUI, Rectangle menuRectangles[])
{
    const Color NEONCYAN = CLITERAL(Color){4, 217, 255, 255};

    BeginDrawing();

    for (int i = static_cast<int>(exitGame); i != static_cast<int>(menu); --i)
    {
        DrawRectangleRec(menuRectangles[i],
                         CheckCollisionPointRec(GetMousePosition(), menuRectangles[i]) ? DARKGRAY : BLACK);
    }

    DrawText("Pong", GetScreenWidth() / 2 - GetScreenHeight() / 6, GetScreenHeight() / 25, GetScreenHeight() / 7,
             WHITE);

    string options[] = {"menu", "Play", "Options", "Rules", "Credits", "exit"};

    for (int i = static_cast<int>(exitGame); i != static_cast<int>(menu); --i)
    {
        DrawText(options[i].c_str(), static_cast<int>(menuUI.xPosition),
                 GetScreenHeight() - static_cast<int>(menuUI.yPosition * (6.4f - i)),
                 menuUI.fontSize, NEONCYAN);
    }

    ClearBackground(BLACK);

    EndDrawing();
}

void OptionsMenu(MenuOptions& menuOptions, int& screenWidth, int& screenHeight, bool& p2Active)
{
    const Rectangle backBackRec = {
        GetScreenWidth() / 16.0f, GetScreenHeight() / 1.8f, GetScreenHeight() / 15.0f * 2.5f, GetScreenHeight() / 15.0f
    };
    const Rectangle screenSizeA = {
        GetScreenWidth() / 16.0f, GetScreenHeight() / 3.6f, GetScreenHeight() / 15 * 3.5f, GetScreenHeight() / 17.0f
    };
    const Rectangle screenSizeB = {
        GetScreenWidth() / 16.0f * 4.15f, GetScreenHeight() / 3.6f, GetScreenHeight() / 15 * 4.3f,
        GetScreenHeight() / 17.0f
    };
    const Rectangle onePlayer = {
        GetScreenWidth() / 16.0f, GetScreenHeight() / 2.2f, GetScreenHeight() / 15 * 3.7f, GetScreenHeight() / 17.0f
    };
    const Rectangle twoPlayers = {
        GetScreenWidth() / 16.0f * 4.5f, GetScreenHeight() / 2.2f, GetScreenHeight() / 15 * 4.8f,
        GetScreenHeight() / 17.0f
    };

    DrawOptions(backBackRec, screenSizeA, screenSizeB, onePlayer, twoPlayers);

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        if (CheckCollisionPointRec(GetMousePosition(), backBackRec))
            menuOptions = menu;
        else if (CheckCollisionPointRec(GetMousePosition(), screenSizeA))
        {
            screenWidth = 1280;
            screenHeight = 960;
            SetWindowSize(screenWidth, screenHeight);
        }
        else if (CheckCollisionPointRec(GetMousePosition(), screenSizeB))
        {
            screenWidth = 1920;
            screenHeight = 1080;
            SetWindowSize(screenWidth, screenHeight);
        }
        else if (CheckCollisionPointRec(GetMousePosition(), onePlayer))
            p2Active = false;
        else if (CheckCollisionPointRec(GetMousePosition(), twoPlayers))
            p2Active = true;
}

void DrawOptions(Rectangle backBackRec, Rectangle screenSizeA, Rectangle screenSizeB, Rectangle onePlayer,
                 Rectangle twoPlayers)
{
    const Color NEONCYAN = CLITERAL(Color){4, 217, 255, 255};
    const int xPos = GetScreenWidth() / 15;
    const int fontSize = GetScreenHeight() / 30;

    BeginDrawing();

    const string optionsTitle = "OPTIONS";
    const string optionsChangeSize = "Cambiar resolucion de pantalla";
    const string optionsSizeA = "1280x920";
    const string optionsSizeB = "Fullscreen";
    const string p2Active = "Cantidad de Jugadores";
    const string onePlayerStr = "1 jugador";
    const string twoPlayersStr = "2 jugadores";
    const string rulesBack = "Back";

    DrawRectangleRec(backBackRec, CheckCollisionPointRec(GetMousePosition(), backBackRec) ? DARKGRAY : BLACK);
    DrawRectangleRec(screenSizeA, CheckCollisionPointRec(GetMousePosition(), screenSizeA) ? DARKGRAY : BLACK);
    DrawRectangleRec(screenSizeB, CheckCollisionPointRec(GetMousePosition(), screenSizeB) ? DARKGRAY : BLACK);
    DrawRectangleRec(onePlayer, CheckCollisionPointRec(GetMousePosition(), onePlayer) ? DARKGRAY : BLACK);
    DrawRectangleRec(twoPlayers, CheckCollisionPointRec(GetMousePosition(), twoPlayers) ? DARKGRAY : BLACK);

    DrawText(optionsTitle.c_str(), xPos, GetScreenHeight() / 9, static_cast<int>(fontSize * 2.3f), WHITE);
    DrawText(optionsChangeSize.c_str(), xPos, GetScreenHeight() / 5, static_cast<int>(fontSize * 1.5f), WHITE);
    DrawText(optionsSizeA.c_str(), xPos, static_cast<int>(GetScreenHeight() / 3.5f), static_cast<int>(fontSize * 1.5f),
             NEONCYAN);
    DrawText(optionsSizeB.c_str(), xPos * 4,     static_cast<int>(GetScreenHeight() / 3.5f), static_cast<int>(fontSize * 1.5f), NEONCYAN);
    DrawText(p2Active.c_str(), xPos,             static_cast<int>(GetScreenHeight() / 2.6f), static_cast<int>(fontSize * 2.0f), WHITE);
    DrawText(onePlayerStr.c_str(), xPos,         static_cast<int>(GetScreenHeight() / 2.2f), static_cast<int>(fontSize * 1.5f), NEONCYAN);
    DrawText(twoPlayersStr.c_str(), static_cast<int>(xPos * 4.4f), static_cast<int>(GetScreenHeight() / 2.2f), static_cast<int>(fontSize * 1.5f), NEONCYAN);
    DrawText(rulesBack.c_str(), xPos, static_cast<int>(GetScreenHeight() / 1.8f), fontSize * 2, WHITE);

    ClearBackground(BLACK);

    EndDrawing();
}

void RulesMenu(MenuOptions& menuOptions)
{
    const Rectangle backRulesRec = {
        GetScreenWidth() / 16.0f, GetScreenHeight() / 1.5f, GetScreenHeight() / 15.0f * 2.5f, GetScreenHeight() / 15.0f
    };

    DrawRules(backRulesRec);

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        if (CheckCollisionPointRec(GetMousePosition(), backRulesRec))
            menuOptions = menu;
}

void DrawRules(Rectangle backRulesRec)
{
    const Color NEONCYAN = CLITERAL(Color){4, 217, 255, 255};

    const int xPos = GetScreenWidth() / 15;
    const int fontSize = GetScreenHeight() / 30;

    BeginDrawing();

    const string rulesTitle = "REGLAS";
    const string rules1P = "Un Jugador:\n-movimiento: WS. Volver al menu: X";
    const string rules2P = "Dos Jugadores:\n-movimiento: WS y flecha hacia arriba y abajo";
    const string rulesPowerUpA = "Poderes:\n-Dwarf Ball: Hace que la pelota se reduzca a la mitad. Dura 6 segundos.";
    const string rulesPowerUpB = "-Grow Bar: Hace que la paleta crezca. Dura 7 segundos.";
    const string rulesBack = "Back";

    DrawRectangleRec(backRulesRec, CheckCollisionPointRec(GetMousePosition(), backRulesRec) ? DARKGRAY : BLACK);

    DrawText(rulesTitle.c_str(), xPos, GetScreenHeight() / 9, fontSize * 2, WHITE);
    DrawText(rules1P.c_str(), xPos, GetScreenHeight() / 5, fontSize, NEONCYAN);
    DrawText(rules2P.c_str(), xPos, GetScreenHeight() / 3, fontSize, NEONCYAN);
    DrawText(rulesPowerUpA.c_str(), xPos, GetScreenHeight() / 2, static_cast<int>(fontSize * 0.9f), NEONCYAN);
    DrawText(rulesPowerUpB.c_str(), xPos, static_cast<int>(GetScreenHeight() / 1.7f), fontSize, NEONCYAN);
    DrawText(rulesBack.c_str(), xPos,     static_cast<int>(GetScreenHeight() / 1.5f), fontSize * 2, WHITE);

    ClearBackground(BLACK);

    EndDrawing();
}

void CreditsMenu(MenuOptions& menuOptions)
{
    float screenHeight = static_cast<float>(GetScreenHeight()); 
    const Rectangle backCreditsRec = {
        GetScreenWidth() / 16.0f, screenHeight / 2.0f, screenHeight / 15.0f * 2.5f, screenHeight / 15.0f
    };

    DrawCredits(backCreditsRec);

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        if (CheckCollisionPointRec(GetMousePosition(), backCreditsRec))
            menuOptions = menu;
}

void DrawCredits(Rectangle backCreditsRec)
{
    const Color NEONCYAN = CLITERAL(Color){4, 217, 255, 255};
    const int xPos = GetScreenWidth() / 15;
    const int fontSize = GetScreenHeight() / 30;

    BeginDrawing();

    const string creditsTitle = "MADE BY";
    const string creditsCredit = "SantiagoBarra";
    const string creditsColor = "Main Color:";
    const string creditsColorCode = " Neon Cyan {4, 217, 255}";
    const string rulesBack = "Back";

    DrawRectangleRec(backCreditsRec, CheckCollisionPointRec(GetMousePosition(), backCreditsRec) ? DARKGRAY : BLACK);

    DrawText(creditsTitle.c_str(), xPos, GetScreenHeight() / 9, fontSize * 2, WHITE);
    DrawText(creditsCredit.c_str(), xPos, GetScreenHeight() / 5, fontSize * 4, NEONCYAN);
    DrawText(creditsColor.c_str(), xPos,         static_cast<int>(GetScreenHeight() / 2.7f), static_cast<int>(fontSize * 1.5f), WHITE);
    DrawText(creditsColorCode.c_str(), xPos * 4, static_cast<int>(GetScreenHeight() / 2.7f), static_cast<int>(fontSize * 1.5f), NEONCYAN);
    DrawText(rulesBack.c_str(), xPos, GetScreenHeight() / 2, fontSize * 2, WHITE);
    ClearBackground(BLACK);

    EndDrawing();
}
