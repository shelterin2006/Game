#include "readData.h"
#include "character.h"
#include  "raymath.h"
#include "turn.h"
#include "gamescreen.h"
int screenWidth = 1280;
int screenHeight = 720;
string title = "Default Title";
int FrameRate = 60;

int main()
{
    readData();
    InitWindow(screenWidth, screenHeight, title.c_str());
    SetTargetFPS(FrameRate);
    TurnState i = PLAYER_TURN;
    GameScreen currentScreen = GAMEPLAY;
    character a{10, {100, 100}, LoadTexture("resources/1.jpeg")};
    character b{10, {500, 100}, LoadTexture("resources/1.jpeg")};
    Card a1[2], b1[2];
    for (int i = 0; i < 2; i++) {
        a1[i].inputNoRec(LoadTexture("resources/card1.png"), 0.0f);
        b1[i].inputNoRec(LoadTexture("resources/card1.png"), 0.0f);
    }
    ScreenGamePlay ga(a, b, a1, 2, b1, 2);
    bool c = false, d = false;
    while (!WindowShouldClose())
    {
        //Update
        switch (currentScreen) {
            case LOGO:
                break; // load game
            case TITLE:
                screenTitle(); break;
            case MAP:
                break;
            case GAMEPLAY:
                if (ga.checkRec()) c = true; else c = false;
                if (ga.isPressed()) d = true; else d = false;
                break;
            default: // ENDING
                int s = 1;
        }
        //Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);
            switch (currentScreen) {
                case LOGO:
                    break; // load game
                case TITLE:
                    screenTitle(); break;
                case MAP:
                    break;
                case GAMEPLAY:
                    ga.display();
                    if (c) DrawText("1", 20, 20, 29, RED);
                    if (d) DrawText("13", 50, 50, 32, BLACK);
                    break;
                default: // ENDING
                    int s = 1;
            }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
