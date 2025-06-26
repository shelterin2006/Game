#include "logo.h"
#include "character.h"
#include "turn.h"
#include "gameplayScreen.h"
#include "title.h"
#include "credits.h"
int screenWidth = 1280;
int screenHeight = 720;
string title = "Default Title";
int FrameRate = 60;
GameScreen currentScreen = TITLE;

int main()
{
    logo::readData();
    InitWindow(screenWidth, screenHeight, title.c_str());
    SetTargetFPS(FrameRate);
    // loadLogo();
    TurnState i = PLAYER_TURN;
    Image test = LoadImage("resources/IDLE.png");
    Image attack = LoadImage("resources/ATTACK_1.png");
    character a(10, {100, 100}, test, attack);
    character b(10, {500, 100}, test, attack);
    Card a1[2], b1[2];
    for (int i = 0; i < 2; i++) {
        Vector2 p = {50 + static_cast<float>(i) * 50.0f, 500};
        Vector2 p2 = {900 + static_cast<float>(i) * 50.0f, 500};
        a1[i].inputNoRec(LoadTexture("resources/card.png"), 0.0f, p);
        b1[i].inputNoRec(LoadTexture("resources/card.png"), 0.0f, p2);
    }
    ScreenGamePlay ga(a, b, a1, 2, b1, 2);
    bool c = false, d = false;
    Title manhinhchinh;
    Credits cr;
    while (!WindowShouldClose())
    {
        //Update
        switch (currentScreen) {
            case LOGO:
                break; // load game
            case CREDITS:
                cr.behavior(); break;
            case TITLE:
                manhinhchinh.behavior(); break;
            case MAP:
                break;
            case GAMEPLAY:
                ga.behavior(); break;
            default: // ENDING
                int s = 1;
        }
        //Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);
            switch (currentScreen) {
                case LOGO:
                    break; // load game
                case CREDITS:
                    cr.display(); break;
                case TITLE:
                    manhinhchinh.display(); break;
                case MAP:
                    break;
                case GAMEPLAY:
                    ga.display();
                    break;
                default: // ENDING
                    int s = 1;
            }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
