#include "menu.h"

#include "RunGame.h"

static float screenWidth;
static float screenHeight;
void Menu()
{
    int width = 1280.0f;
    int height = 960.0f;
    bool p2Active = true;
    char Title[] = "Pong";

    MenuOptions menuOptions = menu;

    InitWindow(width, height, Title);

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
            OptionsMenu(menuOptions, width, height, p2Active);
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
    int fontSize = static_cast<int>(screenHeight) / 9;
    float xPosition = screenWidth / 25;
    float yPosition = fontSize;
    float xRepos = xPosition - xPosition / 5;
    float yRepos = yPosition / 20;
    return {fontSize, xPosition, yPosition, xRepos, yRepos};
}

void MainMenu(MenuOptions& menuOptions)
{
    Rectangle menuRectangles[6];

    MenuUI menuUI = InitMenuUI();

    for (int i = exitGame; i != menu; --i)
    {
        menuRectangles[i] = {
            menuUI.xRepos,
            screenHeight - menuUI.yPosition * (exitGame - static_cast<float>(i) + 1.45f
            + menuUI.yRepos,
            menuUI.fontSize * 3.9f,
            static_cast<float>(menuUI.fontSize))
        };
    }

    Vector2 mousePos = GetMousePosition();

    DrawMainMenu(menuUI, menuRectangles);

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(mousePos, menuRectangles[play]))
            menuOptions = play;

        else if (CheckCollisionPointRec(mousePos, menuRectangles[options]))
            menuOptions = options;

        else if (CheckCollisionPointRec(mousePos, menuRectangles[rules]))
            menuOptions = rules;

        else if (CheckCollisionPointRec(mousePos, menuRectangles[credits]))
            menuOptions = credits;

        else if (CheckCollisionPointRec(mousePos, menuRectangles[exitGame]))
            menuOptions = exitGame;
    }
}

void DrawMainMenu(MenuUI menuUI, Rectangle menuRectangles[])
{
    const Color NEONCYAN = CLITERAL(Color){4, 217, 255, 255};

    BeginDrawing();

    for (int i = exitGame; i != menu; --i)
    {
        DrawRectangleRec(menuRectangles[i],
                         CheckCollisionPointRec(GetMousePosition(), menuRectangles[i]) ? DARKGRAY : BLACK);
    }

    DrawText("Pong", screenWidth / 2 - screenHeight / 6, screenHeight / 25, screenHeight / 7,
             WHITE);

    string options[] = {"menu", "Play", "Options", "Rules", "Credits", "Exit"};

    for (int i = exitGame; i != menu; --i)
    {
        DrawText(options[i].c_str(), menuUI.xPosition, screenHeight - menuUI.yPosition * (6.4f - i),
                 menuUI.fontSize, NEONCYAN);
    }

    ClearBackground(BLACK);

    EndDrawing();
}

void OptionsMenu(MenuOptions& menuOptions, int& screenWidth, int& screenHeight, bool& p2Active)
{
    const Rectangle backBackRec = {
        screenWidth / 16.0f, screenHeight / 1.8f, screenHeight / 15.0f * 2.5f, screenHeight / 15.0f
    };
    const Rectangle screenSizeA = {
        screenWidth / 16.0f, screenHeight / 3.6f, screenHeight / 15 * 3.5f, screenHeight / 17.0f
    };
    const Rectangle screenSizeB = {
        screenWidth / 16.0f * 4.15f, screenHeight / 3.6f, screenHeight / 15 * 4.3f,
        screenHeight / 17.0f
    };
    const Rectangle onePlayer = {
        screenWidth / 16.0f, screenHeight / 2.2f, screenHeight / 15 * 3.7f, screenHeight / 17.0f
    };
    const Rectangle twoPlayers = {
        screenWidth / 16.0f * 4.5f, screenHeight / 2.2f, screenHeight / 15 * 4.8f,
        screenHeight / 17.0f
    };

    DrawOptions(backBackRec, screenSizeA, screenSizeB, onePlayer, twoPlayers);

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        if (CheckCollisionPointRec(GetMousePosition(), backBackRec))
            menuOptions = menu;
        else if (CheckCollisionPointRec(GetMousePosition(), screenSizeA))
        {
            screenWidth = 1280.0f;
            screenHeight = 960.0f;
            SetWindowSize(screenWidth, screenHeight);
        }
        else if (CheckCollisionPointRec(GetMousePosition(), screenSizeB))
        {
            screenWidth = 1920.0f;
            screenHeight = 1080.0f;
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
    const int xPos = screenWidth / 15;
    const int fontSize = screenHeight / 30;

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

    DrawText(optionsTitle.c_str(), xPos, screenHeight / 9, fontSize * 2.3, WHITE);
    DrawText(optionsChangeSize.c_str(), xPos, screenHeight / 5, fontSize * 1.5f, WHITE);
    DrawText(optionsSizeA.c_str(), xPos, screenHeight / 3.5f, fontSize * 1.5f, NEONCYAN);
    DrawText(optionsSizeB.c_str(), xPos * 4, screenHeight / 3.5f, fontSize * 1.5f, NEONCYAN);
    DrawText(p2Active.c_str(), xPos, screenHeight / 2.6f, fontSize * 2.0f, WHITE);
    DrawText(onePlayerStr.c_str(), xPos, screenHeight / 2.2f, fontSize * 1.5f, NEONCYAN);
    DrawText(twoPlayersStr.c_str(), xPos * 4.4f, screenHeight / 2.2f, fontSize * 1.5f, NEONCYAN);
    DrawText(rulesBack.c_str(), xPos, screenHeight / 1.8, fontSize * 2, WHITE);

    ClearBackground(BLACK);

    EndDrawing();
}

void RulesMenu(MenuOptions& menuOptions)
{
    const Rectangle backRulesRec = {
        screenWidth / 16.f, screenHeight / 1.5f, screenHeight / 15.0f * 2.5f, screenHeight / 15.0f
    };

    DrawRules(backRulesRec);

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(GetMousePosition(), backRulesRec)) menuOptions = menu;
    }
}

