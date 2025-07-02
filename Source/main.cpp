#include "logo.h"
#include "character.h"
#include "turn.h"
#include "gameplayScreen.h"
#include "title.h"
#include "credits.h"
#include "pickCard.h"
int screenWidth = 1280;
int screenHeight = 720;
string title = "Default Title";
int FrameRate = 60;
GameScreen currentScreen = GAMEPLAY;

int main()
{
    logo::readData();
    InitWindow(screenWidth, screenHeight, title.c_str());
    SetTargetFPS(FrameRate);
    TurnState i = PLAYER_TURN;
    Image test = LoadImage("resources/IDLE.png");
    Image attack = LoadImage("resources/ATTACK_1.png");
    character a(10, {100, 100}, test, attack);
    character b(10, {500, 100}, test, attack);
    // Load texture một lần duy nhất
    Texture2D cardTexture = LoadTexture("resources/card.png");

    Card a1[2], b1[2];
    for (int i = 0; i < 2; i++) {
        Vector2 p = {50 + static_cast<float>(i) * 50.0f, 500};
        Vector2 p2 = {900 + static_cast<float>(i) * 50.0f, 500};
        Vector2 l1 = {100, 100}, l2 = {1100, 100};
        float ss = 0.02f, sl = 0.03f;
        a1[i].input(cardTexture, p, l1, ss, sl);
        b1[i].input(cardTexture, p2, l2, ss, sl);
    }
    pick pi(a1, 2, b1, 2);
    ScreenGamePlay ga(a, b, a1, 2, b1, 2);
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
            case PICKCATD:
                pi.behavior(); break;
            case GAMEPLAY:
                ga.behavior();
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
                case CREDITS:
                    cr.display(); break;
                case TITLE:
                    manhinhchinh.display(); break;
                case MAP:
                    break;
                case PICKCATD:
                    pi.display(); break;
                case GAMEPLAY:
                    ga.display();
                    break;
                default: // ENDING
                    int s = 1;
            }
        EndDrawing();
    }

    // Unload textures trước khi đóng window
    UnloadTexture(cardTexture);
    UnloadImage(test);
    UnloadImage(attack);

    CloseWindow();
    return 0;
}
