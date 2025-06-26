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

// void loadLogo() {
//     logo beg;
//     while () {
//         BeginDrawing();
//         ClearBackground(RAYWHITE);
//         beg.display();
//         EndDrawing();
//     }
// }

int main()
{
    logo::readData();
    InitWindow(screenWidth, screenHeight, title.c_str());
    SetTargetFPS(FrameRate);
    // loadLogo();
    TurnState i = PLAYER_TURN;
    character a{10, {100, 100}, LoadTexture("resources/1.jpeg")};
    character b{10, {500, 100}, LoadTexture("resources/1.jpeg")};
    Card a1[2], b1[2];
    for (int i = 0; i < 2; i++) {
        a1[i].inputNoRec(LoadTexture("resources/card1.png"), 0.0f);
        b1[i].inputNoRec(LoadTexture("resources/card1.png"), 0.0f);
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