void DrawRules(Rectangle backRulesRec)
{
    const Color NEONCYAN = CLITERAL(Color){4, 217, 255, 255};

    const int xPos = screenWidth / 15;
    const int fontSize = screenHeight / 30;

    BeginDrawing();

    const string rulesTitle = "REGLAS";
    const string rules1P = "Un Jugador:\n-movimiento: WS. Volver al menu: ESC";
    const string rules2P = "Dos Jugadores:\n-movimiento: WS y flecha hacia arriba y abajo\n\nPoderes:";
    const string rulesPowerUpA =
        "\n-Dwarf Ball: Hace que la pelota se reduzca a la mitad. Se resetea cada 10 segundos.";
    const string rulesPowerUpB = "-Grow Bar: Hace que la paleta crezca. Se resetea cada 8 segundos.";
    const string rulesBack = "Back";

    DrawRectangleRec(backRulesRec, CheckCollisionPointRec(GetMousePosition(), backRulesRec) ? DARKGRAY : BLACK);

    DrawText(rulesTitle.c_str(), xPos, screenHeight / 9, fontSize * 2, WHITE);
    DrawText(rules1P.c_str(), xPos, screenHeight / 5, fontSize, NEONCYAN);
    DrawText(rules2P.c_str(), xPos, screenHeight / 3, fontSize, NEONCYAN);
    DrawText(rulesPowerUpA.c_str(), xPos, screenHeight / 2, fontSize * 0.9f, GRAY);
    DrawText(rulesPowerUpB.c_str(), xPos, screenHeight / 1.7, fontSize, RED);
    DrawText(rulesBack.c_str(), xPos, screenHeight / 1.5, fontSize * 2, WHITE);

    ClearBackground(BLACK);

    EndDrawing();
}

void CreditsMenu(MenuOptions& menuOptions)
{
    const Rectangle backCreditsRec = {
        screenWidth / 16.0f, screenHeight / 2.0f, screenHeight / 15.0f * 2.5f, screenHeight / 15.0f
    };

    DrawCredits(backCreditsRec);

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        if (CheckCollisionPointRec(GetMousePosition(), backCreditsRec))
            menuOptions = menu;
}

void DrawCredits(Rectangle backCreditsRec)
{
    const Color NEONCYAN = CLITERAL(Color){4, 217, 255, 255};
    const int xPos = screenWidth / 15;
    const int fontSize = screenHeight / 30;

    BeginDrawing();

    const string creditsTitle = "MADE BY";
    const string creditsCredit = "SantiagoBarra";
    const string creditsColor = "Main Color:";
    const string creditsColorCode = " Neon Cyan {4, 217, 255}";
    const string rulesBack = "Back";

    DrawRectangleRec(backCreditsRec, CheckCollisionPointRec(GetMousePosition(), backCreditsRec) ? DARKGRAY : BLACK);

    DrawText(creditsTitle.c_str(), xPos, screenHeight / 9, fontSize * 2, WHITE);
    DrawText(creditsCredit.c_str(), xPos, screenHeight / 5, fontSize * 4, NEONCYAN);
    DrawText(creditsColor.c_str(), xPos, screenHeight / 2.7f, fontSize * 1.5f, WHITE);
    DrawText(creditsColorCode.c_str(), xPos * 4, screenHeight / 2.7f, fontSize * 1.5f, NEONCYAN);
    DrawText(rulesBack.c_str(), xPos, screenHeight / 2, fontSize * 2, WHITE);
    ClearBackground(BLACK);

    EndDrawing();
}
